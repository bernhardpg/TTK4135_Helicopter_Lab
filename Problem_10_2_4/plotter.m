clear all; close all; clc;

problem_10_2_4;

load('data.mat');

figure
plot(t,x3)
hold on;
plot(simout(1,:),simout(3,:) / 180 * pi)
title('Optimal trajectory without feedback - Pitch $p$')
ylabel('Pitch angle [rad]');
xlabel('Time [s]');
legend({'Pitch reference $p_c$', 'Pitch measured $p$'});
saveas(gcf, 'problem_10_2_4_plot_pitch','eps');
savefig('problem_10_2_4_plot_pitch');

figure
plot(t,x1)
hold on;
plot(simout(1,:),simout(2,:) / 180 * pi)
title('Optimal trajectory without feedback - Travel $\lambda$')
ylabel('Travel angle [rad]');
xlabel('Time [s]');
legend({'Travel reference $\lambda_c$', 'Travel measured $\lambda$'});
saveas(gcf, 'problem_10_2_4_plot_travel','eps');
savefig('problem_10_2_4_plot_travel');
