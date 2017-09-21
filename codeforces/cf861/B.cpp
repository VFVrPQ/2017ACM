/*
    author : VFVrPQ
    problem : cf861-B, 有一个建筑每个楼层的房间数相同，房间号连续，给出m个已知信息，房间号和对应的楼层。询问房间号为n的楼层是否唯一。
    solve : 情况好多做题的时候一时懵逼。
        1、已知房间号5在楼层1，那么房间号1肯定也在楼层1；
        2、已知房间号5和房间10在楼层2，那么6，7，8，9也都在2.
        3、7在2，6在2，1在1,询问8.  8只能在楼层2（比赛的时候就错这个）
        这三种情况没考虑到。
        比赛时候就枚举了房间数，但对于第三个情况房间数不同楼层数相同也是成立的（再加个判断就好了。）
    time : 2017-09-21-21.36.01
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG
vector< pair<int,int> > V;
int a[N],b[N];
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int n,m;
    cin>>n>>m;
    for (int i=0;i<m;i++){
            scanf("%d%d",&a[i],&b[i]);
            if (a[i]==n){
                cout<<b[i]<<endl;
                return 0;
            }
            V.emplace_back(a[i],b[i]);
    }
    int ans=-1;
    for (int ret=1;ret<=100;ret++){
        for (int step=1;step<=100;step++){
            if ((n-1)/step+1 != ret)  continue;
            int flag=1;
            for (int j=0;j<m;j++){
                if ((a[j]-1)/step+1!=b[j]){
                    flag=0;break;
                }
            }
            if (flag){
                if (ans!=-1){
                        puts("-1");
                        return 0;
                }
                ans=(n-1)/step+1;
                break;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
