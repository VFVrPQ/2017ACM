/*
    author : VFVrPQ
    problem : 2017MUTC10-1001 Admiral
    solve : 双向BFS
    time : 2017-08-24-23.26.22
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int M = 1e9+7;
const int N = 100000+10;
const LL INF  = 1LL<<60;

map<string,int> Map;
int a[6][6],pos[6][6];
string b;

void dfs(int dep,int x,int y){
    map<string,int>::iterator it = Map.find(b);
    if (it == Map.end()){
        Map[b] = dep;
    }else{
        Map[b] = min(dep,it->second);
    }
    if (dep==10) return ;
    if (x-1>=0 && y-1>=0){
        swap(b[ pos[x-1][y-1] ],b[ pos[x][y] ]);
        dfs(dep+1,x-1,y-1);
        swap(b[ pos[x-1][y-1] ],b[ pos[x][y] ]);
    }
    if (x-1>=0 && y>=0 && y<=x-1){
        swap(b[ pos[x-1][y] ],b[ pos[x][y] ]);
        dfs(dep+1,x-1,y);
        swap(b[ pos[x-1][y] ],b[ pos[x][y] ]);
    }
    if (x+1<6){
        swap(b[ pos[x+1][y+1] ],b[ pos[x][y] ]);
        dfs(dep+1,x+1,y+1);
        swap(b[ pos[x+1][y+1] ],b[ pos[x][y] ]);
    }
    if (x+1<6){
        swap(b[ pos[x+1][y] ],b[ pos[x][y] ]);
        dfs(dep+1,x+1,y);
        swap(b[ pos[x+1][y] ],b[ pos[x][y] ]);
    }
}

int Ans;
void Find(int dep,int x,int y){
    map<string,int>::iterator it = Map.find(b);
    if (it != Map.end()){
        Ans = min(Ans, it->second+dep);
    }
    if (dep==10) return ;
    if (x-1>=0 && y-1>=0){
        swap(b[ pos[x-1][y-1] ],b[ pos[x][y] ]);
        Find(dep+1,x-1,y-1);
        swap(b[ pos[x-1][y-1] ],b[ pos[x][y] ]);
    }
    if (x-1>=0 && y>=0 && y<=x-1){
        swap(b[ pos[x-1][y] ],b[ pos[x][y] ]);
        Find(dep+1,x-1,y);
        swap(b[ pos[x-1][y] ],b[ pos[x][y] ]);
    }
    if (x+1<6){
        swap(b[ pos[x+1][y+1] ],b[ pos[x][y] ]);
        Find(dep+1,x+1,y+1);
        swap(b[ pos[x+1][y+1] ],b[ pos[x][y] ]);
    }
    if (x+1<6){
        swap(b[ pos[x+1][y] ],b[ pos[x][y] ]);
        Find(dep+1,x+1,y);
        swap(b[ pos[x+1][y] ],b[ pos[x][y] ]);
    }
}
int main()
{
    int Case;scanf("%d",&Case);

    int cnt=0;
    ostringstream s1;
    for (int i=0;i<6;i++){
        for (int j=0;j<=i;j++){
            pos[i][j]=cnt++;
            s1<<i;
        }
    }
    b = s1.str();
    //cout<<"b="<<b<<endl;
    dfs(0,0,0);

    //cout<<s1.str()<<endl;
    while (Case--){
        s1.str("");
        int x,y;
        for (int i=0;i<6;i++){
            for (int j=0;j<=i;j++){
                scanf("%d",&a[i][j]);
                s1<<a[i][j];
                if (a[i][j]==0) x=i,y=j;
            }
        }
        b = s1.str();
        //cout << "b=" << b<<endl;
        Ans = 100;
        Find(0,x,y);

        if (Ans>20){
            printf("too difficult\n");
        }else {
            printf("%d\n",Ans);
        }
    }
    return 0;
}
