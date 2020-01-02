#include <bits/stdc++.h>
#define rua system("pause")
using namespace std;
typedef long long ll;

const int MAXN = 755;
const int MAXM = 1e7 + 10;
vector<char> s[MAXN];
bool g[MAXN][MAXN];
int n, fail[MAXM], tot = 1, ch[MAXM][2], any[MAXM];

void build()
{
	int head = 1, tail = 0;
	static int q[MAXM];
	fail[1] = 1;
	for (int i = 0; i < 2; i ++)
		if (!ch[1][i]) ch[1][i] = 1;
		else fail[q[++ tail] = ch[1][i]] = 1; 
	while (head <= tail)
	{
		int x = q[head ++];
		if (!any[x]) any[x] = any[fail[x]];
		for (int i = 0; i < 2; i ++)
		{
			if (ch[x][i])
			{
				fail[ch[x][i]] = ch[fail[x]][i];
				q[++ tail] = ch[x][i];
			}
			else ch[x][i] = ch[fail[x]][i];
		}
	}
}

bool vis[MAXN];
int match[MAXN];

inline int find(int x)
{
	for (int i = 1; i <= n; i ++)
	{
		if (g[x][i] && !vis[i])
		{
			vis[i] = 1;
			if (!match[i] || find(match[i]))
			{
				match[i] = x;
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
	{
		static char buf[MAXM];
		scanf("%s", buf);
		int len = strlen(buf);
		s[i].resize(len);
		for (int j = 0; j < len; j ++)
			s[i][j] = buf[j];
	}
	
	for (int i = 1; i <= n; i ++)
	{
		int now = 1;
		for (int j = 0; j < s[i].size(); j ++)
		{
			char c = s[i][j] - 'a';
			if (!ch[now][c]) ch[now][c] = ++ tot;
			now = ch[now][c];
		}
		any[now] = i;
	}
	build();
	for (int i = 1; i <= n; i ++)
	{
		int now = 1;
		for (int j = 0; j < s[i].size(); j ++)
		{
			char c = s[i][j] - 'a';
			now = ch[now][c];
			if (any[now] == i)
			{
				if (any[fail[now]])
					g[i][any[fail[now]]] = 1;
			}
			else if (any[now])
				g[i][any[now]] = 1;
		}
	}
	for (int k = 1; k <= n; k ++)
		for (int i = 1; i <= n; i ++) if (g[i][k])
			for (int j = 1; j <= n; j ++) if (g[k][j]) g[i][j] = 1;
	vector<int> ed(0);
	for (int i = 1; i <= n; i ++)
	{
		memset(vis, 0, sizeof vis);
		if (!find(i)) ed.push_back(i);
	}
	printf("%d\n", ed.size());
	bool flag = 0;
	do
	{
		flag = 0;
		static bool mark[MAXN];
		memset(mark, 0, sizeof mark);
		for (int cur : ed)
			for (int i = 1; i <= n; i ++)
				mark[i] |= g[cur][i];
		for (int &cur : ed)
		{
			while (mark[cur]) cur = match[cur], flag = 1;
		}
	} while (flag);
	for (int cur : ed) printf("%d ", cur); puts("");
	return 0;
}
