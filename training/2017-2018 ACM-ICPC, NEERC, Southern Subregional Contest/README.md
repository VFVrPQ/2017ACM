# 2017-2018 ACM-ICPC, NEERC, Southern Subregional Contest

#### link : http://codeforces.com/contest/847

### *codeforces847-D - Dog Show*
##### problem : 狗狗竞吃大赛，有n碗饭，每碗饭相距1，放在x轴的[1,n]上，i位置的饭要ti时间后才能吃，狗狗从0出发，只能向+1的方向走，在T时间内最多能吃到多少碗。
##### solve : 有些饭需要等待，那么我们总能找到等待时间最长的位置，枚举这个位置，其他位置根据相对时间可以算得。还有一种直接走过去。

### *codeforces847-J - Students Initiation*
##### problem : 给n(<=5000)个点，m(<=5000)条无向边的图，将所有的无向边改成有向边，问所有方案中出度最大的最小值是多少。
##### solve : 二分，然后网络流，S->e(e是边）:流量为1；e->u,e->v，流量为1；u->u'，流量为mid；u'->T，无穷。

### *codeforces847-L - Berland SU Computer Network*
##### problem : n(<=1000)个点，给定以每个点为根有几个子树，每个子树包含哪些点，求是否能形成树。
##### solve : 如果能形成树，那么直接相连的点的 包含对方的集合 交集是空，并集是全集。用bitset压位，n/60即可判断。 枚举点对是O(n^2).总的复杂度是O(n^3/60).如果是错误数据， 那么边数不为n-1,或者形成环，或者度数不一致。

***

| A | B | C | D | E | F | G | H | I | J | K | L | M |
| - | - | - | - | - | - | - | - | - | - | - | - | - |
| O | O | O | O | O | O | O | O | O | O | O | O | O |
