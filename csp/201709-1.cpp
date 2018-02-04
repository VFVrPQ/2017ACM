#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    scanf("%d",&n);
    n/=10;

    int ans=n;
    for (int i=0;i<=n/3;i++){
        ans=max(ans,i*4+(n-3*i)%5+(n-3*i)/5*7);
    }
    cout<<ans<<endl;
    return 0;
}
