#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3005;
char s[maxn << 1];
int n, a[maxn], b[maxn], pos[maxn << 1];
bool dp[maxn][maxn];

string get_s(int x)
{
	string ans = "";
	for (int i = 1; i <= n * 2; i ++)
		if (dp[x][pos[i]]) ans.push_back(s[i]);
	return ans;
}

int main()
{
	cin >> n;
	scanf("%s", s + 1);
	int ta = 0, tb = 0;
	for (int i = 1; i <= n * 2; i ++)
	{
		if (s[i] == 'a') a[++ ta] = i, pos[i] = ta;
		else b[++ tb] = i, pos[i] = tb;
	}
	dp[n][n] = 1;
	for (int i = n - 1; i >= 1; i --)
	{
		dp[i][i] = 1;
		if (b[i] > a[i])
		{
			int k = i;
			for (int j = a[i] + 1; j <= b[i]; j ++)
				if (s[j] == 'a') k = max(k, pos[j]);
			for (int j = i + 1; j <= k; j ++)
				dp[i][j] = 0;
			for (int j = k + 1; j <= n; j ++)
				dp[i][j] = dp[k + 1][j];
		}
		else
		{
			int k = i, r = a[i];
			for (int j = b[i]; j <= r; j ++)
			{
				if (s[j] == 'b')
				{
					r = max(r, a[pos[j]]);
					k = max(k, pos[j]);
				}
			}
			for (int j = i + 1; j <= k; j ++)
				dp[i][j] = 1;
			for (int j = k + 1; j <= n; j ++)
				dp[i][j] = dp[k + 1][j];
		}
		if (get_s(i) < get_s(i + 1))
		{
			for (int j = 1; j <= n; j ++)
				dp[i][j] = dp[i + 1][j];
		}
	}
	cout << get_s(1) << endl;
	return 0;
}