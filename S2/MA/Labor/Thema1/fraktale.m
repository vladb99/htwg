function fraktale()
    tic
    Q = IFS();
    
    close all
    
    x = [0.5 0.5];
    LOOPmax = 100;
    
    plot(x(1), x(2), '.', 'color' ,[0 0.8 0])
    set(gca, 'color', [0 0 0]);
    hold on
    
    Xminmax = [-2.152858 0.500000 2.653972 9.964024];
    M = round(sqrt(LOOPmax))*3;
    N = round(M*(Xminmax(3)-Xminmax(1))/(Xminmax(4)-Xminmax(2)));
    Pic = zeros(M,N);
    
    for loop = 1:LOOPmax
        i = RandP(Q(:,7));
        xd(1) = Q(i, 1:2) * x';
        xd(2) = Q(i, 3:4) * x';
        x = xd + Q(i, 5:6);
        plot(x(1), x(2), '.', 'color' ,[0 0.8 0])
        
        raw = M+1-min(M,max(1,RawCol(x(2),Xminmax(2),Xminmax(4),M)));
        col = min(N,max(1,RawCol(x(1),Xminmax(1),Xminmax(3),N)));
        Pic(raw,col)=1;
    end
    
    
    PicRGB = zeros(M,N,3);
    PicRGB(:,:,2)=0.8*Pic;
    %imshow(PicRGB)
    imwrite(PicRGB,"fractal.png")
    
    toc
end

function Q = IFS()
    Q=[[0 0 0 0.16 0 0 0.01]; [0.20 -0.26 0.23 0.22 0 1.60 0.07]; [-0.15 0.28 0.26 0.24 0 0.44 0.07];
    [0.85 0.04 -0.04 0.85 0 1.60 0.85]];

end

function i = RandP(P)
    CP = cumsum(P) * 100;
    ir = round(rand * 100 - 1);
    i = 1;
    for l = length(CP) - 1:-1:1
        if ir >= CP(l)
            i = l + 1;
            break;
        end
    end
end

function ij=RawCol(x,xmin,xmax,L)
    ij = round(1+(x-xmin)/(xmax-xmin)*(L-1));
end
