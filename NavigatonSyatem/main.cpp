#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <map>
#include <conio.h>
#include <windows.h>

#define MaxNum 128
#define INF 9999
using namespace std;

//�ص���Ϣ
typedef struct Building
{
    int id;
    string name;
    string introduction;
} Building, *ptrToBuilding;

//�ڽӾ���
typedef struct AdjMatrix
{
    int edge[MaxNum][MaxNum];  //����Ϣ��·�����ȣ�
    Building building[MaxNum]; //�ص���Ϣ
    int vNum, eNum;
} AdjMatrix;

//ȫ�ֱ���
AdjMatrix G;
int dist[MaxNum][MaxNum]; // Floyd�㷨����̾���
int path[MaxNum][MaxNum]; // Floyd�㷨����ת�ڵ�
bool isAdministrator;     // �Ƿ���й���ԱȨ��
bool createdALG = false;  // �Ƿ��Ѿ������ڽӱ�

// UI
void UI_Login();            //��¼UI
void UI_Administrator();    //����ԱUI
void UI_Tourist();          //�ο�UI
void UI_Map();              //����ص�����
void Menu_Login();          // ��¼����
void Menu_Administrator();  // ����Ա����
void Menu_Tourist();        // �οͽ���
void Menu_return();         // ������һ����
void Login_Administrator(); // ����Ա��¼��˲���
void Login_Tourist();       // �ο͵�¼��˲���
void Out_ALL();             // �˳���¼

// �㷨
void CreateGraph();         // ���� �����ڽӱ��洢У԰��ͼ
void Search_info_All();     // ��� ��ѯ���еص���Ϣ
void Search_info();         // ��� ��ѯָ���ص���Ϣ
void ShortestPath_Floyd();  // ���� �������������·����Floyd�㷨
void Search_path_All2All(); // ��� ��ѯ������������·��
void Search_path_A2All();   // ��� ��ѯĳ�㵽�����������·��
void Search_path_A2B();     // ��� ��ѯA�㵽B������·��
int Locate(string name);    // ���� �����ص����ƣ����ض�Ӧ�����
void Insert_Vex();          // ���� ����У԰�ص�
void Insert_Edge();         // ���� ����У԰·��
void Delete_Vex();          // ���� ɾ��У԰�ص�
void Delete_Edge();         // ���� ɾ��У԰·��
void Modify_info();         // ���� ���µص���Ϣ
void Save_info();           // ��� �ļ���� �����޸ĵ���Ϣ��"mapInfo.txt"

int main()
{
    Menu_Login();
    return 0;
}

// UI
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
    printf("\t|               [1] ��ѯĳ���ص���Ϣ                      |\n");
    printf("\t|               [2] ��ѯ���еص���Ϣ                      |\n");
    printf("\t|               [3] ȥĳ�ص����·����ѯ                  |\n");
    printf("\t|               [4] ȥ�������еص�����·����ѯ          |\n");
    printf("\t|               [0] �˳���¼                              |\n");
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
    UI_Map();
    printf("\t������ָ�\n\t");
}
void UI_Map()
{
    printf("\n");
    printf("\t___________________________________________________________\n");
    printf("\t                                                         \n");
    printf("\t                    �ӱ���ѧУ԰�ص�һ��                   \n");
    printf("\t                                                         \n");
    printf("\t");
    for (int i = 1; i <= G.vNum; i++)
    {
        cout << setiosflags(ios::left) << setw(22) << G.building[i].name;
        if (i % 3 == 0)
            cout << "\n\t";
    }
    printf("\n");
    printf("\t___________________________________________________________\n");
    printf("\n");
}
void Menu_Login() // ��¼����
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
            cout << "\t������0~2֮������֣�\n\t";
            break;
        }
        UI_Login();
    }
    cout << "\n\t�����˳�ϵͳ..." << endl;
    Sleep(500);
    exit(0);
}
void Menu_Administrator() // ����Ա����
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
            Search_path_A2B();
            break;
        case 5:
            Search_path_A2All();
            break;
        case 6:
            Insert_Vex();
            break;
        case 7:
            Delete_Vex();
            break;
        case 8:
            Insert_Edge();
            break;
        case 9:
            Delete_Edge();
            break;
        default:
            cout << "\t������0~9֮������֣�\n\t";
            break;
        }
        UI_Administrator();
    }
}
void Menu_Tourist() // �οͽ���
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
            Search_path_A2B();
            break;
        case 4:
            Search_path_A2All();
            break;
        default:
            cout << "\t������0~4֮������֣�\n\t";
            break;
        }
        UI_Tourist();
    }
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
    map<string, string> m; // map��keyֵ�ǹ���Ա���˺š�valueֵ�ǹ���Ա������
    //��ӹ���Ա���˺�������Ϣ
    m["123456"] = "123456";
    m["20201202039"] = "123456";
    int count = 3;     //�˺ź������������Ĵ������ܳ���3��
    bool flag = false; //�ж������Ƿ�Ϊ��
    while (count--)
    {
        string id;
        cout << "\t�����������˺ţ�\n\t";
        cin >> id;
        int i = 0;
        char password[50], ch;
        cout << "\t�������������룺\n\t";
        while ((ch = getch()) != '\r') // \r�ǻس���,�ص�����
        {
            if (ch == '\b') // \b���˸��
            {
                if (i > 0)
                {
                    printf("\b \b");
                    --i;
                }
            }
            else
            {
                password[i++] = ch;
                printf("*");
            }
        }
        password[i] = '\0';
        cout << endl;
        for (auto it : m) // for-eachѭ������map
        {
            // string�Ϳ���ֱ��==�Ƚ�,string�ͺ�char*�ͱȽ���Ҫ��string��c_str()ת��������strcmp�Ƚ�
            if ((it.first == id) && strcmp(it.second.c_str(), password) == 0)
            {
                flag = true;
                count = 0;
            }
        }
        if (flag)
        {
            isAdministrator = true; //�ǹ���Ա
            cout << "\t" << id << "����ϲ����¼�ɹ���������ת����Ա����..." << endl;
            Sleep(1000);
            Menu_Administrator();
            break;
        }
        else
        {
            isAdministrator = false; //���ǹ���Ա
            if (count == 0)
            {
                break;
            }
            cout << "\t��������˺Ż��������,�����������롣\n\t";
        }
    }
    if (!count && !flag)
    {
        cout << "\t����������������������ο���ݽ���У԰����ϵͳ..." << endl;
        system("pause");
        Menu_Tourist();
    }
}
void Login_Tourist() // �ο͵�¼��˲���
{
    Menu_Tourist();
}
void Out_ALL() // �˳���¼
{
    isAdministrator = false;
    cout << "���˳���¼�����ڷ�����һ����..." << endl;
    Sleep(1000);
    Menu_Login();
}

//�㷨
void CreateGraph() // ���� �����ڽӱ��洢У԰��ͼ
{
    fflush(stdin);
    int i, j, k, l;
    freopen("mapInfo.txt", "r", stdin);
    cin >> G.vNum >> G.eNum; //���붥�����ͱ���
    getchar();
    for (i = 0; i <= G.vNum; i++) //�����ڽӱ���
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
void Search_info_All() // ��� ��ѯ���еص���Ϣ
{
    cout << "\t���еص���Ϣ��ѯ�����" << endl;
    for (int i = 1; i <= G.vNum; i++)
        cout << "\t" << G.building[i].name << "��" << G.building[i].introduction << endl;
    cout << "\n\t�����������..." << endl;
    getchar();
    // Menu_return();
}
void Search_info() // ��� ��ѯָ���ص���Ϣ
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
void ShortestPath_Floyd() // ���� �������������·����Floyd�㷨
{
    // path[i][j]=k ��¼��ת���
    // dist[i][j]=sum ��¼��̾���
    int i, j, k, temp;
    //��ʼ��
    memset(dist, INF, sizeof(dist)); //����������������memory.hͷ�ļ�
    memset(path, -1, sizeof(path));
    for (i = 1; i <= G.vNum; i++)
    {
        for (j = 1; j <= G.vNum; j++)
        {
            dist[i][j] = G.edge[i][j];
            path[i][j] = j;
        }
        // dist[i][i] = 0;
    }
    //�㷨����
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
void Search_path_All2All() // ��� ��ѯ������������·��
{
    fflush(stdin);
    int i, j, k, l = 1;
    cout << "\t������������·�����������" << endl;
    for (i = 1; i <= G.vNum; i++)
    {
        for (j = 1; j <= G.vNum; j++)
        {
            if (i != j)
            {
                cout << "\t" << l++ << ":" << endl;
                stack<string> st;
                cout << "\t·��Ϊ��" << G.building[i].name;
                st.push(G.building[j].name);
                if (path[i][j] != j)
                {
                    k = j;
                    while (path[i][k] != k)
                    {
                        k = path[i][k];
                        st.push(G.building[k].name);
                    }
                }
                while (st.size())
                {
                    cout << " -> ";
                    cout << st.top();
                    st.pop();
                }
                cout << "\n"
                     << endl;
            }
        }
    }
    cout << "�����������..." << endl;
    getchar();
    // Menu_return();
}
void Search_path_A2All() // ��� ��ѯĳ�㵽�����������·��
{
    fflush(stdin);
    int i, j, k;
    string name;
    cout << "\t��������㣺\n\t";
    getline(cin, name);
    i = Locate(name);
    if (i)
    {
        cout << "\n\t" << G.building[i].name << " �������ص�����·����ѯ�����\n"
             << endl;
        for (j = 1; j <= G.vNum; j++)
        {
            if (i != j)
            {
                cout << "\t" << G.building[i].name << " �� " << G.building[j].name << " �����·������Ϊ��" << dist[i][j] << "�ס�" << endl;
                stack<string> st;
                cout << "\t·��Ϊ��" << G.building[i].name;
                st.push(G.building[j].name);
                if (path[i][j] != j)
                {
                    k = j;
                    while (path[i][k] != k)
                    {
                        k = path[i][k];
                        st.push(G.building[k].name);
                    }
                }
                while (st.size())
                {
                    cout << " -> ";
                    cout << st.top();
                    st.pop();
                }
                cout << "\n"
                     << endl;
            }
        }
    }
    else
        cout << "\t�����յ����" << endl;
    cout << "\t�����������..." << endl;
    getchar();
    // Menu_return();
}
void Search_path_A2B() // ��� ��ѯA�㵽B������·��
{
    fflush(stdin);
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
                    stack<string> st;
                    cout << "\t·��Ϊ��" << G.building[i].name;
                    st.push(G.building[j].name);
                    if (path[i][j] != j)
                    {
                        k = j;
                        while (path[i][k] != k)
                        {
                            k = path[i][k];
                            st.push(G.building[k].name);
                        }
                    }
                    while (st.size())
                    {
                        cout << " -> ";
                        cout << st.top();
                        st.pop();
                    }
                    cout << "\n"
                         << endl;
                }
            }
        }
    }
    else
        cout << "\t�����յ����" << endl;
    cout << "\t�����������..." << endl;
    getchar();
    // Menu_return();
}
int Locate(string name) // ���� �����ص����ƣ����ض�Ӧ�����
{
    for (int i = 1; i <= G.vNum; i++)
    {
        if (G.building[i].name == name)
            return i;
    }
    cout << "\tû�ҵ� " << name << endl;
    return 0;
}
void Insert_Vex() // ���� ����У԰�ص�
{
    fflush(stdin);
    if (G.vNum >= MaxNum)
    {
        cout << "\t�Ѵﵽ�洢�ص�����ޣ��޷��洢�������������..." << endl;
        getchar();
        return;
    }
    int i = G.vNum + 1;
    G.building[i].id = i;
    cout << "\t������ص����ƣ�";
    getline(cin, G.building[i].name);
    cout << "\t������ص��飺";
    getline(cin, G.building[i].introduction);
    G.vNum++;
    Save_info();
    cout << "\t�ɹ����ӵص㣺" << G.building[i].name << "\n\t�����������..." << endl;
    getchar();
    // Menu_return();
}
void Insert_Edge() // ���� ����У԰·��
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
        Save_info();
        cout << "\t�ɹ�����·��" << endl;
        cout << "\t�Ƿ��������·��������������������1���˳�����������0��\n\t";
    } while (cin >> n && n != 0);
    cout << "\t�����������..." << endl;
    getchar();
    // Menu_return();
}
void Delete_Vex() // ���� ɾ��У԰�ص�
{
    fflush(stdin);
    string name;
    cout << "\t������Ҫɾ���ĵص㣺\n\t";
    getline(cin, name);
    int x = Locate(name);
    if (x)
    {
        cout << "\tȷ��ɾ����ȷ��������1��ȡ��������0��\n\t";
        int op;
        cin >> op;
        if (op)
        {
            for (int i = x; i < G.vNum; i++)
            {
                G.building[i] = G.building[i + 1];
                for (int j = x; j < G.vNum; i++)
                    G.edge[i][j] = G.edge[i + 1][j + 1];
            }
            G.vNum--;
            Save_info();
            cout << "\t�ѳɹ�ɾ���õص㡣�����������..." << endl;
            CreateGraph();
        }
    }
    else
        cout << "\t�޴˵ص㡣�����������..." << endl;
    getchar();
    // Menu_return();
}
void Delete_Edge() // ���� ɾ��У԰·��
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
        cout << "\tȷ��ɾ����ȷ��������1��ȡ��������0��\n\t";
        int op;
        cin >> op;
        if (op)
        {
            G.edge[i][j] = INF;
            G.edge[j][i] = INF;
            G.eNum--;
            Save_info();
            cout << "\t�ѳɹ�ɾ����·���������������..." << endl;
            CreateGraph();
        }
    }
    else
        cout << "\t�޴�·���������������..." << endl;
    getchar();
    // Menu_return();
}
void Modify_info() // ���� ���µص���Ϣ
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
        Save_info();
        cout << "\t�޸ĳɹ��������������..." << endl;
    }
    else
        cout << "\t�޴˵ص㡣�����������..." << endl;
    getchar();
    // Menu_return();
}
void Save_info()
{
    freopen("mapInfo.txt", "w", stdout);
    printf("%d %d\n", G.vNum, G.eNum);

    for (int i = 0; i <= G.vNum; i++)
        cout << G.building[i].name << "\n"
             << G.building[i].introduction << endl;
    for (int i = 1; i <= G.vNum; i++)
    {
        for (int j = i + 1; j <= G.vNum; j++)
        {
            if (G.edge[i][j])
                cout << i << " " << j << " " << G.edge[i][j] << endl;
        }
    }
    freopen("CON", "w", stdout);
    cout << "\t�ѱ���" << endl;
    // getchar();
}