/*
POJ   3461 Oulipo
统计子串出现的次数
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int M = 1e9+7;
char W[1000010],T[1000010];
int wlen,tlen;
int Next[1000010];
LL f[1000010];
void getNext()
{
    int j,k;
    j=0;
    k=-1;
    Next[0]=-1;
    while(j<wlen)
    {
        if(k==-1||W[j]==W[k])
        {
            Next[++j]=++k;
        }
        else k=Next[k];
    }
}
LL KMP_count()
{
    LL ans=0;
    int i,j=0;
    if(wlen==1&&tlen==1)
    {
        if(W[0]==T[0])return 1;
        else return 0;
    }
    getNext();
    //for (i=0;i<=wlen;i++) f[i]=0;

    f[0]=0;
    for (int i=1;i<=wlen;i++) {
            f[i]= f[ Next[i]] + i;
            if (f[i]>=M) f[i]-=M;
    }
    for(i=0;i<tlen;i++)
    {
        while(j>0&&T[i]!=W[j])
          j=Next[j];
        if(W[j]==T[i])j++;
        //f[j] = f[ Next[j] ] + j;
        //if (f[j]>=M) f[j]-=M;

        ans = ans + f[j];//
        if (ans>=M) ans-=M;

        if(j==wlen)
        {
            j=Next[j];
        }
    }
    return ans;
}

int main()
{
    int tcase;
    scanf("%d",&tcase);
    while(tcase--)
    {
        scanf("%s%s",T,W);

        reverse(W,W+strlen(W));reverse(T,T+strlen(T));
        wlen=strlen(W);
        tlen=strlen(T);

        printf("%lld\n",KMP_count());
    }
    return 0;
}
