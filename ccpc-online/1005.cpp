#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int main()
{
    int Case;scanf("%d",&Case);
    while (Case--)
    {
        LL s, n;
        scanf("%lld",&s);

        n = LL((-1.0+sqrt(1.0+2*s))/2 + 1); //最后+1是向上取整

        LL ans = 4*n+2, mys = 2*n*(n+1);
        if (mys-(n+0.5)<s) printf("%lld\n",ans);else
            if (mys-(2*n)<s) printf("%lld\n",ans-1);else
                if (mys-(3*n+0.5)<s) printf("%lld\n",ans-2);else
                    if (mys-(4*n)<s) printf("%lld\n",ans-3);else
                        printf("%lld\n",ans-4);

    }
    return 0;
}
