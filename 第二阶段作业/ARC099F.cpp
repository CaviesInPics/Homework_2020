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
inline int inc(int x, int y) {x += y; return x >= MOD ? x - MOD : x;}
inline int mul(int x, int y) {return 1LL * x * y % MOD;}
inline int qpow(int x, int y)
{
	int res = 1;
	for (; y; y >>= 1, x = 1LL * x * x % MOD)
		if (y & 1) res = 1LL * res * x % MOD;
	return res;
}

const int base[] = {23, 233, 2333, 23333, 1926, 817};
const int inv[] = {217009642, 844009174, 653800845, 823862834, 100031755, 814968156};

struct HashValue
{
	int v[6];
	HashValue() {memset(v, 0, sizeof v);}
	inline void operate(char opt)
	{
		for (int i = 0; i < 6; i ++)
		{
			if (opt == '+') v[i] = inc(v[i], 1);
			else if (opt == '-') v[i] = inc(v[i], MOD - 1);
			else if (opt == '>') v[i] = 1LL * v[i] * base[i] % MOD;
			else if (opt == '<') v[i] = 1LL * v[i] * inv[i] % MOD;
		}
	}
	inline bool operator == (const HashValue &rhs) const
	{
		for (int i = 0; i < 6; i ++) if (v[i] != rhs.v[i]) return 0;
		return 1;
	}
	inline bool operator < (const HashValue &rhs) const
	{
		for (int i = 0; i < 6; i ++)
			if (v[i] != rhs.v[i]) return v[i] < rhs.v[i];
		return 0;
	}
};

map<HashValue, int> bucket;
typedef pair<int, int> mypair;
#define fi first
#define se second

const int MAXN = 3e5 + 10;
int n; char s[MAXN]; ll ans;

int main()
{
	n = read(), scanf("%s", s + 1);
	HashValue now, all; mypair func[6];
	for (int i = 0; i < 6; i ++) func[i] = make_pair(1, 0);
	for (int i = n; i >= 1; i --) all.operate(s[i]); bucket[all] ++;
//	for (int i = 0; i < 6; i ++) assert(mul(base[i], inv[i]) == 1);
	int p = 0;
	for (int i = 1; i <= n; i ++)
	{
		if (s[i] == '>') p ++;
		else if (s[i] == '<') p --;
		else if (s[i] == '+')
		{
			for (int j = 0; j < 6; j ++)
				now.v[j] = inc(now.v[j], 1LL * (p >= 0 ? qpow(base[j], p) : qpow(inv[j], -p)) % MOD);
		}
		else
		{
			for (int j = 0; j < 6; j ++)
				now.v[j] = inc(now.v[j], MOD - 1LL * (p >= 0 ? qpow(base[j], p) : qpow(inv[j], -p)) % MOD);
		}
		ans += bucket[now];
//		if (bucket[now])
//			cerr << "i = " << i << endl;
		HashValue foo;
		for (int j = 0; j < 6; j ++)
		{
			if (s[i] == '+') func[j].se = inc(func[j].se, MOD - 1);
			else if (s[i] == '-') func[j].se = inc(func[j].se, 1);
			else if (s[i] == '>') func[j].fi = mul(func[j].fi, inv[j]), func[j].se = mul(func[j].se, inv[j]);
			else if (s[i] == '<') func[j].fi = mul(func[j].fi, base[j]), func[j].se = mul(func[j].se, base[j]);
			foo.v[j] = inc(all.v[j], MOD - func[j].se);
			if (func[j].fi) foo.v[j] = mul(foo.v[j], qpow(func[j].fi, MOD - 2));
		}
//		for (int j = 0; j < 6; j ++)
//			printf("(%dx+%d), ", func[j].fi, func[j].se); puts("");
		bucket[foo] ++;
	}
	cout << ans << endl;
	return 0;
}
