/*
    author : VFVrPQ
    problem : cf842-B
    solve : 水题
    time : 2017-09-03-17.42.16
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;

int main(){
    int d,R,n;
    scanf("%d%d%d",&R,&d,&n);
    int ans=0;
    while (n--){
        int x,y,r;
        scanf("%d%d%d",&x,&y,&r);
        if (x*x+y*y>r*r &&
            sqrt((double)x*x+y*y)-r>=R-d &&
            sqrt((double)x*x+y*y)+r<=R){
            ans++;
            //printf("****%d %d %d\n",x,y,r);
        }

    }
    printf("%d\n",ans);
    return 0;
}
