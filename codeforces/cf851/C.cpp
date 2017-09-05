/*
    author : VFVrPQ
    problem : cf851-C,n(n<=1000)个5维向量，如果向量ab和向量ac的夹角为锐角，那么a是bad；问有哪几个good点
    solve : 刷uoj裙刷到了解法。O(n^3)暴力判断有锐角直接bad,可以过的，。。
            1、一个钝角必然对应两个锐角，所以最多只有1个good(n=1,n=2特判），其实好像没有什么用（逃
            2、观察二维坐标，一个good，周围最多4个点（坐标轴）；3维坐标是6个。。。推理，5维坐标是10个。所以>11puts("0").
                （5根坐标轴，2个方向，所以是10个）
    time : 2017-09-05-10.02.01
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e3+10;
struct Node{
    int a[5];
    friend Node operator - (Node&x,Node &y){
        Node z;
        for (int i=0;i<5;i++){
            z.a[i]=x.a[i]-y.a[i];
        }
        return z;
    }
};
int cross(Node a,Node b){
    int ans=0;
    for (int i=0;i<5;i++) ans+=a.a[i]*b.a[i];
    return ans;
}
Node a[N];
int ans[N],h;
int mark[N];
int main(){
    int n;scanf("%d",&n);
    for (int i=0;i<n;i++){
        for (int j=0;j<5;j++){
            scanf("%d",&a[i].a[j]);
        }
    }
    //int my=1;
    for (int i=0;i<n;i++)if (!mark[i]){
        int flag=1;
        for (int j=0;j<n;j++)if (j!=i){
            for (int k=0;k<n;k++)if (k!=i && k!=j){
                int tmp = cross(a[j]-a[i],a[k]-a[i]);

                //printf("%d %d %d %d\n",i,j,k,tmp);
                if (tmp>0) {flag=0;break;}
                //my=0;
                mark[j]=1;mark[k]=1;
            }
            if (flag==0) break;
        }
        if (flag){
            //printf("1\n%d",i+1);return 0;
            ans[h++]=i+1;
        }
    }
    printf("%d\n",h);
    for (int i=0;i<h;i++) printf("%d\n",ans[i]);
    return 0;
}
//arg()
