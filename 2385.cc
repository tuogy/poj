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

const int mxT = 1001;
int dp[31][2][mxT];
int apple[mxT];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T, W;
    cin >> T >> W;
    for (int i = 0; i < T; i++) cin >> apple[i];

    for (int w = 0; w <= W; w++) {
        for (int tree = 0; tree < 2; tree++) {
            for (int t = T - 1; t >= 0; t--) {
                dp[w][tree][t] = max(
                    (apple[t] == tree + 1) + dp[w][tree][t + 1],
                    w ? dp[w - 1][tree ^ 1][t] : 0
                );
            }
        }
    }
    cout << dp[W][0][0] << endl;
    

    return 0;
}