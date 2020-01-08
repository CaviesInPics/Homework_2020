#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double db;

const ll inf = 1ll << 60;

const int maxn = 1e5 + 10;
int n, l, id[maxn], _t[maxn];
ll t[maxn], x[maxn], y[maxn];
ll ans_x[maxn], ans_y[maxn];

inline bool cmp(const int &a, const int &b) {return _t[a] < _t[b];}

inline bool sgn(ll x) {return x > 0 ? 1 : -1;}

inline void designate(int l, int r, ll d_x, ll d_y)
{
	if (((r - l + 1) & 1) != (abs(d_x) & 1) || (((r - l + 1) & 1) != (abs(d_y) & 1)))
	{
		puts("NO");
		exit(0);
	}
	if (abs(d_x) > (r - l + 1) || abs(d_y) > (r - l + 1))
	{
		puts("NO");
		exit(0);
	}
	for (int i = l; i <= l + (abs(d_x) - 1); i ++)
		ans_x[i] = sgn(d_x);
	for (int i = l + abs(d_x); i <= r; i ++)
	{
		ans_x[i] = (i & 1) ? 1 : -1;
	}
	for (int i = l; i <= l + (abs(d_y) - 1); i ++)
		ans_y[i] = sgn(d_y);
	for (int i = l + abs(d_y); i <= r; i ++)
	{
		ans_y[i] = (i & 1) ? 1 : -1;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> l;
	for (int i = 1; i <= n; i ++)
		cin >> t[i] >> x[i] >> y[i], _t[i] = t[i] % l;
	for (int i = 1; i <= n; i ++)
	{
		ll u = x[i] + y[i], v = x[i] - y[i];
		x[i] = u, y[i] = v;
	}
	for (int i = 1; i <= n; i ++) id[i] = i;
	sort(id + 1, id + 1 + n, cmp);
	bool flag = 0; ll all_x = 0, all_y = 0;
	for (int i = 2; i <= n; i ++)
	{
		if (_t[id[i]] == _t[id[i - 1]])
		{
			ll turn = ((t[id[i]] - t[id[i - 1]]) / l);
			if (!flag)
			{
				flag = 1;
				all_x = (x[id[i]] - x[id[i - 1]]) / turn;
				all_y = (y[id[i]] - y[id[i - 1]]) / turn;
			}
			else
			{
				if (all_x != ((x[id[i]] - x[id[i - 1]]) / turn) || all_y != ((y[id[i]] - y[id[i - 1]]) / turn))
					return puts("NO"), 0;
			}
		}
	}
	if (flag)
	{
		for (int i = 1; i <= n; i ++)
		{
			if (_t[id[i]] != _t[id[i - 1]])
			{
				ll d_t = _t[id[i]] - _t[id[i - 1]];
				ll d_x = x[id[i]] - x[id[i - 1]];
				ll d_y = y[id[i]] - y[id[i - 1]];
				ll turn = (t[id[i]] - _t[id[i]] - (t[id[i - 1]] - _t[id[i - 1]])) / l;
				d_x -= turn * all_x;
				d_y -= turn * all_y;
				if (abs(d_x) > d_t || abs(d_y) > d_t)
					return puts("NO"), 0;
				designate(_t[id[i - 1]] + 1, _t[id[i]], d_x, d_y);
			}
		}
	}
	else
	{
		db up = inf, down = -inf;
		ll coef1 = 0, coef2 = 0;
		for (int i = 1; i <= n; i ++)
			ll d_t = _t[id[i]] - _t[id[i - 1]];
			ll d_x = x[id[i]] - x[id[i - 1]];
			ll coef = ((t[id[i]] - _t[id[i]]) - (t[id[i - 1]] - _t[id[i - 1]])) / l;
			coef = -coef, coef1 += coef, coef2 += d_x;
			// abs(coef * all + d_x) <= d_t
			if (coef == 0 && abs(d_x) > d_t) return puts("NO"), 0;
			if (coef > 0) up = min(up, 1.0l * (d_t - d_x) / coef), down = max(down, 1.0l * (-d_t - d_x) / coef);
			else up = min(up, 1.0l * (-d_t - d_x) / coef), down = max(down, 1.0l * (d_t - d_x) / coef);
		}
	}
}