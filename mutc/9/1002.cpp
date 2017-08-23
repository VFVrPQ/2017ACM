/*
author : VFVrPQ
problem :
solve :
time :
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;
vector< pair<int,int> > c;
vector<int> V[N];
int n,m;

struct Node{
    int s,t,a,f,id;
    Node(){}
    Node(int s,int t,int a,int f,int id):s(s),t(t),a(a),f(f),id(id){}
    bool operator < (const Node&x)const{
        return a<x.a;
    }
};

int Size[N],dep[N],fa[N],top[N];
int id[N];
int totn;
void dfs(int u,int f=-1){
    Size[u]=1;
    for (auto v:V[u]){
        if (v==f)continue;
        dep[v]=dep[u]+1;
        fa[v]=u;
        dfs(v,u);
        Size[u]+=Size[v];
    }
}
void dfs2(int u,int f=-1){
    id[u]=++totn;
    int myv=-1;
    for (auto v:V[u]){
        if (v==f)continue;
        if (myv==-1 || Size[myv]<Size[v]) myv = v;
    }
    if (myv==-1) return ;

    top[myv]=top[u];
    dfs2(myv,u);
    for (auto v:V[u]){
        if (v==f)continue;
        if (v==myv)continue;
        top[v]=v;
        dfs2(v,u);
    }
}

LL T[N<<2];
void build(int p,int L,int R){
    T[p]=0;
    if (L==R) return ;
    int m=(L+R)>>1;
    build(p<<1,L,m);
    build(p<<1|1,m+1,R);
}
void Insert(int p,int L,int R,int pos,int v){
    if (L==R){
        T[p]=v;
        return ;
    }
    int m=(L+R)>>1;
    if (pos<=m) Insert(p<<1,L,m,pos,v);
    else        Insert(p<<1|1,m+1,R,pos,v);

    T[p]=T[p<<1]+T[p<<1|1];
}
LL query(int p,int L,int R,int l,int r){
    if (L==l && R==r){
        return T[p];
    }
    int m=(L+R)>>1;
    if (r<=m) return query(p<<1,L,m,l,r);else
    if (m< l) return query(p<<1|1,m+1,R,l,r);else {
        LL ret1=query(p<<1,L,m,l,m);
        LL ret2=query(p<<1|1,m+1,R,m+1,r);
        return ret1+ret2;
    }
}
LL getSum(int s,int t){
    LL ans=0;
    while (1){
        int f1=top[s],f2=top[t];

        if (f1==f2){
            if (dep[s]>dep[t])swap(s,t);
            ans+=query(1,1,totn,id[s],id[t]);
            return ans;
        }
        if (dep[f1]>dep[f2]) swap(s,t),swap(f1,f2);
        //dep[f1]<dep[f2],s,t

        ans+=query(1,1,totn,id[f2],id[t]);
        t=fa[f2];
    }
}
Node Q[N<<1];
LL ans[N];
int main(){
    //freopen("1.txt","r",stdin);
    while (scanf("%d%d",&n,&m)!=EOF){
        c.clear();
        for (int i=0;i<n;i++){
            int x ; scanf("%d",&x);
            c.emplace_back(x,i);
        }
        sort(c.begin(),c.end());
        for (int i=0;i<n;i++) V[i].clear();
        for (int i=0;i<n-1;i++){
            int x,y;scanf("%d%d",&x,&y);x--;y--;
            V[x].push_back(y);
            V[y].push_back(x);
        }

        dep[0]=0;Size[0]=0;
        dfs(0,-1);
        totn=0;top[0]=0;dfs2(0);
        build(1,1,totn);


        //for (int i=0;i<n;i++) printf("%d:%d\n",i,id[i]);
        int cnt=0;
        for (int i=0;i<m;i++){
            int s,t,a,b;scanf("%d%d%d%d",&s,&t,&a,&b);
            s--;t--;
            Q[cnt++] = Node(s,t,a,-1,i);
            Q[cnt++] = Node(s,t,b+1,1,i);
        }


        sort(Q,Q+cnt);
        //for (int i=0;i<cnt;i++) printf("%d :%d %d\n",i,Q[i].s,Q[i].t);

        for (int i=0;i<m;i++)ans[i]=0;
        int hc=0;
        for (int i=0;i<cnt;i++){
            while (hc<n && c[hc].first < Q[i].a){
                Insert(1,1,totn,id[c[hc].second],c[hc].first);
                hc++;
            }
            ans[ Q[i].id ] += (LL)Q[i].f * getSum(Q[i].s,Q[i].t);

            //printf("%d %d %d\n",Q[i].id,Q[i].f,ans[ Q[i].id ]);
        }
        for (int i=0;i<m-1;i++) printf("%lld ",ans[i]);
        if (m) printf("%lld\n",ans[m-1]);
    }
    return 0;
}
