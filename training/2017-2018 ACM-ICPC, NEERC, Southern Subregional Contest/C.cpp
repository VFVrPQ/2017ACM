/*
    author : VFVrPQ
    problem :
    solve :
    time :
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG

LL Find(LL K){
    LL L=1,R=2*(sqrt(K)+1)+1,ans=1;//R之前开了sqrt(K)+1，WA了
    while (L<=R){
        LL mid=(L+R)>>1;
        if (mid*(mid+1)/2<=K) ans=mid,L=mid+1;
        else R=mid-1;
    }
    return ans;
}
vector<int>V;
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int n;LL K;
    LL Max=0;
    cin>>n>>K;
    //(((())))一个括号嵌套的形式达到最大，然后每次取最大嵌入
    if (K){
        LL t = Find(K);
        if (t+1>n){
            puts("Impossible");
            return 0;
        }
        n-=(t+1);
        K-=t*(t+1)/2;
        V.push_back(t+1);

        Max=t;
    }
    while (K && n){
        if (K<=Max){
            V.push_back(K);
            K=0;
        }else {
            K-=Max;
            V.push_back(Max);
        }
        n--;
    }
    //printf("Max=%d\n",Max);
    //for (int i=0;i<V.size();i++) printf("%d ",V[i]);puts("");
    if (!K){
        V.push_back(0);
        for (int i=V.size()-2;i>=0;i--){
            for (int j=0;j<V[i]-V[i+1];j++)printf("(");
            if (i)printf("()");
        }
        for (int i=0;i<V[0];i++) printf(")");
        while (n--){
            printf("()");
        }
    }else puts("Impossible");
    return 0;
}
