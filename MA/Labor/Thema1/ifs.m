function ifs()
close all
tic
KOF = 1;            % KindOfFaractal
Q=AffineAbbildung(KOF); % Q Definitionen
% Q=CreateQ(Q);     %Manipualtion von Q oder selst "bauen"
UnderstandQ(2,Q); %Quadrate abbilden, um Abbildungen zu verstehen

LOOPmax = 10;
PLOT=1; % ohne plot 99% Zeitersparnis bei LOOPmax=10000
%Xminmax = [-2.152858 0.500000 2.653972 9.964024];
% Fuer png-Datei bei PLOT=0
if ~PLOT
    switch KOF
        case 1
        Xminmax = [-2.152858 0.500000 2.653972 9.964024]; 
        case 2
        Xminmax = [0. 0. 1. 1.];
        otherwise
    end

    M = round(sqrt(LOOPmax));
    N = round(M*(Xminmax(3)-Xminmax(1))/(Xminmax(4)-Xminmax(2)));
    Pic = ones(M,N);
end
%%
% Startwert
x=[0.5 0.5]; 
if PLOT
    plot(x(1),x(2),'.','color',[0 1 0]);
    set(gca,'color',[0 0 0]);
    hold on
    xmin=x(1); xmax = x(1);
    ymin=x(2); ymax = x(2);
end

%%
for loop=1:LOOPmax
    ii=RandP(Q(:,7));    % liefert eine Zahl zwischen 1 und 
                         % NumZeilen(Q) mit Gewichtung aus Q(:,7)
    
    xd(1) = Q(ii,1:2)*x'; xd(2) = Q(ii,3:4)*x';
    x = xd+Q(ii,5:6);
    
    
    if PLOT
        plot(x(1),x(2),'.','color',[0 1 0]); 
        if x(1)<xmin; xmin = x(1); end;
        if x(1)>xmax; xmax = x(1); end;
        if x(2)<ymin; ymin = x(2); end;
        if x(2)>ymax; ymax = x(2); end;
        if loop==LOOPmax
            fprintf('Plotrahmen(lu,ro): %f %f %f %f\n',xmin,ymin,xmax,ymax);
        end
    else
        raw = M+1-min(M,max(1,RawCol(x(2),Xminmax(2),Xminmax(4),M)));
        col = min(N,max(1,RawCol(x(1),Xminmax(1),Xminmax(3),N)));
        
        Pic(raw,col)=0;
    end
end

if ~PLOT
    PicRGB = zeros(M,N,3);
    PicRGB(:,:,2)=0.8*(1-Pic);
    imshow(PicRGB)
    imwrite(PicRGB,"fractal.png")
end
toc
end

function i=RandP(P)
    CP = cumsum(P)*100;
    ir = round(rand*100-1);
    i=1;
    for l=length(CP)-1:-1:1
        if ir>=CP(l)
            i=l+1;
            break;
        end
    end
end

function Q=AffineAbbildung(flag)

switch flag
    case 1 % Barnsley
    Q=[ [0      0       0       0.16 	0 	0       0.01];
        [0.20 	-0.26 	0.23 	0.22 	0 	1.60 	0.07];
        [-0.15 	0.28 	0.26 	0.24 	0 	0.44 	0.07];
        [0.85 	0.04 	-0.04 	0.85 	0 	1.60 	0.85]]; 
 
    case 2 % fraktaler Baum
    Q=[ [0.200 	-0.500 	0.340 	0.400 	0.440 	0.250 	0.200];
        [0.460 	0.410 	-0.250 	0.360 	0.250 	0.570 	0.200];
        [-0.060 	-0.070 	0.450 	-0.110 	0.600 	0.097 	0.200];
        [-0.350 	0.070 	-0.470 	-0.020 	0.490 	0.500 	0.200];
        [-0.640 	0.000 	0.000 	0.500 	0.860 	0.250 	0.200]];
    
    otherwise
end
end

function ij=RawCol(x,xmin,xmax,L)

    ij = round(1+(x-xmin)/(xmax-xmin)*(L-1));

end

function Q2=CreateQ(Q)

Q2 = Q;

% Barnsley, Abbidlung A4, Winkel aendern
ii = 4;
A = [Q(ii,1:2); Q(ii,3:4)];

alpha=sqrt(A(1,1)^2+A(1,2)^2);
A2=A/alpha;
phi = acos(A2(1,1)); % original 0.047024131842746
phi = -0.2;          % neuen Winkel definieren


Aneu = alpha*[[cos(phi) sin(phi)];[-sin(phi) cos(phi)]];

Q2(ii,1:2) = Aneu(1,:);
Q2(ii,3:4) = Aneu(2,:);

end

function UnderstandQ(ii,Q)

A = [Q(ii,1:2); Q(ii,3:4)];
b = Q(ii,5:6)';

Quad = [[0 0]; [1 0]; [1 1]; [0 1]; [0 0]];
Quad2 = (A*Quad')';

figure(2)
% Originalquader (blau)
plot(Quad(:,1),Quad(:,2),'b-','LineWidth',2)
hold on 
% Bildquader (rot)
plot(Quad2(:,1),Quad2(:,2),'r-','LineWidth',2)
% Punkte fuer erste und zweite Ecke wegen der Orientierung (det +/-)
plot([Quad(1,1) Quad2(1,1)],[Quad(1,2) Quad2(1,2)],'go','LineWidth',2)
plot([Quad(2,1) Quad2(2,1)],[Quad(2,2) Quad2(2,2)],'mo','LineWidth',2)
xlim([min(min(Quad(:,1),Quad2(:,1))) max(max(Quad(:,1),Quad2(:,1)))])
ylim([min(min(Quad(:,2),Quad2(:,2))) max(max(Quad(:,2),Quad2(:,2)))])
daspect([1 1 1]); % Seitenverhaeltnis beibehalten

end