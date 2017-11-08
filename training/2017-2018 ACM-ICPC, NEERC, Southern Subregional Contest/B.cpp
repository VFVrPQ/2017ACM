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
const int N = 2e5+10;

//#define DEBUG
vector<int> V[N];
int n;
int a[N];
int Find(int L,int R,int v){

    int ans=-1;
    while (L<=R){
        int mid=(L+R)>>1;
        if (V[mid][V[mid].size()-1]<v) ans=mid,R=mid-1;
        else L=mid+1;
    }
    if (ans==-1) return R+1;
    return ans;
}
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    scanf("%d",&n);

    int cnt=0;
    for (int i=1;i<=n;i++){
        scanf("%d",&a[i]);

        int p = Find(0,cnt-1,a[i]);

        V[p].push_back(a[i]);
        if (cnt<=p)cnt++;
    }
    for (int i=0;i<cnt;i++){
        int flag=1;
        for (auto v:V[i]){
            if (flag)flag=0;else printf(" ");
            printf("%d",v);
        }
        printf("\n");
    }
    //cout<<(*S.begin()).first<<endl;
    return 0;
}
