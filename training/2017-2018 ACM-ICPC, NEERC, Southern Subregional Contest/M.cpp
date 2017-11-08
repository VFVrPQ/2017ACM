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

int n;
int t[N];
//#define DEBUG
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    scanf("%d",&n);

    int flag=1;
    for (int i=1;i<=n;i++){
        scanf("%d",&t[i]);
        if (i>=3 && t[i]-t[i-1]!=t[i-1]-t[i-2])flag=0;
    }
    printf("%d\n",flag?t[n]+t[n]-t[n-1]:t[n]);
    return 0;
}
