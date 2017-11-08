#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N =100+10;

int L[N],R[N];
int bcj[N];

int Find(int x){
    if (x!=bcj[x]) return bcj[x]=Find(bcj[x]);
    return x;
}
void Union(int x,int y){
    x=Find(x);
    y=Find(y);
    bcj[x]=y;
}
int main(){
    int n;
    scanf("%d",&n);

    for (int i=1;i<=n;i++) bcj[i]=i;

    int num=0;
    for (int i=1;i<=n;i++){
            scanf("%d%d",&L[i],&R[i]);
            if (L[i]!=0)Union(i,L[i]);
            if (R[i]!=0)Union(i,R[i]);
            if (L[i]==0)num++;
    }
    while (num>1){
        int id=0;
        for (int i=1;i<=n;i++)if (L[i]==0){id=i;break;}

        int id2=0;
        for (int i=1;i<=n;i++)if (R[i]==0 && Find(id)!=Find(i)){id2=i;break;}

        R[id2]=id;L[id]=id2;Union(id,id2);
        num--;
    }
    for (int i=1;i<=n;i++) printf("%d %d\n",L[i],R[i]);
    return 0;
}
