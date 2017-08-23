#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 2e5+10;
int l[N],r[N];
int n;
int y[N*2];
int b[N*2];
int main()
{
    scanf("%d",&n);
    int cnt=0;
    for (int i=0;i<n;i++){
            scanf("%d%d",&l[i],&r[i]);
            y[cnt++]=l[i];
            y[cnt++]=r[i];
    }
    sort(y,y+cnt);
    cnt=1;
    for (int i=1;i<2*n;i++)if (y[i]!=y[i-1]){
        y[cnt++]=y[i];
    }

    memset(b,0,sizeof b);

    for (int i=0;i<n;i++){
        int x = lower_bound(y,y+cnt,l[i])-y;
        b[x]++; //printf("%d+\n",x);
        x = lower_bound(y,y+cnt,r[i])-y;
        b[x+1]--;//printf("%d-\n",x);
    }
    int flag=b[0]>2;
    for (int i=1;i<N*2;i++){
        b[i]=b[i]+b[i-1];
        flag|=b[i]>2;
    }
    if (flag) puts("NO");else puts("YES");
    return 0;
}
