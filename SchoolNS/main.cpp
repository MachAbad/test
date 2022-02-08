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

// �㷨
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
    printf("\t|                ��ӭʹ�úӱ���ѧУ԰����ϵͳ             |\n");
    printf("\t|                                                         |\n");
    printf("\t|                     ��ѡ�����ĵ�¼��ʽ                  |\n");
    printf("\t|               [1] ���ο���ݽ���                        |\n");
    printf("\t|               [2] �Թ���Ա��ݵ�¼                      |\n");
    printf("\t|               [0] �˳�ϵͳ                              |\n");
    printf("\t|                                                         |\n");
    printf("\t|_________________________________________________________|\n");
    printf("\n");
    printf("\t�������Ӧ�����ʹ����Ӧ���ܣ�\n\t");
}
void UI_Tourist()
{
    system("cls");
    printf("\n");
    printf("\t _________________________________________________________\n");
    printf("\t|                                                         |\n");
    printf("\t|                                                         |\n");
    printf("\t|               �ӱ���ѧУ԰������ϵͳ�οͽ���            |\n");
    printf("\t|                                                         |\n");
    printf("\t|               [1] ĳ����Ϣ                              |\n");
    printf("\t|               [2] ���еص���Ϣ                          |\n");
    printf("\t|               [3] ȥĳ�����·��                        |\n");
    printf("\t|               [0] �˳�                                  |\n");
    printf("\t|                                                         |\n");
    printf("\t|_________________________________________________________|\n");
    UI_Map();
    printf("\t������ָ��:\n\t");
}
void UI_Administrator()
{
    system("cls");
    printf("\n");
    printf("\t _________________________________________________________\n");
    printf("\t|                                                         |\n");
    printf("\t|                                                         |\n");
    printf("\t|               �ӱ���ѧУ԰������ϵͳ����Ա����          |\n");
    printf("\t|                                                         |\n");
    printf("\t|               [1] ĳ����Ϣ                              |\n");
    printf("\t|               [2] ���еص���Ϣ                          |\n");
    printf("\t|               [3] �޸ĵص���Ϣ                          |\n");
    printf("\t|               [4] ȥĳ�����·��                        |\n");
    printf("\t|               [6] ��ӵص�                              |\n");
    printf("\t|               [7] ɾ���ص�                              |\n");
    printf("\t|               [8] ���·��                              |\n");
    printf("\t|               [9] ɾ��·��                              |\n");
    printf("\t|               [0] �˳�                                  |\n");
    printf("\t|                                                         |\n");
    printf("\t|_________________________________________________________|\n");
    UI_Map();
    printf("\t������ָ�\n\t");
}
void UI_Map()
{
    printf("-------------------------------------------------------����÷԰3��4��5��-----------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("---УҽԺ----------------------------------����÷԰6��-----------------------------------����÷԰2��-------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-------����Ժ-------------------------------��Ժ����----------��������---------------�ٳ�-----------����÷԰1��----------\n");
    printf("-------------------------����ѧԺ--------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-------------------������-------------------��ѧѧԺ--------------����ѧԺ-------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------�ݷ�¥-------------------����ѧԺ--------------��ѧ¥--------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("------------------------------------��2�ſ�--------------��1�ſ�-------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("------------------------------------��1�ſ�--------------��2�ſ�-------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("--------------------��Է¥---------------------------------------------�๦�ܹ�----------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-��Ժ����--------------------------------------------------------------------------------------------------------------------\n");
    printf("------------------�ڰ˽�ѧ¥-------�ھŽ�ѧ¥-----------------��¥-----------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("-------------------------------------------ع��԰----------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("--���߽�ѧ¥-------�ۺϽ�ѧ¥------------------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    printf("--------------------------------���ʽ���ѧԺ---------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
}
void Menu_Login()
{
    printf("\n\t�����У����Ժ�...");
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
    cout << "\t���еص���Ϣ��ѯ�����" << endl;
    for (int i = 1; i <= G.vNum; i++)
        cout << "\t" << G.building[i].name << "��" << G.building[i].introduction << endl;
    cout << "\n\t�����������..." << endl;
    getchar();
    // Menu_return();
}
void Search_info()
{
    fflush(stdin);
    int i;
    string name;
    cout << "\t������Ҫ��ѯ�ĵص㣺\n\t";
    getline(cin, name);
    i = Locate(name);
    if (i)
        cout << "\t" << G.building[i].name << "��" << G.building[i].introduction << endl;
    else
        cout << "\t�޴˵ص㣬���������루������ѯ������0����" << endl;
    cout << "\t�����������..." << endl;
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
    cout << "\t��������㣺";
    getline(cin, name);
    x = Locate(name);
    cout << "\t�������յ㣺";
    getline(cin, name);
    y = Locate(name);
    if (x && y)
    {
        cout << "\t" << G.building[x].name << " �� " << G.building[y].name << " �����·����ѯ�����" << endl;
        for (i = 1; i <= G.vNum; i++)
        {
            for (j = 1; j <= G.vNum; j++)
            {
                if (i == x && j == y)
                {
                    cout << "\t" << G.building[i].name << " �� " << G.building[j].name << " �����·������Ϊ��" << dist[i][j] << "�ס�" << endl;
                    cout << "\t·��Ϊ��" << G.building[j].name;
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
        cout << "�����յ����" << endl;
    cout << "�����������..." << endl;
}
int Locate(string name)
{
    for (int i = 1; i <= G.vNum; i++)
    {
        if (G.building[i].name == name)
            return i;
    }
    cout << "\tû�ҵ� " << name << endl;
    return 0;
}
void Insert_Vex()
{
    fflush(stdin);
    int i = G.vNum + 1;
    G.building[i].id = i;
    cout << "\t������ص����ƣ�";
    getline(cin, G.building[i].name);
    cout << "\t������ص��飺";
    getline(cin, G.building[i].introduction);
    G.vNum++;
    cout << "\t�ɹ����ӵص㣺" << G.building[i].name << "\n\t�����������..." << endl;
}
void Insert_Edge()
{
    int n;
    do
    {
        fflush(stdin);
        int i, j, l;
        string name;
        cout << "\t������·����һ���˵㣺\n\t";
        getline(cin, name);
        i = Locate(name);
        cout << "\t������·������һ���˵㣺\n\t";
        getline(cin, name);
        j = Locate(name);
        cout << "\t������·���ĳ��ȣ���λ���ף���\n\t";
        cin >> l;
        G.edge[i][j] = l;
        G.edge[j][i] = l;
        G.eNum++;
        cout << "\t�ɹ�����·��" << endl;
        cout << "\t�Ƿ��������·��������������������1���˳�����������0��\n\t";
    } while (cin >> n && n != 0);
    cout << "\t�����������..." << endl;
}
void Delete_Vex()
{
    fflush(stdin);
    string name;
    cout << "\t������Ҫɾ���ĵص㣺\n\t";
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
        cout << "\t�ѳɹ�ɾ���õص㡣�����������..." << endl;
        CreateGraph();
    }
    else
        cout << "\t�޴˵ص㡣�����������..." << endl;
}
void Delete_Edge()
{
    fflush(stdin);
    int i, j;
    string name;
    cout << "\t������Ҫɾ����·�����ӵ�����һ���ص㣺\n\t";
    getline(cin, name);
    i = Locate(name);
    cout << "\t������Ҫɾ����·�����ӵ���һ���ص㣺\n\t";
    getline(cin, name);
    j = Locate(name);
    if (i && j && G.edge[i][j] < INF)
    {
        G.edge[i][j] = INF;
        G.edge[j][i] = INF;
        G.eNum--;
        cout << "\t�ѳɹ�ɾ����·���������������..." << endl;
        CreateGraph();
    }
    else
        cout << "\t�޴�·���������������..." << endl;
}
void Modify_info()
{
    fflush(stdin);
    int i;
    string name;
    cout << "\t������Ҫ�޸���Ϣ�ĵص����ƣ�\n\t";
    getline(cin, name);
    i = Locate(name);
    if (i)
    {
        cout << "\t[1]�ص�����\n\t[2]�ص���\n\t����������ĵ���Ϣ��Ӧ����ţ�1~2����\n\t";
        int op;
        cin >> op;
        fflush(stdin);
        if (op == 1)
        {
            cout << "\t������ " << G.building[i].name << " �������ƣ�\n\t";
            string name;
            getline(cin, name);
            G.building[i].name = name;
        }
        if (op == 2)
        {
            cout << "\t������ " << G.building[i].name << " �ļ�飺\n\t";
            string intro;
            getline(cin, intro);
            G.building[i].introduction = intro;
        }
        cout << "\t�޸ĳɹ��������������..." << endl;
    }
    else
        cout << "\t�޴˵ص㡣�����������..." << endl;
}