#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
int n, k, len;
int main()
{
	cin >> n >> k;
	int l = 1; bool flag = 0;
	for (int i = 1; i < k; i ++)
	{
		l <<= 1;
		if (l >= n)
		{
			flag = 1;
			break;
		}
	}
	cin >> s;
	string t = s;
	reverse(t.begin(), t.end());
	s.append(t);
	char mn = 'z';
	for (int i = 0; i < n; i ++)
		mn = min(mn, s[i]);
	if (flag)
	{
		for (int i = 0; i < n; i ++)
			putchar(mn);
		puts("");
		return 0;
	}
	len = 0;
	vector<int> foo(n << 1);
	for (int i = 0; i < n + n; i ++) if (s[i] == mn)
	{
		int cnt = 0;
		for (int j = i; j < n + n; j ++)
		{
			if (s[j] != mn) break;
			++ cnt;
		}
		foo[i] = cnt;
		len = max(len, cnt);
	}
	int _len = len;
	len = min(len, n);
	for (int i = 1; i <= k - 1; i ++)
		len = min(len << 1, n);
	if (len >= n)
	{
		for (int i = 1; i <= n; i ++)
			putchar(mn);
		puts("");
		return 0;
	}
	int rem = n - len; string ans = "";
	for (int i = 0; i < n; i ++)
	{
		if (foo[i] >= _len)
		{
			string bar = s.substr(i + _len, rem);
			if (ans == "")
			{
				ans = bar;
			}
			else
			{
				if (ans > bar)
					ans = bar;
			}
		}
	}
	for (int i = 0; i < len; i ++) putchar(mn);
	cout << ans << endl;
}