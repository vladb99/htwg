clear all
close all

%% Daten eines Merkmals (kuenstlich erzeugt)
Val = [20 80];                      %Merkmalsauspraegung
N = 100;                             % Anzahl der Messungen

Q = linspace(1,N,N)';               % quantitativ, diskret
rr = rand(N,1);
Q(:,2) = round(rr*Val(2) + (1-rr)*Val(1)); % zufaellige Werte aus dem 
                                    % Merkmalsbereich Val

% oder hier Daten einlesen aus Datei
%%
subplot(2,2,1)
plot(Q(:,1),Q(:,2),'ko')
xlabel('Merkmal')
ylabel('Messwerte')
title('Urliste')
grid on

%% Hauefigkeitsverteilung matlab: hist, histrogram

qmin = min(Q(:,2));
qmax = max(Q(:,2));

H = zeros(qmax - qmin+1,2);
H(:,1) = linspace(qmin,qmax,qmax-qmin+1);
for qm=qmin:1:qmax
    Ind = find(Q(:,2)==qm);
    H(qm+1-qmin, 2) = length(Ind);
end
subplot(2,2,2) 
bar(H(:,1),H(:,2))
xlabel('Messwerte')
ylabel('Anzahl')
title('absolute Häufigkeit')

% relative Häufigkeit
subplot(2,2,3)
stairs(H(:,1),H(:,2)/N)
title('relative Häufigkeit')

%% kumulative Summe, matlab: cumsum
HN = length(H);
H(:,3) = H(:,2)/N;
for i=2:HN
    H(i,3) = H(i-1,3) + H(i,2)/N; %oder + H(i,3)
end
subplot(2,2,4)
stairs(H(:,1),H(:,3))
title('kumulative Summe')  

%% Mittelwert, matlab: mean(Q(:,2))

Ma = sum(Q(:,2))/N;

fprintf('arithmetisches Mittel: %.2e (%.2e)\n',Ma, mean(Q(:,2)));
subplot(2,2,1)
hold on %Nicht neues Bild sondern das erste Bild verwenden
plot(Q(:,1),Ma*ones(N,1),'r-','LineWidth',2)

%% Median matlab: median(Q)
SQ = sort(Q(:,2));
if mod(N,2)== 0 %gerade
    Med = (SQ(N/2)+SQ(N/2+1))/2;
else %ungerade
    Med = SQ((N+1)/2);
end
fprintf('Median: %.2e (%.2e)\n',Med,median(Q(:,2)))

%% p-quantil, matlab: quantile(Q,p)
p = 0.1;
gaussklammer = @(x) floor(x+1);
if abs(N*p-floor(N*p)) == 0 % N*p natuerliche Zahl
    pQuantil = (SQ(N*p)+SQ(N*p+1))/2;
else
    pQuantil = SQ(gaussklammer(N*p));
end

fprintf('%.2e-Quantil = %.2f (%.2e)\n',p,pQuantil,quantile(Q(:,2),p));

%}