/*
#include <cstdio>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;
#define MAX 100001
#define INF (1<<20)
#define pii pair< int, int >
#define pb(x) push_back(x)
 
struct comp
{
        bool operator()(const pii &a, const pii &b)
        {
            return a.second > b.second;
        }
};
 
priority_queue<pii, vector<pii > , comp> Q;
vector<pii > G[MAX];
int D[MAX];
bool F[MAX];
/*
int main()
{
    int i, u, v, w, sz, nodes, edges, starting;
 
    // create graph
    cout << "Enter the number of vertices and edges: ";
    cin >> nodes >> edges;
    cout << "Enter the edges with weigth: <source> <destination> <weigth>: \n";
    for (i = 0; i < edges; i++)
    {
        cin >> u >> v >> w;
        G[u].pb(pii(v, w));
        G[v].pb(pii(u, w)); // for undirected
    }
    cout << "Enter the source node: ";
    cin >> starting;
 
    // initialize distance vector
    for (i = 1; i <= nodes; i++)
        D[i] = INF;
    D[starting] = 0;
    Q.push(pii(starting, 0));
 
    // dijkstra
    while (!Q.empty())
    {
        u = Q.top().first;
        Q.pop();
        if (F[u])
            continue;
        sz = G[u].size();
        for (i = 0; i < sz; i++)
        {
            v = G[u][i].first;
            w = G[u][i].second;
            if (!F[v] && D[u] + w < D[v])
            {
                D[v] = D[u] + w;
                Q.push(pii(v, D[v]));
            }
        }
        F[u] = 1; // done with u
    }
 
    // result
    for (i = 1; i <= nodes; i++)
        cout << "Node " << i << ", min weight = " << D[i] << endl;
    return 0;
}

/*

Enter the number of vertices and edges: 6
7
Enter the edges with weigth: <source> <destination> <weigth>: 
0 1 1
1 2 3
1 4 5
3 4 7
4 5 9
5 3 8
0 3 3
Enter the source node: 1
Node 1, min weight = 0
Node 2, min weight = 3
Node 3, min weight = 12
Node 4, min weight = 5
Node 5, min weight = 14
Node 6, min weight = 1048576

*/