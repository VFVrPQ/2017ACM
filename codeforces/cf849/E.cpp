/*
    author : VFVrPQ
    problem : cf849-E ,Difference between last occurrence and first occurrence equals the sum of differences between pairs of adjacent occurrences. Handle this with some segment tree
                给定一个数组n，和若干询问Q, (n,Q<=1e5, a[i]<=1e5)
                1.修改位置的值，变成x(1<=x<=n);
                2.询问区间内 同一个值第一次出现和最后一次出现的差值 的和。
    solve : 线段树套树状数组（第一次写，改了好久QAQ）。首先，对于同一个值在区间内的差值可以转化为相邻位置的差值之和。所以对于询问[l,r]，答案是sigma{i-pre[i]},其中pre[i]>=l。
            建一棵序号线段树，每个节点建一棵数值树状数组；每次询问 树状数组给出val>=的值.需要用数据结构维护一下额外的东西
    time : 2017-09-03-13.35.29
*/
#include <bits/stdc++.h>

using namespace std;

//#define DEBUG
const int N = 100000+10;

typedef long long LL;
struct Query{
    int t,l,r;
    Query(int t=0,int l=0,int r=0):t(t),l(l),r(r){}
};
vector<Query> Que;

int n,Q;
int pr[N];
int a[N],aa[N];
int ls[N];
vector<int> vars[N*4];
vector<LL> T[N*4];
set<int> ids[N*4];
LL Tsum[N*4];
#ifdef DEBUG
int maxp = 0;
#endif // DEBUG

void addSTF(int p,int pos,int n,int val){
    Tsum[p]+=val;
    for (;pos<=n;pos+=pos&(-pos))
        T[p][pos]+=val;
}
void build(int k,int p,int l,int r)
{
    #ifdef DEBUG
    maxp = max(maxp,p);
    #endif // DEBUG
    for (int i=l;i<=r;i++){
        if (k==0){
            vars[p].push_back(pr[i]);
        }else{
            int pos = int(lower_bound(vars[p].begin(),vars[p].end(),pr[i])-vars[p].begin());
            assert(pos != vars[p].size());
            pos++;
            addSTF(p,pos,int(vars[p].size()),i-pr[i]);
        }
    }
    if (l == r) return ;
    int mid=(l+r)>>1;
    build (k,p<<1,l,mid);
    build (k,p<<1|1,mid+1,r);
}
void updateST(int k,int p,int l,int r,int pos,int pos2,int val){
    if (k==0){
        vars[p].push_back(pos2);
    }else{
        int mypos = int(lower_bound(vars[p].begin(),vars[p].end(),pos2)-vars[p].begin());
        assert(mypos != vars[p].size());
        mypos++;
        addSTF(p,mypos,int(vars[p].size()),val);
    }
    if (l==r) return ;
    int m = (l+r)>>1;
    if (pos<=m) updateST(k,p<<1,l,m,pos,pos2,val);
    else        updateST(k,p<<1|1,m+1,r,pos,pos2,val);
}
void DeleteST(int k,int l){
    updateST(k,1,1,n,l,pr[l],-(l-pr[l]) );

    auto it_np = ids[ a[l] ].upper_bound(l);

    if (it_np != ids[ a[l] ].end()){
        int np = *it_np;

        updateST(k,1,1,n,np,pr[np],-(np-pr[np]));

        pr[np] = pr[l];
        updateST(k,1,1,n,np,pr[np],np-pr[np]);
    }
    ids[ a[l] ].erase(l);
    pr[l]=0;
    a[l]=0;
}
void InsertST(int k,int l,int val){

    auto it_np = ids[val].upper_bound(l);

    int pre = 0;
    if (it_np != ids[val].end()){
        int np = *it_np;

        updateST(k,1,1,n,np,pr[np],-(np-pr[np]));

        pre = pr[np];

        pr[np] = l;
        updateST(k,1,1,n,np,pr[np],(np-pr[np]));
    }else
    if (it_np != ids[val].begin()){
        it_np--;
        pre = *it_np;
    }

    pr[l] = pre;
    a[l] = val;
    updateST(k,1,1,n,l,pr[l],(l-pr[l]));

    ids[val].insert(l);
}
LL getSumSTF(int p,int pos){
    LL ret=0;
    for (;pos;pos-=pos&(-pos))
        ret+=T[p][pos];
    return ret;
}
LL getSum(int p,int l,int r,int L,int R,int myL){
    if (l==L && R==r){
        int pos = int(lower_bound(vars[p].begin(),vars[p].end(),myL) - vars[p].begin());
        return Tsum[p]-getSumSTF(p,pos);
    }
    int mid=(l+r)>>1;
    LL ret=0;
    if (L<=mid)
        ret += getSum(p<<1,l,mid,L,min(mid,R),myL);
    if (mid< R)
        ret += getSum(p<<1|1,mid+1,r,max(L,mid+1),R,myL);

    return ret;
}
int main()
{
#ifdef DEBUG
    freopen("1.txt","r",stdin);
#endif // DEBUG
    scanf("%d%d",&n,&Q);
    for (int i=1;i<=n;i++){
        scanf("%d",&aa[i]);
    }
    for (int i=1;i<=Q;i++){
        int t,l,r;scanf("%d%d%d",&t,&l,&r);
        Que.emplace_back(t,l,r);
    }


    for (int k=0;k<2;k++){

        if (k){//initial
            for (int i=1;i<=n;i++) ids[i].clear(),ls[i]=0;

            for (int i=0;i<4*N;i++)if (vars[i].size()>=1){

                sort(vars[i].begin(),vars[i].end());
                vars[i].erase(unique(vars[i].begin(),vars[i].end()),vars[i].end());

                T[i].assign(vars[i].size()+1,0);
            }

            #ifdef DEBUG
//                printf("maxp=%d\n",maxp);
//                for (int i=1;i<=maxp;i++){
//                    printf("%d:",i);
//                    for (auto var:vars[i]){
//                        printf("%d ",var);
//                    }
//                    puts("");
//                }
            #endif // DEBUG
        }
        for (int i=1;i<=n;i++) a[i]=aa[i];
        for (int i=1;i<=n;i++){
                pr[i] = ls[ a[i] ];
                ls[ a[i] ] =i;
                ids[a[i]].insert(i);
        }

        build(k,1,1,n);//ok

        for (int i=0;i<Q;i++){
            int t,l,r; t=Que[i].t;l=Que[i].l;r=Que[i].r;
            if (t==1){
                DeleteST(k,l);
                InsertST(k,l,r);
            }else{
                if (k) printf("%I64d\n",getSum(1,1,n,l,r,l));
            }
        }

    }
    return 0;
}
