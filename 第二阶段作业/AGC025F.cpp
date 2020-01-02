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

const int MAXN = 2e6 + 10;
char buf[MAXN]; mypair st[MAXN];
int n, m, k, s[MAXN], t[MAXN], S[MAXN], T[MAXN];
#define fi first
#define se second

int main()
{
//	freopen("in30.txt", "r", stdin);
//	freopen("out30.txt", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	scanf("%s", buf + 1), reverse(buf + 1, buf + 1 + n);
	for (int i = 1; i <= n; i ++) s[i] = buf[i] == '1';
	scanf("%s", buf + 1), reverse(buf + 1, buf + 1 + m);
	for (int i = 1; i <= m; i ++) t[i] = buf[i] == '1';
	int top = 0;
	for (int i = max(n, m); i; i --)
	{
		if (s[i] && t[i])
		{
			vector<mypair> foo(0);
			int now = k, x = 3, pos = i;
			s[i] = t[i] = 0;
			while (x && top)
			{
				auto cur = st[top];
				if (x == 3)
				{
					if (cur.fi - pos > now)
					{
						S[pos + now] = T[pos + now] = 1;
						now = -1;
						break;
					}
					else
					{
						now -= cur.fi - pos;
						foo.emplace_back(cur.fi, x ^ cur.se);
						x &= cur.se, pos = cur.fi;
					}
				}
				else
				{
					if (cur.fi - pos > 1)
					{
						foo.emplace_back(pos + 1, x);
						now = -1;
						break;
					}
					else
					{
						if ((x ^ cur.se) == 3) x = 3;
						else x &= cur.se;
						pos ++;
					}
				}
				top --;
			}
			if (now >= 0)
			{
				if (x == 3) S[pos + now] = T[pos + now] = 1;
				else if (x) foo.emplace_back(pos + 1, x);
			}
			reverse(foo.begin(), foo.end());
			for (auto cur : foo) st[++ top] = cur;
			foo.clear();
		}
		else if (s[i] || t[i])
			st[++ top] = mypair(i, s[i] << 1 | t[i]);
//		cerr << top << endl;
	}
	while (top)
	{
		auto cur = st[top --];
		S[cur.fi] = cur.se >> 1;
		T[cur.fi] = cur.se & 1;
	}
	int pos = 0;
	for (int i = max(n, m) + k + 1; i >= 0; i --) if (S[i]) {pos = i; break;}
	for (int i = pos; i >= 1; i --) putchar(S[i] + '0'); putchar(10);
	for (int i = max(n, m) + k + 1; i >= 0; i --) if (T[i]) {pos = i; break;}
	for (int i = pos; i >= 1; i --) putchar(T[i] + '0'); putchar(10);
	return 0;
}
