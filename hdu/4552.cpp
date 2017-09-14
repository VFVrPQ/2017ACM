/*
    author : VFVrPQ
    problem : hdu4552，怪盗基德的挑战书
    solve : 每个后缀和原串求lcp的长度，累加即可（kmp也可以做）
    time : 2017-09-14-20.35.45
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

int t1[N],t2[N],c[N];
bool cmp(int*r,int a,int b,int l){
    return r[a] == r[b] && r[a+l] == r[b+l];
}
int da(int str[],int sa[],int Rank[],int height[],int n,int m)
{
    n++;
    int i,j,p, *x= t1, *y=t2;
    for (i=0;i<m;i++) c[i]=0;
    for (i=0;i<n;i++) c[ x[i]=str[i] ]++;
    for (i=1;i<m;i++) c[i]+=c[i-1];
    for (i=n-1;i>=0;i--) sa[ --c[x[i]] ] = i;
    for (j=1;j<=n;j<<=1){
        p=0;
        for (i=n-j;i<n;i++) y[p++]=i;
        for (i=0;i<n;i++) if (sa[i]>=j) y[p++]=sa[i]-j;

        for (i=0;i<m;i++)c[i]=0;
        for (i=0;i<n;i++)c[x[y[i]]]++;
        for (i=1;i<m;i++)c[i]+=c[i-1];
        for (i=n-1;i>=0;i--) sa[ --c[x[y[i]]]] = y[i];

        swap(x,y);
        p = 1;x[sa[0]]=0;
        for (i=1;i<n;i++)
            x[sa[i]] = cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        if (p>=n) break;
        m=p;
    }
    int k=0;
    n--;
    for (i=0;i<=n;i++) Rank[ sa[i]] = i;
    for (i=0;i<n;i++){
        if (k)k--;
        j = sa[Rank[i]-1];
        while (str[j+k]==str[i+k])k++;
        height[Rank[i]]=k;
    }
}
int r[N],sa[N],Rank[N],height[N];
char str[N];
int RMQ[20][N];
int askRMQ(int x,int y){
    assert( x != y);
    if (x>y) swap(x,y);
    x++;
    int k=0;for (;(1<<k)<=y-x+1;k++); k--;
    return min(RMQ[k][x],RMQ[k][y-(1<<k)+1]);
}
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG

    while (scanf("%s",str)!=EOF){
        int n = strlen(str);

        for (int i=0;i<n;i++) r[i] = str[i]-'a'+1;
        r[n]=0;
        da(r,sa,Rank,height,n,27);

        for (int i=1;i<=n;i++){
            //printf("%d %d\n",i,height[i]);
        }
        for (int i=1;i<=n;i++) RMQ[0][i] = height[i];
        for (int i=1;(1<<i)<=n;i++){
            for (int j=1;j+(1<<i)-1<=n;j++){
                RMQ[i][j]=min(RMQ[i-1][j],RMQ[i-1][j+(1<<i-1)]);
            }
        }

        int ans = n % 256;
        for (int i=1;i<n;i++){
            int t = askRMQ(Rank[0],Rank[i]);
            t = min(n-i,t);
            ans = (ans + t) % 256;
        }
        printf("%d\n",ans);
    }
    return 0;
}
