%% Initialization and model definition
clear all; close all; clc;

addpath('../');
addpath('../help_functions');
init;

q_values =[0.1 1 10];

figure()
for iteration = 1:length(q_values)
    q = q_values(iteration);
    problem_10_2_3;
    
    %% Plotting
    t = 0:delta_t:delta_t*(length(u)-1);
    subplot(3,1,iteration)
    plot(t,u,t,x3),grid
    legend({'Pitch reference $u = p_c$', 'Estimated pitch $p$'});
    xlabel('Time [s]'),ylabel('Pitch angle [rad]');
    title(['Optimal trajectory with weight q = ', num2str(q)])

    
end
saveas(gcf, ['problem_10_2_3_plot_'], 'epsc');
savefig(['problem_10_2_3_plot_']);
    
