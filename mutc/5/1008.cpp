#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 1e4+10;
int n,m;
LL b[N],my[N];
int a[N],cnt;
int main(){
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d%d",&n,&m);
        for (int i=0;i<=m;i++)scanf("%lld",&b[i]);
        for (int i=0;i<=m;i++) my[i]=0;
        my[0]=1;

        cnt=0;
        for (int i=1;i<=m;i++)if (my[i]<b[i]){
            while (my[i]<b[i]){
                a[cnt]=i;cnt++;
                for (int j=m;j>=i;j--)
                    my[j]+=my[j-i];
            }
        }

        for (int i=0;i<cnt-1;i++) printf("%d ",a[i]);
        printf("%d\n",a[cnt-1]);
    }
    return 0;
}
