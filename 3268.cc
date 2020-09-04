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

const int mxn = 1000;
int dist[mxn], cost_f[mxn], cost_b[mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, X, A, B, T; 
    scanf("%d%d%d", &N, &M, &X); X--;
    vector<vector<ii> > adj_f(N), adj_b(N), adj(N);
    for (int i = 0; i < M; i++) {
        scanf("%d%d%d", &A, &B, &T);
        A--, B--;
        adj_f[B].push_back(make_pair(A, T));
        adj_b[A].push_back(make_pair(B, T));
    }
    for (int i = 0; i < N; i++) {
        memset(dist, 0x3f, N * sizeof(int)); dist[i] = 0;
        for (int j = 0; j < adj_f[i].size(); j++) {
            dist[adj_f[i][j].first] = min(dist[adj_f[i][j].first], adj_f[i][j].second);
        }
        for (int j = 0; j < N; j++) {
            if (i != j && dist[j] < INT_INF) adj[i].push_back(make_pair(j, dist[j]));
        }
    }
    memset(cost_f, 0x3f, N * sizeof(int));
    memset(cost_b, 0x3f, N * sizeof(int));
    cost_f[X] = cost_b[X] = 0;

    {
        priority_queue<ii, vector<ii>, greater<ii> > minq;
        minq.push(make_pair(0, X));
        while (!minq.empty()) {
            ii cur = minq.top(); minq.pop();
            int u = cur.second, w = cur.first;
            if (cost_f[u] < w) continue;
            for (int j = 0; j < adj_f[u].size(); j++) {
                int v = adj_f[u][j].first, d = adj_f[u][j].second;
                if (cost_f[v] > w + d) {
                    cost_f[v] = w + d; minq.push(make_pair(cost_f[v], v));
                }
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        adj[i].clear();
        memset(dist, 0x3f, N * sizeof(int)); dist[i] = 0;
        for (int j = 0; j < adj_b[i].size(); j++) {
            dist[adj_b[i][j].first] = min(dist[adj_b[i][j].first], adj_b[i][j].second);
        }
        for (int j = 0; j < N; j++) {
            if (i != j && dist[j] < INT_INF) adj[i].push_back(make_pair(j, dist[j]));
        }
    }

    {
        priority_queue<ii, vector<ii>, greater<ii> > minq;
        minq.push(make_pair(0, X));
        while (!minq.empty()) {
            ii cur = minq.top(); minq.pop();
            int u = cur.second, w = cur.first;
            if (cost_b[u] < w) continue;
            for (int j = 0; j < adj_b[u].size(); j++) {
                int v = adj_b[u][j].first, d = adj_b[u][j].second;
                if (cost_b[v] > w + d) {
                    cost_b[v] = w + d; minq.push(make_pair(cost_b[v], v));
                }
            }
        }
    }
    
    int best = 0;
    for (int i = 0; i < N; i++) {
        best = max(best, cost_f[i] + cost_b[i]);
    }

    printf("%d\n", best);


    return 0;
}