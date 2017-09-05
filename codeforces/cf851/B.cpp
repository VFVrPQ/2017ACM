/*
    author : VFVrPQ
    problem : cf851-B, 已知三个点，问是否存在一个点和一个角度，使得A能旋转到B，B旋转到C
    solve : ABC共线不行。这个点必定在AB，BC的中垂线上，又因为角度相同，AB=BC
    time : 2017-09-05-18.29.51
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;

struct Node{
    LL x,y;
    Node(LL x=0,LL y=0):x(x),y(y){}
    friend Node operator - (Node&a,Node&b){
        return Node(a.x-b.x,a.y-b.y);
    }
};
LL cj(Node a,Node b){
    return a.x*b.y-a.y*b.x;
}
LL sqr(LL x){return x*x;}
LL dis(Node a,Node b){
    return sqr(a.x-b.x)+sqr(a.y-b.y);
}
int main(){

    Node a[3];
    for (int i=0;i<3;i++){
        cin>>a[i].x>>a[i].y;
    }
    if (cj(a[1]-a[0],a[2]-a[0])==0 || dis(a[1],a[0])!=dis(a[2],a[1]))
        puts("NO");
    else puts("YES");
    return 0;
}
