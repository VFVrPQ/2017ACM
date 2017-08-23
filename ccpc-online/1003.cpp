#include <bits/stdc++.h>

using namespace std;

const int N = 3000+10;
int n;
int a[100][100];
int main()
{
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d",&n);

        if (n>=80){
            printf("Bad Team!\n");
            for (int i=1;i<=n;i++){
                for (int j=1;j<=n-i;j++){
                        int x;
                    scanf("%d",&x);
                }
            }
            continue;
        }
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n-i;j++){
                scanf("%d",&a[i][i+j]);
                a[i+j][i] = a[i][j+i];
            }
        }

        int flag=0;
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++){
                for (int k=1;k<=n;k++){
                    if (i==j || j==k || i==k)continue;
                    if (a[i][j] && a[j][k] && a[i][k]){
                        flag=1;
                    }
                    if (!a[i][j] && !a[j][k] && !a[i][k]){
                        flag=1;
                    }
                }
            }
        }
        if (flag) printf("Bad Team!\n");
        else printf("Great Team!\n");
    }
    return 0;
}
