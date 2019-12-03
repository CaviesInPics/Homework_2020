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
int flag;
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

namespace MAXFLOW
{
    const int MAXN = 4e4 + 10;
    const int MAXM = 1e5 + 10;
    const int MAX_BUF = 1e6 + 10;
    const int INF = 0x3f3f3f3f;
    struct edge {
        int nxt , to , w;
        edge() {}
        edge(int nxt , int to , int w) : nxt(nxt) , to(to) , w(w) {}
    } e[MAXM << 1];	
    int S = 0 , T = 0 , last[MAXN] , cur[MAXN] , dis[MAXN] , cnt = 1 , q[MAXN] , tot = 0;
    inline void insert(int u , int v , int w) {e[++ cnt] = edge(last[u] , v , w); last[u] = cnt;}
    inline void addedge(int u , int v , int w) {insert(u , v , w); insert(v , u , 0);}	
    inline bool bfs()
    {
        int head = 1 , tail = 0;
        for(int i = 1; i <= tot; i ++) dis[i] = INF; dis[S] = 0; q[++ tail] = S;
        while(head <= tail)
        {
            int x = q[head ++];
            for(int i = last[x]; i; i = e[i].nxt)
            {
                int v = e[i].to;
                if(dis[v] == INF && e[i].w) dis[v] = dis[x] + 1 , q[++ tail] = v;
            }
        }
        return dis[T] != INF;
    }
    inline int dfs(int x , int low)
    {
        if(x == T || !low) return low;
        int res = 0 , st;
        for(int &i = cur[x]; i; i = e[i].nxt)
        {
            int v = e[i].to;
            if(dis[v] == dis[x] + 1 && e[i].w && ((st = dfs(v , min(low , e[i].w))) > 0))
            {
                res += st; low -= st;
                e[i].w -= st; e[i ^ 1].w += st;
            }
        }
        return res;
    }
    inline int dinic() {int res = 0, s = 0; while(bfs() || s <= MAX_BUF) {s ++; for(int i = 1; i <= tot; i ++) cur[i] = last[i]; res += dfs(S , INF);} return res;}
}
#define MF MAXFLOW
#define add MF::addedge

char buf[200];
int n, m, a[200][200];

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i ++)
	{
		scanf("%s", buf + 1);
		for (int j = 1; j <= m; j ++)
			a[i][j] = buf[j] == '.';
	}
    MF::S = n * m + 7, MF::tot = MF::T = MF::S + 1;
    for (int i = 1; i <= n; i ++)
    	for (int j = 1; j <= m; j ++)
    	{
    		if (a[i][j]) add(MF::S, (i - 1) * m + j, 1);
    		else add((i - 1) * m + j, MF::T, 1);
    	}
    for (int i = 1; i <= n; i ++)
    	for (int j = 1; j <= m; j ++)
    	{
//    		cerr << i << " " << j << " " << flag << endl;
    		if (a[i][j] && a[i][j + 1] && flag)
    			add((i - 1) * m + j, (i - 1) * m + j + 1, 1);
    		if (i == n && j == m && !flag)
    			add(MF::S, MF::T, MF::S + MF::T - n * m), flag = 0; 
		}
    printf("%d\n" , MF::dinic() - n * m);
    return 0;
}
