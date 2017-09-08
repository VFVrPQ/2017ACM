/*
    author : VFVrPQ
    problem : cf854-D, (n+1)个城市，1-n个城市的代表要到0城市开会，并且要开连续k个时间段的会。现已知m组数据，(d,f,t,c),(1<=d<=1e6;0<=f,t<=n;1<=c<=1e6)
                f=0表示从0城市到t城市，出发时间是d，花费是c；
                t=0表示从f城市到0城市，出发时间是d，花费是c；
              问如果有满足条件的时间段，最小花费是多少；否则输出-1.
    solve : 求前缀和和后缀和，然后枚举开会的开始时间搞一搞.前缀和表示当前n个城市（不一定是n个）到达0城市的最小费用，同时统计是否是n个城市；后缀和类似
    time : 2017-09-08-20.54.41
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e6+10;

vector< pair<pair<LL,LL>,LL> >a,b;
LL pre[N],nxt[N];
int prem[N],nxtm[N];//共有几个数
LL mask[N];
//#define DEBUG
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int n,m,K;
    scanf("%d%d%d",&n,&m,&K);
    for (int i=0;i<m;i++){
        int d,f,t,c;scanf("%d%d%d%d",&d,&f,&t,&c);
        if (f==0){
            b.emplace_back(make_pair(d,c),t);
        }else {
            a.emplace_back(make_pair(d,c),f);
        }
    }
    sort(a.begin(),a.end());
    int Size=0;
    for (int i=1;i<=1000000;i++){
        pre[i] = pre[i-1];
        prem[i] = prem[i-1];
        while (Size<a.size() && a[Size].first.first==i){
            if (!mask[a[Size].second]){
                mask[a[Size].second] = a[Size].first.second;
                pre[i] += a[Size].first.second;
                prem[i]++;
            }else if (mask[a[Size].second]>a[Size].first.second){
                pre[i] += a[Size].first.second - mask[a[Size].second];
                mask[a[Size].second] = a[Size].first.second;
            }
            Size++;
        }
    }
    sort(b.begin(),b.end());
    Size=b.size()-1;
    memset(mask,0,sizeof mask);
    for (int i=1000000;i>=1;i--){
        nxt[i] = nxt[i+1];
        nxtm[i] = nxtm[i+1];
        while (Size>=0 && b[Size].first.first==i){
            if (!mask[b[Size].second]){
                nxt[i] += b[Size].first.second;
                mask[b[Size].second] = b[Size].first.second;
                nxtm[i]++;
            }else if (mask[b[Size].second]>b[Size].first.second){
                nxt[i] += b[Size].first.second - mask[b[Size].second];
                mask[b[Size].second] = b[Size].first.second;
            }
            Size--;
        }
    }

    LL ans = 1LL<<60;
    for (int i=1;i+K+1<=1000000;i++){
        if (prem[i]!=n) continue;
        if (nxtm[i+K+1]!=n) break;
        ans=min(ans,pre[i]+nxt[i+K+1]);
    }
    printf("%I64d\n", (ans==(1LL<<60))? -1 : ans);
    return 0;
}
