/*
    author : VFVrPQ
    problem : cf842-A,水题
    solve :
    time : 2017-09-03-17.56.38
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;

int main(){
    LL l,r,x,y,k;
    cin>>l>>r>>x>>y>>k;
    for (LL i=x;i<=y;i++){
        LL now = i*k;
        if (l<=now && now<=r){
            puts("YES");return 0;
        }
    }
    puts("NO");
    /*if (r>=k*x && l<=k*y){
        puts("YES");
    }else {
        puts("NO");
    }*/
    return 0;
}
