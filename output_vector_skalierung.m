
t= linspace(0,300,300000)
x=sin(2*pi*t*1.2)+sin(2*pi*t*5)+sin(2*pi*t*10)+sin(2*pi*t*100)+sin(2*pi*t*2.3)+sin(2*pi*t*2.5);
x=x/6;
plot(t,x);
grid on;
