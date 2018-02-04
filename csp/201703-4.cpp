#include<bits/stdc++.h>

using namespace std;

const int N = 1e5+10;
const int M = 1e9+7;

vector<int>V[N],W[N];


struct Node{
    int v,w;
    Node(){}
    Node(int v,int w):v(v),w(w){}
    bool operator < (const Node&a)const{
        return w>a.w;
    }
};
priority_queue<Node> Q;//×îÐ¡¶Ñ

int dist[N];
int vis[N];
void dijkstra(int n){
    for (int i=1;i<=n;i++) dist[i]=M,vis[i]=0;
    dist[1]=0;

    Q.push(Node(1,0));
    while (!Q.empty()){
        Node tmp = Q.top();Q.pop();

        int u=tmp.v;
        if (vis[u])continue;//保证每个点访问一次
        vis[u]=1;

        for (int i=0;i<V[u].size();i++){
            int v=V[u][i],w=W[u][i];
            if (dist[v]>max(dist[u],w)){
                dist[v]=max(dist[u],w);
                Q.push(Node(v,dist[v]));
            }
        }
    }
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=0;i<m;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        V[u].push_back(v);
        W[u].push_back(w);
        V[v].push_back(u);
        W[v].push_back(w);
    }
    dijkstra(n);

    printf("%d\n",dist[n]);
    return 0;
}
