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

int dist[500][500], spath[500];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int F, N, M, W, s, e, t;
    for (scanf("%d", &F); F; F--) {
        scanf("%d%d%d", &N, &M, &W);
        memset(dist, 0x3f, sizeof(dist));
        memset(spath, 0x3f, sizeof(spath));
        for (int i = 0; i < N; i++) dist[i][i] = 0;
        spath[0] = 0;
        vector<ii> paths, wormholes;
        for (int i = 0; i < M; i++) {
            scanf("%d%d%d", &s, &e, &t);
            dist[s][e] = min(dist[s][e], t);
            dist[e][s] = min(dist[e][s], t);
            paths.push_back(make_pair(s, e));
        }
        for (int i = 0; i < W; i++) {
            scanf("%d%d%d", &s, &e, &t);
            dist[s][e] = min(dist[s][e], -t);
            wormholes.push_back(make_pair(s, e));
        }
        for (int vv = 0; vv < N - 1; vv++) {
            for (int i = 0; i < paths.size(); i++) {
                int u = paths[i].first, v = paths[i].second;
                if (spath[u] + dist[u][v] < spath[v]) spath[v] = spath[u] + dist[u][v];
                if (spath[v] + dist[v][u] < spath[u]) spath[u] = spath[v] + dist[v][u];
            }
            for (int i = 0; i < wormholes.size(); i++) {
                int u = wormholes[i].first, v = wormholes[i].second;
                if (spath[u] + dist[u][v] < spath[v]) spath[v] = spath[u] + dist[u][v];
            }
        }
        bool ncycle = false;
        for (int i = 0; i < paths.size() && !ncycle; i++) {
            int u = paths[i].first, v = paths[i].second;
            if (spath[u] + dist[u][v] < spath[v] || spath[v] + dist[v][u] < spath[u]) ncycle = true;
        }
        for (int i = 0; i < wormholes.size() && !ncycle; i++) {
            int u = wormholes[i].first, v = wormholes[i].second;
            if (spath[u] + dist[u][v] < spath[v]) ncycle = true;
        }

        if (ncycle) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}