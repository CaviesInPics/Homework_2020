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

char t[30], s[205], ans[205];
vector<int> linker[405], V, C;
int n, m, vis[405], l, q[405];

void dfs(int x)
{
	vis[x] = 1;
	for (int cur : linker[x])
		if (!vis[cur]) vis[cur] = 1, dfs(cur);
}

bool mark[405];

inline bool Valid()
{
	for (int i = 1; i <= n * 2; i ++) mark[i] |= vis[i];
	for (int i = 1; i <= n; i ++)
		if (mark[i] && mark[i + n]) return 0;
	for (int i = 1; i <= n; i ++)
	{
		if (mark[i] && C.empty()) return 0;
		if (mark[i + n] && V.empty()) return 0;
	}
	return 1;
}

void try_dfs(int x)
{
	mark[x] = 1;
	for (int cur : linker[x])
		if (!mark[cur] && !vis[cur])
			mark[cur] = 1, try_dfs(cur);
}

inline void clear() {memset(mark, 0, sizeof mark);}

inline bool check(int x)
{
	char c = t[s[x] - 'a' + 1];
	if (c == 'V' && V.empty()) return 0;
	if (c == 'C' && C.empty()) return 0;
	int now = x + (c == 'V') * n;
	int head = 1, tail = 0;
	if (!vis[now]) q[++ tail] = now;
	while (head <= tail)
	{
		int x = q[head ++];
		for (int cur : linker[x])
			if (!vis[cur]) vis[q[++ tail] = cur] = 1;
	}
	for (int i = 1; i <= n; i ++)
		if (vis[i] && vis[i + n]) return 0;
	for (int i = x + 1; i <= n; i ++) if (vis[i] || vis[i + n])
	{
		if (vis[i])
		{
			auto now = lower_bound(C.begin(), C.end(), s[i] - 'a' + 1);
			if (now == C.end()) return 0;
			if (*now > s[i] - 'a' + 1) return 1;
		}
		else
		{
			auto now = lower_bound(V.begin(), V.end(), s[i] - 'a' + 1);
			if (now == V.end()) return 0;
			if (*now > s[i] - 'a' + 1) return 1;
		}
	}
	return 1;
}

int main()
{
	scanf("%s", t + 1), l = strlen(t + 1);
	for (int i = 1; i <= l; i ++)
	{
		if (t[i] == 'V') V.push_back(i);
		else C.push_back(i);
	}
	n = read(), m = read();
	for (int i = 1; i <= m; i ++)
	{
		static char opt[5];
		int p1, p2, q1, q2;
		p1 = read(), scanf("%s", opt), q1 = p1 + (opt[0] == 'C') * n, p1 += (opt[0] == 'V') * n;
		p2 = read(), scanf("%s", opt), q2 = p2 + (opt[0] == 'C') * n, p2 += (opt[0] == 'V') * n;
		linker[p1].push_back(p2);
		linker[q2].push_back(q1);
	}
	scanf("%s", s + 1);
	int lcp = 0;
	for (int i = 1; i <= n; i ++)
		if (!check(i)) {lcp = i - 1; break;}
	if (lcp == n)
	{
		for (int i = 1; i <= n; i ++)
			putchar(s[i]);
		puts("");
		return 0;
	}
	memset(vis, 0, sizeof vis);
	int head = 1, tail = 0;
	for (int i = 1; i <= lcp; i ++)
	{
		int now = i + n * (s[i] == 'V');
		if (!vis[now]) vis[q[++ tail] = now] = 1;
	}
	int col = t[s[lcp + 1] - 'a' + 1] == 'V' ? 0 : 1;
	int now = (lcp + 1) + n * col;
	if (!vis[now]) vis[q[++ tail] = now] = 1;
	while (head <= tail)
	{
		int now = q[head ++];
		for (int cur : linker[now])
			if (!vis[cur]) vis[q[++ tail] = cur] = 1;
	}
	
	if (!Valid()) return puts("-1"), 0;
	
	for (int i = 1; i <= lcp; i ++) ans[i] = s[i];
//	cerr << "ck " << vis[lcp + 1] << " " << vis[lcp + 1 + n] << endl;
	if (vis[lcp + 1])
	{
		auto it = lower_bound(C.begin(), C.end(), s[lcp + 1] - 'a' + 1);
		if (it == C.end()) return puts("-1"), 0;
		ans[lcp + 1] = *it;
	}
	else
	{
		auto it = lower_bound(V.begin(), V.end(), s[lcp + 1] - 'a' + 1);
//		cerr << "ck" << (it == V.end()) << " " << V[0] << " " << s[lcp + 1] - 'a' + 1 << " " << s[lcp + 1] << endl;
		if (it == V.end()) return puts("-1"), 0;
		ans[lcp + 1] = *it;
	}
	for (int i = lcp + 2; i <= n; i ++)
	{
		if (vis[i]) ans[i] = C[0];
		else if (vis[i + n]) ans[i] = V[0];
		else if (V.empty())
		{
			ans[i] = C[0], vis[i] = 1, dfs(i);
			if (!Valid()) return puts("-1"), 0;
		}
		else if (C.empty())
		{
			ans[i] = V[0], vis[i + n] = 1, dfs(i + n);
			if (!Valid()) return puts("-1"), 0;
		}
		else
		{
			memset(mark, 0, sizeof mark);
			if (V[0] < C[0])
			{
				try_dfs(i + n);
				if (Valid())
				{
					for (int i = 1; i <= n * 2; i ++) vis[i] |= mark[i];
					ans[i] = V[0];
					memset(mark, 0, sizeof mark);
				}
				else
				{
					memset(mark, 0, sizeof mark);
					dfs(i), ans[i] = C[0];
					if (!Valid()) return puts("-1"), 0;
				}
			}
			else
			{
				try_dfs(i);
				if (Valid())
				{
					for (int i = 1; i <= n * 2; i ++) vis[i] |= mark[i];
					ans[i] = C[0];
					memset(mark, 0, sizeof mark);
				}
				else
				{
					memset(mark, 0, sizeof mark);
					dfs(i), ans[i] = V[0];
					if (!Valid()) return puts("-1"), 0;
				}
			}
		}
	}
	for (int i = 1; i <= n; i ++)
		putchar(ans[i] + 'a' - 1);
	puts("");
	return 0;
}
