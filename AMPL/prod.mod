#conjunto P
set P;
#parametros 
param a {j in P};
param b;
param c {j in P};
param u {j in P};
# variavel a qual queremos descobrir o valor 
var X {j in P};
#funcao objetivo onde sum simboliza um somatorio 
maximize Total_Profit: sum {j in P} c[j] * X[j];
#restricoes 
subject to Time: sum {j in P} (1/a[j]) * X[j] <=b;
subject to Limit {j in P}: 0 <= X[j] <= u[j];

