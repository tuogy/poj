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

char tag[2000];
int cost[26];
int dp[3][2000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, inc, dec;
    cin >> N >> M;
    for (int i = 0; i < M; i++) cin >> tag[i];
    char x;
    for (int i = 0; i < N; i++) {
        cin >> x >> inc >> dec;
        cost[x - 'a'] = min(inc, dec);
    }
    int* prev2 = dp[0], *prev = dp[1], *cur = dp[2], *tmp;
    memset(prev, 0, M * sizeof(int));
    memset(cur, 0, M * sizeof(int));

    for (int l = 2; l <= M; l++) {
        tmp = prev2, prev2 = prev, prev = cur, cur = tmp;
        for (int i = 0, j; i + l - 1 < M; i++) {
            j = i + l - 1;
            if (tag[i] == tag[j]) cur[i] = prev2[i + 1];
            else cur[i] = INT_MAX;
            int best = min(cost[tag[j] - 'a'] + prev[i], cost[tag[i] - 'a'] + prev[i + 1]);
            cur[i] = min(cur[i], best);
        }
    }
    cout << cur[0] << endl;

    return 0;
}