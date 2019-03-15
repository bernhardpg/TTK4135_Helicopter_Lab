init;

%% Run script

delta_t = 0.25;
N = 60;
problem_10_4_3;

%% Plot
subplot(2,1,1);
plot(travel, elevation); hold on;
title("Elevation constraint with $\Delta t = 0.25$ and $N = 60$");

alpha = 0.2;
beta = 20;
lambda_t = 2*pi/3;
plot(travel, alpha*exp(-beta*(travel - lambda_t).^2)); hold on;
plot(0:0.0001:pi, alpha*exp(-beta*([0:0.0001:pi] - lambda_t).^2));
ylabel("Elevation $e$");
xlabel("Travel $\lambda$");

%% Run script

delta_t = 0.25/2;
N = 60*2;
problem_10_4_3;

%% Plot
subplot(2,1,2);
plot(travel, elevation); hold on;
title("Elevation constraint with $\Delta t = 0.125$ and $N = 120$");

alpha = 0.2;
beta = 20;
lambda_t = 2*pi/3;
plot(travel, alpha*exp(-beta*(travel - lambda_t).^2)); hold on;
plot(0:0.0001:pi, alpha*exp(-beta*((0:0.0001:pi) - lambda_t).^2));
ylabel("Elevation $e$");
xlabel("Travel $\lambda$");

legend({"Calculated optimal trajectory for elevation", "Elevation constraint used for optimization", ...
    "Actual elevation constraint"}, 'Location', 'southwest');

sgtitle("Elevation constraint - Varying the step size");

saveas(gcf, 'eps/problem_10_4_step_size','epsc');
savefig('fig/problem_10_4_step_size');