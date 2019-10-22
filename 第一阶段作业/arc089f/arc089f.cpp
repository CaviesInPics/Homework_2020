#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;
inline int inc(int x, int y) {x += y; return x >= MOD ? x - MOD : x;}
inline void add(int &x, int y) {y += x; x = y >= MOD ? y - MOD : y;}
inline int mul(int x, int y) {return (ll)x * y % MOD;}
inline int qpow(int x, int y)
{
	int res = 1;
	for (; y; y >>= 1, x = mul(x, x))
		if (y & 1) res = mul(res, x);
	return res;
}

string s;
int n, k;

#define N n
#define K k
bool C(vector<int> &v) {
	bool used[70] = {};
	int pos[70];
	int now= 0;
	for (int i = 0; i < v.size(); i++) {
		while (now < s.size()) {
			if (s[now] == 'r') break;
			now++;
		}
		if (now == s.size()) return 0;
		used[now] = 1;
		pos[i] = now;
		now++;
	}
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == 1) break;
		now = pos[i] + 1;
		while (now < s.size()) {
			if (!used[now] && s[now] == 'b') break;
			now++;
		}
		if (now == s.size()) return 0;
		used[now] = 1;
		pos[i] = now;
	}
	for (int i = 0; i < v.size(); i++) {
		if (v[i] <= 2) break;
		int cnt = 0;
		now = pos[i] + 1;
		while (now < s.size()) {
			if (!used[now]) {
				used[now] = 1;
				cnt++;
			}
			if (cnt >= v[i] - 2) break;
			now++;
 		}
		if (now == s.size()) return 0;
	}
	return 1;
}

bool check(vector<int> &v)
{
	static int pos[75], use[75];
	memset(pos, 0, sizeof pos);
	memset(use, 0, sizeof use);
	int now = 0;
	for (int i = 0; i < v.size(); i ++)
	{
		while (now < k)
		{
			if (s[now] == 'r') break;
			now ++;
		}
		if (now == k) return 0;
		pos[i] = now, use[now] = 1;
		now ++;
	}
	for (int i = 0; i < v.size(); i ++)
	{
		if (v[i] < 2) continue;
		now = pos[i] + 1;
		while (now < k)
		{
			if (!use[now] && s[now] == 'b') break;
			now ++;
		}
		if (now == k) return 0;
		use[now] = 1, pos[i] = now;
		now ++;
	}
	for (int i = 0; i < v.size(); i ++)
	{
		if (v[i] < 3) continue;
		int cnt = 0;
		now = pos[i] + 1;
		while (now < k)
		{
			if (!use[now])
			{
				++ cnt, use[now] = 1;
				if (cnt + 2 == v[i])
					break;
			}
			now ++;
		}
		if (now == k) return 0;
	}
	return 1;
}

int fac[205], ifac[205];

inline int binom(int x, int y)
{
	if (y > x || y < 0) return 0;
	return mul(mul(fac[x], ifac[y]), ifac[x - y]);
}

int Getans(vector<int> &v)
{
	if (v.empty()) return 1;
	if (v.size() == 1)
	{
		if (v[0] == 1) return binom(n + 1, 2);
		else return binom(n + 3, v[0] * 2);
	}
	static int buc[75];
	memset(buc, 0, sizeof buc);
	for (int i = 0; i < v.size(); i ++)
		buc[v[i]] ++;
	int res = fac[v.size()];
	for (int i = 1; i <= n; i ++)
		res = mul(res, ifac[buc[i]]);
	int num = n + 1, pos = 0;
	for (int i = 0; i < v.size(); i ++)
	{
		pos += v[i] * 2;
		if (v[i] >= 2) num += 2;
	}
	return mul(res, binom(num, pos));
}

int ans;
void dfs(int now, int remain, int pre, vector<int> &v)
{
	if (check(v)) add(ans, Getans(v));
	for (int i = min(remain, pre); i >= 1; i --)
	{
		int cnt = i == 1 ? 1 : ((i - 1) * 2 - 1); // BR...RB
		if (now + cnt + max(0, (int)v.size() - 1) > n) continue;
		v.push_back(i);
		dfs(now + cnt, remain - i, i, v);
		v.pop_back();
	}
}

int main()
{
	cin >> n >> k >> s;
	fac[0] = ifac[0] = 1;
	for (int i = 1; i <= 200; i ++) fac[i] = mul(fac[i - 1], i);
	ifac[200] = qpow(fac[200], MOD - 2);
	for (int i = 200; i >= 1; i --) ifac[i - 1] = mul(ifac[i], i);
	vector<int> foo(0); ans = 0;
	dfs(0, k, k, foo);
	cout << ans << endl;
	return 0;
}
