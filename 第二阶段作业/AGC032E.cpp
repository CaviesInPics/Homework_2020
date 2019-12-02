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

const int MAXN = 2e5 + 10;
int n, m, a[MAXN];

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n * 2; i ++) a[i] = read();
	sort(a + 1, a + 1 + n * 2);
	int l = 0, r = n, res = 0;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		bool flag = 1;
		for (int i = 1; i <= n - mid; i ++)
			if ((a[n * 2 - i + 1] + a[mid * 2 + i]) < m) flag = 0;
		if (flag) res = mid, r = mid - 1;
		else l = mid + 1;
	}
	int ans = 0;
	for (int i = 1; i <= res; i ++)
		ans = max(ans, a[i] + a[res * 2 - i + 1]);
	for (int i = 1; i <= n - res; i ++)
		ans = max(ans, (a[n * 2 - i + 1] + a[res * 2 + i]) % m);
	printf("%d\n", ans);
	return 0;
}
