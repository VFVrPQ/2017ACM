/*
    author : VFVrPQ
    problem : cf861-E，n(<=1e5)个的数(6位数，a-z0-9)分成两类，放到1-n这n个位置，第一类要放在第二类之前.求最少移动次数及方案
    solve : 若错位的有cnt个数，那么最少移动cnt次，最多移动cnt+1。在1-n之外的最后插空放。在1-n之内错位的能插空的插空放，不能的（肯定是k个第一类错位和k个第二类错位）将其中一个拿出，其他轮着插空放，再把它拿回来
    time : 2017-09-21-21.12.40
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG


string toString(int i){
    char ret[10];
    sprintf(ret,"%d",i);
    return ret;
}
int pd(string str,int n){
    int x=0;
    int flag=1;
    for (int i=0;i<str.length();i++){
        if (str[i]>'9' || str[i]<'0') return -1;
        if (flag){
            if (str[i]=='0') return -1;
            flag=0;
        }
        x=x*10+str[i]-'0';
    }
    if (x>n) return -1;
    return x;
}

string str[N];
int type[N];
map<string,int>Map;
vector< pair<string,string> > ans;

queue<string> A[2];//放错位置的字符串
queue<string> B[2];//空的位置
vector<string> other[2];
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int n;
    int s[2]={};
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        cin>>str[i]>>type[i];
        type[i]^=1;//0在前面，1在后面

        s[ type[i] ]++;
        Map[ str[i] ]=1;
    }
    s[1]+=s[0];
    //printf("%d %d\n",s[0],s[1]);
    for (int i=1;i<=n;i++){
        if (Map[toString(i)]==0){
            B[i<=s[0]?0:1].push(toString(i));
        }
    }
    for (int i=0;i<n;i++){
        int tmp = pd(str[i],n);
        //printf("%d %d\n",i,tmp);
        if (tmp==-1) other[type[i]].push_back(str[i]);
        else{
            if (type[i]==0 && tmp>s[0]) A[0].push(str[i]);
            else if (type[i]==1 && tmp<=s[0]) A[1].push(str[i]);
        }
    }
    //printf("%d %d\n",A[0].size(),A[1].size());

    int cnt=200001;
    while (true){
        int flag=1;
        for (int i=0;i<2;i++){
            while (!A[i].empty() && !B[i].empty()){//A -> B
                string t1 = A[i].front(); A[i].pop();
                string t2 = B[i].front(); B[i].pop();

                ans.emplace_back(t1,t2);
                Map[t1]=0;
                Map[t2]=1;

                B[i^1].push(t1);//放错地方的位置空出来
                flag=0;
            }
        }
        if (flag){
            for (int i=0;i<2 && flag;i++){
                if (!A[i].empty()){
                    string t1 = A[i].front(); A[i].pop();

                    string tmp = toString(cnt);
                    while (Map[tmp]){cnt++;tmp=toString(cnt);}
                    ans.emplace_back(t1,tmp);

                    cnt++;

                    other[i].push_back(tmp);
                    B[i^1].push(t1);
                    flag=0;
                }
            }
        }
        if (flag) break;
    }

    int t[2]={};
    for (int i=1;i<=n;i++){
        string tmp = toString(i);
        if (Map[tmp]) continue;

        int index = i<=s[0]?0:1;
        assert(t[index]+1 <= other[index].size());
        ans.emplace_back(other[index][t[index]++],tmp);
    }
    printf("%d\n",ans.size());
    for (auto t:ans){
        cout<<"move "<<t.first<<" "<<t.second<<endl;
    }
    return 0;
}
/*
4
4 1
3 1
1 0
2 0
ans:5
*/
