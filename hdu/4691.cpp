/*
    author : VFVrPQ
    problem : hdu4691,给定一个字符串和k个子串，问k个子串用front compression表示的长度
    solve : 后缀数组搞一搞
    time : 2017-09-11-16.01.57
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG
int t1[N],t2[N],c[N];
bool cmp(int *r,int a,int b,int l){
    return r[a] == r[b] && r[a+l] == r[b+l];
}
void da(int str[],int sa[],int Rank[],int height[],int n,int m){
    n++;
    int i,j,p, *x = t1, *y = t2;
    for (i=0;i<m;i++) c[i]=0;
    for (i=0;i<n;i++) c[ x[i]=str[i] ]++;
    for (i=1;i<m;i++) c[i]+=c[i-1];
    for (i=n-1;i>=0;i--) sa[ --c[x[i]] ] = i;
    for (j=1;j<=n;j<<=1){
        p=0;
        for (i=n-j;i<n;i++) y[p++] = i;
        for (i=0;i<n;i++) if (sa[i]>=j) y[p++] = sa[i]-j;

        for (i=0;i<m;i++) c[i]=0;
        for (i=0;i<n;i++) c[x[y[i]]]++;
        for (i=1;i<m;i++) c[i]+=c[i-1];
        for (i=n-1;i>=0;i--) sa[ --c[x[y[i]]]]=y[i];
        swap(x,y);

        p=1;x[sa[0]]=0;
        for (i=1;i<n;i++){
            x[sa[i]] = cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        }
        if (p>=n)break;
        m=p;
    }
    int k=0;
    n--;
    for (i=0;i<=n;i++)Rank[sa[i]]=i;
    for (i=0;i<n;i++){
        if (k)k--;
        j=sa[Rank[i]-1];
        while (str[i+k]==str[j+k])k++;
        height[Rank[i]]=k;
    }
}
int r[N],Rank[N],height[N],sa[N];
char str[N];
int calc(int x){
    if (x==0) return 1;
    int ans=0;
    while (x){
        ans++;
        x/=10;
    }
    return ans;
}
int rmq[20][N];
int askRMQ(int x,int y){
    if (x>y) swap(x,y);
    x++;
    int k=0;
    for (;(1<<k)<=(y-x+1);k++); k--;
    return min(rmq[k][x],rmq[k][y-(1<<k)+1]);
}
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    while (scanf("%s",str)!=EOF){
        int n=strlen(str);

        for (int i=0;i<n;i++)
            r[i] = str[i]-'a'+1;
        r[n]=0;
        da(r,sa,Rank,height,n,27);

        for (int i=0;i<=n;i++){
            //printf("%d:height=%d,Rank=%d,sa=%d\n",i,height[i],Rank[i],sa[i]);
        }
        //RMQ
        for (int i=0;i<=n;i++) {
                rmq[0][i] = height[i];
                //printf("%d:rmq=%d\n",i,rmq[0][i]);
        }
        for (int i=1;(1<<i)<=n;i++){
            for (int j=0;j+(1<<i)-1<=n;j++){
                rmq[i][j] = min(rmq[i-1][j],rmq[i-1][j+(1<<i-1)]);
            }
        }

        LL ans1=0,ans2=0;
        int Q;
        scanf("%d",&Q);
        int lastx,lasty;
        for (int q=1;q<=Q;q++){
            int x,y;scanf("%d%d",&x,&y);
            ans1+=y-x +1;
            if (q==1){
                ans2+= y-x+3;
            }else{
                int tmp = (x==lastx)?n-x:askRMQ(Rank[lastx],Rank[x]);
                int tmp2 = min(min(tmp,y-x),lasty-lastx);
                ans2 += (y-x) - tmp2 + calc(tmp2) + 2;
                //printf("tmp=%d,tmp2=%d,ans2=%d\n",tmp,tmp2,ans2);
            }

            lastx=x;lasty=y;
        }
        cout<<ans1<<" "<<ans2<<endl;
    }
    return 0;
}
