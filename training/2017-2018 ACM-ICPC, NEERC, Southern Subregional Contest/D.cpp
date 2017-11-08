/*
    author : VFVrPQ
    problem : codeforces847-J Dog Show,狗狗竞吃大赛，有n碗饭，每碗饭相距1，放在x轴的[1,n]上，i位置的饭要ti时间后才能吃，狗狗从0出发，只能向+1的方向走，在T时间内最多能吃到多少碗。
    solve : 有些饭需要等待，那么我们总能找到等待时间最长的位置，枚举这个位置，其他位置根据相对时间可以算得。还有一种直接走过去。
    time : 2017-11-08-18.37.12
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 2e5+10;

//#define DEBUG
int n,T;
int a[N];
struct Tree{
    int l,r,s;
    void init(){
        l=r=s=0;
    }
};
int cnt;
Tree myT[N*30];
void Insert(int &p,int l,int r,int v){
    cnt++;myT[cnt]=myT[p];
    myT[cnt].s++;

    p=cnt;
    if (l==r) return ;
    int m=(l+r)>>1;
    if (v<=m) Insert(myT[p].l,l,m,v);
    else      Insert(myT[p].r,m+1,r,v);
}
int Find(int p,int L,int R,int l,int r){//[l,r]的个数
    if (p==0) return 0;//有些点没有定义
    if (L==l && R==r){
        return myT[p].s;
    }
    int m=(L+R)>>1;

    int ret=0;
    if (r<=m) ret=Find(myT[p].l,L,m,l,r);
    else if (m< l) ret=Find(myT[p].r,m+1,R,l,r);
    else {
        ret=Find(myT[p].l,L,m,l,m)+Find(myT[p].r,m+1,R,m+1,r);
    }
    return ret;
}
vector<int>y;
int Root[N];
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    scanf("%d%d",&n,&T);

    for (int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        y.push_back(a[i]-i);
    }

    y.push_back(0);
    sort(y.begin(),y.end());
    y.erase(unique(y.begin(),y.end()),y.end());

    cnt=0;Root[0]=0;
    for (int i=1;i<=n;i++){
        Root[i]=Root[i-1];
        Insert(Root[i],1,y.size(),lower_bound(y.begin(),y.end(),a[i]-i)-y.begin()+1);
    }

    int l=1,r=min(T-1,n);
    int ans=Find(Root[r],1,y.size(),1,lower_bound(y.begin(),y.end(),0)-y.begin()+1);

    for (int i=1;i<=n;i++){
        if (a[i]-i>=0){
            int r = min(T-a[i]+i-1,n);
            int l = 1;
            if (l>r) continue;//防止太小

            int ret=Find(Root[r],1,y.size(),1,lower_bound(y.begin(),y.end(),a[i]-i)-y.begin()+1);
            ans=max(ans,ret);
        }
    }
    printf("%d\n",ans);
    return 0;
}
