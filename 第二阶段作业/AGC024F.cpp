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

char buf[(1 << 20) + 5];
int n, a[(1 << 21) + 5];
vector<int> dp[1 << 21];
int nxt[1 << 21][2], mylog[1 << 21];

int main()
{	
	n = read(); int lim = read();
	mylog[1] = 0;
	for (int i = 2; i < (1 << (n + 1)); i ++)
		mylog[i] = mylog[i >> 1] + 1;
		
	for (int i = 0; i <= n; i ++)
	{
		scanf("%s", buf);
		for (int j = 0; j < (1 << i); j ++)
			if (buf[j] == '1') a[j | (1 << i)] = 1;
	}
	
	nxt[1][0] = nxt[1][1] = 0;
	for (int s = 2; s < (1 << (n + 1)); s ++)
	{
		static int foo[25], bar[25];
		int cnt = 0, _s = s;
		while (_s) foo[cnt ++] = _s & 1, _s >>= 1;
		bar[0] = foo[0];
		for (int i = 1; i < cnt; i ++)
			bar[i] = foo[i] << i | bar[i - 1];
		for (int i = cnt - 2; i >= 0; i --)
		{
			if (!nxt[s][foo[i]])
				nxt[s][foo[i]] = (i ? bar[i - 1] : 0) | (1 << i);
		}
	}
	
	for (int s = 1; s < (1 << (n + 1)); s ++)
	{
		int cnt = 0, _s = s;
		while (_s) cnt ++, _s >>= 1;
		dp[s].resize(1 << (n + 2 - cnt));
	}
	
	for (int s = 0; s < (1 << (n + 1)); s ++) dp[1][s] = a[s];
	
	int ans = 0;
	for (int s = 1; s < (1 << (n + 1)); s ++)
		for (int j = 1; j < dp[s].size(); j ++) if (dp[s][j])
		{
			int now = dp[s][j];
			if (nxt[j][0]) dp[s << 1][nxt[j][0]] += now; // , assert(nxt[j][0] < dp[s << 1].size());
			if (nxt[j][1]) dp[s << 1 | 1][nxt[j][1]] += now; // , assert(nxt[j][1] < dp[s << 1 | 1].size());
		}
	for (int s = 1; s < (1 << (n + 1)); s ++)
	{
		int res = 0;
		for (int j = 1; j < dp[s].size(); j ++) res += dp[s][j];
		if (res >= lim)
		{
			if ((mylog[s] > mylog[ans])) ans = s;
			else if (mylog[s] == mylog[ans] && s < ans) ans = s;
		}
	}
	for (int i = mylog[ans] - 1; i >= 0; i --)
		putchar(((ans >> i) & 1) + '0');
	puts("");
	return 0;
}
