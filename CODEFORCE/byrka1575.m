% Byrka 2010, shows 1.575 ratio by LP-rounding
% ratio is max{r, 1+2*exp(-r), (exp(-1)+exp(-r))/(1-1/r)
% for 1<=r<=2
% 11/17/2011
clear
ezplot('(exp(-1)+exp(-x))/(1-1/x)',[1.4,2])
hold on
ezplot('1+2*exp(-x)',[1.4,2])
ezplot('x',[1.4,2])
xlabel('gamma')
ylabel('ratio')
grid on
% output the r=1.574906375697598
format long
fzero('(exp(-1)+exp(-x))/(1-1/x)-x',1.5)