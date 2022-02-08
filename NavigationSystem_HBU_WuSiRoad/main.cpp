/* #include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib> */
#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

#define MaxNum 64
#define INF 9999
using namespace std;

//地点信息
typedef struct Building
{
    int id;
    string name;
    string introduction;
} Building, *ptrToBuilding;

//边结点结构
typedef struct node
{
    int id;            // 连通的结点
    int info_len;      // 路径长度
    struct node *next; // 指向下一个顶点的指针域
} EdgeNode;

//顶点结点结构
typedef struct vnode
{
    Building building;   // 顶点域
    EdgeNode *firstedge; // 第一条边的指针
} vnode;

//邻接表
typedef struct ALGraph
{
    vector<vnode> adjList;
    int vNum, eNum;
} ALGraph;

//全局变量
ALGraph G;
int dist[MaxNum][MaxNum]; // Floyd算法，最短距离
int path[MaxNum][MaxNum]; // Floyd算法，中转节点
bool isAdministrator;     // 是否具有管理员权限
bool createdALG = false;  // 是否已经建立邻接表

// UI
void Menu_Login();          // 登录界面
void Menu_Administrator();  // 管理员界面
void Menu_Tourist();        // 游客界面
void Menu_return();         // 返回上一界面
void Login_Administrator(); // 管理员登录后端操作
void Login_Tourist();       // 游客登录后端操作
void Out_ALL();             // 退出登录

// 算法
void CreateALGraph();               // 计算 创建邻接表，存储校园地图
void Search_info_All();             // 输出 查询所有地点信息
void Search_info(int x);            // 输出 查询指定地点信息
void ShortestPath_Floyd();          // 计算 任意两点间的最短路径，Floyd算法
void Search_path_All2All();         // 输出 查询任意两点间最短路径
void Search_path_A2All(int x);      // 输出 查询某点到其它点间的最短路径
void Search_path_A2B(int x, int y); // 输出 查询A点到B点的最短路径
int Locate(string name);            // 计算 给定地点名称，返回对应的序号
void Insert_Vex();                  // 计算 增加校园地点
void Insert_Edge();                 // 计算 增加校园路径
void Delete_Vex();                  // 计算 删除校园地点
void Delete_Edge();                 // 计算 删除校园路径
void Modify_info();                 // 计算 更新地点信息

int main()
{
    Menu_Login();
    return 0;
}

// UI
void Menu_Login() // 登录界面
{
    printf("\n\t加载中，请稍后...");
    // Sleep(1000);
    system("cls");
    printf("\n");
    printf("\t _________________________________________________________\n");
    printf("\t|                                                         |\n");
    printf("\t|                                                         |\n");
    printf("\t|                欢迎使用河北大学校园导航系统             |\n");
    printf("\t|                                                         |\n");
    printf("\t|                     请选择您的登录方式                  |\n");
    printf("\t|               [1] 以游客身份进入                        |\n");
    printf("\t|               [2] 以管理员身份登录                      |\n");
    printf("\t|               [0] 退出系统                              |\n");
    printf("\t|                                                         |\n");
    printf("\t|_________________________________________________________|\n");
    printf("\n");
    printf("\t请输入对应序号以使用相应功能：\n\t");
    // freopen("a.txt", "r", stdin);
    int n;
    while (cin >> n && n != 0)
    {
        if (!createdALG)
        {
            CreateALGraph();
            createdALG = true;
        }
        switch (n)
        {
        case 1:
            Login_Tourist();
            isAdministrator = false;
            break;
        case 2:
            Login_Administrator();
            isAdministrator = true;
            break;
        default:
            cout << "\t请输入0~2之间的数字：" << endl;
            break;
        }
        // if (cin.get() == '\n')  break;
    }
    cout << "\n\t正在退出系统..." << endl;
    Sleep(500);
    exit(0);
}
void Menu_Administrator() // 管理员界面
{
    system("cls");
    printf("\n");
    printf("\t _________________________________________________________\n");
    printf("\t|                                                         |\n");
    printf("\t|                                                         |\n");
    printf("\t|               河北大学校园导航管系统管理员界面          |\n");
    printf("\t|                                                         |\n");
    printf("\t|               [1] 查询某个地点信息                      |\n");
    printf("\t|               [2] 查询所有地点信息                      |\n");
    printf("\t|               [3] 修改地点信息                          |\n");
    printf("\t|               [4] 去某地的最短路径查询                  |\n");
    printf("\t|               [5] 去其它所有地点的最短路径查询          |\n");
    printf("\t|               [6] 添加校园地点                          |\n");
    printf("\t|               [7] 删除校园地点                          |\n");
    printf("\t|               [8] 添加校园路径                          |\n");
    printf("\t|               [9] 删除校园路径                          |\n");
    printf("\t|               [0] 退出登录                              |\n");
    printf("\t|                                                         |\n");
    printf("\t|_________________________________________________________|\n");
    printf("\n");
    printf("\t请输入指令：");
    int n;
    while (cin >> n && n != 0)
    {
        switch (n)
        {
        case 1:
            cout << "111" << endl;
            break;
        case 2:
            cout << "222" << endl;
            break;
        case 3:
            cout << "333" << endl;
            break;
        case 4:
            cout << "444" << endl;
            break;
        case 5:
            cout << "555" << endl;
            break;
        case 6:
            cout << "666" << endl;
            break;
        case 7:
            cout << "777" << endl;
        default:
            cout << "000" << endl;
            break;
        }
    }
}
void Menu_Tourist() // 游客界面
{
    system("cls");
    printf("\n");
    printf("\t _________________________________________________________\n");
    printf("\t|                                                         |\n");
    printf("\t|                                                         |\n");
    printf("\t|               河北大学校园导航管系统游客界面            |\n");
    printf("\t|                                                         |\n");
    printf("\t|               [1] 查询某个地点信息                      |\n");
    printf("\t|               [2] 查询所有地点信息                      |\n");
    printf("\t|               [3] 去某地的最短路径查询                  |\n");
    printf("\t|               [4] 去其它所有地点的最短路径查询          |\n");
    printf("\t|               [0] 退出登录                              |\n");
    printf("\t|                                                         |\n");
    printf("\t|_________________________________________________________|\n");
    printf("\n");
    printf("\t请输入指令：");
}
void Menu_return() // 返回上一界面
{
    if (isAdministrator)
        Menu_Administrator();
    else
        Menu_Tourist();
}
void Login_Administrator() // 管理员登录后端操作
{
    Menu_Administrator();
}
void Login_Tourist() // 游客登录后端操作
{
    Menu_Tourist();
}
void Out_ALL() // 退出登录
{
    isAdministrator = false;
    Menu_Login();
}

//算法
void CreateALGraph() // 计算 创建邻接表，存储校园地图
{
    int i, j, k, l;
    EdgeNode *s;
    freopen("mapInfo.txt", "r", stdin);
    cin >> G.vNum >> G.eNum; //输入顶点数和边数
    getchar();
    for (i = 0; i <= G.vNum; i++) //创建邻接表顶点
    {
        vnode v;
        v.building.id = i;
        getline(cin, v.building.name);
        getline(cin, v.building.introduction);
        // cin >> v.building.name >> v.building.introduction; //不能输入空格，已弃用
        v.firstedge = NULL;
        G.adjList.push_back(v);
    }
    for (k = 0; k < G.eNum; k++)
    {
        cin >> i >> j >> l;
        s = (EdgeNode *)malloc(sizeof(EdgeNode));
        s->id = j;
        s->info_len = l;
        s->next = G.adjList[i].firstedge;
        G.adjList[i].firstedge = s;
        s = (EdgeNode *)malloc(sizeof(EdgeNode));
        s->id = i;
        s->info_len = l;
        s->next = G.adjList[j].firstedge;
        G.adjList[j].firstedge = s;
    }
    /* debug 输出边的信息（没啥用）
    for (i = 0; i < G.vNum; i++)
    {
        EdgeNode *p = G.adjList[i].firstedge;
        while (p)
        {
            cout << i << " " << p->id << " " << p->info_len << endl;
            p = p->next;
        }
    }
    */
}
void Search_info_All() // 输出 查询所有地点信息
{
    for (int i = 1; i <= G.vNum; i++)
        cout << G.adjList[i].building.id << "." << G.adjList[i].building.name << "：" << G.adjList[i].building.introduction << endl;
}
void Search_info(int x) // 输出 查询指定地点信息
{
    int n;
    while (cin >> n && n != 0)
    {
        int i;
        for (i = 1; i <= G.vNum; i++)
            if (G.adjList[i].building.id == x)
            {
                cout << G.adjList[i].building.name << "：" << G.adjList[i].building.introduction << endl;
                break;
            }
        if (i > G.vNum)
            cout << "无此地点，请重新输入（放弃查询请输入0）：" << endl;
    }
}
void ShortestPath_Floyd() // 计算 任意两点间的最短路径，Floyd算法
{
    // path[i][j]=k 锟斤拷示i锟斤拷j锟斤拷锟斤拷锟铰凤拷锟斤拷峋拷锟絢
    // dist[i][j]=sum 锟斤拷示i锟斤拷j锟斤拷锟斤拷锟铰凤拷锟斤拷锟斤拷锟轿猻um
    int i, j, k, temp;
    EdgeNode *p;
    //锟斤拷始锟斤拷
    for (i = 1; i <= G.vNum; i++)
    {
        for (j = 1; j <= G.vNum; j++)
        {
            dist[i][j] = INF;
            path[i][j] = j;
        }
        dist[i][i] = 0;
    }
    //锟斤拷录锟斤拷锟叫讹拷锟斤拷之锟斤拷木锟斤拷耄拷诮泳锟斤拷锟阶拷诮颖锟斤拷锟?
    for (i = 1; i <= G.vNum; i++)
    {
        p = G.adjList[i].firstedge;
        while (p)
        {
            dist[i][p->id] = p->info_len;
            p = p->next;
        }
    }
    //锟斤拷锟斤拷锟斤拷锟铰凤拷锟?
    for (k = 1; k <= G.vNum; k++)
    {
        for (i = 1; i <= G.vNum; i++)
        {
            for (j = 1; j <= G.vNum; j++)
            {
                temp = (dist[i][k] == INF || dist[k][j] == INF) ? INF : (dist[i][k] + dist[k][j]);
                if (dist[i][j] > temp)
                {
                    dist[i][j] = temp;
                    path[i][j] = k;
                }
            }
        }
    }
    /* debug,锟斤拷锟?
    int l = 1;
    cout << "锟斤拷锟斤拷锟斤拷锟斤拷之锟斤拷锟斤拷锟斤拷路锟斤拷锟斤拷锟斤拷锟斤拷" << endl;
    for (i = 1; i < G->vNum; i++)
    {
        for (j = 1; j < G->vNum; j++)
        {
            if (i != j)
            {
                cout << l++ << ":" << endl;
                cout << i << "." << G->adjList[i].building.name << " 锟斤拷 " << j << "." << G->adjList[j].building.name << " 锟斤拷锟斤拷锟铰凤拷锟斤拷锟斤拷锟轿拷锟?" << dist[i][j] << endl;
                cout << "路锟斤拷为锟斤拷" << j << "." << G->adjList[j].building.name;
                if (path[i][j] == j)
                    cout << "<-" << i << "." << G->adjList[i].building.name << endl;
                else
                {
                    k = j;
                    while (path[i][k] != k)
                    {
                        k = path[i][k];
                        cout << "<-" << k << "." << G->adjList[k].building.name;
                    }
                    cout << "<-" << i << "." << G->adjList[i].building.name << endl;
                }
            }
        }
    }
    */
}
void Search_path_All2All() // 输出 查询任意两点间最短路径
{
    int i, j, k, l = 1;
    cout << "任意两点间最短路径搜索结果：" << endl;
    for (i = 1; i <= G.vNum; i++)
    {
        for (j = 1; j <= G.vNum; j++)
        {
            if (i != j)
            {
                cout << l++ << ":" << endl;
                cout << i << "." << G.adjList[i].building.name << " 到 " << j << "." << G.adjList[j].building.name << " 的最短路径长度为：" << dist[i][j] << "米。" << endl;
                cout << "路径为：" << j << "." << G.adjList[j].building.name;
                if (path[i][j] == j)
                    cout << "<-" << i << "." << G.adjList[i].building.name << endl;
                else
                {
                    k = j;
                    while (path[i][k] != k)
                    {
                        k = path[i][k];
                        cout << "<-" << k << "." << G.adjList[k].building.name;
                    }
                    cout << "<-" << i << "." << G.adjList[i].building.name << endl;
                }
            }
        }
    }
}
void Search_path_A2All(int x) // 输出 查询某点到其它点间的最短路径
{
}
void Search_path(int x, int y) // 输出 查询A点到B点的最短路径
{
    int i, j, k;
    cout << x << " 到 " << y << " 的最短路径查询结果：" << endl;
    for (i = 1; i <= G.vNum; i++)
    {
        for (j = 1; j <= G.vNum; j++)
        {
            if (i == x && j == y)
            {
                cout << i << "." << G.adjList[i].building.name << " 到 " << j << "." << G.adjList[j].building.name << " 的最短路径长度为：" << dist[i][j] << "米。" << endl;
                cout << "路径为：" << j << "." << G.adjList[j].building.name;
                if (path[i][j] == j)
                    cout << " <- " << i << "." << G.adjList[i].building.name << endl;
                else
                {
                    k = j;
                    while (path[i][k] != k)
                    {
                        k = path[i][k];
                        cout << " <- " << k << "." << G.adjList[k].building.name;
                    }
                    cout << " <- " << i << "." << G.adjList[i].building.name << endl;
                }
            }
        }
    }
}
int Locate(string name) // 计算 给定地点名称，返回对应的序号
{
    for (int i = 1; i <= G.vNum; i++)
    {
        if (G.adjList[i].building.name == name)
            return i;
    }
    cout << "没找到 " << name << endl;
    return 0;
}
void Insert_Vex() // 计算 增加校园地点
{
    if (G.adjList.size() >= MaxNum)
    {
        cout << "\t已达到存储地点的上限，无法存储。" << endl;
        return;
    }
    vnode v;
    v.building.id = G.adjList.size();
    cout << "\t请输入地点名称：\n\t";
    getline(cin, v.building.name);
    cout << "\t请输入地点简介：\n\t";
    getline(cin, v.building.introduction);
    G.adjList.push_back(v);
    G.vNum++;
    cout << "\t成功增加地点：" << v.building.name << endl;
}
void Insert_Edge() // 计算 增加校园路径
{
    int n;
    do
    {
        int i, j, l;
        string name;
        cout << "\t请输入路径的一个端点：" << endl;
        getline(cin, name);
        i = Locate(name);
        cout << "\t请输入路径的另一个端点：" << endl;
        getline(cin, name);
        j = Locate(name);
        cout << "\t请输入路径的长度（单位：米）：" << endl;
        cin >> l;
        EdgeNode *s;
        s = (EdgeNode *)malloc(sizeof(EdgeNode));
        s->id = j;
        s->info_len = l;
        s->next = G.adjList[i].firstedge;
        G.adjList[i].firstedge = s;
        s = (EdgeNode *)malloc(sizeof(EdgeNode));
        s->id = i;
        s->info_len = l;
        s->next = G.adjList[j].firstedge;
        G.adjList[j].firstedge = s;
        G.eNum++;
        cout << "\t成功增加路径" << endl;
        cout << "\t是否继续增加路径？（继续增加请输入1，退出增加请输入0）\n\t" << endl;
    } while (cin >> n && n != 0);
}
void Delete_Vex() // 计算 删除校园地点
{
}
void Delete_Edge() // 计算 删除校园路径
{
    int i,j;
    cout << "请输入要删除的两个地点";
}
void Modify_info() // 计算 更新地点信息
{
}