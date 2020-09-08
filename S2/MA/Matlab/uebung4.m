% Aufgabe 11 Blatt 4:
I = [ 0 , 1 ] ;
N = 100;
h = (I(2) - I(1))/(N-1);
func = @(x) sin(2*pi*x ) ;
dfunc = @(x) 2*pi*cos(2*pi*x ) ;
%%
x = I(1):h:I(2) ;
u = func(x) ;
d1u = dfunc(x) ; % e xa k te / k o n t i n u i e r l i c h e e r s t e Ablei tung
%% e r s t e Ablei tung ( vo rwae r t s , r u e c kwa e r t s und g e m i t t e l t )
duv = zeros(1,N); dur = zeros(1,N); dum = zeros(1,N);
for i=1:N
    if i<N; duv(i) = (u(i+1)-u(i))/h; end
    if i>1; dur(i) = (u(i)-u(i-1))/h; end
    if i<N && i >1; dum(i) = (u(i+1)-u(i-1))/(2*h); end
end
%%
plot(x ,u ,'k-' ,x ,d1u, 'k-' ) ;
hold on
grid on
plot(x(2:N-1), duv(2:N-1),'r-');
plot(x(2:N-1), dur(2:N-1), 'b-');
plot(x(2:N-1), dum(2:N-1), 'm-');

