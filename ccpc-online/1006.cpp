#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N=1e5+10;
const int M = 1e9+7;
struct Tree{
    LL a,b,c,d,e,f,tag;
    Tree(){}
    Tree(LL a,LL b,LL c,LL d,LL e,LL f,LL tag):a(a),b(b),c(c),d(d),e(e),f(f),tag(tag){}
}T[N<<2];

char str[N];

LL mul(LL a,LL b){
    return a*b%M;
}
LL add(LL a,LL b){
    return (a+b)%M;
}
//x:p,q,r,u,v,w
//y:a,b,c,d,e,f
Tree calc(Tree x,Tree y,int tag)
{
    return Tree(add(mul(y.a,x.a),mul(y.b,x.d)),add(mul(y.a,x.b),mul(y.b,x.e)),add(add(mul(y.a,x.c),mul(y.b,x.f)),y.c),
                add(mul(y.d,x.a),mul(y.e,x.d)),add(mul(y.d,x.b),mul(y.e,x.e)),add(add(mul(y.d,x.c),mul(y.e,x.f)),y.f),tag);
}
void build(int p,int L,int R)
{

    if (L==R){
        if (str[L]=='0'){
            T[p].a=1;
            T[p].b=1;
            T[p].c=1;
            T[p].d=0;
            T[p].e=1;
            T[p].f=0;
            T[p].tag=0;
        }else{
            T[p].a=1;
            T[p].b=0;
            T[p].c=0;
            T[p].d=1;
            T[p].e=1;
            T[p].f=1;
            T[p].tag=0;
        }
        return ;
    }
    int m = (L+R)>>1;
    build(p<<1,L,m);
    build(p<<1|1,m+1,R);

    T[p] = calc(T[p<<1],T[p<<1|1],0);
}
void pushdown(int p,int L,int R)
{
    if (T[p].tag){
        swap(T[p<<1].a,T[p<<1].e);
        swap(T[p<<1].b,T[p<<1].d);
        swap(T[p<<1].c,T[p<<1].f);
        swap(T[p<<1|1].a,T[p<<1|1].e);
        swap(T[p<<1|1].b,T[p<<1|1].d);
        swap(T[p<<1|1].c,T[p<<1|1].f);
        T[p<<1].tag^=1;
        T[p<<1|1].tag^=1;
        T[p].tag=0;
    }
}
void flip(int p,int L,int R,int l,int r)
{
    if (l==L && R==r){
        swap(T[p].a,T[p].e);
        swap(T[p].b,T[p].d);
        swap(T[p].c,T[p].f);
        T[p].tag^=1;
        return ;
    }
    pushdown(p,L,R);

    int m = (L+R)>>1;
    if (r<=m) flip(p<<1,L,m,l,r);else
    if (m< l) flip(p<<1|1,m+1,R,l,r);else{
        flip(p<<1,L,m,l,m);
        flip(p<<1|1,m+1,R,m+1,r);
    }

    T[p] = calc(T[p<<1],T[p<<1|1],T[p].tag);
}
Tree query(int p,int L,int R,int l,int r)
{
    if (l==L && R==r) return T[p];
    pushdown(p,L,R);

    int m = (L+R)>>1;
    Tree ret;
    if (r<=m) ret=query(p<<1,L,m,l,r);else
    if (m< l) ret=query(p<<1|1,m+1,R,l,r);else{
        Tree ret1=query(p<<1,L,m,l,m);
        Tree ret2=query(p<<1|1,m+1,R,m+1,r);
        ret=calc(ret1,ret2,0);
    }
    T[p] = calc(T[p<<1],T[p<<1|1],T[p].tag);
    return ret;
}
int main()
{
    //freopen("1.txt","r",stdin);
    int Case;scanf("%d",&Case);
    while (Case--){
        int n,Q;
        scanf("%d%d",&n,&Q);
        scanf("%s",str+1);

        build(1,1,n);

        while (Q--){
            int type,l,r;
            scanf("%d%d%d",&type,&l,&r);
            if (type==1){
                flip(1,1,n,l,r);
            }else {
                Tree tmp = query(1,1,n,l,r);
                printf("%lld\n",add(tmp.c,tmp.f));
                //printf("%lld\n",add(T[1].c,T[1].f));
            }
        }
    }
    return 0;
}
