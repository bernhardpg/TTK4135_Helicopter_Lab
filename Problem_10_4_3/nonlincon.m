function [c,ceq] = nonlincon(x)
    % Inequality constraint
    global N;
    
    alpha = 0.2;
    beta = 20;
    lambda_t = 2*pi/3;
    c = zeros(N,1);
    for k = 1:N
        c(k) = alpha*exp(-beta*(x((k-1)*6 + 1) ...
        -lambda_t)^2)-x((k-1)*6 + 5);
    end
    ceq = [];
end