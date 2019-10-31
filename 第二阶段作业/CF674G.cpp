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

typedef pair<int, int> mypair;

const int MAXN = 1.5e5 + 10;
int n, m, p, a[MAXN], cnt;

#define fi first
#define se second

inline bool cmp(const mypair &a, const mypair &b) {return a > b;}

struct info
{
	vector<mypair> v;
	info() {v.clear();}
	void fix() {sort(v.begin(), v.end(), cmp);}
	inline void add(int x, int y)
	{
		bool flag = 0;
		for (auto &cur : v)
		{
			if (cur.se == x)
			{
				cur.fi += y;
				flag = 1;
				break;
			}
		}
		if (flag)
		{
			fix();
			return;
		}
		if (v.size() < cnt)
		{
			v.push_back(mypair(y, x));
			fix(); return;
		}
		if (v.back().fi >= y)
		{
			for (auto &cur : v)
				cur.fi -= y; return;
		}
		else
		{
			int now = v.back().fi;
			v.pop_back();
			v.push_back(mypair(y, x));
			for (auto &cur : v)
				cur.fi -= now;
			fix(); return;
		}
	}
};

inline info Merge(const info &a, const info &b)
{
	info res = a;
	for (auto cur : b.v)
		res.add(cur.se, cur.fi);
	return res;
}

#define ls (x << 1)
#define rs (x << 1 | 1)

info sum[MAXN << 2];
int tag[MAXN << 2];

inline void update(int x) {sum[x] = Merge(sum[ls], sum[rs]);}

inline void operate(int x, int v, int sz)
{
	tag[x] = v;
	sum[x].v = vector<mypair>(1, mypair(sz, v));
}

inline void pushdown(int x, int l, int r)
{
	if (tag[x])
	{
		int v = tag[x];
		int mid = (l + r) >> 1;
		operate(ls, v, mid - l + 1);
		operate(rs, v, r - mid);
		tag[x] = 0;
	}
}

void Cover(int x, int l, int r, int ql, int qr, int v)
{
	if (l >= ql && r <= qr) return operate(x, v, r - l + 1);
	int mid = (l + r) >> 1; pushdown(x, l, r);
	if (ql <= mid) Cover(ls, l, mid, ql, qr, v);
	if (qr > mid) Cover(rs, mid + 1, r, ql, qr, v);
	update(x);
}

void build(int x, int l, int r)
{
	if (l == r) {sum[x].v = vector<mypair>(1, mypair(1, a[l])); return;}
	int mid = (l + r) >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	update(x);
}

info res;

void init() {res = info();}

void query(int x, int l, int r, int ql, int qr)
{
	if (l >= ql && r <= qr) {res = Merge(res, sum[x]); return;}
	int mid = (l + r) >> 1; pushdown(x, l, r);
	if (ql <= mid) query(ls, l, mid, ql, qr);
	if (qr > mid) query(rs, mid + 1, r, ql, qr);
}

int main()
{
//	freopen("input.txt", "r", stdin);
	n = read(), m = read(), p = read(), cnt = 100 / p;
	for (int i = 1; i <= n; i ++) a[i] = read();
	build(1, 1, n);
	while (m --)
	{
		int opt = read(), l = read(), r = read();
		if (opt == 1) {int id = read(); Cover(1, 1, n, l, r, id);}
		else
		{
			init(), query(1, 1, n, l, r);
			printf("%d ", res.v.size());
			for (auto cur : res.v)
				printf("%d ", cur.se);
			puts("");
		}
	}
	return 0;
}
