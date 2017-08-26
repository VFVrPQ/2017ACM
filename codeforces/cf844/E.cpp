/*
    author : VFVrPQ
    problem : cf844-E ,将树通过指定方法转化成所有点对距离平方最小的树，<=2*n步转化
    solve : 找到树的重心(n为奇数只有1个，n为偶数有两个),重心的儿子转化成菊花状的最优
    time : 2017-08-25-16.00.29
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 2e5+10;

int c1=-1,c2=-1;
vector<int> V[N];
int n;
int dfs(int u,int p=-1){
    int s=1;
    for (auto v:V[u])if (v^p){
        s+=dfs(v,u);
    }
    if (c1 == -1 && 2*s>=n){
        c1=u;
        if (s*2==n) c2=p;
        else c2=-1;
    }
    return s;
}
struct Trees{
    int root;
    int curRoot;
    int par;
    vector< pair<int,int> > V;
};
vector<Trees> trees;
struct Triple{
    int x,y,z;
};
vector<Triple> ans;

void Find(int u,int p=-1){
    for (auto v:V[u])if (v^p){
        Find(v,u);
    }
    trees.back().V.emplace_back(u,p);
}
int main(){
    scanf("%d",&n);
    for (int i=0;i<n-1;i++){
        int x,y;scanf("%d%d",&x,&y);x--;y--;
        V[x].push_back(y);
        V[y].push_back(x);
    }
    dfs(0);

    //printf("%d %d\n",c1,c2);
    for (auto u:V[c1]){
        if (u==c2)continue;
        trees.emplace_back();
        trees.back().curRoot = u;
        trees.back().root = u;
        trees.back().par = c1;
        Find(u,c1);
    }
    if (c2!=-1){
        for (auto u:V[c2]){
            if (u==c1)continue;
            trees.emplace_back();
            trees.back().curRoot = u;
            trees.back().root = u;
            trees.back().par = c2;
            Find(u,c2);
        }
    }
    for (Trees& tree:trees){
        for (auto pa:tree.V){
            int u=pa.first, p = pa.second;
            if (u==tree.root) break;
            ans.push_back({tree.par, tree.curRoot, u});
            tree.curRoot = u;
            ans.push_back({u, p, tree.root});
        }
        ans.push_back({tree.par, tree.curRoot, tree.root});
    }
    printf("%d\n",ans.size());
    for (auto i:ans){
        printf("%d %d %d\n",i.x+1,i.y+1,i.z+1);
    }
    return 0;
}
