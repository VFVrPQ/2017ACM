/*
    author : VFVrPQ
    problem : 2017MUTC10-1010 Schedule
    solve : 答案的差异在于空隙，空隙越小越好；所以按start从小到大排序，相同按end小的排序；加入满足条件的机器，不满足增加一个机器(优先加到end时间最大的机器里，这样可以减少空隙）
    time : 2017-08-24-17.14.40
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int M = 1e9+7;
const int N = 100000+10;
const LL INF  = 1LL<<60;

int getInt()
{
    char c = getchar();int x=0;
    while (c>'9' || c<'0') c=getchar();
    while (1){
        x=x*10+c-'0';
        c=getchar();
        if (c>'9' || c<'0') return x;
    }
}
struct Node{
    int s,t;
    Node(){}
    Node(int s,int t):s(s),t(t){}
    bool operator < (const Node&a){
        return (s<a.s)||(s==a.s && t<a.t);
    }
};
Node a[N];
set< pair<int,int> > S;
int st[N],ed[N];
int n;
int main()
{
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d",&n);
        for (int i=0;i<n;i++)
            a[i].s = getInt(),a[i].t = getInt();
        sort(a,a+n);

        int ans1=0;
        S.clear();
        for (int i=0;i<n;i++){
            set< pair<int,int> >::iterator it = S.lower_bound(make_pair(a[i].s,M));

            if (it == S.begin()){
                st[ans1] = a[i].s;
                ed[ans1] = a[i].t;
                S.insert(make_pair(a[i].t,ans1));
                ans1++;
            }else{
                it--;
                //printf("%d %d %d %d\n",a[i].s,a[i].t,it->first,it->second);
                pair<int,int> pa(a[i].t,it->second);
                ed[it->second] = a[i].t;

                S.erase(it);
                S.insert(pa);
            }
        }

        LL ans2=0;
        for (int i=0;i<ans1;i++) ans2+=(LL)ed[i]-st[i];
        printf("%d %lld\n",ans1,ans2);
    }
    return 0;
}
