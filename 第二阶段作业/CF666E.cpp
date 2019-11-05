#include <bits/stdc++.h>
#define rua system("pause")
using namespace std;
typedef long long ll;

const int MAXN = 5e5 + 10;
const int MAXM = 5e4 + 10;

map<char, int> ch[MAXM << 1];
char s[MAXN], t[MAXM];
int n, m, lst = 1, root = 1, tot = 1, cnt = 0, fa[MAXM << 1], len[MAXM << 1];
int rt[MAXM << 1], ls[MAXM * 50], rs[MAXM * 50], mx[MAXM * 50], mxp[MAXM * 50];
vector<int> foo[MAXM << 1];

inline void update(int x)
{
	mx[x] = mx[ls[x]], mxp[x] = mxp[ls[x]];
	if (mx[rs[x]] > mx[x]) mx[x] = mx[rs[x]], mxp[x] = mxp[rs[x]];
}

inline int insert(int y, int l, int r, int pos)
{
	int x = ++ cnt;
	if (l == r) {mxp[x] = pos, mx[x] = mx[y] + 1; return x;}
	int mid = (l + r) >> 1;
	if (pos <= mid) rs[x] = rs[y], ls[x] = insert(ls[y], l, mid, pos);
	else ls[x] = ls[y], rs[x] = insert(rs[y], mid + 1, r, pos);
	update(x);
	return x;
}

void extend(int x, int now)
{
	int p = lst;
	if (ch[p][x])
	{
		int q = ch[p][x];
		if (len[q] == len[p] + 1)
		{
			rt[q] = insert(rt[q], 1, m, now);
			foo[q].push_back(now);
			lst = q;
		}
		else
		{
			int nq = ++ tot;
			ch[nq] = ch[q];
			fa[nq] = fa[q];
			fa[q] = nq;
			len[nq] = len[p] + 1;
			foo[nq].push_back(now);
			while (p && ch[p][x] == q)
				ch[p][x] = nq, p = fa[p];
			lst = nq;
		}
	}
	else
	{
		int np = ++ tot; lst = np;
		foo[np].push_back(now);
		while (p && !ch[p][x])
			ch[p][x] = np, p = fa[p];
		if (!p) fa[np] = root;
		else
		{
			int q = ch[p][x];
			if (len[q] == len[p] + 1) fa[np] = q;
			else
			{
				int nq = ++ tot;
				ch[nq] = ch[q];
				fa[nq] = fa[q];
				fa[q] = fa[np] = nq;
				len[nq] = len[p] + 1;
				while (p && ch[p][x] == q)
					ch[p][x] = nq, p = fa[p];
			}
		}
	}
}

int dfn[MAXM << 1], seq[MAXM << 1], out[MAXM << 1], pnt[MAXM << 1][20], ind;
vector<int> linker[MAXM];

void build()
{
	for (int i = 2; i <= tot; i ++)
		linker[fa[i]].push_back(i);
}

void dfs(int x)
{
	seq[dfn[x] = ++ ind] = x;
	for (int cur : linker[x]) dfs(cur);
}

struct ask
{
	int l, r, L, id;
	ask() {}
	ask(int l, int r, int L, int id): l(l), r(r), L(L), id(id) {}
};

vector<ask> vec[MAXN];

const int MAXQ = 5e5 + 10;
pair<int, int> ans[MAXQ];

int res, nmx;

void query(int x, int y, int l, int r, int ql, int qr)
{
	if (l >= ql && r <= qr)
	{
		if (mx[x] )
	}
}

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	scanf("%d", &m);
	for (int i = 1; i <= m; i ++)
	{
		scanf("%s", t + 1);
		int len = strlen(t + 1);
		extend(t[i] - 'a', i);
	}
	build(), dfs(1);
	for (int i = 2; i <= ind; i ++)
	{
		int cur = seq[i];
		pnt[cur][0] = fa[cur];
		for (int j = 1; j <= 17; j ++)
			pnt[cur][j] = pnt[pnt[cur][j - 1]][j - 1];
		rt[i] = rt[i - 1];
		for (int now : foo[cur])
			rt[i] = insert(rt[i], 1, m, now);
	}
	int q = read();
	for (int i = 1; i <= q; i ++)
	{
		int l, r, L, R;
		scanf("%d%d%d%d", &l, &r, &L, &R);
		vec[R].push_back(ask(l, r, L, i));
	}
	int now = root;
	for (int r = 1; r <= n; r ++)
	{
		int c = s[r] - 'a';
		while (now && !ch[now][r])
			now = fa[now];
		if (!now) now = root;
		else now = ch[now][r];
		for (auto cur : vec[r])
		{
			int pos = now;
			for (int i = 17; i >= 0; i --)
				if (len[pnt[pos][i]] >= r - cur.L + 1)
					pos = pnt[pos][i];
			nmx = 0, res = 0;
			query(rt[out[pos]], rt[dfn[pos] - 1], 1, m, cur.l, cur.r);
			ans[cur.id] = pair<int, int>(res, nmx);
		}
	}
	for (int i = 1; i <= q; i ++)
		printf("%d %d\n", ans[i].first, ans[i].second);
	return 0;
}
