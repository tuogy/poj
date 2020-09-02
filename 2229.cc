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
const int mod = 1e9, mxn = 1000001;

int dp[mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    dp[0] = 1;
    for (int base = 1; base <= N; base <<= 1) {
        for (int i = base; i <= N; i++) {
            if (base == 1) dp[i] = 1;
            else {
                dp[i] += dp[i - base];
                dp[i] %= mod;
            }
        }
    }
    cout << dp[N] << endl;

    return 0;
}