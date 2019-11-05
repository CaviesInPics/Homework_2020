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

const int MAXN = 3e5 + 10;
struct road
{
	int u, v, c;
	road() {}
	road(int u, int v, int c): u(u), v(v), c(c) {}
} a[MAXN];
int n, m, fa[MAXN], dep[MAXN], dfn[MAXN], out[MAXN], ind;
ll dp[MAXN], mn[MAXN << 2], tag[MAXN << 2];
vector<int> linker[MAXN];

inline bool cmp(const road &a, const road &b) {return dfn[a.u] < dfn[b.u];}

#define ls (x << 1)
#define rs (x << 1 | 1)

const ll inf = 1LL << 60;

inline void update(int x) {mn[x] = min(mn[ls], mn[rs]);}

inline void operate(int x, ll v) {tag[x] += v, mn[x] += v;}

inline void pushdown(int x)
{
	if (tag[x])
	{
		ll v = tag[x];
		operate(ls, v);
		operate(rs, v);
		tag[x] = 0;
	}
}

void Modify(int x, int l, int r, int ql, int qr, ll v)
{
	if (l >= ql && r <= qr) return operate(x, v);
	int mid = (l + r) >> 1; pushdown(x);
	if (ql <= mid) Modify(ls, l, mid, ql, qr, v);
	if (qr > mid) Modify(rs, mid + 1, r, ql, qr, v);
	update(x);
}

void Change(int x, int l, int r, int pos)
{
	if (l == r) {mn[x] = inf; return;}
	int mid = (l + r) >> 1; pushdown(x);
	if (pos <= mid) Change(ls, l, mid, pos);
	else Change(rs, mid + 1, r, pos);
	update(x);
}

void build(int x, int l, int r)
{
	if (l == r) {mn[x] = a[l].c; return;}
	int mid = (l + r) >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	update(x);
}

void dfs(int x)
{
	dfn[x] = ++ ind;
	dep[x] = dep[fa[x]] + 1;
	for (int cur : linker[x])
		if (cur != fa[x])
			fa[cur] = x, dfs(cur);
	out[x] = ind;
}

vector<int> foo[MAXN], bar[MAXN];

inline int findl(int pos)
{
	int l = 1, r = m, res = m + 1;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (dfn[a[mid].u] >= pos) res = mid, r = mid - 1;
		else l = mid + 1;
	}
	return res;
}

inline int findr(int pos)
{
	int l = 1, r = m, res = 0;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (dfn[a[mid].u] <= pos) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	return res;
}

inline ll query(int x, int l, int r, int ql, int qr)
{
//	if (ql == 3 && qr == 5)
//		printf("%d %d %d %d %d %lld\n", x, l, r, ql, qr, mn[x]);
	if (l >= ql && r <= qr) return mn[x];
	int mid = (l + r) >> 1; pushdown(x); ll res = inf;
	if (ql <= mid) res = min(res, query(ls, l, mid, ql, qr));
	if (qr > mid) res = min(res, query(rs, mid + 1, r, ql, qr));
	return res;
}

void dfs2(int x)
{
	for (int cur : linker[x])
	{
		if (cur == fa[x]) continue;
		dfs2(cur);
	}
	if (x == 1) return;
	for (int cur : foo[x])
		Change(1, 1, m, cur);
	ll s = 0;
	for (int cur : linker[x])
		if (cur != fa[x]) s += dp[cur];
	for (int cur : linker[x])
		if (cur != fa[x])
		{
			int ql = findl(dfn[cur]), qr = findr(out[cur]);
//			cerr << cur << " " << ql << " " << qr << " " << s - dp[cur] << endl; rua;
			Modify(1, 1, m, ql, qr, s - dp[cur]);
		}
	for (int cur : bar[x])
		Modify(1, 1, m, cur, cur, s);
	int ql = findl(dfn[x]), qr = findr(out[x]);
//	cerr << x << " " << dfn[x] << " " << out[x] << " " << ql << " " << qr << endl;
	if (ql > qr || dfn[a[ql].u] > out[x] || dfn[a[qr].u] < dfn[x])
	{
		puts("-1");
		exit(0);
	}
	dp[x] = query(1, 1, m, ql, qr);
//	cerr << x << " " << dp[x] << endl; rua;
}

int main()
{
//	freopen("input.txt", "r", stdin);
	n = read(), m = read();
	for (int i = 1; i < n; i ++)
	{
		int u = read(), v = read();
		linker[u].push_back(v);
		linker[v].push_back(u);
	}
	dfs(1);
	for (int i = 1; i <= m; i ++)
	{
		int u = read(), v = read(), c = read();
//		if (dfn[u] < dfn[v]) swap(u, v);
		a[i] = road(u, v, c);
	}
	sort(a + 1, a + 1 + m, cmp);
	build(1, 1, m);
	for (int i = 1; i <= m; i ++)
		foo[a[i].v].push_back(i), bar[a[i].u].push_back(i);
	dfs2(1);
	ll ans = 0;
	for (int cur : linker[1])
	{
		if (dp[cur] >= inf) return puts("-1"), 0;
		ans += dp[cur];
	}
	printf("%lld\n", ans);
	return 0;
}
