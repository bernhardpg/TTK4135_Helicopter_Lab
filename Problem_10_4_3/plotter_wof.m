clear all; close all; clc;

problem_10_4_3;

load('data_wof.mat');

figure
plot(t,x3)
hold on;
plot(simout(1,:),simout(4,:))
title('Optimal trajectory without feedback - Pitch $p$')
ylabel('Pitch angle [rad]');
xlabel('Time [s]');
legend({'Pitch reference $p_c$', 'Pitch measured $p$'});
saveas(gcf, 'problem_10_4_plot_pitch','epsc');
savefig('problem_10_4_plot_pitch');

figure
plot(t,x1)
hold on;
plot(simout(1,:),simout(2,:))
title('Optimal trajectory without feedback - Travel $\lambda$')
ylabel('Travel angle [rad]');
xlabel('Time [s]');
legend({'Travel reference $\lambda_c$', 'Travel measured $\lambda$'});
saveas(gcf, 'problem_10_4_plot_travel','epsc');
savefig('problem_10_4_plot_travel');

e_constraint = nonlincon_lambda(simout(2,:));

figure
plot(t,x5)
hold on;
plot(simout(1,:),[simout(6,:)' e_constraint]);
title('Optimal trajectory without feedback - Elevation $e$')
ylabel('Elevation angle [rad]');
xlabel('Time [s]');
ylim([-0.5 0.25])
legend({'Elevation reference $e_c$', 'Elevation measured $e$', 'Lower elevation constraint'});
saveas(gcf, 'problem_10_4_plot_elevation','epsc');
savefig('problem_10_4_plot_elevation');