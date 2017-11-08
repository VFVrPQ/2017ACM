/*
    author : VFVrPQ
    problem :
    solve :
    time :
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG
int dp[333][333];
string  x[333],y[333];
int cost[333];
int vis[333];
vector<int>V;
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG

    int n,a,b,f,k;
    scanf("%d%d%d%d%d",&n,&a,&b,&k,&f);

    int tot=0;
    for (int i=1;i<=n;i++){
        cin>>x[i]>>y[i];

        cost[i]=a;
        if (i>=2 && x[i]==y[i-1]) cost[i]=b;

        tot+=cost[i];
    }

    memset(vis,0,sizeof vis);
    for (int i=1;i<=n;i++)if (!vis[i]){
        int now=cost[i];
        for (int j=i+1;j<=n;j++)if ((x[i]==x[j] && y[i]==y[j])||(x[i]==y[j] && x[j]==y[i])){
            now+=cost[j];
        }
        if (now>f){
            for (int j=i+1;j<=n;j++)if ((x[i]==x[j] && y[i]==y[j])||(x[i]==y[j] && x[j]==y[i])){
                vis[j]=1;
            }
            V.push_back(f-now);
        }
    }
    sort(V.begin(),V.end());
    for (int i=0;i<V.size() && i<k;i++) tot+=V[i];
    printf("%d",tot);
    return 0;
}
