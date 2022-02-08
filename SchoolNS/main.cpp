#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <windows.h>

#define MaxNum 50
#define INF 2000

using namespace std;

typedef struct Building
{
    int id;
    string name;
    string introduction;
} Building, *ptrToBuilding;

typedef struct AdjMatrix
{
    int edge[MaxNum][MaxNum];
    Building building[MaxNum];
    int vNum, eNum;
} AdjMatrix;

AdjMatrix G;
int dist[MaxNum][MaxNum];
int path[MaxNum][MaxNum];
bool isAdministrator;
bool createdALG = false;

void UI_Login();
void UI_Administrator();
void UI_Tourist();
void UI_Map();
void Menu_Login();
void Menu_Administrator();
void Menu_Tourist();
void Menu_return();
void Login_Administrator();
void Login_Tourist();
void Out_ALL();

// 算法
void CreateGraph();
void Search_info_All();
void Search_info();
void ShortestPath_Floyd();
void Search_path();
int Locate(string name);
void Insert_Vex();
void Insert_Edge();
void Delete_Vex();
void Delete_Edge();
void Modify_info();

int main()
{
    Menu_Login();
    return 0;
}

void UI_Login()
{
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
}
void UI_Tourist()
{
    system("cls");
    printf("\n");
    printf("\t _________________________________________________________\n");
    printf("\t|                                                         |\n");
    printf("\t|                                                         |\n");
    printf("\t|               河北大学校园导航管系统游客界面            |\n");
    printf("\t|                                                         |\n");
    printf("\t|               [1] 某地信息                              |\n");
    printf("\t|               [2] 所有地点信息                          |\n");
    printf("\t|               [3] 去某地最短路径                        |\n");
    printf("\t|               [0] 退出                                  |\n");
    printf("\t|                                                         |\n");
    printf("\t|_________________________________________________________|\n");
    UI_Map();
    printf("\t请输入指令:\n\t");
}
void UI_Administrator()
{
    system("cls");
    printf("\n");
    printf("\t _________________________________________________________\n");
    printf("\t|                                                         |\n");
    printf("\t|                                                         |\n");
    printf("\t|               河北大学校园导航管系统管理员界面          |\n");
    printf("\t|                                                         |\n");
    printf("\t|               [1] 某地信息                              |\n");
    printf("\t|               [2] 所有地点信息                          |\n");
    printf("\t|               [3] 修改地点信息                          |\n");
    printf("\t|               [4] 去某地最短路径                        |\n");
    printf("\t|               [6] 添加地点                              |\n");
    printf("\t|               [7] 删除地点                              |\n");
    printf("\t|               [8] 添加路径                              |\n");
    printf("\t|               [9] 删除路径                              |\n");
    printf("\t|               [0] 退出                                  |\n");
    printf("\t|                                                         |\n");
    printf("\t|_________________________________________________________|\n");
    UI_Map();
    printf("\t请输入指令：\n\t");
}
void UI_Map()
{
    printf("-------------------------------------------------------宿舍梅园3、4、5号-----------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("---校医院----------------------------------宿舍梅园6号-----------------------------------宿舍梅园2号-------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-------生科院-------------------------------北院餐厅----------篮球场网球场---------------操场-----------宿舍梅园1号----------\n");
    printf("-------------------------建工学院--------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-------------------理化中心-------------------化学学院--------------电信学院-------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------逸夫楼-------------------物理学院--------------竞学楼--------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("------------------------------------南2门口--------------南1门口-------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("------------------------------------北1门口--------------北2门口-------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("--------------------文苑楼---------------------------------------------多功能馆----------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-南院餐厅--------------------------------------------------------------------------------------------------------------------\n");
    printf("------------------第八教学楼-------第九教学楼-----------------主楼-----------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-------------------------------------------毓秀园----------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("--第七教学楼-------综合教学楼------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("--------------------------------国际交流学院---------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
}
void Menu_Login()
{
    printf("\n\t加载中，请稍后...");
    Sleep(1000);
    UI_Login();
    int n;
    while (cin >> n && n != 0)
    {
        fflush(stdin);
        if (!createdALG)
        {
            CreateGraph();
            createdALG = true;
        }
        ShortestPath_Floyd();
        switch (n)
        {
        case 1:
            isAdministrator = false;
            Login_Tourist();
            break;
        case 2:
            isAdministrator = true;
            Login_Administrator();
            break;
        default:
            break;
        }
        UI_Login();
    }
    exit(0);
}
void Menu_Administrator()
{
    UI_Administrator();
    int n;
    while (cin >> n && n != 0)
    {
        fflush(stdin);
        switch (n)
        {
        case 1:
            Search_info();
            break;
        case 2:
            Search_info_All();
            break;
        case 3:
            Modify_info();
            break;
        case 4:
            Search_path();
            break;
        case 5:
            Insert_Vex();
            break;
        case 6:
            Delete_Vex();
            break;
        case 7:
            Insert_Edge();
            break;
        case 8:
            Delete_Edge();
            break;
        default:
            break;
        }
        UI_Administrator();
    }
}
void Menu_Tourist()
{
    UI_Tourist();
    int n;
    while (cin >> n && n != 0)
    {
        fflush(stdin);
        switch (n)
        {
        case 1:
            Search_info();
            break;
        case 2:
            Search_info_All();
            break;
        case 3:
            Search_path();
            break;
        default:
            break;
        }
        UI_Tourist();
    }
}
void Menu_return()
{
    if (isAdministrator)
        Menu_Administrator();
    else
        Menu_Tourist();
}
void Login_Administrator()
{
    Menu_Administrator();
}
void Login_Tourist()
{
    Menu_Tourist();
}
void Out_ALL()
{
    isAdministrator = false;
    Menu_Login();
}

void CreateGraph()
{
    fflush(stdin);
    int i, j, k, l;
    freopen("mapInfo.txt", "r", stdin);
    cin >> G.vNum >> G.eNum;
    getchar();
    for (i = 0; i <= G.vNum; i++)
    {
        G.building[i].id = i;
        getline(cin, G.building[i].name);
        getline(cin, G.building[i].introduction);
    }
    for (i = 0; i <= G.vNum; i++)
        for (j = 0; j <= G.vNum; j++)
            G.edge[i][j] = INF;
    for (k = 0; k < G.eNum; k++)
    {
        cin >> i >> j >> l;
        G.edge[i][j] = l;
        G.edge[j][i] = l;
    }
    freopen("CON", "r", stdin);
}
void Search_info_All()
{
    cout << "\t所有地点信息查询结果：" << endl;
    for (int i = 1; i <= G.vNum; i++)
        cout << "\t" << G.building[i].name << "：" << G.building[i].introduction << endl;
    cout << "\n\t按任意键返回..." << endl;
    getchar();
    // Menu_return();
}
void Search_info()
{
    fflush(stdin);
    int i;
    string name;
    cout << "\t请输入要查询的地点：\n\t";
    getline(cin, name);
    i = Locate(name);
    if (i)
        cout << "\t" << G.building[i].name << "：" << G.building[i].introduction << endl;
    else
        cout << "\t无此地点，请重新输入（放弃查询请输入0）：" << endl;
    cout << "\t按任意键返回..." << endl;
    getchar();
    // Menu_return();
}
void ShortestPath_Floyd()
{
    int i, j, k, temp;
    memset(dist, INF, sizeof(dist));
    memset(path, -1, sizeof(path));
    for (i = 1; i <= G.vNum; i++)
    {
        for (j = 1; j <= G.vNum; j++)
        {
            dist[i][j] = G.edge[i][j];
            path[i][j] = j;
        }
    }
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
}
void Search_path()
{
    int i, j, k, x, y;
    string name;
    cout << "\t请输入起点：";
    getline(cin, name);
    x = Locate(name);
    cout << "\t请输入终点：";
    getline(cin, name);
    y = Locate(name);
    if (x && y)
    {
        cout << "\t" << G.building[x].name << " 到 " << G.building[y].name << " 的最短路径查询结果：" << endl;
        for (i = 1; i <= G.vNum; i++)
        {
            for (j = 1; j <= G.vNum; j++)
            {
                if (i == x && j == y)
                {
                    cout << "\t" << G.building[i].name << " 到 " << G.building[j].name << " 的最短路径长度为：" << dist[i][j] << "米。" << endl;
                    cout << "\t路径为：" << G.building[j].name;
                    if (path[i][j] == j)
                        cout << " <- " << G.building[i].name << endl;
                    else
                    {
                        k = j;
                        while (path[i][k] != k)
                        {
                            k = path[i][k];
                            cout << " <- " << G.building[k].name;
                        }
                        cout << " <- " << G.building[i].name << endl;
                    }
                }
            }
        }
    }
    else
        cout << "起点或终点错误。" << endl;
    cout << "按任意键返回..." << endl;
}
int Locate(string name)
{
    for (int i = 1; i <= G.vNum; i++)
    {
        if (G.building[i].name == name)
            return i;
    }
    cout << "\t没找到 " << name << endl;
    return 0;
}
void Insert_Vex()
{
    fflush(stdin);
    int i = G.vNum + 1;
    G.building[i].id = i;
    cout << "\t请输入地点名称：";
    getline(cin, G.building[i].name);
    cout << "\t请输入地点简介：";
    getline(cin, G.building[i].introduction);
    G.vNum++;
    cout << "\t成功增加地点：" << G.building[i].name << "\n\t按任意键返回..." << endl;
}
void Insert_Edge()
{
    int n;
    do
    {
        fflush(stdin);
        int i, j, l;
        string name;
        cout << "\t请输入路径的一个端点：\n\t";
        getline(cin, name);
        i = Locate(name);
        cout << "\t请输入路径的另一个端点：\n\t";
        getline(cin, name);
        j = Locate(name);
        cout << "\t请输入路径的长度（单位：米）：\n\t";
        cin >> l;
        G.edge[i][j] = l;
        G.edge[j][i] = l;
        G.eNum++;
        cout << "\t成功增加路径" << endl;
        cout << "\t是否继续增加路径？（继续增加请输入1，退出增加请输入0）\n\t";
    } while (cin >> n && n != 0);
    cout << "\t按任意键返回..." << endl;
}
void Delete_Vex()
{
    fflush(stdin);
    string name;
    cout << "\t请输入要删除的地点：\n\t";
    getline(cin, name);
    int x = Locate(name);
    if (x)
    {
        for (int i = x; i < G.vNum; i++)
        {
            G.building[i] = G.building[i + 1];
            for (int j = x; j < G.vNum; i++)
                G.edge[i][j] = G.edge[i + 1][j + 1];
        }
        G.vNum--;
        cout << "\t已成功删除该地点。按任意键返回..." << endl;
        CreateGraph();
    }
    else
        cout << "\t无此地点。按任意键返回..." << endl;
}
void Delete_Edge()
{
    fflush(stdin);
    int i, j;
    string name;
    cout << "\t请输入要删除的路径连接的其中一个地点：\n\t";
    getline(cin, name);
    i = Locate(name);
    cout << "\t请输入要删除的路径连接的另一个地点：\n\t";
    getline(cin, name);
    j = Locate(name);
    if (i && j && G.edge[i][j] < INF)
    {
        G.edge[i][j] = INF;
        G.edge[j][i] = INF;
        G.eNum--;
        cout << "\t已成功删除该路径。按任意键返回..." << endl;
        CreateGraph();
    }
    else
        cout << "\t无此路径。按任意键返回..." << endl;
}
void Modify_info()
{
    fflush(stdin);
    int i;
    string name;
    cout << "\t请输入要修改信息的地点名称：\n\t";
    getline(cin, name);
    i = Locate(name);
    if (i)
    {
        cout << "\t[1]地点名称\n\t[2]地点简介\n\t请输入想更改的信息对应的序号（1~2）：\n\t";
        int op;
        cin >> op;
        fflush(stdin);
        if (op == 1)
        {
            cout << "\t请输入 " << G.building[i].name << " 的新名称：\n\t";
            string name;
            getline(cin, name);
            G.building[i].name = name;
        }
        if (op == 2)
        {
            cout << "\t请输入 " << G.building[i].name << " 的简介：\n\t";
            string intro;
            getline(cin, intro);
            G.building[i].introduction = intro;
        }
        cout << "\t修改成功。按任意键返回..." << endl;
    }
    else
        cout << "\t无此地点。按任意键返回..." << endl;
}