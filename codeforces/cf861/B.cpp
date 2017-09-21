/*
    author : VFVrPQ
    problem : cf861-B, ��һ������ÿ��¥��ķ�������ͬ�����������������m����֪��Ϣ������źͶ�Ӧ��¥�㡣ѯ�ʷ����Ϊn��¥���Ƿ�Ψһ��
    solve : ����ö������ʱ��һʱ�±ơ�
        1����֪�����5��¥��1����ô�����1�϶�Ҳ��¥��1��
        2����֪�����5�ͷ���10��¥��2����ô6��7��8��9Ҳ����2.
        3��7��2��6��2��1��1,ѯ��8.  8ֻ����¥��2��������ʱ��ʹ������
        ���������û���ǵ���
        ����ʱ���ö���˷������������ڵ����������������ͬ¥������ͬҲ�ǳ����ģ��ټӸ��жϾͺ��ˡ���
    time : 2017-09-21-21.36.01
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG
vector< pair<int,int> > V;
int a[N],b[N];
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int n,m;
    cin>>n>>m;
    for (int i=0;i<m;i++){
            scanf("%d%d",&a[i],&b[i]);
            if (a[i]==n){
                cout<<b[i]<<endl;
                return 0;
            }
            V.emplace_back(a[i],b[i]);
    }
    int ans=-1;
    for (int ret=1;ret<=100;ret++){
        for (int step=1;step<=100;step++){
            if ((n-1)/step+1 != ret)  continue;
            int flag=1;
            for (int j=0;j<m;j++){
                if ((a[j]-1)/step+1!=b[j]){
                    flag=0;break;
                }
            }
            if (flag){
                if (ans!=-1){
                        puts("-1");
                        return 0;
                }
                ans=(n-1)/step+1;
                break;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
