#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    scanf("%d",&n);
    n/=10;

    cout<<n/5*7+n%5/3*4+n%5%3;
    return 0;
}
