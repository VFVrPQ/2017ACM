/*
    author : VFVrPQ
    problem : cf854-A, 水题
    solve : 枚举
    time : 2017-09-08-20.40.00
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG

    int n;
    scanf("%d",&n);

    for (int i=n/2;i;i--){
        int j=n-i;
        if (__gcd(i,j)==1) {
            printf("%d %d\n",i,j);
            return 0;
        }
    }
    return 0;
}
