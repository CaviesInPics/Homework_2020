// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define FIO "maxflow"
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef double lf;
typedef long double llf;
typedef std::pair<int,int> pr;
template<typename T> inline T gcd(T a,T b){T t;if(a<b){while(a){t=a;a=b%a;b=t;}return b;}else{while(b){t=b;b=a%b;a=t;}return a;}}
template<typename T> inline T sqr(T x){return x*x;}
template<typename T> inline bool Min(T &x , T y) {return x>y?x=y,1:0;}
template<typename T> inline bool Max(T &x , T y) {return x<y?x=y,1:0;}
#define pb push_back
#define MP make_pair
#define xx first
#define yy second
using namespace std;
#define int ll
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*f;
}

namespace MCMF
{
	const int MAXN = 5010;
	const int MAXM = 50010;
	const int INF = 1LL << 60;
	struct edge {
		int nxt , to , w , c;
		edge() {}
		edge(int nxt , int to , int w , int c) : nxt(nxt) , to(to) , w(w) , c(c) {}
	} e[MAXM << 1];
	int S = 0 , T = 0 , last[MAXN] , pre[MAXN] , dis[MAXN] , cnt = 1 , tot = 0; queue<int> q;
	bool inq[MAXN];
	inline void insert(int u , int v , int w , int c) {e[++ cnt] = edge(last[u] , v , w , c); last[u] = cnt;}
	inline void addedge(int u , int v , int w , int c) {insert(u , v , w , c); insert(v , u , 0 , -c);}
	inline bool spfa()
	{
		for(int i = 1; i <= tot; i ++) dis[i] = -INF;
		memset(inq, 0, sizeof(inq)), dis[S] = 0, q.push(S);
		while(q.size())
		{
			int x = q.front(); q.pop();
			for(int i = last[x]; i; i = e[i].nxt)
			{
				int v = e[i].to;
				if(dis[v] < dis[x] + e[i].c && e[i].w)
				{
					dis[v] = dis[x] + e[i].c;
					pre[v] = i; if(!inq[v]) q.push(v), inq[v] = 1;
				}
			}
			inq[x] = 0;
		}
//		cerr << dis[T] << endl;
		return dis[T] != -INF;
	}
	ll maxflow = 0 , maxcost = 0;
	inline void augment()
	{
		int now_flow = INF; ll now_cost = 0;
		for(int i = pre[T]; i; i = pre[e[i^1].to])
			now_flow = min(now_flow , e[i].w);
		now_cost = 1LL * now_flow * dis[T];
		for(int i = pre[T]; i; i = pre[e[i^1].to])
			e[i].w -= now_flow , e[i^1].w += now_flow;
		maxflow += now_flow , maxcost += now_cost;
	}
	inline void Solve() {while(spfa()) augment();}
}

#define add MCMF::addedge
#define id(i , j) ((i - 1) * m + j)

using MCMF::S;
using MCMF::INF;
using MCMF::T;
using MCMF::tot;

int n, ind;
ll ans = 0;

signed main()
{
	n = read();
	int p1 = n * 2 + 1, p2 = p1 + 1, p3 = p2 + 1, p4 = p3 + 1;
	S = p4 + 1, tot = T = S + 1;
	for (int i = 1; i <= n; i ++)
	{
		int x = read(), y = read(), c = read();
		add(S, ++ ind, c, 0);
		add(ind, p1, c, -x - y);
		add(ind, p2, c, x - y);
		add(ind, p3, c, -x + y);
		add(ind, p4, c, x + y);
	}
	for (int i = 1; i <= n; i ++)
	{
		int x = read(), y = read(), c = read();
		add(++ ind, T, c, 0);
		add(p1, ind, c, x + y);
		add(p2, ind, c, -x + y);
		add(p3, ind, c, x - y);
		add(p4, ind, c, -x - y);
	}
	MCMF::Solve();
	ans = MCMF::maxcost;
	printf("%lld\n", ans);
    return 0;
}
