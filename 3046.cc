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

const int mod = 1000000;
int N[1000];
int dp[2][100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T, A, S, B, t;
    cin >> T >> A >> S >> B;
    memset(N, 0, T * sizeof(int));
    for (int i = 0; i < A; i++) {
        cin >> t; N[t - 1]++;
    }
    int *prev = dp[0], *cur = dp[1];
    memset(cur, 0, (B + 1) * sizeof(int));
    cur[0] = 1;
    for (int t = 0; t < T; t++) {
        swap(cur, prev);
        cur[0] = 1;
        for (int s = 1; s <= B; s++) {
            cur[s] = prev[s] + cur[s - 1] + mod - (s - 1 >= N[t] ? prev[s - 1 - N[t]] : 0);
            cur[s] %= mod;
        }
    }
    int ret = 0;
    for (int s = S; s <= B; s++) ret = (ret + cur[s]) % mod;
    cout << ret << endl;

    return 0;
}