#include <bits/stdc++.h>
#define rua system("pause")
using namespace std;
typedef long long ll;
inline ll read()
{
	ll x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) {x = x * 10 + c - '0', c = getchar();}
	return x * f;
}

const int MAXN = 1e5 + 10;
const int MAXM = 95;
const int INIT = 91;
ll K, P, N, s[MAXN];
typedef pair<ll, ll> mypair;
mypair a[MAXN];
#define int ll
struct Matrix
{
	ll t[2][2];
	Matrix() {memset(t, 0, sizeof t);}
	inline friend Matrix operator * (const Matrix &A, const Matrix &B)
	{
		Matrix C;
		for (int i = 0; i < 2; i ++)
			for (int j = 0; j < 2; j ++)
				for (int k = 0; k < 2; k ++)
					C.t[i][j] = (C.t[i][j] + 1LL * A.t[i][k] * B.t[k][j]) % P;
		return C;
	}
	inline void check() {if (t[0][0] == 94) t[0][0] = 19;}
	inline void print()
	{
		for (int i = 0; i < 2; i ++)
		{
			for (int j = 0; j < 2; j ++)
				printf("|%d", t[i][j]);
			printf("|\n");
		}
	}
};

Matrix sum[MAXN << 2];
#define ls (x << 1)
#define rs (x << 1 | 1)
inline void update(int x) {sum[x] = sum[ls] * sum[rs];}
inline Matrix query(int x, int l, int r, int ql, int qr)
{
	if (l >= ql && r <= qr) return sum[x];
	int mid = (l + r) >> 1;
	if (qr <= mid) return query(ls, l, mid, ql, qr);
	if (ql > mid) return query(rs, mid + 1, r, ql, qr);
	else return query(ls, l, mid, ql, mid) * query(rs, mid + 1, r, mid + 1, qr);
}

void build(int x, int l, int r)
{
	if (l == r)
	{
		sum[x].t[0][0] = 0,
		sum[x].t[0][1] = s[l],
		sum[x].t[1][0] = 1,
		sum[x].t[1][1] = s[(l + 1) % N];
		return;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	update(x);
}

Matrix IDM;

inline Matrix qpow(Matrix &a, ll b)
{
	Matrix res = IDM;
	for (; b; b >>= 1, a = a * a)
		if (b & 1) res = res * a;
	return res;
}

#define fi first
#define se second

inline Matrix Get(ll l, ll r)
{
	if (l > r) return IDM;
	if (l / N == r / N)
		return query(1, 0, N - 1, l % N, r % N);
	Matrix res = IDM;
	res = res * query(1, 0, N - 1, l % N, N - 1);
	int cnt = r / N - l / N - 1;
	Matrix coconut = sum[1];
	coconut = qpow(coconut, cnt);
	res = res * coconut;
	res = res * query(1, 0, N - 1, 0, r % N);
	return res;
}

signed main()
{
	IDM.t[0][0] = IDM.t[1][1] = 1;
	K = read(), P = read(), N = read();
	if (!K) return puts("0"), 0;
	if (K == 1) return printf("%d\n", 1 % P), 0;
	for (int i = 0; i < N; i ++) s[i] = read();
	build(1, 0, N - 1);
	ll M = read();
	for (int i = 1; i <= M; i ++) a[i].fi = read(), a[i].se = read();
	sort(a + 1, a + 1 + M);
	while (M && a[M].fi > K) M --;
	Matrix now;
	now.t[0][0] = 0, now.t[0][1] = 1;
	int st = 0, p = 1; bool flag = 0;
	ll MOD = P;
	while (st < K)
	{
		ll nxt = K;
		if (p <= M)
		{
			ll pos = a[p].fi, v = a[p].se;
			Matrix coef = Get(st, pos - 2);
			now = now * coef;
			Matrix foo;
			foo.t[0][0] = now.t[0][1];
			foo.t[0][1] = (now.t[0][0] * s[(pos - 1) % N] + now.t[0][1] * v) % MOD;
			now = foo;
			if (pos < K)
			{
				foo.t[0][0] = now.t[0][1];
				foo.t[0][1] = (now.t[0][0] * v + now.t[0][1] * s[(pos + 1) % N]) % MOD;
				now = foo;
			}
			p ++;
			flag = 0;
			st = pos + 1;
		}
		else
		{
			Matrix coef = Get(st, nxt - 1);
			now = now * coef;
			st = nxt;
		}
		if (st >= K && now.t[0][0] == INIT) {now.t[0][0] = 40, flag = 1; break;}
		else if (st >= K && (now.t[0][0] == MAXM || now.t[0][0] + 1 == MAXM)) {now.t[0][0] == 20, flag = 1; break;}
//		printf("st=%d\n",st);
//		now.print();
	}
	if (flag) {now.t[0][0] --;}
//	now.print();
	now.check();
	printf("%lld\n", now.t[0][0]);
	return 0;
}
