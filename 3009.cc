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
typedef long long ll;

int grid[20][20];
int w, h;
int d4i[] = {0, 1, 0, -1}, d4j[] = {1, 0, -1, 0};
ii s, g;

bool dfs(ii cur, int rem) {
    if (rem == 0) return cur == g;
    else {
        bool ret = false;
        int r = cur.first, c = cur.second;
        for (int k = 0; k < 4 && !ret; k++) {
            int rr = r + d4i[k], cc = c + d4j[k];
            if (rr < 0 || rr >= h || cc < 0 || cc >= w || grid[rr][cc] == 1) continue;
            while (rr >= 0 && rr < h && cc >= 0 && cc < w && (grid[rr][cc] & 1) == 0) rr += d4i[k], cc += d4j[k];
            if (rr < 0 || rr >= h || cc < 0 || cc >= w) continue;
            else if (grid[rr][cc] == 3) ret = true;
            else if (grid[rr][cc] == 1) {
                grid[rr][cc] = 0;
                if (dfs(make_pair(rr - d4i[k], cc - d4j[k]), rem - 1)) ret = true;
                grid[rr][cc] = 1;
            }
        }
        return ret;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> w >> h) {
        if (w == 0 && h == 0) break;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> grid[i][j];
                if (grid[i][j] == 2) s = make_pair(i, j);
                else if (grid[i][j] == 3) g = make_pair(i, j);
            }
        }
        bool success = false;
        for (int i = 1; i <= 10 && !success; i++) {
            if (dfs(s, i)) {
                cout << i << endl;
                success = true;
                break;
            }
        }
        if (!success) cout << -1 << endl;


    }

    return 0;
}