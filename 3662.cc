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
#define scanf(...) fscanf(__fp, __VA_ARGS__)
#define cin fin
std::ifstream cin("__sample.in");
#endif

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
const int INT_INF = 0x3f3f3f3f, INT_NINF = 0xc0c0c0c0;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

const int mxn = 1000, mxp = 10000;
int N, P, K, dist[mxn];
bool vis[mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int a, b, l;
    scanf("%d%d%d", &N, &P, &K);
    vector<vector<ii> > adj(N);
    for (int i = 0; i < P; i++) {
        scanf("%d%d%d", &a, &b, &l);
        --a, --b;
        adj[a].push_back(make_pair(b, l));
        adj[b].push_back(make_pair(a, l));
    }

    memset(dist, -1, N * sizeof(int));
    {
        queue<ii> bfs; 
        dist[0] = 0, bfs.push(make_pair(0, 0));
        while (dist[N - 1] == -1 && !bfs.empty()) {
            int u = bfs.front().first, d = bfs.front().second; bfs.pop();
            for (int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].first;
                if (dist[v] == -1) {
                    dist[v] = d + 1, bfs.push(make_pair(v, d + 1));
                }
            }
        }
    }
    if (dist[N - 1] == -1) printf("-1\n");
    else if (dist[N - 1] <= K) printf("0\n");
    else {
        int l = 0, r = 1000000;
        while (l < r - 1) {
            int c = (l + r) / 2;
            memset(dist, 0x3f, N * sizeof(int));
            memset(vis, false, N * sizeof(bool));
            priority_queue<ii, vector<ii>, greater<ii> > bfs; 
            dist[0] = 0, bfs.push(make_pair(0, 0));
            while (!vis[N - 1] && !bfs.empty()) {
                ii cur = bfs.top(); bfs.pop();
                int u = cur.second;
                if (vis[u]) continue;
                vis[u] = true;
                for (int i = 0; i < adj[u].size(); i++) {
                    int v = adj[u][i].first, w = adj[u][i].second, ww = (w > c);
                    if (!vis[v] && dist[v] > dist[u] + ww) {
                        dist[v] = dist[u] + ww, bfs.push(make_pair(dist[u] + ww, v));
                    }
                }
            }
            if (dist[N - 1] <= K) r = c;
            else l = c;
        }
        printf("%d\n", r);
    }


    return 0;
}