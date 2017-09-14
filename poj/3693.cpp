/*
    author : VFVrPQ
    problem : poj3693,求重复次数最多的子串
    solve : 重复次数为1显然。考虑重复次数>=2,长度l,那么str[0],str[l],str[l+l],...必然有相邻的两个在答案里。
            枚举相邻两个，得到lcp=M, 答案是M/l+1.但它并不是最优的。可能起点和终点不是当前点。lcp多了M%l，或者说前面少了l-M%l,
            K=i*l+(l-M%l),再求一次。得到最大重复次数后，枚举sa得到最小值
    time : 2017-09-14-20.19.15
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
bool cmp(int*r,int a,int b,int l){
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
int t1[N],t2[N],c[N];
void da(int *str,int *sa,int*Rank,int*height,int n,int m){
    n++;
    int i,j,p,*x=t1,*y=t2;
    for(i=0;i<m;i++) c[i]=0;
    for(i=0;i<n;i++) c[x[i]=str[i]]++;
    for(i=1;i<m;i++) c[i]+=c[i-1];
    for(i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
    for(j=1;j<=n;j<<=1){
        p=0;
        for(i=n-j;i<n;i++)y[p++]=i;
        for(i=0;i<n;i++)if (sa[i]>=j) y[p++]=sa[i]-j;

        for(i=0;i<m;i++) c[i]=0;
        for(i=0;i<n;i++) c[x[y[i]]]++;
        for(i=1;i<m;i++) c[i]+=c[i-1];
        for(i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];

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
        while (str[i+k]==str[j+k])k++;
        height[Rank[i]]=k;
    }
}
char str[N];
int r[N],sa[N],height[N],Rank[N];
int rmq[20][N];
int ans[N];
int askRMQ(int x,int y){
    //assert(x!=y);
    if (x>y)swap(x,y);
    x++;
    int k=0;for (;(1<<k)<=y-x+1;k++);k--;
    return min(rmq[k][x],rmq[k][y-(1<<k)+1]);
}
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int Case=0;
    while (scanf("%s",str)!=EOF && str[0]!='#'){
        Case++;
        int n = strlen(str);
        for (int i=0;i<n;i++){
            r[i]=str[i];
        }
        r[n]='@';
        da(r,sa,Rank,height,n,128);

        //rmq
        for (int i=1;i<=n;i++) rmq[0][i]=height[i];
        for (int i=1;(1<<i)<=n;i++){
            for (int j=1;j+(1<<i)-1<=n;j++){
                rmq[i][j]=min(rmq[i-1][j],rmq[i-1][j+(1<<i-1)]);
            }
        }
        int bestcs=1,cnt=0;
        for (int l=1;l<=n;l++){
            for (int i=0;i+l<=n;i+=l){
                //i,i+l
                int r=askRMQ(Rank[i],Rank[i+l]);
                int t=r/l+1;
                if(bestcs<t){
                        bestcs=t;
                        cnt=0;
                        ans[cnt++]=l;
                }else
                if (bestcs==t) ans[cnt++]=l;
                int k=i-(l-r%l);
                if (k>=0&&r%l){
                    r=askRMQ(Rank[k],Rank[k+l]);
                    int t=r/l+1;
                    if(bestcs<t){
                            bestcs=t;
                            cnt=0;
                            ans[cnt++]=l;
                    }else
                    if (bestcs==t)ans[cnt++]=l;
                }
            }
        }
        int be=0,len=-1;
        for (int i=1;i<=n;i++){
            int st=sa[i];
            for (int j=0;j<cnt;j++){
                int l=ans[j];
                if (st+l<=n && askRMQ(Rank[st],Rank[st+l])/l+1>=bestcs){
                    be=st;len=l;break;
                }
            }
            if (len!=-1)break;
        }
        printf("Case %d: ",Case);
        for (int i=be;i<be+len*bestcs;i++)printf("%c",str[i]);
        puts("");
    }
    return 0;
}
/*
bcaeccdacdcadada
#
adad而不是cc.(得到最长的次数后，要用sa去寻找）
*/
