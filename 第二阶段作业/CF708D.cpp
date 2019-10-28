#include <bits/stdc++.h>
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
	const int INF = 0x3f3f3f3f;
	struct edge
	{
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
		for(int i = 1; i <= tot; i ++) dis[i] = INF;
		memset(inq , 0 , sizeof(inq)); dis[S] = 0; q.push(S);
		while(q.size())
		{
			int x = q.front(); q.pop();
			for(int i = last[x]; i; i = e[i].nxt)
			{
				int v = e[i].to;
				if(dis[v] > dis[x] + e[i].c && e[i].w)
				{
					dis[v] = dis[x] + e[i].c;
					pre[v] = i; if(!inq[v]) q.push(v) , inq[v] = 1;
				}
			}
			inq[x] = 0;
		}
		return dis[T] != INF;
	}
	ll maxflow = 0 , mincost = 0;
	inline void augment()
	{
		int now_flow = INF; ll now_cost = 0;
		for(int i = pre[T]; i; i = pre[e[i^1].to])
			now_flow = min(now_flow , e[i].w);
		now_cost = 1LL * now_flow * dis[T];
		for(int i = pre[T]; i; i = pre[e[i^1].to])
			e[i].w -= now_flow , e[i^1].w += now_flow;
		maxflow += now_flow , mincost += now_cost;
	}
	inline void Solve() {while(spfa()) augment();}
}

#define add MCMF::addedge

using MCMF::S;
using MCMF::T;
using MCMF::tot;
using MCMF::INF;

const int MAXN = 105;
int n, m, deg[MAXN];
ll ans = 0;

int main()
{
	n = read(), m = read(), S = n + 1, tot = T = S + 1;
	for (int i = 1; i <= m; i ++)
	{
		int u = read(), v = read(), cap = read(), flow = read();
			deg[u] += flow, deg[v] -= flow;
		if (cap < flow)
		{
			ans += flow - cap;
			add(v, u, flow - cap, 0);
			add(u, v, INF, 2);
			add(v, u, cap, 1);
		}
		else
		{
			add(v, u, flow, 1);
			add(u, v, cap - flow, 1);
			add(u, v, INF, 2);
		}
	}
	
	for (int i = 1; i <= n; i ++)
	{
		if (deg[i] > 0) add(i, T, deg[i], 0);
		else add(S, i, -deg[i], 0);
	}
	
	add(n, 1, INF, 0); 
	
	MCMF::Solve();
	ans += MCMF::mincost;
	cout << ans << endl;
	return 0;
}
