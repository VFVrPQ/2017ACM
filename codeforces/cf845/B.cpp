#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 100+10;
int a[N];
int b[N];
int ans=100;
void dfs(int dep)
{
    if (dep==6){
        if (b[0]+b[1]+b[2]==b[3]+b[4]+b[5]){
            int ret=0;
            for (int i=0;i<6;i++) ret+=(b[i]!=a[i]);

            if (ret<ans)ans=ret;
        }
        return ;
    }
    for (int i=0;i<10;i++){
        b[dep]=i;
        dfs(dep+1);
    }
}
int main()
{
    for (int i=0;i<6;i++)scanf("%1d",&a[i]);

    dfs(0);
    cout<<ans<<endl;
    return 0;
}
