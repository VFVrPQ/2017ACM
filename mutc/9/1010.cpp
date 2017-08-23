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

const int N = 2500+10;

bool dp[N][N];
int tag[N][N];
char a[N],b[N];
int last[N];
int main(){
    //freopen("1.txt","r",stdin);
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%s%s",b+1,a+1);

        int n= strlen(a+1), m = strlen(b+1);

        for (int i=m;i>=1;i--)if (b[i]!=b[i+1]) last[i] = i;
        else last[i] = last[i+1];
        for (int i=0;i<=n;i++) for (int j=0;j<=m;j++) dp[i][j]=0,tag[i][j]=0;

        dp[0][0]=1;

        for (int i=0;i<=n;i++){
            for (int j=0;j<=m;j++){
                if (j>0) tag[i][j]+=tag[i][j-1];
                if (tag[i][j]>0) dp[i][j]=1;

                if (dp[i][j]){
                    if (i+2<=n && a[i+2]=='*'){
                            dp[i+2][j]=dp[i][j];
                            if (j<m && (a[i+1]=='.' || a[i+1]==b[j+1])){
                                tag[i+2][j+1]++;
                                tag[i+2][last[j+1]+1]--;
                            }
                    }
                    if (i<n && j<m && a[i+1]==b[j+1]) dp[i+1][j+1]=dp[i][j];
                    if (i<n && j<m && a[i+1]=='.')    dp[i+1][j+1]=dp[i][j];
                }
            }
        }

        if (dp[n][m]) puts("yes");else puts("no");
    }
    return 0;
}
