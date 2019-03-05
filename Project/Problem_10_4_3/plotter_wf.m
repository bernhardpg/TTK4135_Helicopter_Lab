clear all; close all; clc;

problem_10_4_3;

load('data_wf.mat');

figure
plot(t,u1)
hold on;
plot(simout(1,:),simout(4,:))
title('Optimal trajectory without feedback - Pitch $p$')
ylabel('Pitch angle [rad]');
xlabel('Time [s]');
legend({'Pitch reference $p_c$', 'Pitch measured $p$'});
saveas(gcf, 'problem_10_4_wf_plot_pitch','eps');
savefig('problem_10_4_wf_plot_pitch');

figure
plot(t,x1)
hold on;
plot(simout(1,:),simout(2,:))
title('Optimal trajectory without feedback - Travel $\lambda$')
ylabel('Travel angle [rad]');
xlabel('Time [s]');
legend({'Travel reference $\lambda_c$', 'Travel measured $\lambda$'});
saveas(gcf, 'problem_10_4_wf_plot_travel','eps');
savefig('problem_10_4_wf_plot_travel');

e_constraint = nonlincon_lambda(simout(2,:));

figure
plot(t,x5)
hold on;
plot(simout(1,:),[simout(6,:)' e_constraint]);
title('Optimal trajectory without feedback - Elevation $e$')
ylabel('Elevation angle [rad]');
xlabel('Time [s]');
legend({'Elevation reference $e_c$', 'Elevation measured $e$','Constraint'});
saveas(gcf, 'problem_10_4_wf_plot_elevation','eps');
savefig('problem_10_4_wf_plot_elevation');