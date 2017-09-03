/*
    author : VFVrPQ
    problem : cf842-D, 给定数组A和Q个询问(n,Q<=3e5),询问有两种：1.对所有元素异或x;2. 求mex(A)
    solve : mask表示询问到当前的异或和，对数组A建立01树，mask查找最小的未出现的元素即可
    time : s2017-09-03-17.50.24
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 3e5+10;

int T[1<<22];
//int tot[1<<22];
int a[N],b[N];
void add(int p,int x){
    for (int i=19;i>=0;i--){
        T[p]++;
        int index = x>>i&1;
        p=p*2+(index);
    }
    T[p]++;
}
int Find(int x){
    int p=1;
    int ans=0;
    for (int i=19;i>=0;i--){
        int index = x>>i&1;

        int nxt = p*2+index;
        if (T[nxt]==(1<<i)) nxt^=1,ans^=(1<<i);
        p=nxt;
    }
    return ans;
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    //build(1,19);
    for (int i=0;i<n;i++){
        int x;scanf("%d",&x);
        if (!b[x])add(1,x);
        b[x]=1;
    }
    int ans=0,Xor=0;
    for (int i=0;i<=300000;i++) if (!b[i]) {
        ans=i;
        break;
    }
    while (m--){
        int x;scanf("%d",&x);
        Xor^=x;
        /*if ((ans^x)<=ans){
            ans^=x;
            printf("%d\n",ans);
        }else{*/
            ans = Find(Xor);
            printf("%d\n",ans);
        //}
    }
    return 0;
}
