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

const int maxn = 4e5 + 10;

map<char, int> ch[maxn];
int n, len[maxn], fa[maxn], rt = 1, lst = 1, tot = 1, cnt = 0;
int dp[maxn], pos[maxn], r[maxn], ls[maxn * 20], rs[maxn * 20], sum[maxn * 20];
char s[maxn]; bool mark[maxn];
vector<int> linker[maxn];

void insert(int &x, int y, int l, int r, int p)
{
	sum[x = ++ cnt] = sum[y] + 1, ls[x] = ls[y], rs[x] = rs[y];
	if (l == r) return; int mid = (l + r) >> 1;
	if (p <= mid) insert(ls[x], ls[y], l, mid, p);
	else insert(rs[x], rs[y], mid + 1, r, p);
}

int query(int x, int y, int l, int r, int ql, int qr)
{
	if (sum[x] == sum[y]) return 0;
	if (l >= ql && r <= qr) return sum[x] - sum[y];
	int res = 0, mid = (l + r) >> 1;
	if (ql <= mid) res += query(ls[x], ls[y], l, mid, ql, qr);
	if (qr > mid) res += query(rs[x], rs[y], mid + 1, r, ql, qr);
	return res;
}

int dfn[maxn], out[maxn], seq[maxn], top[maxn], ind = 0;

void build()
{
	for (int i = 2; i <= tot; i ++)
		if (fa[i]) linker[fa[i]].push_back(i);
}

void dfs(int x)
{
	dfn[x] = ++ ind, seq[ind] = x;
	for (int cur : linker[x]) dfs(cur);
	out[x] = ind;
}

void init()
{
	for (int i = 1; i <= ind; i ++)
	{
		if (mark[seq[i]]) insert(r[i], r[i - 1], 1, n, pos[seq[i]]);
		else r[i] = r[i - 1];
	}
}

inline void extend(int x, int now)
{
	int p = lst, np = ++ tot;
	len[np] = len[p] + 1;
	for (; p && !ch[p][x]; p = fa[p])
		ch[p][x] = np;
	pos[np] = now;
	mark[np] = 1;
	if (!p) fa[np] = rt;
	else
	{
		int q = ch[p][x];
		if (len[q] == len[p] + 1) fa[np] = q;
		else
		{
			int nq = ++ tot;
			len[nq] = len[p] + 1;
			fa[nq] = fa[q];
			pos[nq] = now;
			fa[q] = fa[np] = nq;
			ch[nq] = ch[q];
			for (; p && ch[p][x] == q; p = fa[p])
				ch[p][x] = nq;
		}
	}
	lst = np;
}

int main()
{
	n = read(), scanf("%s", s + 1);
	for (int i = 1; i <= n; i ++) extend(s[i] - 'a', i);
	build(), dfs(rt), init();
	for (int i = 2; i <= ind; i ++)
	{
		int now = seq[i];
		if (fa[now] == rt) dp[now] = 1, top[now] = now;
		else
		{
			int up = top[fa[now]];
			if (query(r[out[up]], r[dfn[up] - 1], 1, n, pos[now] - len[now] + len[up], pos[now] - 1))
				dp[now] = dp[fa[now]] + 1, top[now] = now;
			else dp[now] = dp[fa[now]], top[now] = top[fa[now]];
		}
	}
	assert(ind == tot);
	int ans = 0;
	for (int i = 2; i <= tot; i ++)
		ans = max(ans, dp[i]);
	printf("%d\n", ans);
	return 0;
}
