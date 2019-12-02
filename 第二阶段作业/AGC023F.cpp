#include <bits/stdc++.h>
#define rua system("pause")
using namespace std;
typedef long long ll;
inline int read()
{
	int x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) {x = x * 10 + c - '0', c = getchar();}
	return x * f;
}

const int MAXN = 2e5 + 10;

struct node
{
	int x, f, g;
	node() {}
	node(int x, int f, int g): x(x), f(f), g(g) {}
	inline bool operator == (const node &rhs) const {return x == rhs.x && f == rhs.f && g == rhs.g;}
	inline bool operator < (const node &rhs) const
	{
		ll foo = 1LL * f * rhs.g, bar = 1LL * g * rhs.f;
		if (foo == bar) return x < rhs.x;
		else return bar < foo;
	}
};

int n, fa[MAXN], pnt[MAXN], v[MAXN], f[MAXN], g[MAXN];

set<node> s;

inline int find(int x)
{
	while (x != pnt[x]) x = pnt[x] = pnt[pnt[x]];
	return x;
}

int main()
{
	n = read();
	for (int i = 2; i <= n; i ++) fa[i] = read();
	for (int i = 1; i <= n; i ++) v[i] = read();
	pnt[1] = 1, f[1] = v[1] == 0, g[1] = v[1] == 1;
	for (int i = 2; i <= n; i ++)
		pnt[i] = i, f[i] = v[i] == 0, g[i] = v[i] == 1, s.insert(node(i, f[i], g[i]));
	
	ll ans = 0;
	
	while (s.size())
	{
		auto cur = *s.begin();
		int x = cur.x; s.erase(*s.begin());
		assert(find(x) == x);
		int y = find(fa[x]);
//		cerr << x << " " << y << " " << s.size() << endl;
		ans += 1LL * f[x] * g[y];
		if (y > 1) s.erase(node(y, f[y], g[y]));
		f[y] += f[x], g[y] += g[x], pnt[x] = y;
		if (y > 1) s.insert(node(y, f[y], g[y]));
	}
	
	printf("%lld\n", ans);
	
	return 0;
}
