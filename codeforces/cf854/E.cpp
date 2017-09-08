/*
    author : VFVrPQ
    problem : cf854-E,n*n的网格有n个点，横坐标从1->n,纵坐标题目输入（也是1-n），n个点各不相同。
              定义beautiful rectangle为矩阵的两个对角分别有两个点(共n*(n-1)/2个矩阵）。
              每次给出一个矩阵左下角(l,d),右上角(r,u)，询问与多少个beautiful rectangle相交
              n,q<=2e5
    solve : 直接求比较难，考虑总的-不成立的。总的是n*(n-1)/2,不成立的是四个边-四个小角。每次用主席树求解横坐标[l,r]，纵坐标[d,u]内点的个数。

    time : 2017-09-08-21.04.19
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 2e5+10;

//#define DEBUG
int p[N];
int root[N];
struct Tree{
    LL num;
    int l,r;
    Tree(){}
    Tree(LL num):num(num){}
};
Tree tr[N*20];
int cnt;
void Insert(int&root,int l,int r,int pos,LL num){
    cnt++;
    tr[cnt]=tr[root];
    root=cnt;
    if (l==r){
        tr[root].num+=num;
        return ;
    }
    int m = (l+r)>>1;
    if (pos<=m) Insert(tr[root].l,l,m,pos,num);
    else        Insert(tr[root].r,m+1,r,pos,num);
    tr[root].num = tr[tr[root].l].num+tr[tr[root].r].num;
}
LL Find2(int root,int l,int r,int L,int R){
    if (l==L && r==R){
        return tr[root].num;
    }
    int m=(l+r)>>1;
    if (R<=m) return Find2(tr[root].l,l,m,L,R);
    else if (m< L) return Find2(tr[root].r,m+1,r,L,R);
    else{
        Tree ret1 = Find2(tr[root].l,l,m,L,m);
        Tree ret2 = Find2(tr[root].r,m+1,r,m+1,R);
        return ret1.num+ret2.num;
    }
}
int n,Q;
LL Find(int root1,int root2,int l,int r){
    if (l>r) return 0;
    LL ans1 = Find2(root1,1,n,l,r);
    LL ans2 = Find2(root2,1,n,l,r);
    return (ans2-ans1)*(ans2-ans1-1)/2;
}
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG

    scanf("%d%d",&n,&Q);
    for (int i=1;i<=n;i++)scanf("%d",&p[i]);

    //zhuxishu
    root[0]=0;cnt=0;
    for (int i=1;i<=n;i++){
        root[i]=root[i-1];
        Insert(root[i],1,n,p[i],1);
    }

    LL tot = Find(root[0],root[n],1,n);
    while (Q--){
        int l,d,r,u;scanf("%d%d%d%d",&l,&d,&r,&u);
        LL ans = Find(root[0],root[l-1],1,n);
        ans=ans+Find(root[r],root[n],1,n);
        ans=ans+Find(root[0],root[n],u+1,n);
        ans=ans+Find(root[0],root[n],1,d-1);
        ans=ans-Find(root[0],root[l-1],1,d-1);
        ans=ans-Find(root[0],root[l-1],u+1,n);
        ans=ans-Find(root[r],root[n],1,d-1);
        ans=ans-Find(root[r],root[n],u+1,n);

        printf("%I64d\n",tot-ans);
    }
    return 0;
}
