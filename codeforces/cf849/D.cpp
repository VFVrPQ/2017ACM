/*
    author : VFVrPQ
    problem : cf849-D, X轴、Y轴上分别有舞者，分别朝正向走，相遇会交换方向，求最终舞者停止的位置
    solve : p-t 相同的为1类，在图上画画很容易得出结论~
    time : 2017-09-03-17.38.13
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 100000+10;
const int NN= 100000;
struct Node{
    int id,x,y;
    Node(){}
    Node(int id,int x,int y):id(id),x(x),y(y){}
};
vector<Node> pa[N*2],a[N*2],b[N*2];
int n,W,H;
Node ans[N*2];
bool cmp_a(Node a,Node b){
    return a.x<b.x;
}
bool cmp_b(Node a,Node b){
    return a.y>b.y;
}
bool cmp_pa(Node a,Node b){
    return a.x<b.x;
}
int main(){
#ifdef DEBUG
    freopen("1.txt","r",stdin);
#endif // DEBUG
    scanf("%d%d%d",&n,&W,&H);
    for (int i=0;i<n;i++){
        int g,p,t;scanf("%d%d%d",&g,&p,&t);

        int x,y;
        if (g==1){
            x=p;y=-t;
            a[p-t+NN].emplace_back(i,x,H);
        }else {
            x=-t;y=p;
            b[p-t+NN].emplace_back(i,W,y);
        }
        pa[p-t+NN].emplace_back(i,x,y);
    }
    for (int i=0;i<2*N;i++)if (a[i].size()>1){
        sort(a[i].begin(),a[i].end(),cmp_a);
    }
    for (int i=0;i<2*N;i++)if (b[i].size()>1){
        sort(b[i].begin(),b[i].end(),cmp_b);
    }
    for (int i=0;i<2*N;i++)if (pa[i].size()>1){
        sort(pa[i].begin(),pa[i].end(),cmp_pa);
    }
    for (int i=0;i<2*N;i++)if (pa[i].size()){
        int cnt=0;
        for (int j=0;j<a[i].size();j++){
            ans[ pa[i][cnt++].id ] = Node(1,a[i][j].x, a[i][j].y);
        }
        for (int j=0;j<b[i].size();j++){
            ans[ pa[i][cnt++].id ] = Node(1,b[i][j].x, b[i][j].y);
        }
    }

    for (int i=0;i<n;i++){
        printf("%d %d\n",ans[i].x,ans[i].y);
    }
    return 0;
}
