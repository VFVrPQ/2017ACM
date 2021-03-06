/*
    author : VFVrPQ
    problem : spoj694,不相同的子串个数
    solve : 对(n-sa[i]-height[i])求和,1<=i<=n. n-sa[i]就是当前字符串的长度，-height[i]是和前面重叠部分
    time : 2017-09-14-20.07.09
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG
int t1[N],t2[N],c[N];
bool cmp(int*r,int a,int b,int l){
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
    for (i=0;i<=n;i++) Rank[sa[i]]=i;
    for (i=0;i<n;i++){
        if (k)k--;
        j=sa[Rank[i]-1];
        while (str[j+k]==str[i+k])k++;
        height[Rank[i]]=k;
    }
}
char str[N];
int r[N],Rank[N],sa[N],height[N];
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%s",str);
        int n=strlen(str);
        for (int i=0;i<n;i++) r[i]=str[i];
        r[n]=0;
        da(r,sa,Rank,height,n,128);

        LL ans=0;
        for (int i=1;i<=n;i++){
            ans+=n-sa[i]-height[i];
        }
        cout<<ans<<endl;
    }
    return 0;
}
