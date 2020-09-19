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

const int mxn = 10;
int dp[mxn][1 << mxn];

int a[mxn], b[mxn], c[mxn], P[mxn], R[mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, m;
    cin >> N >> m;
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> c[i] >> P[i] >> R[i];
        a[i]--, b[i]--, c[i]--;
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][1] = 0;
    for (int s = 1; s < 1 << N; s++) {
        for (int v = 0; v < N; v++) {
            for (int j = 0; j < m; j++) {
                int u = a[j], v = b[j], w = c[j];
                if (s >> v & 1 && s >> u & 1) {
                    int ss = s ^ 1 << v;
                    dp[v][s] = min(dp[v][s], min(dp[u][s], dp[u][ss]) + (ss >> w & 1 ? P[j] : R[j]));
                }
            }
        }
    }
    int ret = *min_element(dp[N - 1], dp[N]);
    if (ret >= INT_INF) cout << "impossible" << endl;
    else cout << ret << endl;

    

    return 0;
}
