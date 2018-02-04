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
int minLen[N];

void dijkstra(int n){
    for (int i=1;i<=n;i++) dist[i]=M;
    dist[1]=0;

    Q.push(Node(1,0));
    while (!Q.empty()){
        Node tmp = Q.top();Q.pop();

        int u=tmp.v;
        for (int i=0;i<V[u].size();i++){
            int v=V[u][i],w=W[u][i];
            if (dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                minLen[v]=w;
                Q.push(Node(v,dist[v]));
            }else
            if (dist[v]==dist[u]+w){
                minLen[v]=min(minLen[v],w);
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

    int ans=0;
    for (int i=2;i<=n;i++) ans+=minLen[i];
    printf("%d\n",ans);
    return 0;
}
