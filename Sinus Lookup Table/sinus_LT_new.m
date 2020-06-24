% %%Parameter Settings
% blocksize = 9600;
% funcstr = 'sin(2*pi/9600*x)'; % Define the sine function
% xmin = 0; % Set the minimum input of interest
% xmax = 9600; % Set the maximum input of interest
% xdt = ufix(32); % Set the x data type
% xscale = 2^-16; % Set the x data scaling
% ydt = sfix(16); % Set the y data type
% yscale = 2^-14; % Set the y data scaling
% rndmeth = 'Floor'; % Set the rounding method
% errmax = 2^-10; % Set the maximum allowed error
% nptsmax = 9600; % Specify the maximum number of points
% [xdata, ydata, errworst] = fixpt_look1_func_approx(funcstr,xmin,xmax,xdt,xscale,ydt,yscale,rndmeth,errmax,[]);
% fixpt_look1_func_plot(xdata,ydata,funcstr,xmin,xmax,xdt,xscale,ydt,yscale,rndmeth);
clear;

funcstr = 'sin(2*pi/9600*x)'; % Define the sine function
xmin = 0; % Set the minimum input of interest
xmax = 9600; % Set the maximum input of interest
xdt = ufix(32); % Set the x data type
xscale = 1; % Set the x data scaling
ydt = sfix(32); % Set the y data type
yscale = ; % Set the y data scaling
rndmeth = 'Floor'; % Set the rounding method
%errmax = 2^-10; % Set the maximum allowed error
nptsmax = 9600; % Specify the maximum number of points
spacing = 'even';
[xdata, ydata, errworst] = fixpt_look1_func_approx(funcstr, ...
xmin,xmax,xdt,xscale,ydt,yscale,rndmeth,[],nptsmax,spacing);
fixpt_look1_func_plot(xdata,ydata,funcstr,xmin,xmax,xdt, ...
xscale,ydt,yscale,rndmeth);
