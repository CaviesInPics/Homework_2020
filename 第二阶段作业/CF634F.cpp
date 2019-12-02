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
	for (int l = 1; l <= ::r; l ++)
	{
		s.clear();
		for (int i = 0; i <= k + 1; i ++)
			s.insert(0), s.insert(c + 1);
		for (int r = l; r <= ::r; r ++)
		{
			for (auto cur : foo[r])
			{
				auto it = s.insert(y[cur]), it2 = it;
				assert(it != s.end() && *it == y[cur]);
				static int pos[MAXN];
				for (int i = k; i >= 0; i --) pos[i] = *it --;
				for (int i = k + 1; i <= 2 * k; i ++) pos[i] = *(++ it2);
//				for (int i = 0; i <= 2 * k; i ++) printf("%d ", pos[i]); puts("");
				for (int i = k; i <= 2 * k - 1; i ++)
					ans += 1LL * (pos[i + 1] - pos[i]) * (::r - r + 1) * (pos[i - k + 1] - pos[i - k]);
//				cerr << ans << endl;
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
