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

const int R = 5, C = 6;
int tot = 0, best_tot = INT_MAX, init[R][C], press[R][C], cur[R][C], best[R][C];

void flip(int i, int j) {
    press[i][j] = 1, cur[i][j] ^= 1, tot++;
    for (int k = 0; k < 4; k++) {
        int ii = i + d4r[k], jj = j + d4c[k];
        if (ii < 0 || ii >= R || jj < 0 || jj >= C) continue;
        else cur[ii][jj] ^= 1;
    }
}

void solve() {
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) scanf("%d", &init[i][j]);
    }
    best_tot = INT_MAX;
    for (int r0 = 0; r0 < 1 << C; r0++) {
        tot = 0;
        memcpy(cur, init, sizeof(cur));
        memset(press, 0, sizeof(press));
        for (int j = 0, i = 0; j < C; j++) {
            if (r0 >> j & 1) flip(i, j);
        }
        for (int i = 1; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (cur[i - 1][j]) flip(i, j);
            }
        }
        for (int j = 0; j < C; j++) 
            if (cur[R - 1][j]) tot = INT_MAX;
        if (tot < best_tot) {
            best_tot = tot;
            memcpy(best, press, sizeof(best));
        }
    }
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("%d%c", best[i][j], j == C - 1 ? '\n' : ' ');
        }
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T; scanf("%d", &T);
    for (int ks = 1; ks <= T; ks++) {
        printf("PUZZLE #%d\n", ks);
        solve();
    }

    return 0;
}