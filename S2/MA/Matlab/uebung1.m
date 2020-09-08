alpha = 1; % Kleiner Exponent
DIM = 100000; % Anzahl darzustellender Folgenglieder
n=linspace(1,DIM,DIM); % Feld aller Indizes
an = (n+1).^(alpha)./log(n+1); % Die Folgenglieder
% plot mit schwarzen Kugeln, Groesse 2
plot(n,an,'ko','LineWidth',2)
grid on