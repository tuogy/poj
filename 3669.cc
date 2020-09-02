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
#include <limits>
#include <bitset>

#ifdef __APPLE__
#define cin fin
std::ifstream cin("__sample.in");
#endif

using namespace std;

typedef pair<int, int> ii;
typedef pair<ii, int> pi;
typedef long long ll;

const int INT_INF = 0x3f3f3f3f;
int dtime[305][305];
bool vis[305][305];
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    memset(dtime, 0x3f, sizeof(dtime));
    memset(vis, 0, sizeof(vis));
    int M, x, y, t;
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> x >> y >> t;
        dtime[x][y] = min(dtime[x][y], t);
        for (int k = 0; k < 4; k++) {
            int xx = x + d4r[k], yy = y + d4c[k];
            if (xx < 0 || yy < 0) continue;
            dtime[xx][yy] = min(dtime[xx][yy], t);
        }
    }
    if (dtime[0][0] == 0) {
        cout << -1 << endl; return 0;
    }
    queue<pi> bfs;
    bfs.push(make_pair(make_pair(0, 0), 0)), vis[0][0] = true;
    while (!bfs.empty()) {
        pi cur = bfs.front(); bfs.pop();
        ii pos = cur.first;
        int time = cur.second;
        if (dtime[pos.first][pos.second] == INT_INF) {
            cout << time << endl; return 0;
        }
        for (int k = 0; k < 4; k++) {
            int rr = pos.first + d4r[k], cc = pos.second + d4c[k];
            if (rr < 0 || cc < 0 || vis[rr][cc] || dtime[rr][cc] <= time + 1) continue;
            vis[rr][cc] = true;
            bfs.push(make_pair(make_pair(rr, cc), time + 1));
        }
    }
    cout << -1 << endl;

    
    return 0;
}