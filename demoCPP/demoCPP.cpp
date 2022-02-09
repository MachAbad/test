#include <bits/stdc++.h>
using namespace std;

int G[202][202];

int judge(int num)
{
    int n, m = 0, d[202];
    bool book[202] = {false};
    cin >> n;
    for (int i = 1; i <= n; i++)
        scanf("%d", &d[i]);
    d[0] = 0, d[n + 1] = 0;
    if (n != num)
        return 0;
    for (int i = 1; i < n + 2; i++)
    {
        if (!book[d[i]] && G[d[i - 1]][d[i]])
        {
            m += G[d[i - 1]][d[i]];
            book[d[i]] = true;
        }
        else
            return 0;
    }
    return m;
}

int main()
{
    // freopen("a.txt","r",stdin);
    int n, m, x, y, w, k, cnt = 0, num = 0, money = 0x3f3f3f3f;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &x, &y, &w);
        G[x][y] = G[y][x] = w;
    }
    cin >> k;
    for (int i = 1; i <= k; i++)
    {
        w = judge(n);
        if (w)
        {
            cnt++;
            if (w < money)
            {
                num = i;
                money = w;
            }
        }
    }
    cout << cnt << endl
         << num << " " << money << endl;
    return 0;
}
/*
#include <bits/stdc++.h>
#define maxn 100000
using namespace std;

int lenth[maxn];
int pre[maxn];
void init()
{
    for (int i = 0; i < maxn; i++)
        pre[i] = i;
}
int find(int t)
{
    int l = lenth[pre[t]], x = t;
    while (pre[x] != x)
    {
        x = pre[x];
        l++;
    }
    lenth[t] = l;
    return x;
}

int main()
{
    freopen("a.txt", "r", stdin);
    int n, k, t;
    init();
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &k);
        while (k--)
        {
            scanf("%d", &t);
            pre[t] = i;
        }
    }
    for (int i = 1; i <= n; i++)
        pre[i] = find(i);
    for (int i = 1; i <= n; i++)
        cout << i << " " << lenth[i] << endl;
    t = 0, k = 1;
    for (int i = 1; i <= n; i++)
        if (lenth[i] > t)
        {
            t = lenth[i];
            k = i;
        }
    cout << k;
    return 0;
}
*/