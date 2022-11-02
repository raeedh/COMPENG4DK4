syms k

lambda = 2;
h = 3;
A = h*lambda;
N = 10;

Pw = double(((A^N)/factorial(N)) / (((A^N)/factorial(N)) + (1-(A/N))*symsum(A^k/factorial(k),k,0,N)))

Tw = (Pw*h) / (N*(1 - (A/N))) 