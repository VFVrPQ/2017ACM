/*
    author : VFVrPQ
    problem : 给n(<=5000)个点，m(<=5000)条无向边的图，将所有的无向边改成有向边，问所有方案中出度最大的最小值是多少。
    solve : 二分，然后网络流，S->e(e是边）:流量为1；e->u,e->v，流量为1；u->u'，流量为mid；u'->T，无穷。
    time : 2017-11-08-19.48.29
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 2e4+10;
const int E = 1e5+10;
//#define DEBUG

int n,m;

int S=0,T=2*n+1;
int num;
int Vet[E],Len[E],Next[E],Head[N];
struct Edge{
    int u,v;
    Edge(){}
    Edge(int u,int v):u(u),v(v){}
};
Edge edges[E];
void add(int u,int v,int w){
    num++;Vet[num]=v;Len[num]=w;Next[num]=Head[u];Head[u]=num;
    num++;Vet[num]=u;Len[num]=0;Next[num]=Head[v];Head[v]=num;
}
int bz[E];
int cnt;
int dis[N];
bool dinic_bfs(){
    int tot=cnt;
    for (int i=0;i<tot;i++) dis[i]=M;
    dis[S]=0;
    queue<int>Q;Q.push(S);
    while (!Q.empty()){
        int u = Q.front();Q.pop();
        for (int e=Head[u];e!=-1;e=Next[e]){
            int v=Vet[e];
            if (e<4*m && bz[e/4] && e%2==0) continue;//边不能重复选
            if (Len[e] && dis[v]==M){
                dis[v]=dis[u]+1;
                Q.push(v);
            }
        }
    }
    return dis[T]!=M;
}
int dinic_dfs(int u,int flow){
    if (u==T) return flow;
    int ret=0;
    for (int e=Head[u];e!=-1;e=Next[e]){
        if (dis[u]+1==dis[Vet[e]] && Len[e]){
            //if (e<4*m && bz[e/4] && e%2==0) continue;//边不能重复选
            int tmp = dinic_dfs(Vet[e],min(flow-ret,Len[e]));
            if (tmp){
                Len[e]-=tmp;
                Len[e^1]+=tmp;
                ret+=tmp;

                /*if (e<4*m){
                    if (e%2==0) bz[e/4]=1;
                    else bz[e/4]=0;
                }*/
            }
        }
    }
    return ret;
}
int dinic(){
    int sum=0;
    while (dinic_bfs()){
        sum += dinic_dfs(S,M);
    }
    return sum;
}
vector<pair<int,int>>ans;
bool pd(int mid){
    memset(Head,-1,sizeof Head);
    num=-1;
    S=0;T=2*n+1;


    for (int i=0;i<m;i++){
        add(1+i+2*n+1,edges[i].u,1);//0,1
        add(1+i+2*n+1,edges[i].v,1);//2,3
    }
    for (int i=0;i<m;i++){
        add(S,1+i+2*n+1,1);
    }
    for (int i=1;i<=n;i++){
        add(i,i+n,mid);
    }
    for (int i=1;i<=n;i++){
        add(i+n,T,M);
    }
    //printf("***\n");
    //for (int i=0;i<4*m;i++) bz[i]=0;
    cnt=2*n+m+2;
    int ret = dinic();
    assert(ret<=m);
    if (ret==m){
            ans.clear();
            for (int i=0;i<m;i++){
                    //printf("%d %d %d %d\n",Vet[4*i],Vet[4*i+1],Vet[4*i+2],Vet[4*i+3]);
                if (Len[4*i]==0) ans.emplace_back(Vet[4*i],Vet[4*i+2]);
                else ans.emplace_back(Vet[4*i+2],Vet[4*i]);
            }
            return true;
    }
    else return false;
}
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    scanf("%d%d",&n,&m);
    if (m==0){
        puts("0");return 0;
    }
    for (int i=0;i<m;i++){
        int u,v;scanf("%d%d",&u,&v);
        edges[i]=Edge(u,v);
    }
    int L=1,R=n,myans=n;
    while (L<=R){
        int mid=(L+R)>>1;
        if (pd(mid)) R=mid-1,myans=mid;
        else L=mid+1;
    }
    printf("%d\n",myans);
    for (int i=0;i<ans.size();i++) printf("%d %d\n",ans[i].first,ans[i].second);
    return 0;
}
