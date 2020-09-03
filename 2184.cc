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
const int INT_INF = 0x3f3f3f3f, INT_NINF = 0xc0c0c0c0;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

const int mxn = 100, offset = 100000, mxv = 100000;
int dp[mxv << 1 | 1];
int S[mxn], F[mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    for (int i = 0; i < N; i++) cin >> S[i] >> F[i];
    memset(dp, 0xc0, sizeof(dp)); dp[offset] = 0;
    for (int i = 0; i < N; i++) {
        int si = S[i], fi = F[i];
        if (si >= 0) {
            for (int s = mxv; s - si >= -mxv; s--) {
                dp[s + offset] = max(dp[s + offset], dp[s - si + offset] + fi);
            }
        }
        else {
            for (int s = -mxv; s - si <= mxv; s++) {
                dp[s + offset] = max(dp[s + offset], dp[s - si + offset] + fi);
            }
        }
    }
    int ret = 0;
    for (int s = 0; s <= mxv; s++) {
        if (dp[s + offset] >= 0) ret = max(ret, s + dp[s + offset]);
    }
    cout << ret << endl;

    return 0;
}