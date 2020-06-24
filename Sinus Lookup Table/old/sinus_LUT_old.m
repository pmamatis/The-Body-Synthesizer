%% Parameter Settings
blocksize = 9600;
funcstr = 'sin(2*pi/9600*x)'; % Define the sine function and insert blocksize


xmin = 0; % Set the minimum input of interest
xmax = blocksize; % Set the maximum input of interest
xdt = ufix(32); % Set the x data type
%xscale = 2^-16; % Set the x data scaling
xscale = 1;
ydt = sfix(32); % Set the y data type
yscale = 2^-14; % Set the y data scaling
rndmeth = 'Floor'; % Set the rounding method
errmax = 2^-10; % Set the maximum allowed error
nptsmax = 2*blocksize; % Specify the maximum number of points

%% Create Lookup Table
[xdata, ydata, errworst] = fixpt_look1_func_approx(funcstr,xmin,xmax,xdt,xscale,ydt,yscale,rndmeth,[],nptsmax,'even');
fixpt_look1_func_plot(xdata,ydata,funcstr,xmin,xmax,xdt,xscale,ydt,yscale,rndmeth);

%% Export Lookup Table
ydata = ydata(1:9600)';
%cd "E:\GIT\Body-Synthesizer_STM32_F746ZG_Matlab"
csvwrite('LookUpTableSIN.txt', ydata)


