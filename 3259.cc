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

int dist[500][500], spath[500], vis[500];
bool inqueue[500];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int F, N, M, W, s, e, t;
    for (scanf("%d", &F); F; F--) {
        scanf("%d%d%d", &N, &M, &W);
        memset(dist, 0x3f, sizeof(dist));
        memset(spath, 0x3f, sizeof(spath));
        memset(vis, 0, sizeof(vis));
        memset(inqueue, 0, sizeof(inqueue));
        for (int i = 0; i < N; i++) dist[i][i] = 0;
        spath[0] = 0;
        vector<vector<int> > adj(N);
        for (int i = 0; i < M; i++) {
            scanf("%d%d%d", &s, &e, &t); s--, e--;
            dist[s][e] = min(dist[s][e], t);
            dist[e][s] = min(dist[e][s], t);
            adj[s].push_back(e);
            adj[e].push_back(s);
        }
        for (int i = 0; i < W; i++) {
            scanf("%d%d%d", &s, &e, &t); s--, e--;
            dist[s][e] = min(dist[s][e], -t);
            adj[s].push_back(e);
        }
        queue<int> spfa; bool ncycle = false;
        spfa.push(0), inqueue[0] = true;
        while (!spfa.empty() && !ncycle) {
            int u = spfa.front(); spfa.pop();
            vis[u]++, inqueue[u] = false;
            if (vis[u] >= N) {
                ncycle = true; break;
            }
            for (int j = 0; j < adj[u].size(); j++) {
                int v = adj[u][j];
                if (spath[u] + dist[u][v] < spath[v]) {
                    spath[v] = spath[u] + dist[u][v];
                    if (!inqueue[v]) spfa.push(v), inqueue[v] = true;
                }
            }
        }
        if (ncycle) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}