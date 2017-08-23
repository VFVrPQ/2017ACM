/*
    author : VFVrPQ
    problem : 2017MUTC9-1001/hdu6161
    solve : 不修改可以(lgn)^2求出，若修改点x，则维护f(x),f(x/2),f(x/4)……，f(x)表示以x为根的子树的最大值(代码改了好久）
    time : 2017-08-23-21.56.03
*/
//代码中其实可以不要bool方向
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;

map<int, LL> Now;
map<int, pair<LL,bool> > Map;//bool:0 left,1 right

int n,Q;
pair<LL,bool> solve(int x)//求单边最大
{
    map<int, pair<LL,bool> >::iterator it = Map.find(x);
    if (it != Map.end()) return it->second;

    int l=x,r=x;
    while (l*2<=n){
        l*=2,r=r*2+1;
    }
    int re;
    if (r<=n){
        re = 1;//当前为右边
    }else{
        if (n>(l+r)/2) re = 1;//右边
        else           re = 0;//左边
        r=n;
    }
    LL ans=0;
    while (r>=x){
        ans+=r;
        r/=2;
    }
    return make_pair(ans,re);
}
void Change(int x)
{
    if (!x) return ;

    LL myv = x;

    map<int, LL>::iterator it = Now.find(x);
    if (it != Now.end()) myv = it->second;

    LL ret1 = solve(x*2).first;
    LL ret2 = (x*2+1<=n)?solve(x*2+1).first:0;
    if (ret1<ret2){
        Map[x] = make_pair(ret2+myv,1);
    }else{
        Map[x] = make_pair(ret1+myv,0);
    }

    Change(x/2);
}
LL query(int x)
{
    LL myv = x;

    map<int, LL>::iterator it = Now.find(x);
    if (it != Now.end()) myv = it->second;


    pair<LL,bool> pa = solve(x);
    LL ret1 = pa.first-myv , ret2 = 0;
    //re : left or right
    if (x*2+1-pa.second<=n) ret2 = solve(x*2+1-pa.second).first;//另一边

    //if (x==1) return ret1+ret2+myv;
    //往上
    int nowx = x, lastx;
    LL ret3 = 0, Max = 0;
    while (nowx/2){
        lastx = nowx;
        nowx/=2;
        it = Now.find(nowx);
        if (it != Now.end()) ret3+=it->second;
        else ret3+=nowx;

        int other;
        if (nowx*2==lastx) other = 1;
        else               other = 0;


        //printf("lastx=%d,nowx=%d:ret3=%lld,solve=%lld\n",ret3,((nowx*2+other)<=n)?solve(nowx*2+other).first:0);
        Max = max(Max, ret3 + (((nowx*2+other)<=n)?solve(nowx*2+other).first:0));
    }

    ret3 = Max;
    if (ret3>ret1) swap(ret3,ret1);
    if (ret3>ret2) swap(ret3,ret2);
    return ret1+ret2+myv;
}
int main(){
    //freopen("1.txt","r",stdin);
    char str[10];
    int x;
    while (scanf("%d%d",&n,&Q)!=EOF){
        Map.clear();
        Now.clear();
        while (Q--){
            scanf("%s%d",str,&x);
            if (str[0]=='q'){
                printf("%lld\n",query(x));
            }else{
                LL v;scanf("%lld",&v);

                LL ret1 = (x*2<=n)?solve(x*2).first:0;
                LL ret2 = (x*2+1<=n)?solve(x*2+1).first:0;
                if (ret1<ret2){
                    Map[x] = make_pair(ret2+v,1);
                }else{
                    Map[x] = make_pair(ret1+v,0);
                }

                Now[x] = v;
                Change(x/2);
            }
        }
    }
    return 0;
}
