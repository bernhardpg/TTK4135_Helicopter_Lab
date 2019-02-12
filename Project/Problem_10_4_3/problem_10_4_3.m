clear all;
init;

%% System
% Discrete time system model. x = [lambda r p p_dot e e_dot]'
delta_t	= 0.25; % sampling time
A_d = [0 1 0 0 0 0;
      0 0 -K_2 0 0 0;
      0 0 0 1 0 0;
      0 0 -K_1*K_pp -K_1*K_pd 0 0;
      0 0 0 0 0 1;
      0 0 0 0 -K_3*K_ep -K_3*K_ed] * delta_t + eye(6); % A_d = (TA + I)
  
B_d = [0 0;
    0 0;
    0 0;
    K_1*K_pp 0;
    0 0;
    0 K_3*K_ep] * delta_t; % B_d = TB;

% Eulers forward method: x[k+1] = A_d*x[k] + B_d*u_k

%% Initial values
x1_0 = pi;                              % Lambda
x2_0 = 0;                               % r
x3_0 = 0;                               % p
x4_0 = 0;                               % p_dot
x5_0 = 0;                               % e evt -25
x6_0 = 0;                               % e_dot
x0 = [x1_0 x2_0 x3_0 x4_0 x5_0 x6_0]';  % Initial values

N = 40; % 40 steps of 0.25s = 10s
M = N;
mx = size(A_d,2); % Number of states (number of columns in A)
mu = size(B_d,2); % Number of inputs(number of columns in B)

%% Bounds
ul 	    = -30*pi/180;                   % Lower bound on control
uu 	    = -ul;                          % Upper bound on control

xl      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);               % Upper bound on states (no bound)
xl(3)   = ul;                           % Lower bound on state x3
xu(3)   = uu;                           % Upper bound on state x3

%% Constraints
% Generate constraints on measurements and inputs
% function [vlb,vub] = gen_constraints(N,M,xl,xu,ul,uu)
[vlb,vub]       = gen_constraints(N,M,xl,xu,ul,uu); % hint: gen_constraints
vlb(N*mx+M*mu)  = 0;                    % We want the last input to be zero
vub(N*mx+M*mu)  = 0;                    % We want the last input to be zero



alpha = 0.2;
beta = 20;
lambda_t = 2*pi/3;

% Inequality constraint
% e_k = alpha*exp(-beta(lambda-lambda_t)^2);
% A = [ ] ;   B = [ ] ;

% Equality constraints
Aeq = gen_aeq(A_d,B_d,N,mx,mu);            % Generate A, hint: gen_aeq
beq = zeros(size(Aeq,1),1);             % Generate b
beq(1:mx) = A_d * x0;

%% Generate

% Initialize z
z = zeros(N*mx + M*mu,1);
z0 = z;                                 %z0(1)=pi?;


Q1 = zeros(mx,mx);
Q1(1,1) = 2;                            % Weight on state x1
Q1(2,2) = 0;                            % Weight on state x2
Q1(3,3) = 0;                            % Weight on state x3
Q1(4,4) = 0;                            % Weight on state x4
Q1(5,5) = 0;
Q1(6,6) = 0;

q_1 = 1;
q_2 = 1;
P1 = 2*diag([q_1 q_2]);                                % Weight on input

% function Q = gen_q(Q1,P1,N,M)
Q = gen_q(Q1,P1,N,M);                                  % Generate Q, hint: gen_q

nonlcon = @nonlincon;

fun = @(z) 0.5*z'*Q*z;


% fmincon to optimize
options = optimoptions('fmincon','Display','iter','Algorithm','sqp', 'MaxFunEvals',40000);
tic
z = fmincon(fun, z0, [],[],Aeq, beq, vlb, vub, nonlcon, options);
toc
%% LQ state-feedback
q_1 = 10; % Travel
q_2 = 10; % Travel rate
q_3 = 10; % Pitch
q_4 = 10; % Pitch rate
q_5 = 10; % Elevation
q_6 = 10; % Elevation rate

r_1 = 1; % Pitch setpoint (input)
r_2 = 1;
Q_lq = diag([q_1 q_2 q_3 q_4 q_5 q_6]);
R_lq = diag([r_1 r_2]);

[K_lq,S_lq,e_lq] = dlqr(A_d,B_d,Q_lq,R_lq);

%% Extract control inputs and states
u1 = [z(N*mx+1:2:N*mx+M*mu);z(N*mx+M*mu-1)]; % Control input from solution
u2 = [z(N*mx+2:2:N*mx+M*mu);z(M*mx+M*mu)]; %2*10e7

x1 = [x0(1);z(1:mx:N*mx)];              % State x1 from solution
x2 = [x0(2);z(2:mx:N*mx)];              % State x2 from solution
x3 = [x0(3);z(3:mx:N*mx)];              % State x3 from solution
x4 = [x0(4);z(4:mx:N*mx)];              % State x4 from solution
x5 = [x0(5);z(5:mx:N*mx)];
x6 = [x0(6);z(6:mx:N*mx)];

num_variables = 5/delta_t;
zero_padding = zeros(num_variables,1);
unit_padding  = ones(num_variables,1);

u1   = [zero_padding; u1; zero_padding];
u2  = [zero_padding; u2; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];
x5  = [zero_padding; x5; zero_padding];
x6  = [zero_padding; x6; zero_padding];

t = 0:delta_t:delta_t*(length(x1)-1);

u_star = [t' u1 u2];
x_star = [t' x1 x2 x3 x4 x5 x6];
