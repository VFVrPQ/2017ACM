#include <bits/stdc++.h>

using namespace std;


const int n = 80;
int nown,m;

int main()
{
    nown = n;m=0;
    for (int i=1;i<=n;i++)
    {
        int now = 1;
        for (int j=1;j<=n/i;j++)
        {
            nown++;
            for (int k=1;k<=i;k++){
                //nown,now
                now++;m++;
            }
        }
    }
    printf("%d %d\n",nown,m);

    nown=n;
    for (int i=1;i<=n;i++)
    {
        int now = 1;
        for (int j=1;j<=n/i;j++)
        {
            nown++;
            for (int k=1;k<=i;k++){
                //nown,now
                printf("%d %d\n",nown,now);
                now++;
            }
        }
    }
    //printf("%d %d %.3f\n",nown-n,n,(double)(nown-n)/n);
    //printf("%.2f\n",log(n)/log(2));
    printf("%d\n",n);
    for (int i=1;i<=n;i++){
        printf("%d\n",i);
    }
    return 0;
}
