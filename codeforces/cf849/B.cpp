/*
    author : VFVrPQ
    problem : cf849-B , 判断所有的(i,a[i])能否被两条平行线覆盖，其中每条线至少要覆盖一个点。
    solve : 1.第一个点要么是单独的一个点，要么是在一条线上，依此搞一搞；2.考虑前三个点，三者情况分别考虑O(n)
    time : 2017-09-03-17.31.51
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e4+10;

struct Node{
    int x,y;
    Node(){}
    Node(int x,int y):x(x),y(y){}
    friend Node operator - (const Node&a,const Node&b){
        return Node(a.x-b.x,a.y-b.y);
    }
};
vector<Node> a;
LL cj(Node i,Node j){
    return (LL)i.x*j.y-(LL)i.y*j.x;
}
int main(){
    int n;scanf("%d",&n);
    for (int i=0;i<n;i++){
        int x;scanf("%d",&x);
        a.emplace_back(i,x);
    }
    vector<int> V1;
for (int my=0;my<2;my++){
    for (int i=0;i<n;i++)if (i!=my){
        V1.clear();
        int flag=1;
        for (int j=0;j<n;j++)if(i!=j && my!=j){
            if (cj(a[i]-a[my],a[j]-a[my])!=0){
                if (V1.size()<2) {
                        V1.push_back(j);
                        if (V1.size()==2){
                            if (cj(a[i]-a[my],a[V1[1]]-a[V1[0]])!=0){
                                flag=0;break;
                            }
                        }
                }
                else {
                    if (cj(a[V1[1]]-a[V1[0]],a[j]-a[V1[0]])!=0){
                        flag=0;break;
                    }
                }
            }
        }
        //printf("%d\n",i);
        if (flag && V1.size()>0){puts("YES");return 0;}
    }
}
    puts("NO");
    return 0;
}
