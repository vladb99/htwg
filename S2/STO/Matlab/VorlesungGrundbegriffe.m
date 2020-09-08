clear all
close all

% Wertegrenzen
Val=[20 60];

% Datensatz einlesen
%Q=load('');
% oder kuenstlich erzeugen
N = 100; % Anzahl Messwerte
Q(:,1) = linspace(1,N,N); rr = rand(N,1);
Q(:,2) = min(max(Val(1),round(rr*Val(2) + (1-rr)*Val(1))),Val(2));
N = length(Q);

subplot(2,2,1)
plot(Q(:,1),Q(:,2),'ro')
title('Urliste, arithmetisches Mittel, p-Quantil')
xlabel('Merkmal')
ylabel('Messwerte')
hold on
grid on

%%
% arithmetische Mittel
aM = sum(Q(:,2))/N; % matlab: mean(Q(:,2))
fprintf('arithmetisches Mittel:         %.2e\n',aM);
plot(Q(:,1),aM*ones(N,1),'b-');

%%
% absolute/relative Haeufigkeit matlab: hist(), histogram()
qmin = min(Q(:,2)); qmax = max(Q(:,2));

H = zeros(qmax+1-qmin,2);
for qm=qmin:qmax
    Ind = find(Q(:,2)==qm);
    H(qm+1-qmin,1)=qm;
    H(qm+1-qmin,2)=length(Ind);
end
subplot(2,2,2)
bar(H(:,1),H(:,2))
xlabel('Messwerte')
ylabel('Häufigkeit')
title('absolute Häufigkeit')

subplot(2,2,3)
H(:,3) = H(:,2)/N;
stairs(H(:,1),H(:,3));
grid on
title('relative Häufigkeit')
%%
% kumulative Summe % matlab: cumsum(H)
HN = length(H);
H(1,4) = H(1,3);
for i=2:HN
    H(i,4) = H(i-1,4)+H(i,3);
end
% überzeichnet den vorherigen plot auf Position 3
stairs(H(:,1),H(:,4));
grid on
xlabel('Messwerte')
ylabel('kum. Summe')
title('kumulative Summe der rel. H.')
%%
% (empirischer) Median=0.5 Quantil, matlab: median(Q(:,2))
SQ = sort(Q(:,2));
if mod(N,2)==0 % N gerade
    Med = (SQ(N/2)+SQ(N/2+2))/2;
else % N ungerade
    Med = SQ((N+1)/2);
end
fprintf('Median:                        %.2e\n',Med);

p = 0.25; 
% p-Quantil (gibt Wert nach p*100 % des Datensatzes an), matlab:
% quantile(Q(:,2),p)
gaussklammer = @(x) ceil(x);
 
if abs(N*p-floor(N*p))==0 % N*p ist dann eine natuerliche Zahl
    pQuantil = (SQ(N*p)+SQ(N*p+1))/2;
else
    pQuantil = SQ(gaussklammer(N*p));
end
fprintf('%.2f-Quantil:                  %.2e \n',p,pQuantil);
subplot(2,2,1)
plot(Q(:,1),pQuantil*ones(N,1),'color',[0.5 0 0.5])
qQuantil = quantile(Q(:,2),1-p);
plot(Q(:,1),qQuantil*ones(N,1),'color',[0.5 0 0.5])
text(0.1*N,pQuantil+0.05*(qmax-qmin),'p-Quantil');
text(0.1*N,aM+0.05*(qmax-qmin),'arithmetisches Mittel');
text(0.1*N,qQuantil+0.05*(qmax-qmin),'(1-p)-Quantil');
%%
% alpha-getrimmtes Mittel (Mittelwert des an beiden Enden um 
% alpha*100 %-ig gekuerzten Datensatzes)

Ind = find(Q(:,2)>quantile(Q(:,2),p));
Ind = find(Q(Ind,2)<quantile(Q(:,2),1-p));
Xalpha = mean(Q(Ind,2));
fprintf('%.2f-getrimmtes Mittel:        %.2e \n',p,Xalpha);
plot(Q(:,1),Xalpha*ones(N,1),'b--')

%%
% Modalwert, matlab: mode(Q(:,2))
[mw i] = max(H(:,2));
fprintf('Modalwert:                     %.2e \n',i+qmin-1);

subplot(2,2,4)
boxplot(Q(:,2))
ylabel('Messwerte')
title('Boxplot der Daten')
grid on

