#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
typedef long double db;
double t[maxn];
int n, l;

const db pi = acos(-1);

int main()
{
	scanf("%d %d", &n, &l);
	for (int i = 1; i <= n; i ++)
		scanf("%lf", t + i);
	db ans_x = 0, ans_y = 0;
	for (int i = 1; i <= n; i ++)
		for (int j = i + 1; j <= n; j ++)
		{
			ans_x += cos(pi * (t[i] + t[j]) / l) * (n - (j - i + 1));
			ans_x += cos(pi * (t[i] + t[j] + l) / l) * (j - i - 1);
			ans_y += sin(pi * (t[i] + t[j]) / l) * (n - (j - i + 1));
			ans_y += sin(pi * (t[i] + t[j] + l) / l) * (j - i - 1);
		}
	db cnt = 1.0l * n * (n - 1) / 6.0l * (n - 2);
	ans_x /= cnt, ans_y /= cnt;
	printf("%.15lf %.15lf\n", (double)ans_x, (double)ans_y);
	return 0;
}