/*
    author : VFVrPQ
    problem : poj3415,给定K，字符串A,B(n<=1e5).求公共子串>=K的个数(求长度不小于k的公共子串个数)
    solve : 后缀数组，若子串的lcp是p,则对答案的贡献是p-K+1.那么我们拼接A,B,枚举height,以K分组，枚举到A压入栈中，枚举到B统计个数。B,A类似地统计一遍
    time : 2017-09-13-20.38.22
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
    //cout<<"n="<<n<<endl;
    //for (int i=0;i<=n;i++) printf("%c",str[i]);puts("");
    n++;
    int i,j,p,*x=t1,*y=t2;

    for (i=0;i<m;i++)c[i]=0;
    for (i=0;i<n;i++)c[x[i]=str[i]]++;
    for (i=1;i<m;i++)c[i]+=c[i-1];
    for (i=n-1;i>=0;i--)sa[ --c[x[i]]]=i;
    for (j=1;j<=n;j<<=1){
        p=0;
        for(i=n-j;i<n;i++)y[p++]=i;
        for(i=0;i<n;i++)if (sa[i]>=j) y[p++]=sa[i]-j;

        for(i=0;i<m;i++)c[i]=0;
        for(i=0;i<n;i++)c[x[y[i]]]++;
        for(i=1;i<m;i++)c[i]+=c[i-1];
        for(i=n-1;i>=0;i--) sa[ --c[x[y[i]]]]=y[i];

        swap(x,y);
        p=1;x[sa[0]]=0;
        for(i=1;i<n;i++)
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
char str[N];
int sa[N],Rank[N],height[N],r[N];
int len[N],belong[N];
LL sta[N],sta2[N];//val,num
int st,ed;
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int K;
    while (scanf("%d",&K)!=EOF && K){
        int cnt=0;
        for (int i=0;i<2;i++){
            if (i) r[cnt]='#',len[cnt]=0,belong[cnt]=-1,cnt++;
            scanf("%s",str);
            int n=strlen(str);
            for (int j=0;str[j];j++){
                r[cnt]=str[j];
                len[cnt]=n-j;
                belong[cnt]=i;
                cnt++;
            }
        }
        r[cnt]='@';len[cnt]=0;belong[cnt]=-1;

        da(r,sa,Rank,height,cnt,128);

        for (int i=0;i<=cnt;i++){
                //printf("%4d",sa[i]);
                height[i]=min(height[i],len[sa[i]]);
                //printf("%4d",height[i]);
        }
        //puts("");

        LL ans=0;
        for (int f=0;f<2;f++){
            st=ed=0;
            LL sum=0;
            for (int i=0;i<=cnt;i++){
                if (belong[sa[i]]==-1)continue;
                LL num=0;
                while (st<ed && sta[ed-1]>=height[i]){
                    sum-=(sta[ed-1]-K+1)*sta2[ed-1];
                    num+=sta2[ed-1];
                    ed--;
                }
                if (height[i]>=K && num){
                    sta[ed]=height[i];sta2[ed]=num;ed++;
                    sum+=(height[i]-K+1)*num;
                }
                if (belong[sa[i]]==f)ans+=sum;
                else if (len[sa[i]]>=K){//len[sa[i]]>=height[i]
                    sta[ed]=len[sa[i]];sta2[ed]=1;ed++;
                    sum+=len[sa[i]]-K+1;
                }
                //printf("%d %d %lld\n",f,i,sum);
            }
            //cout<<"ans="<<ans<<endl;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
