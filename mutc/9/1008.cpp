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

const int N = 125250+10;

int a[N],n;
int b[N],c[N],h;

void Dec(int x)
{
    int l=0,r=n-1;
    while (l<=r){
        int mid=(l+r)>>1;
        if (b[mid]==x){
            c[mid]--;
            return ;
        }else
        if (b[mid]>x){
            r=mid-1;
        }else
            l=mid+1;
    }
}
int main(){
    while (scanf("%d",&n)!=EOF){
        for (int i=0;i<n;i++)scanf("%d",&a[i]);
        sort(a,a+n);

        h=1;b[0]=a[0];c[0]=1;
        for (int i=1;i<n;i++){
            if (b[h-1]!=a[i]){
                b[h]=a[i];c[h]=1;h++;
            }else c[h-1]++;
        }

        n=h;h=0;
        for (int i=0;i<n;i++){
            while (c[i]){
                c[i]--;
                for (int j=0;j<h;j++){
                    Dec(b[i]+a[j]);
                }
                a[h++]=b[i];
            }
        }
        printf("%d\n",h);
        for (int i=0;i<h-1;i++) printf("%d ",a[i]);
        if (h)printf("%d\n",a[h-1]);
    }
    return 0;
}
