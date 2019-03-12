function [e_constraint] = nonlincon_lambda(lambda)
    global N;

    alpha = 0.2;
    beta = 20;
    lambda_t = 2*pi/3;
    e_constraint = zeros(length(lambda), 1);
    for k = 1:length(lambda)
        e_constraint(k) = alpha*exp(-beta*(lambda(k)-lambda_t)^2);
    end
end