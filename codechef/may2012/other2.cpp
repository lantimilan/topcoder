#include <cstdio>
#include <iostream>
using namespace std;
int bc[1<<15];
const int M = (1<<15) - 1;
void setMin(int& ret, int c){
if(c < ret) ret = c;
}
void doit(int n, int mask, int currentSteps, int& currentBest) {
int numMax = bc[mask>>15] + bc[mask&M];
if(numMax == n) {
setMin(currentBest, currentSteps);
return;
}
if(currentSteps + 1 >= currentBest) return;
if(currentSteps + 2 >= currentBest) {
if(numMax * 2 >= n) {
setMin(currentBest, 1 + currentSteps);
}
return;
}
if(numMax < (1<<currentSteps)) return;
for(int i=0;i<n;i++) {
int a = 0, b = 0;
int c = mask;
for(int j=i;j<n;j++) {
c |= (1<<j);
if(mask&(1<<j)) b++;
else a++;
if(b >= a) {
doit(n, c, currentSteps + 1, currentBest);
}
}
}
}
int v[32];
void solveCase() {
int n;
scanf(" %d", &n);
int maxElement = 0;
for(int i=0;i<n;i++) {
scanf(" %d", v+i);
if(v[i] > maxElement) maxElement = v[i];
}
int mask = 0;
for(int i=0;i<n;i++) if(v[i] == maxElement) mask |= (1<<i);
int ret = 0, p = 1;
while(p < n) {
ret++;
p *= 2;
}
doit(n, mask, 0, ret);
printf("%d\n",ret);
}
main() {
for(int i=0;i<(1<<15);i++) {
bc[i] = bc[i>>1] + (i&1);
}
int cases;
scanf(" %d",&cases);
while(cases--) solveCase();
}
 
