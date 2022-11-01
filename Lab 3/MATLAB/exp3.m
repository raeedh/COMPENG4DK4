clear; clc;

syms k

for A = 1:40
    for N = 1:40
        PB(A,N) = ((A^N)/factorial(N))/symsum(A^k/factorial(k),k,0,N);
    end
end

for N = 1:40
    fprintf("%d %d\n", N, sum(double(PB(:,N)) < 0.01));
end