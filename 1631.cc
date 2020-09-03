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

int p[40000];
int dp[40001];

bool i_gt(const int& a, const int& b) {
    return a > b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T; cin >> T;
    for (int ks = 0; ks < T; ks++) {
        int P, x; cin >> P;
        for (int i = 0; i < P; i++) {
            cin >> x; p[i] = x - 1;
        }
        memset(dp, -1, (1 + P) * sizeof(int));
        dp[0] = P;
        for (int i = P - 1; i >= 0; i--) {
            int v = upper_bound(dp, dp + P + 1, p[i] + 1, i_gt) - dp - 1;
            dp[v + 1] = max(dp[v + 1], p[i]);
        }
        int ret = 0;
        for (; ret <= P && dp[ret] >= 0; ret++);
        cout << ret - 1 << endl;
    }

    return 0;
}