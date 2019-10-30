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
 
struct Point
{
	int x, y;
	Point() {}
	Point(int x, int y): x(x), y(y) {}
	inline Point operator + (Point rhs) {return Point(x + rhs.x, y + rhs.y);}
	inline Point operator - (Point rhs) {return Point(x - rhs.x, y - rhs.y);}
	inline ll operator * (Point rhs) {return 1ll * x * rhs.x + 1ll * y * rhs.y;}
} a[10], b[1005];
 
inline ll Cross(Point a, Point b) {return 1ll * a.x * b.y - 1ll * a.y * b.x;}
 
int k, n, p[10];
vector<int> block[8][1005];
 
inline bool check(Point a, Point b, Point c)
{
	return Cross(a - c, c - b) == 0 && (b - a) * (c - a) > 0 && (c - a) * (b - c) > 0;
}
 
bool cover[1005];
vector<int> foo;
int now;
 
inline bool dfs(int x)
{
	if (cover[x]) return 1;
	if (now < 1) return 0;
	int np = p[now --];
	for (int cur : block[np][x])
		if (!dfs(cur)) return 0;
	cover[x] = 1, foo.push_back(x);
	return 1;
}
 
inline void clear() {for (int cur : foo) cover[cur] = 0; foo.clear();}
 
int main()
{
	k = read(), n = read();
	for (int i = 1; i <= k; i ++)
		a[i].x = read(), a[i].y = read();
	for (int i = 1; i <= n; i ++)
		b[i].x = read(), b[i].y = read();
	for (int i = 1; i <= k; i ++)
		for (int a = 1; a <= n; a ++)
			for (int b = 1; b <= n; b ++)
				if (a != b && check(::a[i], ::b[a], :: b[b]))
					block[i][a].push_back(b);
	int ans = 0;
	for (int i = 1; i <= n; i ++)
	{
		for (int j = 1; j <= k; j ++) p[j] = j;
		bool flag = 0;
		do
		{
			clear();
			now = k;
			if (dfs(i))
			{
				flag = 1;
				break;
			}
		} while (next_permutation(p + 1, p + 1 + k));
		if (flag) ++ ans;
	}
	printf("%d\n", ans);
	return 0;
}
