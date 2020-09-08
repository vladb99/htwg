function RomeoUndJulia()
close all

% betrachtetes Zeitintervall (Tage)
T = [0,20];
% plotten nur wenn ein plot moeglich ist
DIM = 1000;

%% Startwerte
% Romeos Liebe zu Julia zu Beginn (t=0)
R0 = 1;
% Julias Liebe Romeo gegenüber zu Beginn (t=0)
J0 = 0;
P0 = [J0, R0]; % das Paar

% Die weitere Entwicklung Ihrer Liebe zueinander ....
% dP = A*P => P(t) = P(0)*exp(A*t)

% Für Romeo ist die Sache ganz einfach: Je mehr Julia ihn liebt, desto mehr liebt er auch
% sie (und natürlich umgekehrt: je weniger Julia ihn liebt, desto weniger liebt er sie).
A(2,1) = 4/5; A(2,2) = 0;

% Julias Gefühle lassen sich jedoch nicht so einfach beschreiben: Ihre Liebe zu Romeo
% lässt sofort nach, wenn Romeo beginnt, sie mehr zu lieben. Falls sich jedoch Romeos
% Gefühle abkühlen, dann fängt sie sofort an, ihn mehr zu lieben. Und zu guter Letzt
% wächst ihre Liebe zu ihm, je mehr sie ihn liebt. 
A(1,1) = 2/5; A(1,2) = -1/5;

% Schon ganz erschöpft von dem ganzen Durcheinander, stellt sich Julia ein Ultimatum: Wenn
% Romeo sie am 50. Tag nicht liebt (d.h. falls J(50) = 0 ), trennt sie sich von ihm. Anderenfalls
% will sie mit ihm bis ans Ende ihrer Tage zusammen sein. Bleiben Romeo und Julia zusammen?

[V D]=eig(A);
approx = 0;
if det(V)==0; approx=1; end % das bedeutet v1, v2 la und dann gibt es kein Vi

if 0; fprintf('exponentielles Wachstum\n'); end

if 0
    fprintf('nicht diagonalisierbare Situation\nnur Vermutungen moeglich\n'); 
    approx = 1;
end

if 0; fprintf('oszillierendes Verhalten der Loesung\n'); end

%% dP = A*P
t = linspace(T(1),T(2),DIM);

if ~approx
    % Loesung P ueber Diagonalisierung
    P=dieLiebe(t,V,diag(D),P0);
else
    % Loesung P ueber Taylorreihe
    EA=expMat(A,t,15);
    P(1,:)=P0(1)*EA(1,1,:)+P0(2)*EA(2,1,:);
    P(2,:)=P0(1)*EA(1,2,:)+P0(2)*EA(2,2,:);
end


%% Darstellung der Loesung
if 1
figure('Position',[0 0 600 400])
plot(t,P(2,:),'-','color',[0 0 0.8],'LineWidth',2)
hold on
plot(t,P(1,:),'-','color',[0.8 0 0],'LineWidth',2)
title('Die Liebe zwischen Romeo und Julia')
xlabel('die Tage ziehen dahin ...')
ylabel('die Liebe macht was sie wi!!')
text(0.1*max(t),0.9*max(max(P)),'Romeo','color',[0 0 0.8],'FontSize',18);
text(0.1*max(t),0.6*max(max(P)),'Julia','color',[0.8 0 0],'FontSize',18);
grid on
end
end

function EA=expMat(A,t,N)

    EA = zeros(2,2,length(t));
    for k=0:N
        for i=1:length(t)
            EA(:,:,i) = EA(:,:,i) + A^k/factorial(k)*t(i)^k;    
        end
    end

end
    
    



function y=dieLiebe(t,V,d,P0)

    y   = zeros(2,length(t));
    
    detV = det(V);
    
    A11 = V(2,2)*(V(1,1)*exp(d(1)*t)-V(1,2)*exp(d(2)*t));
    A12 = V(1,1)*V(1,2)*(exp(d(2)*t)-exp(d(1)*t));
    A21 = V(2,1)*V(2,2)*(exp(d(1)*t)-exp(d(2)*t));
    A22 = V(2,1)*(V(1,1)*exp(d(2)*t)-V(1,2)*exp(d(1)*t));
    
    y(1,:) = (P0(1)*A11+P0(2)*A21)/detV;
    y(2,:) = (P0(1)*A12+P0(2)*A22)/detV;   
end
