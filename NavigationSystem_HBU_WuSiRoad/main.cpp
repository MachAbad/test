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

//�ص���Ϣ
typedef struct Building
{
    int id;
    string name;
    string introduction;
} Building, *ptrToBuilding;

//�߽��ṹ
typedef struct node
{
    int id;            // ��ͨ�Ľ��
    int info_len;      // ·������
    struct node *next; // ָ����һ�������ָ����
} EdgeNode;

//������ṹ
typedef struct vnode
{
    Building building;   // ������
    EdgeNode *firstedge; // ��һ���ߵ�ָ��
} vnode;

//�ڽӱ�
typedef struct ALGraph
{
    vector<vnode> adjList;
    int vNum, eNum;
} ALGraph;

//ȫ�ֱ���
ALGraph G;
int dist[MaxNum][MaxNum]; // Floyd�㷨����̾���
int path[MaxNum][MaxNum]; // Floyd�㷨����ת�ڵ�
bool isAdministrator;     // �Ƿ���й���ԱȨ��
bool createdALG = false;  // �Ƿ��Ѿ������ڽӱ�

// UI
void Menu_Login();          // ��¼����
void Menu_Administrator();  // ����Ա����
void Menu_Tourist();        // �οͽ���
void Menu_return();         // ������һ����
void Login_Administrator(); // ����Ա��¼��˲���
void Login_Tourist();       // �ο͵�¼��˲���
void Out_ALL();             // �˳���¼

// �㷨
void CreateALGraph();               // ���� �����ڽӱ��洢У԰��ͼ
void Search_info_All();             // ��� ��ѯ���еص���Ϣ
void Search_info(int x);            // ��� ��ѯָ���ص���Ϣ
void ShortestPath_Floyd();          // ���� �������������·����Floyd�㷨
void Search_path_All2All();         // ��� ��ѯ������������·��
void Search_path_A2All(int x);      // ��� ��ѯĳ�㵽�����������·��
void Search_path_A2B(int x, int y); // ��� ��ѯA�㵽B������·��
int Locate(string name);            // ���� �����ص����ƣ����ض�Ӧ�����
void Insert_Vex();                  // ���� ����У԰�ص�
void Insert_Edge();                 // ���� ����У԰·��
void Delete_Vex();                  // ���� ɾ��У԰�ص�
void Delete_Edge();                 // ���� ɾ��У԰·��
void Modify_info();                 // ���� ���µص���Ϣ

int main()
{
    Menu_Login();
    return 0;
}

// UI
void Menu_Login() // ��¼����
{
    printf("\n\t�����У����Ժ�...");
    // Sleep(1000);
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
            cout << "\t������0~2֮������֣�" << endl;
            break;
        }
        // if (cin.get() == '\n')  break;
    }
    cout << "\n\t�����˳�ϵͳ..." << endl;
    Sleep(500);
    exit(0);
}
void Menu_Administrator() // ����Ա����
{
    system("cls");
    printf("\n");
    printf("\t _________________________________________________________\n");
    printf("\t|                                                         |\n");
    printf("\t|                                                         |\n");
    printf("\t|               �ӱ���ѧУ԰������ϵͳ����Ա����          |\n");
    printf("\t|                                                         |\n");
    printf("\t|               [1] ��ѯĳ���ص���Ϣ                      |\n");
    printf("\t|               [2] ��ѯ���еص���Ϣ                      |\n");
    printf("\t|               [3] �޸ĵص���Ϣ                          |\n");
    printf("\t|               [4] ȥĳ�ص����·����ѯ                  |\n");
    printf("\t|               [5] ȥ�������еص�����·����ѯ          |\n");
    printf("\t|               [6] ���У԰�ص�                          |\n");
    printf("\t|               [7] ɾ��У԰�ص�                          |\n");
    printf("\t|               [8] ���У԰·��                          |\n");
    printf("\t|               [9] ɾ��У԰·��                          |\n");
    printf("\t|               [0] �˳���¼                              |\n");
    printf("\t|                                                         |\n");
    printf("\t|_________________________________________________________|\n");
    printf("\n");
    printf("\t������ָ�");
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
void Menu_Tourist() // �οͽ���
{
    system("cls");
    printf("\n");
    printf("\t _________________________________________________________\n");
    printf("\t|                                                         |\n");
    printf("\t|                                                         |\n");
    printf("\t|               �ӱ���ѧУ԰������ϵͳ�οͽ���            |\n");
    printf("\t|                                                         |\n");
    printf("\t|               [1] ��ѯĳ���ص���Ϣ                      |\n");
    printf("\t|               [2] ��ѯ���еص���Ϣ                      |\n");
    printf("\t|               [3] ȥĳ�ص����·����ѯ                  |\n");
    printf("\t|               [4] ȥ�������еص�����·����ѯ          |\n");
    printf("\t|               [0] �˳���¼                              |\n");
    printf("\t|                                                         |\n");
    printf("\t|_________________________________________________________|\n");
    printf("\n");
    printf("\t������ָ�");
}
void Menu_return() // ������һ����
{
    if (isAdministrator)
        Menu_Administrator();
    else
        Menu_Tourist();
}
void Login_Administrator() // ����Ա��¼��˲���
{
    Menu_Administrator();
}
void Login_Tourist() // �ο͵�¼��˲���
{
    Menu_Tourist();
}
void Out_ALL() // �˳���¼
{
    isAdministrator = false;
    Menu_Login();
}

//�㷨
void CreateALGraph() // ���� �����ڽӱ��洢У԰��ͼ
{
    int i, j, k, l;
    EdgeNode *s;
    freopen("mapInfo.txt", "r", stdin);
    cin >> G.vNum >> G.eNum; //���붥�����ͱ���
    getchar();
    for (i = 0; i <= G.vNum; i++) //�����ڽӱ���
    {
        vnode v;
        v.building.id = i;
        getline(cin, v.building.name);
        getline(cin, v.building.introduction);
        // cin >> v.building.name >> v.building.introduction; //��������ո�������
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
    /* debug ����ߵ���Ϣ��ûɶ�ã�
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
void Search_info_All() // ��� ��ѯ���еص���Ϣ
{
    for (int i = 1; i <= G.vNum; i++)
        cout << G.adjList[i].building.id << "." << G.adjList[i].building.name << "��" << G.adjList[i].building.introduction << endl;
}
void Search_info(int x) // ��� ��ѯָ���ص���Ϣ
{
    int n;
    while (cin >> n && n != 0)
    {
        int i;
        for (i = 1; i <= G.vNum; i++)
            if (G.adjList[i].building.id == x)
            {
                cout << G.adjList[i].building.name << "��" << G.adjList[i].building.introduction << endl;
                break;
            }
        if (i > G.vNum)
            cout << "�޴˵ص㣬���������루������ѯ������0����" << endl;
    }
}
void ShortestPath_Floyd() // ���� �������������·����Floyd�㷨
{
    // path[i][j]=k ��ʾi��j�����·���ᾭ��k
    // dist[i][j]=sum ��ʾi��j�����·������Ϊsum
    int i, j, k, temp;
    EdgeNode *p;
    //��ʼ��
    for (i = 1; i <= G.vNum; i++)
    {
        for (j = 1; j <= G.vNum; j++)
        {
            dist[i][j] = INF;
            path[i][j] = j;
        }
        dist[i][i] = 0;
    }
    //��¼���ж���֮��ľ��루�ڽӾ���תΪ�ڽӱ���?
    for (i = 1; i <= G.vNum; i++)
    {
        p = G.adjList[i].firstedge;
        while (p)
        {
            dist[i][p->id] = p->info_len;
            p = p->next;
        }
    }
    //�������·��?
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
    /* debug,���?
    int l = 1;
    cout << "��������֮������·��������" << endl;
    for (i = 1; i < G->vNum; i++)
    {
        for (j = 1; j < G->vNum; j++)
        {
            if (i != j)
            {
                cout << l++ << ":" << endl;
                cout << i << "." << G->adjList[i].building.name << " �� " << j << "." << G->adjList[j].building.name << " �����·������Ϊ��?" << dist[i][j] << endl;
                cout << "·��Ϊ��" << j << "." << G->adjList[j].building.name;
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
void Search_path_All2All() // ��� ��ѯ������������·��
{
    int i, j, k, l = 1;
    cout << "������������·�����������" << endl;
    for (i = 1; i <= G.vNum; i++)
    {
        for (j = 1; j <= G.vNum; j++)
        {
            if (i != j)
            {
                cout << l++ << ":" << endl;
                cout << i << "." << G.adjList[i].building.name << " �� " << j << "." << G.adjList[j].building.name << " �����·������Ϊ��" << dist[i][j] << "�ס�" << endl;
                cout << "·��Ϊ��" << j << "." << G.adjList[j].building.name;
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
void Search_path_A2All(int x) // ��� ��ѯĳ�㵽�����������·��
{
}
void Search_path(int x, int y) // ��� ��ѯA�㵽B������·��
{
    int i, j, k;
    cout << x << " �� " << y << " �����·����ѯ�����" << endl;
    for (i = 1; i <= G.vNum; i++)
    {
        for (j = 1; j <= G.vNum; j++)
        {
            if (i == x && j == y)
            {
                cout << i << "." << G.adjList[i].building.name << " �� " << j << "." << G.adjList[j].building.name << " �����·������Ϊ��" << dist[i][j] << "�ס�" << endl;
                cout << "·��Ϊ��" << j << "." << G.adjList[j].building.name;
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
int Locate(string name) // ���� �����ص����ƣ����ض�Ӧ�����
{
    for (int i = 1; i <= G.vNum; i++)
    {
        if (G.adjList[i].building.name == name)
            return i;
    }
    cout << "û�ҵ� " << name << endl;
    return 0;
}
void Insert_Vex() // ���� ����У԰�ص�
{
    if (G.adjList.size() >= MaxNum)
    {
        cout << "\t�Ѵﵽ�洢�ص�����ޣ��޷��洢��" << endl;
        return;
    }
    vnode v;
    v.building.id = G.adjList.size();
    cout << "\t������ص����ƣ�\n\t";
    getline(cin, v.building.name);
    cout << "\t������ص��飺\n\t";
    getline(cin, v.building.introduction);
    G.adjList.push_back(v);
    G.vNum++;
    cout << "\t�ɹ����ӵص㣺" << v.building.name << endl;
}
void Insert_Edge() // ���� ����У԰·��
{
    int n;
    do
    {
        int i, j, l;
        string name;
        cout << "\t������·����һ���˵㣺" << endl;
        getline(cin, name);
        i = Locate(name);
        cout << "\t������·������һ���˵㣺" << endl;
        getline(cin, name);
        j = Locate(name);
        cout << "\t������·���ĳ��ȣ���λ���ף���" << endl;
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
        cout << "\t�ɹ�����·��" << endl;
        cout << "\t�Ƿ��������·��������������������1���˳�����������0��\n\t" << endl;
    } while (cin >> n && n != 0);
}
void Delete_Vex() // ���� ɾ��У԰�ص�
{
}
void Delete_Edge() // ���� ɾ��У԰·��
{
    int i,j;
    cout << "������Ҫɾ���������ص�";
}
void Modify_info() // ���� ���µص���Ϣ
{
}