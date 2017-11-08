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

vector<int>V[2];
bool pd(int mid){
    int j=0;
    for (int i=0;i<V[0].size();i++){
        int nowp = V[0][i];
        int nowm = mid;


        if (V[1][j]>nowp){
            while (j<V[1].size() && V[1][j]-nowp<=nowm){
                nowm-=V[1][j]-nowp;
                nowp=V[1][j];
                j++;
            }
        }else{
            //1.先向左吃再向右吃，2.先向右吃再向左吃都有可能
            if (nowp-V[1][j]>nowm) return false;

            int myj = j;
            while (myj<V[1].size() && V[1][myj]<nowp) myj++;
            myj--;//全部覆盖的位置。

            while (myj+1<V[1].size() && ((nowp-V[1][j])*2+(V[1][myj+1]-nowp)<=nowm || (nowp-V[1][j])+(V[1][myj+1]-nowp)*2<=nowm)) myj++;

            j=myj+1;
        }
        if (j>=V[1].size()) return true;
    }
    return false;
}
char str[N];
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int n;
    scanf("%d%s",&n,str);
    for (int i=0;i<n;i++)
        if (str[i]=='P') V[0].push_back(i);
        else if (str[i]=='*') V[1].push_back(i);

    int L=0,R=2*n,ans=2*n;
    while (L<=R){
        int mid=(L+R)>>1;
        if (pd(mid)) ans=mid,R=mid-1;
        else L=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}
