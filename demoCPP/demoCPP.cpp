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
