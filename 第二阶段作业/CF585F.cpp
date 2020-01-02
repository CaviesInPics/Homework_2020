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

const int MAXN = 1005;
const int MAXM = 50005;

char s[MAXM]; bool isend[MAXM]; string L, R;
int n, rt = 1, tot = 1, ch[MAXM][10], fail[MAXM], d;

inline void insert(int l, int r)
{
	int now = rt;
	for (int i = l; i <= r; i ++)
	{
		int c = s[i] - '0';
		if (!ch[now][c]) ch[now][c] = ++ tot;
		now = ch[now][c];
	}
	isend[now] = 1;
}

inline void build()
{
	static int q[MAXM], head, tail;
	head = 1, tail = 0;
	fail[1] = 1;
	for (int i = 0; i < 10; i ++)
	{
		if (ch[1][i]) fail[q[++ tail] = ch[1][i]] = 1;
		else ch[1][i] = 1;
	}
	while (head <= tail)
	{
		int x = q[head ++];
		if (isend[fail[x]]) isend[x] = 1;
		for (int i = 0; i < 10; i ++)
		{
			if (!ch[x][i]) ch[x][i] = ch[fail[x]][i];
			else fail[q[++ tail] = ch[x][i]] = ch[fail[x]][i];
		}
	}
}

const int MOD = 1e9 + 7;
inline int inc(int x, int y) {x += y; return x >= MOD ? x - MOD : x;}

int f[2][MAXN][2];

inline ll Solve(string t)
{
	memset(f, 0, sizeof f);
	f[0][1][1] = 1;
	for (int i = 0; i < d; i ++)
	{
		int np = i & 1, p = np ^ 1;
		memset(f[p], 0, sizeof f[p]);
		for (int j = 1; j <= tot; j ++) if (!isend[j])
			for (int k = 0; k < 2; k ++) if (f[np][j][k])
			{
				int now = f[np][j][k];
//				cerr << i << " " << j << " " << k << " " << now << endl;
				if (k)
				{
					for (int c = 0; c < t[i] - '0'; c ++)
					{
						f[p][ch[j][c]][0] = inc(f[p][ch[j][c]][0], now);
					}
					int c = t[i] - '0';
					f[p][ch[j][c]][k] = inc(f[p][ch[j][c]][k], now);
//						if (i == 1 && j == 1 && k == 1 && t == R)
//							cerr << ch[j][c] << " " << c << endl;
				}
				else
				{
					for (int c = 0; c < 10; c ++)
						f[p][ch[j][c]][0] = inc(f[p][ch[j][c]][0], now);
				}
			}
	}
	int opt = d & 1, res = 0;
	for (int i = 1; i <= tot; i ++) if (!isend[i])
		for (int j = 0; j < 2; j ++)
			res = inc(res, f[opt][i][j]);
	int all = 0;
	for (int i = 0; i < d; i ++)
		all = (1LL * all * 10 + t[i] - '0') % MOD;
//	if (t == R) cerr << "al" << all << " " << res << endl;
	return (all - res + MOD) % MOD;
}

inline int check(string t)
{
	for (int i = 0; i < t.size() - d / 2 + 1; i ++)
		for (int j = 1; j <= n - d / 2 + 1; j ++)
		{
			bool f = 1;
			for (int k = 0; k < d / 2; k ++)
				if (s[j + k] != t[i + k])
				{
					f = 0;
					break;
				}
			if (f) return 1;
		}
	return 0;
}

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	cin >> L >> R;
	d = L.length();
	for (int i = 1; i <= n - d / 2 + 1; i ++) insert(i, i + d / 2 - 1);
	build();
//	cerr << Solve(L) << " " << Solve(R) << endl;
	printf("%d\n", (Solve(R) - Solve(L) + check(L) + MOD) % MOD);
	return 0;
}

