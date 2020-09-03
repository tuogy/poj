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
#define cin fin
std::ifstream cin("__sample.in");
#endif

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
const int INT_INF = 0x3f3f3f3f;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

const int mxn = 2000;
int N;
ii h[mxn];
int hid[mxn];
int dp[2][mxn], cost[mxn];
int mincost;

void solve() {
    memset(cost, 0, N * sizeof(int));
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < N; i++) {
        int hi = h[hid[i]].first;
        int best = INT_MAX;
        for (int j = 0; j < N; j++) {
            int hj = h[j].first;
            if (hi > hj) dp[0][j] += hi - hj;
            else {
                best = min(best, dp[0][j] + hj);
                dp[0][j] = best - hi;
            }
        }
        if (i < N - 1) cost[i + 1] += dp[0][hid[i + 1]];
    }
    for (int i = N - 1; i >= 0; i--) {
        int hi = h[hid[i]].first;
        int best = INT_MAX;
        for (int j = N - 1; j >= 0; j--) {
            int hj = h[j].first;
            if (hj > hi) dp[1][j] += hj - hi;
            else {
                best = min(best, dp[1][j] - hj);
                dp[1][j] = best + hi;
            }
        }
        if (i) cost[i - 1] += dp[1][hid[i - 1]];
    }

    mincost = min(mincost, *min_element(cost, cost + N));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    mincost = INT_MAX;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> h[i].first;
        h[i].second = i;
    }
    sort(h, h + N);
    for (int i = 0; i < N; i++) hid[h[i].second] = i;
    solve();

    for (int i = 0; i < N; i++) h[i].first = -h[i].first;
    sort(h, h + N);
    for (int i = 0; i < N; i++) hid[h[i].second] = i;
    solve();

    cout << mincost << endl;

    return 0;
}