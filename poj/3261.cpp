/*
    author : VFVrPQ
    problem : poj3261,可重叠的k次最长重复子串
    solve : 二分答案mid,将height按mid分组，判定组内个数>=K
    time : 2017-09-14-20.03.45
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
const int N = 2e6+10;

//#define DEBUG
int t1[N],t2[N],c[N];
bool cmp(int *r,int a,int b,int l){
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *str,int *sa,int *Rank,int *height,int n,int m){
    n++;
    int i,j,p,*x=t1,*y=t2;
    for (i=0;i<m;i++) c[i]=0;
    for (i=0;i<n;i++) c[x[i]=str[i]]++;
    for (i=1;i<m;i++) c[i]+=c[i-1];
    for (i=n-1;i>=0;i--) sa[--c[x[i]]]=i;

    for (j=1;j<=n;j<<=1){
        p=0;
        for (i=n-j;i<n;i++) y[p++]=i;
        for (i=0;i<n;i++)if (sa[i]>=j)y[p++]=sa[i]-j;

        for (i=0;i<m;i++) c[i]=0;
        for (i=0;i<n;i++) c[x[y[i]]]++;
        for (i=1;i<m;i++) c[i]+=c[i-1];
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
    for (i=0;i<=n;i++)Rank[sa[i]]=i;
    for (i=0;i<n;i++){
        if (k)k--;
        j=sa[Rank[i]-1];
        while (str[i+k]==str[j+k])k++;
        height[Rank[i]]=k;
    }
}
int n,K;
int r[N],sa[N],Rank[N],height[N];
bool pd(int mid,int K){
    int now=0;
    for (int i=1;i<=n;i++)
        if (height[i]>=mid){
                now++;
                if (now>=K-1) return true;
        }else now=0;
    return false;
}


int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    while (scanf("%d%d",&n,&K)!=EOF){
        for (int i=0;i<n;i++) scanf("%d",&r[i]),r[i]++;
        r[n]=0;
        da(r,sa,Rank,height,n,1000010);

        //for (int i=1;i<=n;i++) printf("%d ",height[i]);puts("");
        int L=1,R=n,ans=0;
        while (L<=R){
            int mid=(L+R)>>1;
            if (pd(mid,K)) L=mid+1,ans=mid;
            else R=mid-1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
