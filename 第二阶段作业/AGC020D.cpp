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

int Q, A, B, C, D;

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	Q = read();
	while (Q --)
	{
		A = read(), B = read(), C = read(), D = read();
		int k = (max(A, B) + min(A, B)) / (min(A, B) + 1);
 		int l = 0, r = A, res = 0;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			int cnt = (mid + k - 1) / k, need_b = max(0, cnt - 1);
			int remain_b = B - need_b;
			if (remain_b < 0)
			{
				r = mid - 1;
				continue;
			}
			if ((remain_b + k - 1) / k <= A - mid + 1)
			{
				res = mid, l = mid + 1;
			}
			else r = mid - 1;
		}
		int cnt = max(0, (res + k - 1) / k), need_b = max(0, cnt - 1);
//		cerr << "res = " << res << endl; rua;
		int front_all = res + need_b;
		for (int i = C; i <= min(front_all, D); i ++)
			putchar(i % (k + 1) == 0 ? 'B' : 'A');
		int all = A + B;
		for (int i = max(C, front_all + 1); i <= D; i ++)
			putchar((all - i + 1) % (k + 1) == 0 ? 'A' : 'B');
		putchar(10);
	}
	return 0;
}
