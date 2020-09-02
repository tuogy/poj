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
#include <functional>
#include <limits>
#include <bitset>

#ifdef __APPLE__
#define cin fin
std::ifstream cin("__sample.in");
#endif

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;

bool grid[20][20];
bool vis[20][20];
int W, H;
int d4i[] = {0, 1, 0, -1}, d4j[] = {1, 0, -1, 0};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> W >> H) {
        if (W == 0 && H == 0) break;
        memset(vis, 0, sizeof(vis));
        char x;
        int r, c;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                cin >> x;
                if (x == '#') grid[i][j] = false;
                else {
                    if (x == '@') r = i, c = j;
                    grid[i][j] = true;
                }
            }
        }
        queue<pair<int, int> > bfs;
        bfs.push(make_pair(r, c));
        int ret = 1;
        vis[r][c] = true;
        while (!bfs.empty()) {
            pair<int, int> pr = bfs.front(); bfs.pop();
            for (int k = 0; k < 4; k++) {
                int rr = pr.first + d4i[k], cc = pr.second + d4j[k];
                if (rr < 0 || rr >= H || cc < 0 || cc >= W || !grid[rr][cc] || vis[rr][cc]) continue;
                ret++, vis[rr][cc] = true, bfs.push(make_pair(rr, cc));
            }
        }
        cout << ret << endl;
    }

    return 0;
}