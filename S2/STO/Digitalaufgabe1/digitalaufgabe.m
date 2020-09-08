clear all
close all

N = 13;
data = readtable('data_numeric.csv');
array = table2array(data);
b(:,1) = linspace(1,N,N);

b(:,2) = array(:,6);
%[39,25,28,24,50,48,33,12,53,134,268,8]; % Bu�gelder
e = [42435,24580,26835,32200,56115,55800,44060,21900,41170,74320,31575,11190]; % Einnahmen Insgesamt
eB = [2262,1307,1413,1746,2976,2945,2345,1230,2043,3860,2695,610]; % G�ltige Beantstandungen
f = [644822,453517,609189,543587,1063749,1108142,864794,637453,759995,1240939,1092858,438475]; % Gemessene Fahrzeuge

temp = sum(f)/sum(eB);
fprintf('Durchgef�hrt: %0.5e\n',temp);

m = median(b(:,2));
d = mean(b(:,2));

fprintf('Median: %0.5e\n',m);
fprintf('Durschnitt: %0.5e\n',d);

plot(b(:,1),b(:,2),'ro')
title('Bu�gelder Monatlich')
xlabel('Monat')
ylabel('Bu�gelder')
hold on
grid on