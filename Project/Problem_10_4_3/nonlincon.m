function [c,ceq] = nonlincon(x)
alpha = 0.2;
beta = 20;
lambda_t = 2*pi/3;
c=alpha*exp(-beta*(x(1)-lambda_t)^2)-x(5);
ceq=[];