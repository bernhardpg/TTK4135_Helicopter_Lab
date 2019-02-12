run ('../Problem_10_2_4/problem_10_2_4.m');
%% LQ state-feedback
q_1 = 100; % Travel
q_2 = 10; % Travel rate
q_3 = 10; % Pitch
q_4 = 10; % Pitch rate

r_1 = 1 ; % Pitch setpoint (input)

Q_lq = diag([q_1 q_2 q_3 q_4]);
R_lq = r_1;

[K_lq,S_lq,e_lq] = dlqr(A1,B1,Q_lq,R_lq);
