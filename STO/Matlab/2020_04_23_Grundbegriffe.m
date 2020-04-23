 
%% Daten eines Merkmals (kuenstlich erzeugt)
Val = [20 80];                      %Merkmalsauspraegung
N = 10;                             % Anzahl der Messungen

Q = linspace(1,N,N)';               % quantitativ, diskret
rr = rand(N,1);
Q(:,2) = rr*Val(2) + (1-rr)*Val(1); % zufaellige Werte aus dem 
                                    % Merkmalsbereich Val

% oder hier Daten einlesen aus Datei
%%
