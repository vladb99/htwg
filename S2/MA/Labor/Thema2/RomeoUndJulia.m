%function RomeoUndJulia
% Teil 1, Vorarbeit

TOL = 1.0e-12;

A     = [[1,2];[3,4]];
[V D] = eig(A);

if abs(det(V))<TOL; fprintf('Die Matrix ist nicht diagonalisierbar'); end

Vi = inv(V);
fprintf('Test Residuum: %.2e\n',norm(A-V*D*Vi))

eA=V*diag(diag(exp(D)))*Vi



%end

