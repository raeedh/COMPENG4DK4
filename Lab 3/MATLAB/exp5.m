syms k

lambda = 2;
h = 7;
A = h*lambda;
N = 15;
t = 1;

Pw = double(((A^N)/factorial(N)) / (((A^N)/factorial(N)) + (1-(A/N))*symsum(A^k/factorial(k),k,0,N)))

Tw = (Pw*h) / (N*(1 - (A/N)))

Wt = 1 - (Pw*exp(-(N-A)*(t/h)))