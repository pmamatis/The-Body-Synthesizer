clear 

a  = 2^(1/12);
f0 = 440;

%n = -141;   % C-7
%n= -93;
%n = -81;
%n = -69;   % C-1 
n = -57;   % C0

oct = 8;
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
%write sin LUT as one whole array

%% C-file
dlmwrite('sinLUT.c','const float LUT = {','delimiter','', 'precision', 10)   
for i = 1 : length(Y)
     dlmwrite('sinLUT.c',Y{i},'delimiter',',', 'precision', 10,'-append');         
end
dlmwrite('sinLUT.c','};','delimiter','', 'precision', 10,'-append');  

%write frequency array
dlmwrite('sinLUT.c','const float LUT_frequency = {','delimiter','', 'precision', 10,'-append')   
dlmwrite('sinLUT.c',FandBS(:,1)','delimiter',',', 'precision', 10,'-append');  
dlmwrite('sinLUT.c','};','delimiter','', 'precision', 10,'-append');  

%write Blocksize array
dlmwrite('sinLUT.c','const uint32_t LUT_SUPPORTPOINTS = {','delimiter','', 'precision', 10,'-append')   
dlmwrite('sinLUT.c',FandBS(:,2)','delimiter',',', 'precision', 10,'-append');  
dlmwrite('sinLUT.c','};','delimiter','', 'precision', 10,'-append');  

%write start index array
dlmwrite('sinLUT.c','const uint32_t LUT_STARTINDEX = {','delimiter','', 'precision', 10,'-append')   
dlmwrite('sinLUT.c',FandBS(:,3)','delimiter',',', 'precision', 10,'-append');  
dlmwrite('sinLUT.c','};','delimiter','', 'precision', 10,'-append');  

%write Blocksize array
dlmwrite('sinLUT.c','const uint32_t LUT_ENDINDEX = {','delimiter','', 'precision', 10,'-append')   
dlmwrite('sinLUT.c',FandBS(:,4)','delimiter',',', 'precision', 10,'-append');  
dlmwrite('sinLUT.c','};','delimiter','', 'precision', 10,'-append');  


%% H-file
length_Y = 0;
for i =1 : length(Y)
    length_Y = length_Y + length(Y{i});
end



dlmwrite('sinLUT.h',['const uint32_t LUT_ENDINDEX[', num2str(length(fn)),'];'],'delimiter','', 'precision', 10) ;
dlmwrite('sinLUT.h',['const float  LUT[',num2str(length_Y),'];'],'delimiter','', 'precision', 10,'-append');
dlmwrite('sinLUT.h',['const uint32_t LUT_STARTINDEX[',num2str(length(fn)),'];'],'delimiter','', 'precision', 10,'-append');  
dlmwrite('sinLUT.h',['const uint32_t LUT_SUPPORTPOINTS[',num2str(length(fn)),'];'],'delimiter','', 'precision', 10,'-append'); 

dlmwrite('sinLUT.h','float LUT_GetSin(uint32_t index);','delimiter','', 'precision', 10,'-append'); 

%%
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