#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 60000+10;

double tag[N<<4],T[N<<4];
int n;
int a[N];
int last[N];
int b[N];
void build(int p,int L,int R,double v){
    tag[p]=0;
    if (L==R){
            T[p] = v*L;
            return ;
    }
    int mid=(L+R)>>1;
    build(p<<1,L,mid,v);
    build(p<<1|1,mid+1,R,v);
    T[p] = min(T[p<<1],T[p<<1|1]);
}
void pushdown(int p,int L,int R){
    if (tag[p]){
        T[p<<1] += tag[p];
        T[p<<1|1] += tag[p];
        tag[p<<1] += tag[p];
        tag[p<<1|1] += tag[p];
        tag[p] = 0;
    }
}
void Insert(int p,int L,int R,int l,int r,double v){
    if (L==l && R==r){
        T[p] +=v;
        tag[p] +=v;
        return ;
    }
    pushdown(p,L,R);
    int mid=(L+R)>>1;
    if (r <= mid) Insert(p<<1,L,mid,l,r,v);else
    if (mid < l) Insert(p<<1|1,mid+1,R,l,r,v);else{
        Insert(p<<1,L,mid,l,mid,v);
        Insert(p<<1|1,mid+1,R,mid+1,r,v);
    }
    T[p] = min(T[p<<1],T[p<<1|1]);
}
double getMin(int p,int L,int R,int l,int r){
    if (L==l && R==r){
        return T[p];
    }
    pushdown(p,L,R);
    int mid =(L+R)>>1;
    double ret;
    if (r <= mid) ret=getMin(p<<1,L,mid,l,r);else
    if (mid < l) ret=getMin(p<<1|1,mid+1,R,l,r);else{
        ret=min( getMin(p<<1,L,mid,l,mid), getMin(p<<1|1,mid+1,R,mid+1,r));
    }
    T[p] = min(T[p<<1],T[p<<1|1]);
    return ret;
}
int work(double mid){
    build(1,1,n,mid);
    for (int r=1;r<=n;r++){
        Insert(1,1,n,last[r]+1,r,1);//1
        double tmp = getMin(1,1,n,1,r);
        if (tmp<=mid*(r+1)) return 1;
    }
    return 0;
}
int main(){
    //freopen("1.txt","r",stdin);
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d",&n);
        for (int i=1;i<=n;i++)b[i]=0;
        for (int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            last[i] = b[ a[i]];
            b[a[i]] = i;

            //printf("last[%d]=%d\n",i,last[i]);
        }
        double L=0,R=1,ans;
        while (R-L>1e-5){
            double mid=(L+R)/2;
            if (work(mid)) ans=mid,R=mid;
            else L=mid;
        }
        printf("%.10lf\n",ans);
    }
    return 0;
}
