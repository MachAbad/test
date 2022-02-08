#include <iostream>
#include <vector>
#define maxn 20001
using namespace std;

bool v[maxn];
int G[maxn][maxn];
vector<vector<int>> G;

void DFS(int x)
{
    if(x == 1)
        printf("%d", x);
    else
        printf(" %d", x);
    v[x] = true;
    for(int i = 0; i < maxn; i++)
    {
        if(!v[i] && G[x][i] > 0)
        {
            DFS(i);
            printf(" %d", x);
        }
    }
}

int main()
{
    int n,u,v;
    cin >> n;
    for(int i=0;i<n;i++)
    {
        scanf("%d %d",&u,&v);
        G[u][v]=G[v][u]=1;
    }
    DFS(1);
    return 0;
}
