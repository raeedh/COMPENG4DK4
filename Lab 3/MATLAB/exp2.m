clear; clc;

syms k

for A = 1:20
    for N = 1:20
        PB(A,N) = ((A^N)/factorial(N))/symsum(A^k/factorial(k),k,0,N);
    end
end

N = 1:20;

figure('Name','4DK4 Lab 3: Experiment 2', 'WindowState', 'maximized');
plot(N,PB(1,:),'-o','MarkerSize',10,'LineWidth',2);

hold on
for i = 2:20
    plot(N,PB(i,:),'-o','MarkerSize',10,'LineWidth',2);
end

ax = gca;
set(ax, 'YScale', 'log', 'FontSize', 18, 'XTick', N, 'XLim', [1 20], 'YLim', [0.0001 1]); xtickangle(0);
xlabel('Number of Channels'); ylabel('Block Probability')
title("Blocking Probability vs. Number of Channels");

for A = 1:20
    lgd_list(A) = append("$a = ", string(A),"$");
end

pbaspect([1 1 1])

lgd = legend(lgd_list, 'Interpreter', 'latex', 'NumColumns', 6, Location='southoutside');
title(lgd, "Offered Load")
lgd.FontSize = 18;

f = gcf;
exportgraphics(f,"exp2.png")
exportgraphics(f,"../report/figures/exp2.png")
close(f)