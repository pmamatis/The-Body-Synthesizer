close all; clc

hh_length    = 20000;
kick_length  = 20000;
snare_length = 20000;
ride_length  = 20000;

SR = 48000;

volume = 0.3;

%% ELOM

[Elom,SR] = audioread('Elom.m4a');

%% 26-33s          high laugh, Elom lacht über Hund
%% E1

ST1 = 32400 + 26*SR;
EN1 = ST1 + 33630;

E1 = zeros(1,40000);
E1_OS = zeros(1,10000);

for i = 1:(EN1-ST1)
    E1(i) = Elom(ST1-1+i);
end

E1 = E1(1:8:end);
E1(1) = 0;

for i = 1:length(E1)
    E1_OS(2*i-1)  = E1(i);
    E1_OS(2*i)    = E1(i);
end

sound(E1_OS,SR/2);

figure(1);
plot(E1'); grid on
title('E1');
pause(1)
% 
% %% E2
% 
% ST2 = EN1;
% EN2 = ST2 + 33780;
% 
% E2 = zeros(1,40000);
% 
% for i = 1:(EN2-ST2)
%     E2(i) = Elom(ST2-1+i);
% end
% 
% E2 = E2(1:4:end);
% E2(1) = 0;
% sound(E2,SR/2);
% 
% figure(2);
% plot(E2'); grid on
% title('E2');
% pause(1)
% 
% %% E3
% 
% ST3 = EN2 + 79920 + 2062;
% EN3 = ST3 + 32050;
% 
% E3 = zeros(1,40000);
% 
% for i = 1:(EN3-ST3)
%     E3(i) = Elom(ST3-1+i);
% end
% 
% E3 = E3(1:4:end);
% E3(1) = 0;
% sound(E3,SR/2);
% 
% figure(3);
% plot(E3'); grid on
% title('E3');
% pause(1)
% 
% 
% %% 46-49s          deeper laugh
% %% E4
% 
% ST4 = 46*SR + 62070;
% EN4 = ST4 + 40000;
% 
% E4 = zeros(1,40000);
% 
% for i = 1:(EN4-ST4)
%     E4(i) = Elom(ST4-1+i);
% end
% 
% 
% E4(1) = 0;
% E4(40000) = 0;
% E4 = E4(1:4:end);
% sound(E4,SR/2);
% 
% figure(4);
% plot(E4'); grid on
% title('E4');
% pause(1)
% 
% %% 54-58s          HIGH laugh
% %% E5
% 
% ST5 = 54*SR + 66830;
% EN5 = ST5 + 37190;
% 
% E5 = zeros(1,40000);
% 
% for i = 1:(EN5-ST5)
%     E5(i) = Elom(ST5-1+i);
% end
% 
% 
% E5(1) = 0;
% E5 = E5(1:4:end);
% sound(E5,SR/2);
% 
% figure(5);
% plot(E5'); grid on
% title('E5');
% pause(1)
% 
% %% E6
% 
% ST6 = EN5 + 1;
% EN6 = ST6 + 39980;
% 
% E6 = zeros(1,40000);
% 
% for i = 1:(EN6-ST6)
%     E6(i) = Elom(ST6-1+i);
% end
% 
% 
% E6(1) = 0;
% E6 = E6(1:4:end);
% sound(E6,SR/2);
% 
% figure(6);
% plot(E6'); grid on
% title('E6');
% pause(1)
% 
% %% 1:47s - 1:48s   einfach
% %% E7              einfach
% 
% ST7 = 107*SR + 5010;
% EN7 = ST7 + 19990;
% 
% E7 = zeros(1,40000);
% 
% for i = 1:(EN7-ST7)
%     E7(i) = Elom(ST7-1+i);
% end
% 
% E7(1) = 0;
% E7 = E7(1:4:end)
% sound(E7,SR/2);
% 
% figure(7);
% plot(E7'); grid on
% title('E7');
% pause(1)
% 
% %% E8          einfach einfach
%  
% ST8 = 107*SR + 5010;
% EN8 = ST8 + 19990;
% 
% E8 = zeros(1,40000);
% 
% for i = 1:(EN8-ST8)
%     E8(i) = Elom(ST8-1+i);
%     E8(i+20000) = Elom(ST8-1+i);
% end
% 
% E8(1) = 0; 
% E8(20001) = 0; 
% E8 = E8(1:4:end);
% sound(E8,SR/2);
% 
% figure(8);
% plot(E8'); grid on
% title('E8');
% pause(1)
% 
% %% 3:01s - 3:02s   Super
% %% E9              Subba
% 
% ST9 = 181*SR + 19004;
% EN9 = ST9 + 16000;
% 
% E9 = zeros(1,40000);
% 
% for i = 1:(EN9-ST9)
%     E9(i) = Elom(ST9-1+i);
% end
% 
% E9(1) = 0;
% E9 = E9(1:4:end);
% sound(E9,SR/2);
% 
% figure(9);
% plot(E9'); grid on
% title('E9');
% pause(1)
% 
% %% E10              Subba, Subba
% 
% ST10 = 181*SR + 19004;
% EN10 = ST10 + 16000;
% 
% E10 = zeros(1,40000);
% 
% for i = 1:(EN10-ST10)
%     E10(i) = Elom(ST10-1+i);
%     E10(i+20000) = Elom(ST10-1+i);
% end
% 
% E10(1) = 0;
% E10(20001) = 0;
% E10 = E10(1:4:end);
% sound(E10,SR/2);
% 
% figure(10);
% plot(E10'); grid on
% title('E10');
% pause(1)
% 
% %% 3:08s - 3:09s   einfach nochmal
% %% E11
% ST11 = 188*SR + 7955;
% EN11 = ST11 + 22088;
% 
% E11 = zeros(1,40000);
% 
% for i = 1:(EN11-ST11)
%     E11(i) = Elom(ST11-1+i);
% end
% 
% E11(1) = 0;
% E11 = E11(1:4:end);
% sound(E11,SR/2);
% 
% figure(11);
% plot(E11'); grid on
% title('E11');
% pause(1)
% 
% %% 3:19s - 3:20s   shoe laugh
% %% E12
% 
% ST12 = 199*SR + 33900 + 7696;
% EN12 = ST12 + 26000;
% 
% E12 = zeros(1,40000);
% 
% for i = 1:(EN12-ST12)
%     E12(i) = Elom(ST12-1+i);
% end
% 
% E12(1) = 0;
% E12 = E12(1:4:end);
% sound(E12,SR/2);
% 
% figure(12);
% plot(E12'); grid on
% title('E12');
% pause(1)
% 
% %% 4:35s - 4:36s   eier auch
% %% E13
% 
% ST13 = 275*SR + 28026;
% EN13 = ST13 + 27380;
% 
% E13 = zeros(1,40000);
% 
% for i = 1:(EN13-ST13)
%     E13(i) = Elom(ST13-1+i);
% end
% 
% E13(1) = 0;
% E13 = E13(1:4:end);
% sound(E13,SR/2);
% 
% figure(13);
% plot(E13'); grid on
% title('E13');
% pause(1)
% 
% %% 5:27s - 5:28s   grunzendes lachen
% %% E14
% 
% ST14 = 327*SR + 10000 + 2050;
% EN14 = ST14 + 39970;
% 
% E14 = zeros(1,40000);
% 
% for i = 1:(EN14-ST14)
%     E14(i) = Elom(ST14-1+i);
% end
% 
% E14(1) = 0;
% E14 = E14(1:4:end);
% sound(E14,SR/2);
% 
% figure(14);
% plot(E14'); grid on
% title('E14');
% pause(1)
% 
% %% TXT-file
% volume = 0.3;
% 
% E1 = volume * (E1 / max(E1));
% E2 = volume * (E2 / max(E2));
% E3 = volume * (E3 / max(E3));
% E4 = volume * (E4 / max(E4));
% E5 = volume * (E5 / max(E5));
% E6 = volume * (E6 / max(E6));
% E7 = volume * (E7 / max(E7));
% E8 = volume * (E8 / max(E8));
% E9 = volume * (E9 / max(E9));
% E10 = volume * (E10 / max(E10));
% E11 = volume * (E11 / max(E11));
% E12 = volume * (E12 / max(E12));
% E13 = volume * (E13 / max(E13));
% E14 = volume * (E14 / max(E14));
% 
% audiowrite('E1.wav', E1, SR/2);
% audiowrite('E2.wav', E2, SR/2);
% audiowrite('E3.wav', E3, SR/2);
% audiowrite('E4.wav', E4, SR/2);
% audiowrite('E5.wav', E5, SR/2);
% audiowrite('E6.wav', E6, SR/2);
% audiowrite('E7.wav', E7, SR/2);
% audiowrite('E8.wav', E8, SR/2);
% audiowrite('E9.wav', E9, SR/2);
% audiowrite('E10.wav', E10, SR/2);
% audiowrite('E11.wav', E11, SR/2);
% audiowrite('E12.wav', E12, SR/2);
% audiowrite('E13.wav', E13, SR/2);
% audiowrite('E14.wav', E14, SR/2);
% 
% E1 = E1 + 1;
% E2 = E2 + 1;
% E3 = E3 + 1;
% E4 = E4 + 1;
% E5 = E5 + 1;
% E6 = E6 + 1;
% E7 = E7 + 1;
% E8 = E8 + 1;
% E9 = E9 + 1;
% E10 = E10 + 1;
% E11 = E11 + 1;
% E12 = E12 + 1;
% E13 = E13 + 1;
% E14 = E14 + 1;
% 
% 
% %% E1
% fid = fopen('Elom_1.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E1(i));
% end
% fclose(fid);
% 
% %% E2
% fid = fopen('Elom_2.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E2(i));
% end
% fclose(fid);
% 
% %% E3
% fid = fopen('Elom_3.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E3(i));
% end
% fclose(fid);
% 
% %% E4
% fid = fopen('Elom_4.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E4(i));
% end
% fclose(fid);
% 
% %% E5
% fid = fopen('Elom_5.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E5(i));
% end
% fclose(fid);
% 
% %% E6
% fid = fopen('Elom_6.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E6(i));
% end
% fclose(fid);
% 
% %% E7
% fid = fopen('Elom_7.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E7(i));
% end
% fclose(fid);
% 
% %% E8
% fid = fopen('Elom_8.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E8(i));
% end
% fclose(fid);
% 
% %% E9
% fid = fopen('Elom_9.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E9(i));
% end
% fclose(fid);
% 
% %% E10
% fid = fopen('Elom_10.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E10(i));
% end
% fclose(fid);
% 
% %% E11
% fid = fopen('Elom_11.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E11(i));
% end
% fclose(fid);
% 
% %% E12
% fid = fopen('Elom_12.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E12(i));
% end
% fclose(fid);
% 
% %% E13
% fid = fopen('Elom_13.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E13(i));
% end
% fclose(fid);
% 
% %% E14
% fid = fopen('Elom_14.txt','w');
% for i = 1:10000
%     a = fprintf(fid,'%1.8f',E14(i));
% end
% fclose(fid);
