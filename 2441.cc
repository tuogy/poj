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

const int mxn = 20, mxm = 20;
int dp[1 << mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, P, x;
    cin >> N >> M;
    vector<vector<int> > barn(M + 1);
    for (int i = 0; i < N; i++) {
        cin >> P;
        for (int j = 0; j < P; j++) {
            cin >> x;
            barn[x].push_back(i);
        }
    }
    memset(dp, 0, sizeof(int) << N);
    dp[0] = 1;
    for (int m = 1; m <= M; m++) {
        for (int s = (1 << N) - 1; s >= 0; s--) {
            if (dp[s] == 0) continue;
            for (int j = 0; j < barn[m].size(); j++) {
                int k = barn[m][j];
                if (!(s >> k & 1)) dp[s | 1 << k] += dp[s];
            }
        }
    }

    printf("%d\n", dp[(1 << N) - 1]);

    return 0;
}
