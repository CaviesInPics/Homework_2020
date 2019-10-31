#include <bits/stdc++.h>
#define rua system("pause")
using namespace std;
typedef long long ll;
#define int ll
inline int read()
{
	int x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) {x = x * 10 + c - '0', c = getchar();}
	return x * f;
}


const int MAXN = 4e5 + 10;

int n, m, a[MAXN];
ll pw[20], mn[MAXN], add_tag[MAXN], cover[MAXN], val[MAXN];

#define ls (x << 1)
#define rs (x << 1 | 1)

inline int find(ll x) {return lower_bound(pw, pw + 12, x) - pw;}

inline ll calc(ll x) {return pw[find(x)] - x;}

inline void update(int x) {mn[x] = min(mn[ls], mn[rs]);}

inline void operate_add(int x, ll v)
{
	if (cover[x])
	{
		cover[x] += v;
		val[x] += v;
		mn[x] -= v;
	}
	else
	{
		add_tag[x] += v;
		val[x] += v;
		mn[x] -= v;
	}
}

inline void pushdown(int x)
{
	if (cover[x])
	{
		ll v = cover[x];
		cover[x] = 0;
		cover[ls] = v;
		val[ls] = v;
		cover[rs] = v;
		val[rs] = v;
		add_tag[ls] = add_tag[rs] = 0;
		mn[ls] = mn[rs] = calc(v);
	}
	else if (add_tag[x])
	{
		ll v = add_tag[x];
		operate_add(ls, v);
		operate_add(rs, v);
		add_tag[x] = 0;
	}
}

int query(int x, int l, int r, int pos)
{
	if (l == r) return val[x];
	int mid = (l + r) >> 1; pushdown(x);
	if (pos <= mid) return query(ls, l, mid, pos);
	else return query(rs, mid + 1, r, pos);
}

#define bound (l == 4 && r == 6)

void fix(int x, int l, int r)
{
	if (mn[x] >= 0) return;
	if (l == r || cover[x]) {mn[x] = calc(val[x]); return;}
	int mid = (l + r) >> 1; pushdown(x);
	fix(ls, l, mid); fix(rs, mid + 1, r);
	update(x);
}

void Cover(int x, int l, int r, int ql, int qr, int v)
{
	if (l >= ql && r <= qr) {val[x] = cover[x] = v, add_tag[x] = 0, mn[x] = calc(v); return;}
	int mid = (l + r) >> 1; pushdown(x);
	if (ql <= mid) Cover(ls, l, mid, ql, qr, v);
	if (qr > mid) Cover(rs, mid + 1, r, ql, qr, v);
	update(x);
}

bool flag = 0;

void Modify(int x, int l, int r, int ql, int qr, int v)
{
	if (l >= ql && r <= qr)
	{
		operate_add(x, v);
		fix(x, l, r);
		if (mn[x] == 0) flag = 1;
		return;
	}
	int mid = (l + r) >> 1; pushdown(x);
	if (ql <= mid) Modify(ls, l, mid, ql, qr, v);
	if (qr > mid) Modify(rs, mid + 1, r, ql, qr, v);
	update(x);
}

void build(int x, int l, int r)
{
	if (l == r)
	{
		cover[x] = val[x] = a[l];
		mn[x] = calc(val[x]);
		return;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	update(x);
}

signed main()
{
//	freopen("input.txt", "r", stdin);
	pw[0] = 1;
	for (int i = 1; i <= 11; i ++) pw[i] = pw[i - 1] * 42LL;
	n = read(), m = read();
	for (int i = 1; i <= n; i ++) a[i] = read();
	build(1, 1, n);
	while (m --)
	{
		int opt = read();
		if (opt == 1)
		{
			int x = read();
			printf("%lld\n", query(1, 1, n, x));
		}
		else if (opt == 2)
		{
			int l = read(), r = read(), x = read();
			Cover(1, 1, n, l, r, x);
		}
		else
		{
			int l = read(), r = read(), x = read();
			flag = 1;
			while (flag)
			{
				flag = 0;
				Modify(1, 1, n, l, r, x);
			}
		}
	}
	return 0;
}
