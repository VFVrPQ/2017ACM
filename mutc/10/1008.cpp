/*
    author : VFVrPQ
    problem : 2017MUTC10-1008 MONKEYS
    solve : 读入优化（fread(buf, 1, BUF_SIZE-1, stdin);）；增加一条边可以覆盖两只猴子较优，找出覆盖两只猴子的最大边数，剩下的增加一条边只增加一个点(练习的时候fread无法stdin输出，没调试，后来发现u用scanf读入QAQ，改成getInt就AC了）
    time : 2017-08-24-17.09.07
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int M = 1e9+7;
const int N = 100000+10;
const LL INF  = 1LL<<60;

const int BUF_SIZE = 100*1024*1024;
char buf[BUF_SIZE];
int buf_h=0;

vector<int> V[N];
int f[N][2];
int n,K;
int getInt()
{
    char c = buf[buf_h++];int x=0;
    while (c>'9' || c<'0') c=buf[buf_h++];
    while (1){
        x=x*10+c-'0';
        c=buf[buf_h++];
        if (c>'9' || c<'0') return x;
    }
}
void dfs(int u,int fa=-1)
{
    for (auto v:V[u]){
        if (v==fa) continue;
        dfs(v,u);

        f[u][0]+=f[v][1];
    }
    for (auto v:V[u]){
        if (v==fa) continue;

        f[u][1] = max(f[u][1], f[u][0]-f[v][1]+f[v][0]+2);
    }
}

int main()
{
    //FILE * fp = fopen("1.txt","r");
    fread(buf, 1, BUF_SIZE-1, stdin);
    int Case = getInt();
    while (Case--){
        n = getInt(); K = getInt();
        for (int i=0;i<n;i++) V[i].clear();
        for (int i=0;i<n-1;i++){
            int u;u=getInt();u--;
            V[u].push_back(i+1);
            V[i+1].push_back(u);
        }
        memset(f,0,sizeof f);
        dfs(0);

        int ans = max(f[0][0],f[0][1]);
        if (ans>=K) ans = (K+1)/2;
        else {
            ans=ans/2+K-ans;
        }
        printf("%d\n",ans);
    }
    return 0;
}
