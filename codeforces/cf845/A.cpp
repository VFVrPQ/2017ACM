#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 100+10;
int a[N];
int main()
{
    int n;
    scanf("%d",&n);
    for (int i=0;i<n+n;i++)scanf("%d",&a[i]);
    sort(a,a+n+n);

    if (a[n]>a[n-1])puts("YES");else puts("NO");
    return 0;
}
