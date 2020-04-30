close all
x = linspace(0, 1, 10);

%y = sin(x);
y = x .* sin(2*pi*x);

plot(x,y);