close all

N = 12;
data = readtable('data_numeric.csv');
array = table2array(data);


buss(:,1) = linspace(1,N,N);   
buss(:,2) = array(:,6);                         %Bussgelder

TageiE(:,1) = linspace(1,N,N);
TageiE(:,2) = array(:,1);                       %Tage im Einsatz

Fahrzeuge(:,1) = linspace(1,N,N);       
Fahrzeuge(:,2) = array(:,2);                    %Fahrzeuge

gBean(:,1) = linspace(1,N,N);
gBean(:,2) = array(:,4);                        %g�ltige Beanstandungen

erwG(:,1) = linspace(1,N,N);
erwG(:,2) = array(:,18);                        %erwarteter Gewinn

%--------------------------------------------------------------------/Berechnungen
gebl = sum(Fahrzeuge(:,2))/sum(gBean(:,2));     %1. Keyfact
fprintf('Geblitzt: jeder %.2f wird geblitzt\n', gebl);

binom = binopdf(1, 10, 1/371.87)*100;           %binomialverteilung 1 von 10 wird geblitzt
fprintf('Binomialverteilung: %.2f%%\n', binom);

dBussw = sum(erwG(:,2))/sum(gBean(:,2));        %2. Keyfact
fprintf('Durchgeführt: %.2f\n',dBussw);

kamera = sum(TageiE(:,2))/365;                  %3. Keyfact
fprintf('Kameras: %.2f\n',kamera);

wah = kamera/16;                                %Wahrscheinlichkeit, bestückter Blitzer zu erwischen
fprintf('Wahrscheinlichkeit: %.2f\n',wah);




    