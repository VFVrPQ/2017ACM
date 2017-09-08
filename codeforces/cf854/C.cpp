/*
    author : VFVrPQ
    problem : cf854-C, 共n(<=3e5)个飞机，i时间起飞的延迟一个单位需要ci花费。n个飞机延迟到了(k+1)-(k+n)的时间段，问在不早于已知起飞时间的情况下，最小的延迟费用和
    solve : 贪心，最先飞的花费要尽可能的大。枚举起飞时间，优先队列维护符合条件的最大费用和对应的起飞时间
    time : 2017-09-08-20.46.03
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 3e5+10;

//#define DEBUG

int c[N],res[N];
priority_queue< pair<int,int> > Q;
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG

    int n,K;scanf("%d%d",&n,&K);
    for (int i=1;i<=n;i++){
        scanf("%d",&c[i]);
    }
    int now=1;
    LL ans=0;
    for (int i=K+1;i<=K+n;i++){
        while (now<=n && now<=i){
            Q.emplace(c[now],now);now++;
        }
        pair<int,int> tmp = Q.top();Q.pop();
        ans+=(LL)tmp.first*(i-tmp.second);
        res[tmp.second] = i;
    }
    cout<<ans<<endl;
    for (int i=1;i<n;i++) printf("%d ",res[i]);printf("%d\n",res[n]);
    return 0;
}
