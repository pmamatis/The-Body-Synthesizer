clear 

a  = 2^(1/12);
f0 = 440;

n = -141;   % C-7

%n = -69;   % C-1 
%n = -57;   % C0

oct = 15;
keys = 12;

nend = n + oct*keys;

for i = n:nend

    fn(i+abs(n)+1,1) = f0 * a^i;
    
end


% Calculation
SR = 96000;
dt = 1/SR;

Y = cell(length(fn),1);


start_ind = zeros(length(fn),1);
end_ind   = zeros(length(fn),1);

start_ind(1,1) = 0;
end_ind  (1,1) = round(SR / fn(1))-1;

for i = 1 : length(fn)
    
    BS(i,1) = round(SR / fn(i));
    
    t = 0:dt:BS(i)*dt-dt;
    
    Y{i} = sin(2*pi*fn(i)*t);
    %y = sin(2*pi*freq(i)*t);

    if i > 1
    
        start_ind(i,1) = start_ind(i-1,1) + BS(i-1,1);
        end_ind  (i,1) = start_ind(i  ,1) + BS(i,  1) - 1;
    
    end
    
    
%     if i == 1
%         
%         plot(t,Y{i});
%         
%     end
    
    % Write single txt files each frequency    
    % csvwrite(strcat('SIN_',num2str(notes(i)),'Hz.txt'), y);
end


FandBS = [fn, BS, start_ind, end_ind];

%csvwrite(strcat('sines.txt'), Y);
csvwrite(strcat('test.txt'), fn, BS);
%csvwrite(strcat('F.txt'), freq);


% Fs = 8000;                   % samples per second
%    dt = 1/Fs;                   % seconds per sample
%    StopTime = 0.25;             % seconds
%    t = (0:dt:StopTime-dt)';     % seconds
%    %%Sine wave:
%    Fc = 60;                     % hertz
%    x = cos(2*pi*Fc*t);
%    % Plot the signal versus time:
%    figure;
%    plot(t,x);
%    xlabel('time (in seconds)');
%    title('Signal versus Time');
%    zoom xon;