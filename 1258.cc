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

int dist[100][100];
int w[100];
bool vis[100];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    while (cin >> N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> dist[i][j];
            }
        }
        memset(w, 0x3f, N * sizeof(int)); w[0] = 0;
        memset(vis, 0, N * sizeof(bool));
        priority_queue<ii, vector<ii>, greater<ii> > minq;
        minq.push(make_pair(0, 0));
        int tot = 0;
        while (!minq.empty()) {
            ii cur = minq.top(); minq.pop();
            int u = cur.second, d = cur.first;
            if (vis[u]) continue;
            else tot += w[u], vis[u] = true;
            for (int v = 0; v < N; v++) {
                if (!vis[v] && w[v] > dist[u][v]) {
                    w[v] = dist[u][v]; minq.push(make_pair(w[v], v));
                }
            }
        }
        cout << tot << endl;

    }

    return 0;
}