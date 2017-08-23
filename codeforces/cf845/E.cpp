//2017-08-22-11.07.06
#include <bits/stdc++.h>

using namespace std;

const int N = 500+10;

int n,m,k;
int x[N][2];
vector <int> points;
int pd(int mid,int c,int n1,int n2)
{
    int otherc = 1 - c;
    points.clear();
    points.push_back(0);
    points.push_back(n1-1);

    for (int i=0;i<k;i++){
        if (x[i][c]-mid>0){
            points.push_back(x[i][c]-mid);
            points.push_back(x[i][c]-mid-1);
        }
        if (x[i][c]+mid<n1-1){
            points.push_back(x[i][c]+mid);
            points.push_back(x[i][c]+mid+1);
        }
    }
    points.erase(unique(points.begin(),points.end()),points.end());

    int minpoint=n1-1;
    int maxpoint=0;

    vector< pair<int,int> > intervals;
    for (auto& point:points){
        intervals.clear();
        for (int i=0;i<k;i++){
            if (abs(x[i][c]-point)<=mid){
                intervals.emplace_back(x[i][otherc]-mid,x[i][otherc]+mid+1);//左闭右开
            }
        }
        sort(intervals.begin(),intervals.end());
        int now=0;
        for (auto& interval:intervals){
            if (interval.first > now)
                break;
            now=interval.second;
        }
        if (now<n2){
            minpoint=min(minpoint,point);
            maxpoint=max(maxpoint,point);
        }
    }
    return maxpoint-minpoint <= 2*mid;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for (int i=0;i<k;i++){
        scanf("%d%d",&x[i][0],&x[i][1]);
        x[i][0]--;
        x[i][1]--;
    }
    int l=0,r=max(n,m),ans;
    while (l<r){
        int mid=(l+r)>>1;
        if (pd(mid,0,n,m) && pd(mid,1,m,n)){
            ans=mid;r=mid-1;
        }else l=mid+1;
    }

    printf("%d\n",ans);
    return 0;
}
