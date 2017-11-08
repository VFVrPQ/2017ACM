/*
    author : VFVrPQ
    problem : codeforces847-L Berland SU Computer Network, n(<=1000)个点，给定以每个点为根有几个子树，每个子树包含哪些点，求是否能形成树。
    solve : 如果能形成树，那么直接相连的点的 包含对方的集合 交集是空，并集是全集。用bitset压位，n/60即可判断。 枚举点对是O(n^2).总的复杂度是O(n^3/60)
            如果是错误数据， 那么边数不为n-1,或者形成环，或者度数不一致。
    time : 2017-11-08-21.11.09
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e3+10;

//#define DEBUG
int dp[N][N];//i,j : i在j的第几个集合里

LL bit60 = 1LL<<60;
LL a[N][N][N/60+1];
LL b[N/60+1];
LL c[N/60+1];

int pos[N];
int bcj[N];
int Find(int x){return bcj[x]==x?x:bcj[x]=Find(bcj[x]);}
void Union(int u,int v){
    u=Find(u);
    v=Find(v);
    bcj[u]=v;
}
//交集为空，并集为全集
int pd(LL b[],LL c[],int n){
    for (int i=0;i<n/60;i++){
        LL a = b[i]|c[i];
        if (a!=(1LL<<60)-1)return false;
        a=b[i]&c[i];
        if (a!=0) return false;
    }
    LL a = b[n/60]|c[n/60];
    if (a!=((1LL<<(n%60+1))-1)) return false;
    a=b[n/60]&c[n/60];
    if (a!=0) return false;
    return true;
}
int d[N];
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int n;
    memset(dp,-1,sizeof dp);
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        int tot=0;

        pos[i]=-1;
        while (tot<n-1){
            int m;scanf("%d:",&m);

            pos[i]++;
            for (int j=1;j<=m;j++){
                int x;scanf("%d",&x);x--;
                if (j!=m)scanf(",");

                dp[x][i]=pos[i];

                a[i][pos[i]][x/60]|=1LL<<(x%60);
            }
            tot+=m;
            if (tot<n-1) scanf("-");
        }
    }
    //for (int i=1;i<=n;i++){for (int j=1;j<=n;j++) printf("%d ",dp[i][j]);puts("");}
    vector<pair<int,int>> ans;
    for (int i=0;i<n;i++){
        for (int j=i+1;j<n;j++){
            int pos1 = dp[i][j];

            for (int k=0;k<=(n-1)/60;k++)
                b[k]=a[j][pos1][k];

            int pos2 = dp[j][i];
            for (int k=0;k<=(n-1)/60;k++)
                c[k]=a[i][pos2][k];


            if (pd(b,c,n-1)) ans.push_back(make_pair(i,j));
        }
    }
    if (ans.size()!=n-1)puts("-1");
    else{

        for (int i=0;i<n;i++) bcj[i]=i;
        for (int i=0;i<ans.size();i++){
            //判是否有环
            int u=ans[i].first,v=ans[i].second;
            if (Find(u)==Find(v)){
                puts("-1");return 0;
            }
            Union(u,v);
            //判断度是否ok
            d[u]++;d[v]++;
        }
        //错误的数据度数不会和树的度数一致
        for(int i=0;i<n;i++)if(d[i]!=pos[i]+1){puts("-1");return 0;}
        printf("%d\n",ans.size());
        for (int i=0;i<ans.size();i++)printf("%d %d\n",ans[i].first+1,ans[i].second+1);
    }
    return 0;
}
/*不判断度出错数据
4
3:2,3,4
1:1-1:3-1:4
2:1,2-1:4
3:1,2,3

-1
*/
