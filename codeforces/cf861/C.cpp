/*
    author : VFVrPQ
    problem : cf861-C,Ë®Ìâ
    solve :
    time : 2017-09-21-21.27.42
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG
char str[N];
char c[N];
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    scanf("%s",str);
    int len=0,st=0;
    int ans=0;
    for (int i=0;str[i];i++)
    if (str[i]!='a' && str[i]!='e' && str[i]!='i' && str[i]!='o' && str[i]!='u'){
        c[len]=str[i];len++;
        if (len==3){
            if (c[0]==c[1] && c[1]==c[2]){
                len=2;continue;
            }
            c[4] = str[i];str[i]='\0';
            printf("%s ",str+st);
            str[i]= c[4];

            c[0]=c[2];len=1;
            st=i;
        }
    }else{
        len=0;
    }
    if (str[st]) printf("%s",str+st);
    return 0;
}
