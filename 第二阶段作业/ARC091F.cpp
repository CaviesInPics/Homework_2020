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

int n, a[205], b[205], mx, blk;

inline int GetSG(int x, int k)
{
	if (x % k == 0) return x / k;
	int now = x / k;
	if (now >= blk) return GetSG(x - now - 1, k);
	int step = x % k / (now + 1);
	return GetSG(x - (now + 1) * max(step, 1), k);
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i ++)
		cin >> a[i] >> b[i], mx = max(mx, a[i]);
	blk = sqrt(mx) + 1;
	int ans = 0;
	for (int i = 1; i <= n; i ++) ans ^= GetSG(a[i], b[i]);
	puts(ans ? "Takahashi" : "Aoki");
	return 0;
}

