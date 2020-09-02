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

struct itv {
    int l, r, e;
};

bool compare(const itv& a, const itv& b) {
    return a.l < b.l;
}

bool lb_compare(const itv& a, int r) {
    return a.l < r;
}

itv v[1000];
int dp[1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, R;
    cin >> N >> M >> R;
    for (int i = 0; i < M; i++) cin >> v[i].l >> v[i].r >> v[i].e;
    sort(v, v + M, compare);
    memset(dp, 0, sizeof(dp));
    for (int i = M - 1; i >= 0; i--) {
        int next = lower_bound(v, v + M, v[i].r + R, lb_compare) - v;
        dp[i] = max(dp[i + 1], v[i].e + dp[next]);
    }
    cout << dp[0] << endl;


    return 0;
}