#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
inline int inc(int x, int y) {x += y; return x >= mod ? x - mod : x;}
const int maxn = 3405;
string a; vector<int> b;
int n, p, k, f[maxn][maxn][2][2];
typedef pair<string, int> mypair;
mypair chu(string now)
{
	ll foo = 0; string res = "";
	for (int i = 0; i < now.length(); i ++)
	{
		foo = foo * 10LL + now[i] - '0';
		if (foo >= p || res.size())
		{
			res.push_back(foo / p + '0');
			foo %= p;
		}
	}
	if (res.empty()) res = "0";
	return mypair(res, foo);
}

inline void add(int &x, int y) {y += x; x = y >= mod ? y - mod : y;}

inline ll sum(int x) {return 1ll * x * (x + 1) / 2;}

int main()
{
	ios::sync_with_stdio(false);
	cin >> p >> k;
	cin >> a;
	while (a != "0")
	{
		mypair cur = chu(a);
		a = cur.first;
		b.push_back(cur.second);
	}
	reverse(b.begin(), b.end());
	f[0][0][1][0] = 1;
	for (int i = 0; i < b.size(); i ++)
	{
		int up = b[i];
		for (int j = 0; j <= i; j ++)
		{
			int coef1 = 1ll * p * (p + 1) / 2 % mod;
			int coef2 = 1ll * p * (p - 1) / 2 % mod;
			int coef3 = (1ll * p * p - coef1) % mod;
			int coef4 = (1ll * p * p - coef2) % mod;
			add(f[i + 1][j][0][0], 1ll * f[i][j][0][0] * coef1 % mod);
			add(f[i + 1][j][0][1], 1ll * f[i][j][0][0] * coef2 % mod);
			add(f[i + 1][j + 1][0][0], 1ll * f[i][j][0][1] * coef3 % mod);
			add(f[i + 1][j + 1][0][1], 1ll * f[i][j][0][1] * coef4 % mod);
			if (up)
			{
				coef1 = 1ll * up * (up + 1) / 2 % mod;
				coef2 = 1ll * up * (up - 1) / 2 % mod;
				coef3 = (1ll * up * (p - up - 1) + 1ll * up * (up + 1) / 2) % mod;
				coef4 = (1ll * up * (p - up) + 1ll * up * (up + 1) / 2) % mod;
//				cerr << coef1 << " " << coef2 << " " << coef3 << " " << coef4 << endl;
				add(f[i + 1][j][1][0], 1ll * f[i][j][1][0] * (up + 1) % mod);
				add(f[i + 1][j][0][0], 1ll * f[i][j][1][0] * coef1 % mod);
				add(f[i + 1][j][0][1], 1ll * f[i][j][1][0] * coef2 % mod);
				add(f[i + 1][j][1][1], 1ll * f[i][j][1][0] * up % mod);
				add(f[i + 1][j + 1][0][0], 1ll * f[i][j][1][1] * coef3 % mod);
				add(f[i + 1][j + 1][0][1], 1ll * f[i][j][1][1] * coef4 % mod);
				add(f[i + 1][j + 1][1][0], 1ll * f[i][j][1][1] * (p - up - 1) % mod);
				add(f[i + 1][j + 1][1][1], 1ll * f[i][j][1][1] * (p - up) % mod);
			}
			else
			{
				add(f[i + 1][j][1][0], f[i][j][1][0]);
				add(f[i + 1][j + 1][1][0], 1ll * f[i][j][1][1] * (p - 1) % mod);
				add(f[i + 1][j + 1][1][1], 1ll * f[i][j][1][1] * p % mod);
			}
		}
	}
	int ans = 0;
	for (int i = k; i < b.size(); i ++)
		add(ans, inc(f[b.size()][i][0][0], f[b.size()][i][1][0]));
	cout << ans << endl;
	return 0;
}
