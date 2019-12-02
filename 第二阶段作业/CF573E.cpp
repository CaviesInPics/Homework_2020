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

mt19937 rnd(time(0));

const int MAXN = 2e5 + 10;
int n, a[MAXN], sz[MAXN], ls[MAXN], rs[MAXN], rnk[MAXN], tot;
ll w[MAXN], tag1[MAXN], tag2[MAXN];

inline void update(int x) {sz[x] = sz[ls[x]] + sz[rs[x]] + 1;}
inline void operate(int x, ll v1, ll v2) {tag1[x] += v1, tag2[x] += v2, w[x] += v1 * sz[ls[x]] + v2;}
inline void pushdown(int x)
{
	if (tag1[x] || tag2[x])
	{
		if (ls[x]) operate(ls[x], tag1[x], tag2[x]);
		if (rs[x]) operate(rs[x], tag1[x], tag2[x] + 1LL * (sz[ls[x]] + 1) * tag1[x]);
		tag1[x] = tag2[x] = 0;
	}
}
int merge(int x, int y)
{
	if (!x || !y) return x ^ y;
	if (rnk[x] < rnk[y])
	{
		pushdown(x);
		rs[x] = merge(rs[x], y);
		update(x); return x;
	}
	else
	{
		pushdown(y);
		ls[y] = merge(x, ls[y]);
		update(y); return y;
	}
}

typedef pair<int, int> mypair;

mypair split(int x, int k)
{
	if (!x) return mypair(0, 0);
	pushdown(x);
	if (sz[ls[x]] >= k)
	{
		mypair nxt = split(ls[x], k);
		ls[x] = nxt.second, update(x);
		return mypair(nxt.first, x);
	}
	else
	{
		k -= sz[ls[x]] + 1;
		mypair nxt = split(rs[x], k);
		rs[x] = nxt.first, update(x);
		return mypair(x, nxt.second);
	}
}

ll query(int x, int k)
{
	pushdown(x);
	if (k <= sz[ls[x]]) return query(ls[x], k);
	if (k == sz[ls[x]] + 1) return w[x];
	return query(rs[x], k - sz[ls[x]] - 1);
}

ll get_ans(int x)
{
	ll res = w[x]; pushdown(x);
	if (ls[x]) res = max(res, get_ans(ls[x]));
	if (rs[x]) res = max(res, get_ans(rs[x]));
	return res;
}

int main()
{
	n = read(), tot = 1, rnk[1] = rnd(), sz[1] = 1;
	for (int i = 1; i <= n; i ++) a[i] = read();
	int rt = 1;
	for (int i = 1; i <= n; i ++)
	{
		int l = 1, r = i - 1, res = i;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			ll v1 = query(rt, mid), v2 = query(rt, mid + 1);
//			if(i==4)
//				cerr<<"fk"<<l<<" "<<mid<<" "<<r<<" "<<v1<<" "<<v2<<endl; 
			if (v1 + 1LL * mid * a[i] > v2) res = mid, r = mid - 1;
			else l = mid + 1;
		}
		int now = ++ tot; rnk[now] = rnd(), sz[now] = 1;
		w[now] = query(rt, res);
		if (res == 1)
		{
			operate(rt, a[i], a[i]);
			rt = merge(now, rt);
		}
		else
		{
			mypair pr = split(rt, res - 1);
			assert(pr.first && pr.second);
			operate(pr.second, a[i], 1LL * res * a[i]);
			rt = merge(pr.first, now);
			rt = merge(rt, pr.second);
		}
//		printf("i=%d,res=%d,ans=%lld\n",i,res,get_ans(rt));
//		for (int i=1;i<=tot;i++)
//			printf("%d %d %d %d %lld\n",i,sz[i],ls[i],rs[i],w[i]);
	}
	
	printf("%lld\n", get_ans(rt));
	
	return 0;
}
