#include <bits/stdc++.h>
using namespace std;

const int N = 120+10;
const int M = 998244353;
struct Trie{
    int Next[N][2],Fail[N],End[N];
    int b[N];
    int root,cnt;
    int newnode(){
        for (int i=0;i<2;i++){
            Next[cnt][i]=-1;
        }
        End[cnt++]=0;
        return cnt-1;
    }
    void init(){
        cnt=0;
        root = newnode();
        memset(b,0,sizeof b);
    }
    void Insert(int id,char buf[]){
        int len = strlen(buf);
        int now = root;
        for (int i=0;i<len;i++){
            if (Next[now][buf[i]-'0']==-1)
                Next[now][buf[i]-'0'] = newnode();
            now=Next[now][buf[i]-'0'];
        }
        End[now]|=1<<id;
    }
    void build()
    {
        queue<int>Q;
        Fail[root] = root;
        for (int i=0;i<2;i++)
            if (Next[root][i] == -1)
                Next[root][i] = root;
            else{
                Fail[Next[root][i]] = root;
                Q.push(Next[root][i]);
            }
        while (!Q.empty()){
            int now = Q.front();
            Q.pop();
            for (int i=0;i<2;i++)
                if (Next[now][i] == -1)
                    Next[now][i]= Next[Fail[now]][i];
                else
                {
                    Fail[Next[now][i]] = Next[Fail[now]][i];
                    Q.push(Next[now][i]);
                }
        }
    }
    int query_mask(char buf[]){
        int now=root;
        int mask=0;
        for (int i=0;buf[i];i++){
            int index = buf[i]-'0';
            now=Next[now][index];

            mask|=get_mask(now);
        }
        return mask;
    }
    int query_pos(char buf[]){
        int now=root;
        for (int i=0;buf[i];i++){
            int index = buf[i]-'0';
            now=Next[now][index];
        }
        return now;
    }
    int query_pos(int pos,int index){
        return Next[pos][index];
    }
    int query_mask(int pos,int index){
        return get_mask(Next[pos][index]);
    }
    int get_mask(int pos){//加上这一步优化不超时，类似于并查集
        if (b[pos]) return End[pos];
        if (pos == root) return End[pos];
        b[pos]=1;
        return End[pos]|=get_mask(Fail[pos]);
    }
};
Trie ac,ac2;
int dp[2][122][122][65];//¹ö¶¯Êý×é
char temp[42],s[6][22];
int n,L,maxs;
void inc(int&x,int y){
    x+=y;
    if (x>=M) x-=M;
}
int main()
{
    //freopen("1.txt","r",stdin);freopen("test.txt","w",stdout);
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d%d",&n,&L);
        ac.init();
        ac2.init();
        maxs=0;
        for (int i=0;i<n;i++){
            scanf("%s",s[i]);
            ac.Insert(i,s[i]);
            reverse(s[i],s[i]+strlen(s[i]));
            ac2.Insert(i,s[i]);

            maxs = max(maxs,(int)strlen(s[i]));
        }
        ac.build();
        ac2.build();

        //printf("ac.cnt=%d,ac2.cnt=%d\n",ac.cnt,ac2.cnt);
        maxs = min(maxs,L);
        memset(dp,0,sizeof dp);
        //dp[0][0][0][0]=1;
        int now=0,nxt=1;
        for (int i=0;i<(1<<maxs);i++){
            //getmask
            int len=0;
            for (int j=maxs-1;j>=0;j--){
                temp[len++]=((i>>j)&1^1)+'0';//×ó²à
            }
            //maxs-1 maxs-2 ¡­¡­ 0
            for (int j=0;j<maxs;j++){
                temp[len++]=(i>>j&1)+'0';
            }
            temp[len]='\0';
            int mask = ac.query_mask(temp);

            //gett2
            int t2= ac.query_pos(temp+maxs);

            //gett1
            len=0;
            for(int j=0;j<maxs;j++){
                temp[len++]=((i>>j)&1^1)+'0';
            }
            temp[len]='\0';
            int t1= ac2.query_pos(temp);

            dp[now][t1][t2][mask]++;
            //printf("%d %d %d %d\n",now,t1,t2,mask);
        }

        for (int len=maxs;len<L;len++){
            for (int i=0;i<ac2.cnt;i++){
                for (int j=0;j<ac.cnt;j++){
                    for (int k=0;k<(1<<n);k++)
                    if (dp[now][i][j][k]){
                        int index = 0;
                        inc(dp[nxt][ac2.query_pos(i,index^1)][ac.query_pos(j,index)][k|ac2.query_mask(i,index^1)|ac.query_mask(j,index)],
                            dp[now][i][j][k]);
                        //printf("now=%d,i=%d,j=%d,k=%d,index=%d,nxt=%d,i=%d,j=%d,k=%d\n",now,i,j,k,index,nxt,ac2.query_pos(i,index),ac.query_pos(j,index),k|ac2.query_mask(i,index)|ac.query_mask(j,index));
                        index=1;
                        inc(dp[nxt][ac2.query_pos(i,index^1)][ac.query_pos(j,index)][k|ac2.query_mask(i,index^1)|ac.query_mask(j,index)],
                            dp[now][i][j][k]);
                        //printf("now=%d,i=%d,j=%d,k=%d,index=%d,nxt=%d,i=%d,j=%d,k=%d\n",now,i,j,k,index,nxt,ac2.query_pos(i,index),ac.query_pos(j,index),k|ac2.query_mask(i,index)|ac.query_mask(j,index));
                    }
                }
            }
            for (int i=0;i<ac2.cnt;i++){
                for (int j=0;j<ac.cnt;j++){
                    for (int k=0;k<(1<<n);k++){
                        dp[now][i][j][k]=0;
                    }
                }
            }
            now^=1;nxt^=1;
        }
        int ans=0;
        for (int i=0;i<ac2.cnt;i++){
            for (int j=0;j<ac.cnt;j++){
                    inc(ans,dp[now][i][j][(1<<n)-1]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
