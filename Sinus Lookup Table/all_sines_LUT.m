clear 
%% global parameters 
a  = 2^(1/12);
f0 = 65.40639;
SR = 48000; %sample rate
dt = 1/SR;

%% normal LUT

%semitones steps related to f0

%n = -24;
%n = -12;   % C-1 
%n = 0;   % C0
%n= 12; % C1

oct_LUT = 6;
keys = 12;

n=[0:12:oct_LUT*keys];

%LUT_start_octave = log(fn/f0)/log(a);
% LUT scale parameter


%calculations


%freqquency
for i = n(1):n(end)

    fn(i+1,1) = f0 * a^i;
    
end

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
end
  LUT_Array = [];
length_Y = 0;
for i =1 : length(Y)
    length_Y = length_Y + length(Y{i});
    LUT_Array = [LUT_Array,Y{i}];  %result vector for LUT
end

FandBS = [fn, BS, start_ind, end_ind];



%% LFO calculation
%parameter
%LFO_ind=[1,13,20,25,32,37,41,44,46,49,61,73,80,85]'; %ausgewählte frequenzen
%n= -129; % C-6

%variables init
LFO_Array = [];
%calculation
nend = n + oct_LFO*keys;
for i = 0:3

   % fn(i+abs(n)+1,1) = f0 * a^i;
    fn_LFO(i+1,1) = 2^(i);
end

Y = cell(length(fn_LFO),1);
start_ind_LFO = zeros(length(fn_LFO),1);
end_ind_LFO   = zeros(length(fn_LFO),1);
BS_LFO =  zeros(length(fn_LFO),1);

%index an der stelle 1
start_ind_LFO(1,1) = 0;
end_ind_LFO  (1,1) = round(SR / fn_LFO(1))-1;


for i = 1 : length(fn_LFO)
    
    BS_LFO(i,1) = round(SR / fn_LFO(i));
    
    t = 0:dt:BS_LFO(i)*dt-dt;
    
    Y{i} = sin(2*pi*fn_LFO(i)*t);
    %y = sin(2*pi*freq(i)*t);

    if i > 1
    
        start_ind_LFO(i,1) = start_ind_LFO(i-1,1) + BS_LFO(i-1,1);
        end_ind_LFO  (i,1) = start_ind_LFO(i  ,1) + BS_LFO(i,  1) - 1;
    
    end
    
    %plot
%     figure(1)
%     plot(t,Y{i});
%     hold on;
    

end

for i =1 : length(Y)
    length_Y = length_Y + length(Y{i});
    LFO_Array = [LFO_Array,Y{i}]; %result vector for LFO
end
FandBS_LFO = [fn_LFO, BS_LFO, start_ind_LFO, end_ind_LFO];

%% C-File generator parameters
precision = 5; %precision of Nachkommastelle
precision_LFO = 2; %precision of Nachkommastelle



%% C-file
dlmwrite('sinLUT.c','#include "sinLUT.h"','delimiter','', 'precision', precision);   
dlmwrite('sinLUT.c','const float LUT[] = {','delimiter','', 'precision', precision,'-append'); 

%LUT

%LUT Array
dlmwrite('sinLUT.c',LUT_Array,'delimiter',',', 'precision', precision,'-append');

% for i = 1 : length(Y)
%      dlmwrite('sinLUT.c',Y{i},'delimiter',',', 'precision', precision,'-append');
%      if i < length(Y)
%          dlmwrite('sinLUT.c',',','delimiter',',', 'precision', precision,'-append'); 
%      end
%      
% end
dlmwrite('sinLUT.c','};','delimiter','', 'precision', precision,'-append');  



%write frequency array
dlmwrite('sinLUT.c','const float LUT_frequency[] = {','delimiter','', 'precision', precision,'-append')   
dlmwrite('sinLUT.c',FandBS(:,1)','delimiter',',', 'precision', precision,'-append');  
dlmwrite('sinLUT.c','};','delimiter','', 'precision', precision,'-append');  

%write Blocksize array
dlmwrite('sinLUT.c','const uint32_t LUT_SUPPORTPOINTS[] = {','delimiter','', 'precision', precision,'-append')   
dlmwrite('sinLUT.c',FandBS(:,2)','delimiter',',', 'precision', precision,'-append');  
dlmwrite('sinLUT.c','};','delimiter','', 'precision', precision,'-append');  

%write start index array
dlmwrite('sinLUT.c','const uint32_t LUT_STARTINDEX[] = {','delimiter','', 'precision', precision,'-append')   
dlmwrite('sinLUT.c',FandBS(:,3)','delimiter',',', 'precision', precision,'-append');  
dlmwrite('sinLUT.c','};','delimiter','', 'precision', precision,'-append');  

%write Blocksize array
dlmwrite('sinLUT.c','const uint32_t LUT_ENDINDEX[] = {','delimiter','', 'precision', precision,'-append')   
dlmwrite('sinLUT.c',FandBS(:,4)','delimiter',',', 'precision', precision,'-append');  
dlmwrite('sinLUT.c','};','delimiter','', 'precision', precision,'-append');  

%LFO

%LFO Array
dlmwrite('sinLUT.c','const float LFO[] = {','delimiter','', 'precision', precision,'-append');   
dlmwrite('sinLUT.c',LFO_Array,'delimiter',',', 'precision', precision_LFO,'-append');
dlmwrite('sinLUT.c','};','delimiter','', 'precision', precision,'-append');  

%write frequency array
dlmwrite('sinLUT.c','const float LFO_frequency[] = {','delimiter','', 'precision', precision,'-append')   
dlmwrite('sinLUT.c',FandBS_LFO(:,1)','delimiter',',', 'precision', precision,'-append');  
dlmwrite('sinLUT.c','};','delimiter','', 'precision', precision,'-append');  

%write Blocksize array
dlmwrite('sinLUT.c','const uint32_t LFO_SUPPORTPOINTS[] = {','delimiter','', 'precision', precision,'-append')   
dlmwrite('sinLUT.c',FandBS_LFO(:,2)','delimiter',',', 'precision', precision,'-append');  
dlmwrite('sinLUT.c','};','delimiter','', 'precision', precision,'-append');  

%write start index array
dlmwrite('sinLUT.c','const uint32_t LFO_STARTINDEX[] = {','delimiter','', 'precision', precision,'-append')   
dlmwrite('sinLUT.c',FandBS_LFO(:,3)','delimiter',',', 'precision', precision,'-append');  
dlmwrite('sinLUT.c','};','delimiter','', 'precision', precision,'-append');  

%write Blocksize array
dlmwrite('sinLUT.c','const uint32_t LFO_ENDINDEX[] = {','delimiter','', 'precision', precision,'-append')   
dlmwrite('sinLUT.c',FandBS_LFO(:,4)','delimiter',',', 'precision', precision,'-append');  
dlmwrite('sinLUT.c','};','delimiter','', 'precision', precision,'-append');  
%% H-file



%include Guard
dlmwrite('sinLUT.h','#ifndef INC_SINLUT_H_','delimiter','', 'precision', precision);
dlmwrite('sinLUT.h','#define INC_SINLUT_H_','delimiter','', 'precision', precision,'-append') 
dlmwrite('sinLUT.h','//includes ','delimiter','', 'precision', precision,'-append');
dlmwrite('sinLUT.h','#include "main.h"','delimiter','', 'precision', precision,'-append') ;

%Space
dlmwrite('sinLUT.h',' ','delimiter','', 'precision', precision,'-append');
dlmwrite('sinLUT.h',' ','delimiter','', 'precision', precision,'-append');

%defines
dlmwrite('sinLUT.h','//defines ','delimiter','', 'precision', precision,'-append');

dlmwrite('sinLUT.h',['#define LUT_SR ',num2str(SR)],'delimiter','', 'precision', precision,'-append');
%LUT defines
dlmwrite('sinLUT.h',['#define LUT_START_OCTAVE ',num2str(FandBS(length(FandBS),1))],'delimiter','', 'precision', precision,'-append');

dlmwrite('sinLUT.h',['#define LUT_FMAX ',num2str(FandBS(length(FandBS),1))],'delimiter','', 'precision', precision,'-append');
dlmwrite('sinLUT.h',['#define LUT_FMIN ',num2str(FandBS(1,1))],'delimiter','', 'precision', precision,'-append');
dlmwrite('sinLUT.h',['#define LUT_OCTAVES ',num2str(oct_LUT)],'delimiter','', 'precision', precision,'-append');
%LFO defines
dlmwrite('sinLUT.h','//defines ','delimiter','', 'precision', precision,'-append');
dlmwrite('sinLUT.h',['#define LFO_FMAX ',num2str(FandBS_LFO(length(FandBS_LFO),1))],'delimiter','', 'precision', precision,'-append');
dlmwrite('sinLUT.h',['#define LFO_FMIN ',num2str(FandBS_LFO(1,1))],'delimiter','', 'precision', precision,'-append');
dlmwrite('sinLUT.h',['#define LFO_OCTAVES ',num2str(oct_LFO)],'delimiter','', 'precision', precision,'-append');


%Space
dlmwrite('sinLUT.h',' ','delimiter','', 'precision', precision,'-append');
dlmwrite('sinLUT.h',' ','delimiter','', 'precision', precision,'-append');

%variables

dlmwrite('sinLUT.h','//variables','delimiter','', 'precision', precision,'-append');
%LUT
dlmwrite('sinLUT.h',['const float  LUT[',num2str(length(LUT_Array)),'];'],'delimiter','', 'precision', precision,'-append');
dlmwrite('sinLUT.h',['const uint32_t LUT_ENDINDEX[', num2str(length(FandBS(:,4))),'];'],'delimiter','', 'precision', precision,'-append') ;
dlmwrite('sinLUT.h',['const uint32_t LUT_STARTINDEX[',num2str(length(FandBS(:,3))),'];'],'delimiter','', 'precision', precision,'-append');  
dlmwrite('sinLUT.h',['const uint32_t LUT_SUPPORTPOINTS[',num2str(length(FandBS(:,2))),'];'],'delimiter','', 'precision', precision,'-append'); 
dlmwrite('sinLUT.h',['const float LUT_FREQUENCYS[',num2str(length(FandBS(:,1))),'];'],'delimiter','', 'precision', precision,'-append'); 

%LFO
dlmwrite('sinLUT.h',['const float LFO[',num2str(length(LFO_Array)),'];'],'delimiter','', 'precision', precision,'-append');
dlmwrite('sinLUT.h',['const uint32_t LFO_ENDINDEX[',num2str(length(FandBS_LFO(:,4))),'];'],'delimiter','', 'precision', precision,'-append') ;
dlmwrite('sinLUT.h',['const uint32_t LFO_STARTINDEX[',num2str(length(FandBS_LFO(:,3))),'];'],'delimiter','', 'precision', precision,'-append');  
dlmwrite('sinLUT.h',['const uint32_t LFO_SUPPORTPOINTS[',num2str(length(FandBS_LFO(:,2))),'];'],'delimiter','', 'precision', precision,'-append'); 
dlmwrite('sinLUT.h',['const float LFO_FREQUENCYS[',num2str(length(FandBS_LFO(:,1))),'];'],'delimiter','', 'precision', precision,'-append'); 


dlmwrite('sinLUT.h','#endif','delimiter','', 'precision', precision,'-append');
