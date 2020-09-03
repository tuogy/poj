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

struct blk {
    int h, a, c;
};

bool blk_lt(const blk& a, const blk& b) {
    return a.a < b.a;
}

const int mxh = 40001;
blk b[400];
int dp[mxh];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int K; cin >> K;
    for (int i = 0; i < K; i++) cin >> b[i].h >> b[i].a >> b[i].c;
    sort(b, b + K, blk_lt);
    memset(dp, -1, sizeof(dp)); dp[0] = 0;
    for (int k = 0; k < K; k++) {
        for (int h = 0; h <= b[k].a; h++) {
            if (dp[h] >= 0) dp[h] = b[k].c;
            else if (h >= b[k].h && dp[h - b[k].h] > 0) dp[h] = dp[h - b[k].h] - 1;
        }
    }
    int ret = b[K - 1].a;
    while (dp[ret] < 0) ret--;
    cout << ret << endl;

    return 0;
}