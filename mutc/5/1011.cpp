#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
int n,K;
int a[N];
int main(){
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d%d",&n,&K);
        for (int i=0;i<n;i++)scanf("%d",&a[i]);
        sort(a,a+n);

        int j=-1;
        for (int i=n-2;i>=0;i--){
            if (a[i+1]-a[i]>K){j=i;break;}
        }
        if (j==-1)printf("%d\n",n);
        else printf("%d\n",n-j-1);
    }
    return 0;
}
