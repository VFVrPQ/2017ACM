#include <stdio.h>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int dis[6][6];
int a[6][6];
int fromx[6][6];
int fromy[6][6];
struct Node{
    int x,y;
    Node(){}
    Node(int x,int y):x(x),y(y){}
};
int way[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int pd(int x,int y){return x>0 && y>0 && x<=5 && y<=5 && !a[x][y] && dis[x][y]==-1;}
void bfs(int x,int y){
    queue<Node>Q;
    Q.push(Node(x,y));

    memset(dis,-1,sizeof dis);
    dis[x][y]=0;

    while (!Q.empty()){
        Node tmp = Q.front(); Q.pop();
        int x = tmp.x, y = tmp.y;

        for (int i=0;i<4;i++){
            int dx=x+way[i][0];
            int dy=y+way[i][1];
            if (pd(dx,dy)){
                Q.push(Node(dx,dy));
                dis[dx][dy]=dis[x][y]+1;
                //记录来自哪个点
                fromx[dx][dy]=x;
                fromy[dx][dy]=y;
            }
        }
    }
}

void print(int x,int y){

    if (!(x==1 && y==1))
        print(fromx[x][y],fromy[x][y]);
    printf("(%d, %d)\n",x-1,y-1);
}
int main()
{
    for (int i=1;i<=5;i++){
        for (int j=1;j<=5;j++){
            scanf("%d",&a[i][j]);
        }
    }
    bfs(1,1);

    print(5,5);
    //printf("%d",dis[5][5]);
    return 0;
}
