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

const int MAXN = 3005;
multiset<int> s;
int r, c, k, n, x[MAXN], y[MAXN]; ll ans = 0;
vector<int> foo[MAXN];

int main()
{
	r = read(), c = read(), n = read(), k = read();
	for (int i = 1; i <= n; i ++)
		x[i] = read(), y[i] = read();
	for (int i = 1; i <= n; i ++)
		foo[x[i]].push_back(i);
	for (int l = 1; l <= n; l ++)
	{
		s.clear();
		for (int i = 0; i <= k; i ++)
			s.insert(0), s.insert(c + 1);
		for (int r = l; r <= n; r ++)
		{
			for (int cur : foo[r])
			{
				s.insert(cur);
				auto it = s.find(cur);
				static int bar[25];
				for (int i = 0; i <= k; i ++) it --;
				for (int i = 0; i <= k; i ++) bar[i] = *it ++;
				it ++;
				for (int i = 1; i <= k; i ++) bar[i + k] = *it ++;
				for (int i = k + 1; i <= k + k; i ++)
					ans += 1LL * (bar[i] - bar[i - 1]) * (bar[i - k] - bar[i - k - 1]);
			}
		}
	}	

	return 0;
}
