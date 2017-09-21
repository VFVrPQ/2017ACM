/*
    author : VFVrPQ
    problem : cf861-D,给定n(<=1e5)个9位数字，问对于每个字符串，唯一标识最少要多少位的子串
    solve : 暴力插入字典树，暴力枚举所有可能的方案，得到最小值
    time : 2017-09-21-21.26.16
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 7e4+10;

//#define DEBUG

char str[N][20],c[20];
int nxt[N*50][10];
int Size[N*50];
int cnt=0;
void Insert(char *str,int f){
    int now=0;
    for (int i=0;str[i];i++){
        int index = str[i]-'0';
        if (nxt[now][index]==-1){
            cnt++;
            nxt[now][index]=cnt;
        }
        Size[now]+=f;
        now=nxt[now][index];
    }
    Size[now]+=f;
}
int Find(char *str){
    int now=0;
    for (int i=0;str[i];i++){
        now=nxt[now][str[i]-'0'];
    }
    return Size[now];
}
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    memset(nxt,-1,sizeof nxt);
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        scanf("%s",str[i]);
        for (int j=0;j<9;j++){
            Insert(str[i]+j,1);
        }
    }
    for (int i=0;i<n;i++){
        for (int j=0;j<9;j++) Insert(str[i]+j,-1);

        int ans=9;
        char best[20]; memcpy(best,str[i],sizeof str[i]);
        for (int j=0;j<9;j++){
            for (int k=j;k<9;k++){
                for (int p=j;p<=k;p++) c[p-j]=str[i][p];
                c[k-j+1]=0;
                //printf("***%s %s\n",str[i],c);
                //c[0]='9'
                if (!Find(c)){
                    if (ans>k-j+1){
                        ans=k-j+1;
                        memcpy(best,c,sizeof c);
                    }
                }
            }
        }
        printf("%s\n",best);
        for (int j=0;j<9;j++) Insert(str[i]+j,1);
    }
    return 0;
}
