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

const int MAXN = 505;
const int MAXM = 1e5 + 10;

int n, prime[MAXM], pcnt;
ll t1[MAXN << 2], t2[MAXN << 2], a[MAXN][MAXN];
bool mark[MAXM];

void init(int m)
{
	for (int i = 2; i <= m; i ++)
	{
		if (!mark[i]) prime[++ pcnt] = i;
		for (int j = 1; j <= pcnt; j ++)
		{
			int np = prime[j], now = np * i;
			if (now > m) break; mark[now] = 1;
			if (i % np == 0) break;
		}
	}
}

inline ll gcd(ll x, ll y) {return y ? gcd(y, x % y) : x;}

inline ll lcm(ll x, ll y) {if (!x || !y) return x ^ y; return x / gcd(x, y) * y;}

int main()
{
	init(1e5);
	n = read();
	if (n == 1) return puts("1"), 0;
	if (n == 2) return printf("4 7\n23 10\n"), 0;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			if (!((i + j) & 1)) a[i][j] = prime[(i - j + n + 1) / 2 + n] * prime[(i + j) >> 1];
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			if ((i + j) & 1) a[i][j] = lcm(a[i - 1][j], lcm(a[i][j - 1], lcm(a[i + 1][j], a[i][j + 1]))) + 1;
//	ll mx = 0;
//	for (int i = 1; i <= n; i ++)
//		for (int j = 1; j <= n;j ++)
//			mx = max(mx, a[i][j]);
//	cerr << mx << endl; return 0;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			printf("%lld%c", a[i][j], j == n ? 10 : 32);
	return 0;
}
