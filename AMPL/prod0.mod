var XB;
var XC;
#funcao objetivo
maximize Profit: 25 *XB +30*XC;
#restricoes 
subject to Time: (1/200)*XB + (1/140)*XC <=40;
subject to B_limit: 0<=XB<=6000;
subject to C_limit: 0 <=XC <=4000;
