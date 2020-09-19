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

const int mxn = 15;
int xs[mxn], ys[mxn];
int rect_inside[mxn][mxn];
int dp[1 << mxn];

bool inside(int x, int y, int x1, int y1, int x2, int y2) {
    int l = min(x1, x2), r = max(x1, x2);
    int t = max(y1, y2), b = min(y1, y2);
    return l <= x && x <= r && b <= y && y <= t;
}

int area(int x1, int y1, int x2, int y2) {
    return max(1, abs(x1 - x2)) * max(1, abs(y1 - y2));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while (cin >> n, n) {
        for (int i = 0; i < n; i++) cin >> xs[i] >> ys[i];

        memset(rect_inside, 0, sizeof(rect_inside));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (inside(xs[k], ys[k], xs[i], ys[i], xs[j], ys[j])) rect_inside[i][j] |= 1 << k;
                }
            }
        }

        memset(dp, 0x3f, sizeof(int) << n);
        dp[0] = 0;
        for (int s = 1; s < 1 << n; s++) {
            int topx = INT_MAX, topy = INT_MIN, topi = -1;
            for (int i = 0; i < n; i++) {
                if (s >> i & 1 && (ys[i] > topy || (ys[i] == topy && xs[i] < topx)))
                    topx = xs[i], topy = ys[i], topi = i;
            }
            for (int i = 0; i < n; i++) {
                if (i == topi) continue;
                dp[s] = min(dp[s], dp[s & ~rect_inside[topi][i]] + area(xs[i], ys[i], topx, topy));
            }
        }
        cout << dp[(1 << n) - 1] << endl;
    }

    return 0;
}
