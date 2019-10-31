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

const int MOD = 998244353;
inline int mul(int x, int y) {return (ll)x * y % MOD;}
inline int inc(int x, int y) {x += y; return x >= MOD ? x - MOD : x;}
inline void add(int &x, int y) {y += x; x = y >= MOD ? y - MOD : y;}

map<string, int> f;
int pw[105]; string s;

int dfs(const string &s)
{
	if (s.length() == 0) return 1;
	else if (s.length() == 1) return s[0] - '0' + 1;
	if (f.count(s)) return f[s];
	int res = 0, len = s.length();
	if (s[0] == '0') res = dfs(s.substr(1, len - 1));
	else res = mul(dfs(s.substr(1, len - 1)), 2);
	for (int i = 1; i * 2 <= len; i ++)
	{
		string cur = s.substr(0, i);
		for (int j = 2; j * i <= len; j ++)
		{
			int st = (j - 1) * i, ed = j * i, cnt = 0;
			for (int k = 0; k < i; k ++)
			{
				if (cur[k] == '1')
				{
					if (s[k + st] == '1') ++ cnt;
					else cur[k] = '0';
				}
			}
			add(res, mul(dfs(cur), dfs(s.substr(ed, len - ed))));
		}
	}
	return f[s] = res;
}

int main()
{
	pw[0] = 1;
	for (int i = 1; i <= 100; i ++) pw[i] = mul(pw[i - 1], 2);
	cin >> s;
	cout << dfs(s) << endl;	

	return 0;
}
