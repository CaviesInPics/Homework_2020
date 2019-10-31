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

typedef unsigned int uint;
uint c[135], a[135], b[135];

int main()
{
	int n, p, q;
	cin >> n >> p >> q;
	int up = min(n - 1, p);
	for (int i = 0; i <= up; i ++) c[i] = 1;
	for (int cur = 1; cur <= up; cur ++)
	{
		for (int i = 1; i <= cur; i ++)
			a[i] = n - i + 1, b[i] = i;
		for (int i = 1; i <= cur; i ++)
			if (b[i] > 1) for (int j = 1, d; j <= up; j ++)
				if ((d = __gcd(b[i], a[j])) > 1)
					a[j] /= d, b[i] /= d;
		for (int i = 1; i <= cur; i ++) assert(b[i] == 1);
		for (int i = 1; i <= cur; i ++) c[cur] *= a[i];
	}
	uint ans = 0;
	for (int i = 1; i <= q; i ++)
	{
		uint res = 0, now = 1;
		for (int k = 0; k <= up; k ++)
			res += now * c[k], now *= i;
		ans ^= res * i; 
	}
	printf("%u\n", ans);
	return 0;
}
