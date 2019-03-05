%% Problem 2.4
%% Initialization and model definition
clear all; close all; clc;

addpath('../');
addpath('../help_functions');
addpath('../Problem_10_2_3');
init;

q = 1;
problem_10_2_3;

%% Create u input matrix

t = 0:delta_t:delta_t*(length(u)-1);

u_star = [t' u];
x_star = [t' x1 x2 x3 x4];

%run('helicopter.slx')