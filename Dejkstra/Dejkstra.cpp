#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>

using namespace std;

const int INF = 99999999;   // бесконечность

void ReadGraphFromFile(ifstream& F, vector<vector<int>>& graph) // чтение графа из файла, создание таблицы смежности
{
    int f = 0;
    int s = 0;
    int dist = 0;

    while (!F.eof())
    {
        F >> f;
        F >> s;
        F >> dist;
        int fIndex = f - 1;
        int sIndex = s - 1;
        graph[fIndex][sIndex] = dist;
    }
}

void DijkstrasAlgorythm(vector<vector<int>>& graph, int n, int& s)
{
    vector<pair<int, int>> metka(n, make_pair(INF, 0));
    metka[s-1] = make_pair(0, 1);
    vector<bool> k_metka(n, false);
    k_metka[s-1] = true;
    int kon = s-1;

    cout << "Steps   ";
    for (int i = 0; i < n; i++)
        cout << i + 1 << "      ";
    cout << "\n";
    cout << "  1    ";
    for (int j = 0; j < n; j++)
    {
        if (metka[j].first == INF)
            cout << "inf" << "   ";
        else
            cout << metka[j].first << "(" << metka[j].second << ")" << "   ";
    }
    cout << "\n";

    int result = 0;

    int step = 2;
    bool exit = false;
    while (!exit)
    {
        exit = true;
        for (int i = 0; i < n; i++)
            if (!k_metka[i])
                exit = false;

        for (int i = 0; i < n; i++)
        {
            if (!k_metka[i] && graph[kon][i] > 0)
                metka[i] = make_pair(min(graph[kon][i] + metka[kon].first, metka[i].first), kon + 1);
        }

        cout << "  " << step << "    ";
        step++;
        for (int j = 0; j < n; j++)
        {
            if (metka[j].first == INF)
                cout << "inf" << "   ";
            else
                cout << metka[j].first << "(" << metka[j].second << ")" << "   ";
        }
        cout << "\n";

        int min_dist = INF;
        for (int i = 0; i < n; i++)
        {
            if (!k_metka[i] && metka[i].first < min_dist)
            {
                min_dist = metka[i].first;
                kon = i;
            }
        }
        k_metka[kon] = true;
        result += min_dist;

        cout << "  " << step << "    ";
        step++;
        for (int j = 0; j < n; j++)
        {
            if (metka[j].first == INF)
                cout << "inf" << "   ";
            else
                cout << metka[j].first << "(" << metka[j].second << ")" << "   ";
        }
        cout << "\n";
    }

    //cout << "Метка для вершины " << t << " стала окончательной, значит алгоритм закончил свою работу\n";
    //cout << "Минимальный путь из вершины " << s << " в вершину " << t << " = " << result << "\n";
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string Fname;
    cout << "Введите имя файла для начала работы: ";
    cin >> Fname;
    ifstream Fin(Fname);
    if (!Fin.is_open())
    {
        cout << "Не удалось открыть файл!\n";
        return 1;
    }

    int n;
    Fin >> n;
    vector<vector<int>> graph(n, vector<int>(n, -1));

    ReadGraphFromFile(Fin, graph);

    int s = -1;
    
    while (s != 0)
    {
        system("cls");
        cout << "Введите вершину, из которой вы хотите найти минимальные пути до всех остальных вершин (если вы хотите выйти, то введите `0`): \n";
        cin >> s;
        if (s != 0)
        {
            DijkstrasAlgorythm(graph, n, s);
            system("pause");
        }
    }
    return 0;
}