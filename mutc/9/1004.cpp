/*
    author : VFVrPQ
    problem : 2017MUTC9-4, 平面几何，暴力模拟反射，（第一次做）
    solve : 反射次数不会超过100，暴力模拟
    time : 2017-08-26-19.29.38
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int M = 1e9+7;
const int N = 1000+10;

struct Point{
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}
    friend Point operator + (const Point&a,const Point&b){
        return Point(a.x+b.x,a.y+b.y);
    }
    friend Point operator - (const Point&a,const Point&b){
        return Point(a.x-b.x,a.y-b.y);
    }
    friend double operator ^ (const Point&a,const Point&b){
        return a.x*b.y-a.y*b.x;
    }
};
struct Line{
    Point s,e;
    Line(Point s = Point(0,0),Point e = Point(0,0)):s(s),e(e){}
};
Point intersection(Line a,Line b)//在a上
{
    double u = (a.s-b.s)^(b.e-b.s);
    double v = (a.e-b.s)^(b.e-b.s);
    return Point((a.s.x*v+a.e.x*u)/(u+v),(a.s.y*v+a.e.y*u)/(u+v));
}

int n;
Point p[N],s[2];
double K[N];
int main(){
    while (scanf("%d",&n)!=EOF){
        for (int i=0;i<n;i++) scanf("%f%f%f",&p[i].x,&p[i].y,&K[i]);
        p[n] = p[0];

        s[0]=Point(0,0);
        scanf("%f%f",&s[1].x,&s[1].y);
        int ans=0;
        double now = 1;
        while (1){
            ans++;
            int flag=1;
            for (int i=0;i<n;i++)
                if (((p[i]-s[0])^(s[1]-s[0]))==0){
                    flag=0;break;
                }
            if (!flag)break;
            for (int i=0;i<n;i++){
                if (((p[i]-s[0])^s[1])>0 && (s[1]^(p[i+1]-s[0]))>0){
                    Line l1,l2;
                    l1 = Line(p[i],p[i+1]);
                    l2 = Line(s[0],s[0]+s[1]);

                    Point tmp = intersection(l1,l2);

                    l1 = Line(s[0],s[0]+(p[i+1]-p[i]));
                    l2 = Line(tmp,Point(p[i].x,(tmp.x-p[i].x)*((p[i+1].x-p[i].x)/(p[i+1].y-p[i].y))+tmp.y));//因为p[i].x肯定不在中垂线上

                    tmp = intersection(l1,l2);

                    Point tmp2 = s[1];
                    s[1]=tmp+tmp-s[0];
                    s[0]=tmp2;

                    s[1]=s[1]-s[0];//相对坐标

                    now*=K[i];
                    break;
                }
            }
            if (now<1e-4) break;
        }
        printf("%d\n",ans);
    }
    return 0;
}
