/*
    author : VFVrPQ
    problem : 2017MUTC5-1001,给定数组a,b(n<=50000),和q(<=50000)个询问,问a[i]%b[j]=k的个数
    solve : 预处理出所有答案。i%j=i-i/j*j, 枚举j和k=i/j,则[kj,(k+1)j)可加到答案[0,j)里，因为模2意义下加法可以用异或实现，压位累加（有点类似分块）
    time : 2017-08-27-13.36.50
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 50000+10;
unsigned int a[32][N],b[N],K[N];
int n,m,Q;
void Set(unsigned int *a,int p){
    a[p>>5]^=1<<(p%32);
    //printf("p=%d\n",1<<(p%32));
}
void addin(int l,int r){
    while (l<r && ((r-l)&31)){
        --r;
        if (a[l&31][(r-(l&31))>>5]&(1<<((r-l)&31)))Set(K,r-l);
    }
    int where = l-l/32*32;
    for (int i=l;i<r;i+=32){
        K[(i-l)>>5]^=a[where][(i-where)>>5];
    }
}
int main()
{
   // freopen("1001.in","r",stdin);
   // freopen("test.txt","w",stdout);
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d%d%d",&n,&m,&Q);
        for (int i=0;i<n;i++){
            int x;scanf("%d",&x);
            for (int j=0;j<32;j++){
                if (x>=j)Set(a[j],x-j);//相对于j的值
            }
        }
        //for (int i=0;i<5;i++)
        //printf("a[%d]=%d\n",i,int(a[i]));
        for (int i=0;i<m;i++){
            int x;scanf("%d",&x);
            b[x]^=1;
        }
        for (int i=1;i<=50000;i++)if (b[i]){
            for (int k=0;k<=50000/i;k++){
                //[i*k,i*(k+1))
                addin(i*k,min(50000+1,i*(k+1)));
            }
        }

        while (Q--){
            int k;scanf("%d",&k);
            printf("%d\n",(int)((K[k>>5]>>(k%32))&1));
        }
        memset(a,0,sizeof a);
        for (int i=0;i<=50000/32;i++) K[i]=0;
        for (int i=0;i<=50000;i++) b[i]=0;
    }
    return 0;
}
