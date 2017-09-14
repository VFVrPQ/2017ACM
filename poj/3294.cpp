/*
    author : VFVrPQ
    problem : poj3294,出现在不少于K个字符串的最长子串
    solve : 拼接，二分答案mid, 将height数组分块，若有一块内不同字符串个数>=K，则存在最长子串
    time : 2017-09-14-20.25.39
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 2e5+10;

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
    for (i=n-1;i>=0;i--) sa[ --c[x[i]]] = i;

    for (j=1;j<=n;j<<=1){
        p=0;
        for (i=n-j;i<n;i++) y[p++] = i;
        for (i=0;i<n;i++) if (sa[i]>=j) y[p++]=sa[i]-j;

        for (i=0;i<m;i++) c[i]=0;
        for (i=0;i<n;i++) c[x[y[i]]]++;
        for (i=1;i<m;i++) c[i]+=c[i-1];
        for (i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];

        swap(x,y);
        p=1;x[sa[0]]=0;
        for (i=1;i<n;i++)
            x[sa[i]] = cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        if (p>=n)break;
        m=p;
    }

    int k=0;
    n--;
    for (i=0;i<=n;i++) Rank[sa[i]]=i;
    for (i=0;i<n;i++){
        if (k)k--;
        int j=sa[Rank[i]-1];
        while (str[i+k]==str[j+k])k++;
        height[Rank[i]]=k;
    }
}
int belong[N],len[N],height[N],sa[N],Rank[N];
int r[N];
bool vis[100+10];
bool solve(int *str,int mid,int n,int K,int f){
    //标记个数要>=K
    int st = 1;
    while (st<=n){
        while (st<=n && (belong[sa[st]]==-1 || height[st]<mid)) st++;
        if (st>n) break;

        int ed = st + 1, tot = 0 ;
        memset(vis,0,sizeof vis);
        tot=1;vis[ belong[sa[st-1]]]=1;
        if (!vis[ belong[sa[st]]])tot++,vis[belong[sa[st]]]=1;
        while (ed<=n && height[ed]>=mid){
                if (!vis[belong[sa[ed]]])tot++,vis[belong[sa[ed]]]=1;
                ed++;
        }

        if (tot>=K){
            if (f==0) return true;else{
                //print
                int beg = sa[st];
                for (int i=beg;i<beg+mid;i++) printf("%c",str[i]+'a'-2);
                puts("");
            }
        }
        st=ed;
    }
    return false;
}
char str[1000+10];
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int Case=0;
    int n;
    while (scanf("%d",&n)!=EOF && n){
        Case++;if (Case>1) puts("");

        int cnt=0;
        for (int i=0;i<n;i++){
            scanf("%s",str);
            if (i) r[cnt]=0,belong[cnt]=-1,len[cnt]=0,cnt++;
            int slen= strlen(str);
            for (int j=0;str[j];j++){
                    r[cnt]=str[j]-'a'+2;
                    belong[cnt]=i;
                    len[cnt]=slen-j;
                    cnt++;
            }
        }
        r[cnt]=1;belong[cnt]=-1;len[cnt]=0;

        //for (int i=0;i<=cnt;i++)printf("%d",r[i]);puts("");
        if (n==1){
            for (int i=0;i<cnt;i++) printf("%c",r[i]+'a'-2);puts("");
            continue;
        }
        da(r,sa,Rank,height,cnt,28);

        for (int i=0;i<=cnt;i++) height[i]=min(height[i],len[sa[i]]);
        int L=1,R=1000,ans=-1;
        while (L<=R){
            int mid=(L+R)>>1;
            if (solve(r,mid,cnt,n/2+1,0)) L=mid+1,ans=mid;
            else R=mid-1;
        }
        if (ans<=0) {puts("?");continue;}
        solve(r,ans,cnt,n/2+1,1);
    }
    return 0;
}
