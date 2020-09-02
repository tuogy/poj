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

const int mxn = 100001;
int dp[mxn];
int A[100], C[100];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        for (int i = 0; i < n; i++) cin >> A[i];
        for (int i = 0; i < n; i++) cin >> C[i];
        memset(dp, -1, (1 + m) * sizeof(int));
        dp[0] = 0;
        int ret = 0;
        for (int i = 0; i < n; i++) {
            int a = A[i], c = C[i];
            for (int j = 0; j <= m; j++) {
                if (dp[j] >= 0) dp[j] = c;
                else if (j >= a && dp[j - a] > 0) dp[j] = dp[j - a] - 1, ret++;
            }
        }
        cout << ret << endl;
    }

    return 0;
}