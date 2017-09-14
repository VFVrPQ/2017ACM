/*
    author : VFVrPQ
    problem : poj1743,最长不重叠子串，至少重复2次
    solve : 二分答案K，将height分组，判定组内sa[i]的最大距离>K
    time : 2017-09-14-19.57.00
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG
int t1[N],t2[N],c[N];
bool cmp(int *r,int a,int b,int l){
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *str,int *sa,int *Rank,int *height,int n,int m){
    n++;
    int i,j,p,*x=t1,*y=t2;
    for (i=0;i<m;i++)c[i]=0;
    for (i=0;i<n;i++)c[x[i]=str[i]]++;
    for (i=1;i<m;i++)c[i]+=c[i-1];
    for (i=n-1;i>=0;i--)sa[--c[x[i]]]=i;

    for (j=1;j<=n;j<<=1){
        p=0;
        for (i=n-j;i<n;i++)y[p++]=i;
        for (i=0;i<n;i++)if (sa[i]>=j) y[p++]=sa[i]-j;

        for (i=0;i<m;i++)c[i]=0;
        for (i=0;i<n;i++)c[x[y[i]]]++;
        for (i=1;i<m;i++)c[i]+=c[i-1];
        for (i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];

        swap(x,y);
        p=1;x[sa[0]]=0;
        for (i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        if (p>=n)break;
        m=p;
    }
    int k=0;
    n--;
    for (int i=0;i<=n;i++)Rank[sa[i]]=i;
    for (int i=0;i<n;i++){
        if (k)k--;
        j=sa[Rank[i]-1];
        while (str[j+k]==str[i+k])k++;
        height[Rank[i]]=k;
    }
}
int n;
int height[N],sa[N],Rank[N],r[N];
int pd(int mid){
    int MIN=M,MAX=0;
    for (int i=1;i<=n;i++){
        if (height[i]>=mid){
            MIN=min(MIN,sa[i]);MIN=min(MIN,sa[i-1]);
            MAX=max(MAX,sa[i]);MAX=max(MAX,sa[i-1]);
            if (MAX-MIN>mid) return true;
        }else{
            MIN=M;MAX=0;
        }
    }
    return false;
}
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    while (scanf("%d",&n)!=EOF && n){
        for (int i=0;i<n;i++) scanf("%d",&r[i]);
        for (int i=n-2;i>=0;i--) r[i+1]-=r[i];
        for (int i=0;i<n-1;i++)r[i]=r[i+1];
        for (int i=0;i<n-1;i++)r[i]+=100;
        n--;
        r[n]=0;
        da(r,sa,Rank,height,n,200);

        //for (int i=1;i<=n;i++) printf("%d ",height[i]);puts("");
        int ans=-1,L=4,R=n;
        while (L<=R){
            int mid=(L+R)>>1;
            if (pd(mid))L=mid+1,ans=mid;
            else R=mid-1;
        }
        printf("%d\n",ans+1);
    }
    return 0;
}
