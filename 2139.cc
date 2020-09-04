#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <climits>
#include <bitset>
#include <functional>

#ifdef __APPLE__
FILE *__fp = fopen("__sample.in", "r");
#define scanf(__VA_ARGS_...) fscanf(__fp, __VA_ARGS_)
#define cin fin
std::ifstream cin("__sample.in");
#endif

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
const int INT_INF = 0x3f3f3f3f, INT_NINF = 0xc0c0c0c0;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, m, x; scanf("%d%d", &N, &M);
    vector<vector<int> > adj(N), adj_movie(N);
    vector<bitset<300> > movie(M);
    for (int i = 0; i < M; i++) {
        movie[i].reset(); 
        scanf("%d", &m);
        for (int j = 0; j < m; j++) {
            scanf("%d", &x); x--;
            adj_movie[x].push_back(i);
            movie[i].set(x);
        }
    }
    for (int i = 0; i < N; i++) {
        bitset<300> cur;
        for (int j = 0; j < adj_movie[i].size(); j++) {
            cur |= movie[adj_movie[i][j]];
        }
        cur.reset(i);
        for (int j = 0; j < N; j++) {
            if (cur[j]) adj[i].push_back(j);
        }
    }

    int best = INT_MAX;
    for (int i = 0; i < N; i++) {
        bool vis[300] = {0};
        queue<ii> bfs;
        bfs.push(make_pair(i, 0)); vis[i] = true;
        int total = 0;
        while (!bfs.empty()) {
            ii cur = bfs.front(); bfs.pop();
            total += cur.second;
            int sz = adj[cur.first].size();
            for (int j = 0; j < sz; j++) {
                if (!vis[adj[cur.first][j]]) {
                    bfs.push(make_pair(adj[cur.first][j], cur.second + 1));
                    vis[adj[cur.first][j]] = true;
                }
            }
        }
        best = min(best, 100 * total / (N - 1));
    }

    cout << best << endl;
    

    return 0;
}