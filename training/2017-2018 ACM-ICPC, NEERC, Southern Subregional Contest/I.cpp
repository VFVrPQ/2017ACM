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
const int N = 3e2+10;

//#define DEBUG
LL a[N][N];
char str[N][N];
int n,m;
int vis[N][N];
bool pd(int x,int y){
    if (x>=0 && x<n && y>=0 && y<m && !vis[x][y] && str[x][y]!='*') return true;
    return false;
}
queue<pair<pair<int,int>,LL>>Q;
void bfs(int x,int y,LL val){
    vis[x][y]=1;
    a[x][y]+=val;
    Q.push(make_pair(make_pair(x,y),val));

    while (!Q.empty()){
        pair<pair<int,int>,LL> tmp = Q.front();Q.pop();
        x = tmp.first.first;
        y = tmp.first.second;
        val = tmp.second;
        if (val==0) continue;

        if (pd(x+1,y)){
            vis[x+1][y]=1;
            a[x+1][y]+=val/2;
            Q.push(make_pair(make_pair(x+1,y),val/2));
        }
        if (pd(x-1,y)){
            vis[x-1][y]=1;
            a[x-1][y]+=val/2;
            Q.push(make_pair(make_pair(x-1,y),val/2));
        }
        if (pd(x,y+1)){
            vis[x][y+1]=1;
            a[x][y+1]+=val/2;
            Q.push(make_pair(make_pair(x,y+1),val/2));
        }
        if (pd(x,y-1)){
            vis[x][y-1]=1;
            a[x][y-1]+=val/2;
            Q.push(make_pair(make_pair(x,y-1),val/2));
        }
    }
}
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int q,p;
    scanf("%d%d%d%d",&n,&m,&q,&p);
    for (int i=0;i<n;i++)scanf("%s",str[i]);

    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++)if ('A'<=str[i][j] && str[i][j]<='Z'){
            for (int u=-25;u<26;u++)if (i+u>=0 && i+u<n){
                for (int v=-25;v<26;v++)if (j+v>=0 && j+v<m){
                    vis[i+u][j+v]=0;
                }
            }
            bfs(i,j,q*(str[i][j]-'A'+1));
        }
    }
    int num=0;
    for (int i=0;i<n;i++)for (int j=0;j<m;j++)if (a[i][j]>p) num++;
    cout<<num<<endl;
    return 0;
}
