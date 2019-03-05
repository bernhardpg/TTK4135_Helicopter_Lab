clear all; close all; clc;

problem_10_3;

load('data.mat');

figure
plot(t,x3)
hold on;
plot(simout(1,:),simout(3,:) / 180 * pi)
title('Optimal trajectory with feedback - Pitch $p$')
ylabel('Pitch angle [rad]');
xlabel('Time [s]');
legend({'Pitch reference $p_c$', 'Pitch measured $p$'});
saveas(gcf, 'problem_10_3_plot_pitch','eps');
savefig('problem_10_3_plot_pitch');

figure
plot(t,x1)
hold on;
plot(simout(1,:),simout(2,:) / 180 * pi)
title('Optimal trajectory with feedback - Travel $\lambda$')
ylabel('Travel angle [rad]');
xlabel('Time [s]');
legend({'Travel reference $\lambda_c$', 'Travel measured $\lambda$'});
saveas(gcf, 'problem_10_3_plot_travel','eps');
savefig('problem_10_3_plot_travel');
