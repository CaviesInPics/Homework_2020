#include <bits/stdc++.h>
using namespace std;
int g[505][505];
int main()
{
	int k,n=500;cin>>k;
	if(k <= n)
	{
		printf("%d\n", k);
		for (int i = 1; i <= k; i ++)
			for(int j = 1; j <= k; j ++)
				printf("%d%c", i, j == k ? 10 : 32);
	}
	else
	{
		puts("500");
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j ++)
			{
				int x = j, y = (i + j - 1 - 1) % n + 1;
				if (n - i + 1 == k)
				{
					g[x][y] = k;
					if (j == n) k --;
				}
				else
				{
					g[x][y] = (j & 1) ? k : k - 1;
					if (j == n) k -= 2;
				}
			}
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j ++)
				printf("%d%c", g[i][j], j == n ? 10 : 32);
	}
}
