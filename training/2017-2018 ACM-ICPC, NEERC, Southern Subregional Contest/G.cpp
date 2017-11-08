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

char str[N][10];
//#define DEBUG
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%s",str[i]);
    }
    int ans=0;
    for (int j=0;j<7;j++){
            int now=0;
            for (int i=1;i<=n;i++) now+=str[i][j]-'0';
            ans=max(ans,now);
    }
    printf("%d\n",ans);
    return 0;
}
