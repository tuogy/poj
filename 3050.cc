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

#ifdef __APPLE__
#define cin fin
std::ifstream cin("__sample.in");
#endif

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
const int INT_INF = 0x3f3f3f3f;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

bool vis[1000000];
int grid[5][5];

void dfs(int i, int j, int cur, int step) {
    if (step == 6) {
        vis[cur] = true;
    }
    else {
        for (int k = 0; k < 4; k++) {
            int ii = i + d4r[k], jj = j + d4c[k];
            if (ii < 0 || ii >= 5 || jj < 0 || jj >= 5) continue;
            dfs(ii, jj, cur * 10 + grid[i][j], step + 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            dfs(i, j, 0, 0);
        }
    }
    int tot = 0;
    for (int i = 0; i < 1000000; i++) tot += vis[i];
    cout << tot << endl;
    

    return 0;
}