/*
    author : VFVrPQ
    problem : cf844-C,每次选择一个子序列（不重不漏）递增排序，使得最终结果是递增的，问最大次数。（n<=100000)
    solve : 每个元素排序前后的位置都是固定的，从排序前位置指向排序后的位置会形成简单环，环的个数就是最大次数
    time : 2017-08-25-08.19.30
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;

const int N = 1e5+10;
vector< pair<int,int> > a;
int b[N];
int vis[N];
int n;
vector<int>V[N];
int main(){
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        int x;scanf("%d",&x);x--;
        a.emplace_back(x,i);
    }
    sort(a.begin(),a.end());
    for (int i=0;i<n;i++)
        b[ a[i].second ] = i;
    int ans=0;
    for (int i=0;i<n;i++)if (!vis[i]){
        int j=i;
        while (!vis[j]){
            vis[j]=1;
            V[ans].push_back(j);
            j=b[j];
        }
        ans++;
    }
    printf("%d\n",ans);
    for (int i=0;i<ans;i++){
        printf("%d",V[i].size());
        for (auto j:V[i]) printf(" %d",j+1);
        puts("");
    }
    return 0;
}
