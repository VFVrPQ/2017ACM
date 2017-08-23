#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 2e5+10;
int a[N],b[N],ha,hb;//
int ans;
int main()
{
    int n;
    scanf("%d",&n);

    ha=hb=1;
    a[0]=300;b[0]=1;
    int now;
    for (int i=0;i<n;i++){
        int type;scanf("%d",&type);

        if (type==1){
            int x;scanf("%d",&x);
            now=x;
            while (a[ha-1]<now)ans++,ha--;
        }else
        if (type==2){
            while (b[hb-1]==0)ans++,hb--;
        }else
        if (type==3){
            int x;scanf("%d",&x);
            a[ha++]=x;
            while (a[ha-1]<now)ans++,ha--;
        }else
        if (type==4){
            b[hb++]=1;
        }else
        if (type==5){
            a[ha++]=300;
        }else {
            b[hb++]=0;
        }
    }
    printf("%d\n",ans);
    return 0;
}
