#include <bits/stdc++.h>
#define rua system("pause")
using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;
string s[MAXN];
vector<int> son[MAXN], large;
int n, q, ch[MAXN][26], fail[MAXN], tot = 1;
ll sum[205][MAXN];

void build()
{
	int head = 1, tail = 0;
	static int q[MAXN];
	fail[1] = 1;
	for (int i = 0; i < 26; i ++)
		if (!ch[1][i]) ch[1][i] = 1;
		else fail[q[++ tail] = ch[1][i]] = 1; 
	while (head <= tail)
	{
		int x = q[head ++];
		for (int i = 0; i < 26; i ++)
		{
			if (ch[x][i])
			{
				fail[ch[x][i]] = ch[fail[x]][i];
				q[++ tail] = ch[x][i];
			}
			else ch[x][i] = ch[fail[x]][i];
		}
	}
	for (int i = 2; i <= tot; i ++)
		son[fail[i]].push_back(i);
}

int mark[MAXN];
vector<int> foo[MAXN];

void run(int id)
{
	memset(mark, 0, sizeof mark);
	int now = 1;
	for (int i = 0; i < s[id].length(); i ++)
	{
		int c = s[id][i] - 'a';
		now = ch[now][c];
		mark[now] ++;
	}
}

vector<int> baz[MAXN];

void dfs(int x, int id)
{
	for (int cur : son[x])
		dfs(cur, id), mark[x] += mark[cur];
	for (int cur : foo[x])
		sum[id][cur] += mark[x];
}

int bel[MAXN];

ll ans[MAXN], bar[MAXN], blk[MAXN], b_cnt, l[505], r[505];
int nid[MAXN];

void init()
{
	for (int i = 1; i <= n; i ++) bel[i] = (i - 1) / 200 + 1;
	b_cnt = bel[n];
	for (int i = 1; i <= n; i ++)
	{
		if (!l[bel[i]]) l[bel[i]] = i;
		r[bel[i]] = i;
	}
}

struct ask
{
	int l, r, pos;
} qwq[MAXN];

inline ll query(int x)
{
	return blk[bel[x] - 1] + bar[x];
}

inline void add(int x, int v)
{
	for (int i = bel[x]; i <= b_cnt; i ++) blk[i] += v;
	for (int i = x; i <= r[bel[x]]; i ++) bar[i] += v;
}

void run2(int qid, int id)
{
	int now = 1;
	for (int i = 0; i < s[id].length(); i ++)
	{
		int c = s[id][i] - 'a';
		now = ch[now][c];
		baz[now].push_back(qid);
	}
}

void dfs3(int x)
{
	if (x > 1)
	 	for (int cur : baz[x])
			ans[cur] += query(qwq[cur].r) - query(qwq[cur].l - 1);
	for (int cur : son[x])
	{
		for (int now : foo[cur]) add(now, 1);
		dfs3(cur);
		for (int now : foo[cur]) add(now, -1);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i ++)
	{
		cin >> s[i];
		if (s[i].length() >= 500)
			large.push_back(i), nid[i] = large.size();
		int now = 1;
		for (int j = 0; j < s[i].length(); j ++)
		{
			int c = s[i][j] - 'a';
			if (!ch[now][c]) ch[now][c] = ++ tot;
			now = ch[now][c];
		}
		foo[now].push_back(i);
	}
	build();
	for (int i = 0; i < large.size(); i ++)
	{
		run(large[i]), dfs(1, i);
		for (int j = 1; j <= n; j ++)
			sum[i][j] += sum[i][j - 1];
	}
	init();
	for (int i = 1; i <= q; i ++)
	{
		cin >> qwq[i].l >> qwq[i].r >> qwq[i].pos;
		if (!nid[qwq[i].pos])
			run2(i, qwq[i].pos);
		else
		{
			int cur = nid[qwq[i].pos] - 1;
			ans[i] = sum[cur][qwq[i].r] - sum[cur][qwq[i].l - 1];
		}
	}
	dfs3(1); 
	for (int i = 1; i <= q; i ++)
		printf("%lld\n", ans[i]);
	return 0;
}
