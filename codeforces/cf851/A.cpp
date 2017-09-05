/*
    author : VFVrPQ
    problem : cf851-A,水题
    solve :
    time : 2017-09-05-18.30.01
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

int main(){
    int n,k,t;
    cin >> n>>k>>t;
    if (t<=k) cout<<t;
    else if (n<=t && t<n+k) cout<<k+n-t;
    else cout<<k;
    return 0;
}
