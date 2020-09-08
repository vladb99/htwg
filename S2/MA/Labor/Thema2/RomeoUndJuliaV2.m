%function RomeoUndJulia
% Teil 1, Vorarbeit

TOL = 1.0e-12;
% Matrix mit komplexen Eigenwerten
 A = [[1 -2];[3 -1]];
% Matrix mit reellen Eigenwerten
%A     = [[1,2];[3,4]];

[V D] = eig(A);

if abs(det(V))<TOL; fprintf('Die Matrix ist nicht diagonalisierbar'); end

Vi = inv(V);
fprintf('Test Residuum: %.2e\n',norm(A-V*D*Vi))

eA=V*diag(diag(exp(D)))*Vi

%% eA approximiert durch ein Taylorpolynom
% falls A nicht diagonalisierbar ist oder als Test: 
% eA mit Taylorreihe approximiert
N = 40;  % Abbruch der Reihe

eAh = zeros(2);
Residuum = 1; k = 0;
while Residuum>1.0e-12
    eAh = eAh + A^k/factorial(k);
    Residuum = norm(eA-eAh); k = k+1;
    fprintf('error = %.2e\n',Residuum);
end


%end

