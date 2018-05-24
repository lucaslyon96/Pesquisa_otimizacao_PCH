param m; 
param n; 
param G; 
param c{1..m};
param dkij {1..m, 1..n, 1..n};
var zkg {1..m,1..G} binary; 
var egij {1.. G,1..n,1.. n} binary;
#var wkgij{1..m,1..G,1..n,1..n}>=0,<=1;
#var wkgij{1..m,1..G,1..n,1..n} binary;

#funcao objetivo

#minimize Obj: sum{k in 1..m,g in 1..G,i in 1..n,j in 1..n}  wkgij[k,g,i,j] * dkij[k,i,j];


minimize Obj: sum{g in 1..G,k in 1..m,i in 1..n,j in 1..n}  zkg[k,g] * dkij[k,i,j] * egij[g,i,j];

#restriçoes
subject to A {g in 1..G,i in 1..n } : sum{j in 1..n}egij [g,i,j]=1;
subject to B {g in 1..G,i in 1..n,j in 1..n}: egij[g,i,j]<=egij[g,j,j];
subject to C {k in 1..m}: sum {g in 1..G}zkg[k,g]=1;
subject to D {g in 1..G}: sum {k in 1..m}zkg[k,g]>=1;
subject to E {g in 1..G}: sum {j in 1..n} egij[g,j,j] <= (sum {k in 1..m}c[k] * zkg[k,g])/(sum {k in 1..m}zkg[k,g]);
#subject to E {g in 1..G}: sum {k in 1..m,j in 1..n} wkgij[k,g,j,j] <= (sum {k in 1..m}c[k] * zkg[k,g]);

#subject to F0 {g in 1..G,k in 1..m, i in 1..n, j in 1 ..n}: wkgij[k,g,i,j]<=egij[g,i,j];
#subject to F1 {g in 1..G,k in 1..m, i in 1..n, j in 1 ..n}: wkgij[k,g,i,j]<=zkg[k,g];# e torna reduntande apos acresentar a equacao F3
#subject to F2 {g in 1..G,k in 1..m, i in 1..n, j in 1 ..n}: wkgij[k,g,i,j]>=(egij[g,i,j]+zkg[k,g]-1);# e torna reduntante apos Seq F4
#subject to F3 {g in 1..G,k in 1..m, i in 1..n}:sum{j in 1..n}wkgij[k,g,i,j]==zkg[k,g];
#subject to F4 {g in 1..G,k in 1..m, i in 1..n}: sum {j in 1..n} (egij[g,i,j]-wkgij[k,g,i,j])=1-zkg[k,g];


