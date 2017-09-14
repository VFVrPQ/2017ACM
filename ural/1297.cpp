/*
    author : VFVrPQ
    problem : ural1297, 后缀数组求最长回文串
    solve : 将正序和反序拼接,设i为中心（奇数长度），则求i-1往前和i+1往后的最长公共子串即可；（偶数同理）
    time : 2017-09-14-20.09.50
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG
int t1[N],t2[N],c[N];
bool cmp(int *r,int a,int b,int l){
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int*str,int*sa,int*Rank,int*height,int n,int m){
    n++;
    int i,j,p,*x=t1,*y=t2;
    for (i=0;i<m;i++)c[i]=0;
    for (i=0;i<n;i++)c[x[i]=str[i]]++;
    for (i=1;i<m;i++)c[i]+=c[i-1];
    for (i=n-1;i>=0;i--)sa[--c[x[i]]]=i;

    for (j=1;j<=n;j<<=1){
        p=0;
        for (i=n-j;i<n;i++) y[p++]=i;
        for (i=0;i<n;i++) if (sa[i]>=j) y[p++]=sa[i]-j;

        for (i=0;i<m;i++)c[i]=0;
        for (i=0;i<n;i++)c[x[y[i]]]++;
        for (i=1;i<m;i++)c[i]+=c[i-1];
        for (i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];

        swap(x,y);
        p=1;x[sa[0]]=0;
        for (i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        if (p>=n)break;
        m=p;
    }
    int k=0;
    n--;
    for (int i=0;i<=n;i++) Rank[sa[i]]=i;
    for (int i=0;i<n;i++){
        if (k)k--;
        j=sa[Rank[i]-1];
        while (str[i+k]==str[j+k])k++;
        height[Rank[i]]=k;
    }
}
char str[N];
int r[N];
int sa[N],height[N],Rank[N];
int RMQ[20][N];
int askRMQ(int x,int y){
    if (x>y)swap(x,y);
    x++;
    int k=0;for (;(1<<k)<=y-x+1;k++);k--;
    return min(RMQ[k][x],RMQ[k][y-(1<<k)+1]);
}
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    scanf("%s",str);
    int n=strlen(str);
    for (int i=0;i<n;i++)r[i]=str[i];
    r[n]=1;
    for (int i=n+1;i<n+n+1;i++)r[i]=r[2*n-i];
    r[n+n+1]=0;
    da(r,sa,Rank,height,n+n+1,128);

    for (int i=0;i<=2*n+1;i++) RMQ[0][i]=height[i];
    for (int i=1;(1<<i)<=2*n+1;i++){
        for (int j=1;j+(1<<i)-1<=2*n+1;j++){
            RMQ[i][j]=min(RMQ[i-1][j],RMQ[i-1][j+(1<<i-1)]);
        }
    }
    //n=n*2+1;
    int MAX=1,id=0;
    for (int i=0;i<n;i++){
         if (i && i<n-1){//奇
             int r=askRMQ(Rank[2*n-(i-1)],Rank[i+1]);
             if (r*2+1>MAX || (r*2+1==MAX && id>i-r)){
                MAX=r*2+1;
                id=i-r;
             }
         }
         if (i<n-1){
            int r=askRMQ(Rank[2*n-i],Rank[i+1]);
            if (r*2>MAX || (r*2==MAX && id>i-r)){
                MAX=r*2;
                id=i-r+1;
            }
         }
    }
    str[id+MAX]=0;
    printf("%s",str+id);
    return 0;
}
