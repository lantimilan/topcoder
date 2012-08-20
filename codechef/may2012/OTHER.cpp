#include<stdio.h>
#include<stdlib.h>
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
int a[32],b[32];
int main()
{
int t;
scanf("%d",&t);
while(t--)
{
int n;
scanf("%d",&n);
int i;int max_num=-1;
for(i=0;i<n;i++)
{
scanf("%d",&a[i]);
max_num=max(max_num,a[i]);
 
}
int cnt=0,cnt1=0;
for(i=0;i<n;i++)
b[i]=a[n-(i+1)];
while(1)
{
int l,h,mmax=0,j,k;
int i;
for(i=0;i<n;i++)
if(a[i]!=max_num)
break;
if(i==n) break;
cnt++;
for(i=0;i<n;i++)
{
for(j=i+1;j<n;j++)
{
int c=0;
for(k=i;k<=j;k++)
{
if(a[k]==max_num)
c++;
}
int num_elements=j-i+1;
if(c>=(num_elements+1)/2 && num_elements>mmax)
{
mmax=num_elements;
l=i;
h=j;
}
}
}
// printf("%d %d\n",l,h);
for(i=l;i<=h;i++)
a[i]=max_num;
}
 
while(1)
{
int l,h,mmax=0,j,k;
int i;
for(i=0;i<n;i++)
if(b[i]!=max_num)
break;
if(i==n) break;
cnt1++;
for(i=0;i<n;i++)
{
for(j=i+1;j<n;j++)
{
int c=0;
for(k=i;k<=j;k++)
{
if(b[k]==max_num)
c++;
}
int num_elements=j-i+1;
if(c>=(num_elements+1)/2 && num_elements>mmax)
{
mmax=num_elements;
l=i;
h=j;
}
}
}
// printf("%d %d\n",l,h);
for(i=l;i<=h;i++)
b[i]=max_num;
}
printf("%d\n",min(cnt,cnt1));
}
}
