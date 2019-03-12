%% Initialization and model definition
clear all; close all; clc;

addpath('../');
addpath('../help_functions');
init;

q_values = [0.1 1 10];

for iteration = 1:length(q_values)
    q = q_values(iteration);
    problem_10_2_3;
    
    %% Plotting
    t = 0:delta_t:delta_t*(length(u)-1);
    figure(iteration)
    subplot(5,1,1)
    stairs(t,u),grid
    ylabel('$u = p_c$')
    subplot(5,1,2)
    plot(t,x1,'m',t,x1,'mo'),grid
    ylabel('$\lambda$')
    subplot(5,1,3)
    plot(t,x2,'m',t,x2','mo'),grid
    ylabel('$r$')
    subplot(5,1,4)
    plot(t,x3,'m',t,x3,'mo'),grid
    ylabel('$p$')
    subplot(5,1,5)
    plot(t,x4,'m',t,x4','mo'),grid
    xlabel('Time [s]'),ylabel('$\dot{p}$')
    suptitle(['Optimal trajectory with weight q = ', num2str(q)])
    saveas(gcf, ['problem_10_2_3_plot_', num2str(iteration)], 'eps');
    savefig(['problem_10_2_3_plot_', num2str(iteration)]);
    
    close all;
    
end


