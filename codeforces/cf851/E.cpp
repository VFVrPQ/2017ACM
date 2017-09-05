/*
    author : VFVrPQ
    problem : cf851-E,博弈题，给n(n<=100)个数，每一轮选手可以选择p^k(p是质数，k是正数）,p^k是n个数中至少一个数的因子，这些数除掉p^k。不能选择p^k的人输
    solve : 质数间互不影响，每个质数看成是一个局面,最后结果是所有局面的异或和。对于每个质数用mask记录出现次数的状态，枚举子状态x>>i|x&((1<<i)-1)，用mex计算
    time : 2017-09-05-09.39.23
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
vector< pair<int,int> > V;
map<int,int>dp;

int grund(int x){
    if (dp.count(x)) return dp[x];
    int vis[33]={};//要写在里面

    for (int i=1;(1<<i)<=x;i++){
        int y = x>>i|x&((1<<i)-1);
        if (y!=x)//x=3,i=1
            vis[grund(y)]=1;
    }
    int i;
    for (i=0;vis[i];i++);

    //printf("%d:",x);
    //for(int j=0;j<10;j++)  printf("%d ",vis[j]);puts("");
    return dp[x]=i;
}
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        int x;scanf("%d",&x);
        for (int j=2;j*j<=x;j++){
            if (x%j==0){
                pair<int,int> t;
                t.first = j;
                t.second = 0;
                while (x%j==0){
                    x/=j;
                    t.second ++;
                }
                V.push_back(t);
            }
        }
        if (x>1){
            pair<int,int> t(x,1);
            V.push_back(t);
        }
    }
    sort(V.begin(),V.end());
    int ans=0;
    for (int i=0;i<V.size();i++){
        int j=i,mask = 1<<(V[i].second);
        while (j+1<V.size() && V[i].first == V[j+1].first){
            j++;
            mask |= 1<<(V[j].second);
        }
        if (j-i+1<n) mask|=1;//0次,异或1可以用grund(1)=0代替
        //cout<<"mask="<<mask<<endl;
        ans^=grund(mask);
        i=j;
    }
    puts( (ans>0)?"Mojtaba":"Arpa" );
    return 0;
}
