/*
    author : VFVrPQ
    problem : cf844-D ,交互题（第一次做）。递增单向链表（n<=50000)，问>=x的值。每次询问返回值和下个位置的索引，最多只能询问2000次
    solve : 玄学啊，询问 start和随机999个数，再从<x的最大的数出发，错误的概率是（1-999/n)^1000=1.7*(10^-9);我在比赛的时候n=1没考虑；订正的时候srand没加！！
    time : 2017-08-25-07.59.18
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;

const int N = 50000+10;

int ans;
int n,start,x;
int perm[N];

int a[N],Next[N];

void query(int u)
{
    if (a[u]>=0) return ;
    printf("? %d\n",u);
    fflush(stdout);
    scanf("%d%d",&a[u],&Next[u]);
}
int main(){
    srand(unsigned(time(NULL)));//这句话一定要加
    memset(a,-1,sizeof a);
    scanf("%d%d%d",&n,&start,&x);

    query(start);

    for (int i=0;i<n;i++) perm[i]=i+1;

    random_shuffle(perm,perm+n);

    for (int i=0;i<999 && i<n;i++){
        int u = perm[i];
        query(u);

        if (a[u]<x && a[u]>a[start])
            start = u;
    }
    //puts("ok");
    while (a[start]<x){
        start = Next[start];
        if (start==-1) break;

        query(start);
    }
    printf("! %d\n", (start==-1)?-1:a[start]);
    return 0;
}
