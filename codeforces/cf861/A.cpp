/*
    author : VFVrPQ
    problem : cf861-A,Ë®Ìâ
    solve :
    time : 2017-09-21-21.28.07
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
    LL n,K;
    cin>>n>>K;
    LL nn=n;
    int b5 = 0;while (n%5==0)n/=5,b5++;
    int b2 = 0;while (n%2==0)n/=2,b2++;
    while (b5<K) b5++,nn*=5;
    while (b2<K) b2++,nn*=2;
    cout<<nn<<endl;
    return 0;
}
