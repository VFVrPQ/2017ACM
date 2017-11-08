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
const int N = 1e5+10;

//#define DEBUG
int b[N],c[N];
int g[N];
vector<pair<pair<int,int>,int>>V;
int ans[N];
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int n,k,m,a;
    scanf("%d%d%d%d",&n,&k,&m,&a);
    for (int i=1;i<=a;i++){
        scanf("%d",&g[i]);
        b[g[i]]++;
        c[g[i]]=i;
    }
    for (int i=1;i<=n;i++){
        V.emplace_back(make_pair(-b[i],c[i]),i);//大的排在前面
    }
    for (int i=1;i<=n;i++){
        int flag = 1;
        vector<pair<pair<int,int>,int>> tmp = V;
        sort(tmp.begin(),tmp.end());

        int id;
        for (int j=0;j<tmp.size();j++)if (tmp[j].second == i){
            id=j;
        }
        if (tmp[id].first.second==0) {
            flag=0;
        }
        if (flag){
            int left = m-a;
            for (int j=id+1;j<tmp.size() && left>0;j++){
                int need = (-tmp[id].first.first)+1-(-tmp[j].first.first);
                if (need>left){
                    break;
                }else{
                    tmp[j].first.first-=need;

                    left-=need;
                    tmp[j].first.second=m-left;

                }
            }
            sort(tmp.begin(),tmp.end());
            //printf("*****TMP**%d\n",tmp.size());
            //for (int i=0;i<tmp.size();i++)printf("%d %d %d\n",tmp[i].first.first,tmp[i].first.second,tmp[i].second);
            int idtmp;
            for (int j=0;j<tmp.size();j++)if (tmp[j].second==i){
                idtmp=j;break;
            }
            if (idtmp>k-1){flag=0;}
        }
        if (flag) ans[i]=1;
        else{
            tmp=V;
            tmp[i-1].first.first-=(m-a);
            tmp[i-1].first.second=m;
            sort(tmp.begin(),tmp.end());

            int idtmp;
            for (int j=0;j<tmp.size();j++)if (tmp[j].second==i){
                idtmp=j;break;
            }
            if (idtmp>k-1 || tmp[idtmp].first.first==0){ans[i]=3;}else ans[i]=2;//不能为0
        }
    }
    int flag=1;
    for (int i=1;i<=n;i++){
        if (flag)flag=0;else printf(" ");
        printf("%d",ans[i]);
    }
    return 0;
}
