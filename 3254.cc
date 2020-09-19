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

const int mxn = 12, mod = 100000000;
int fertile[mxn], plan[1 << mxn], dp[2][1 << mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int M, N, x;
    cin >> M >> N;
    for (int i = 0; i < M; i++) {
        int f = 0;
        for (int j = 0; j < N; j++) {
            cin >> x; f = f << 1 | x;
        }
        fertile[i] = f;
    }

    int nplan = 0;
    for (x = 0; x < 1 << N; x++) {
        if ((x & x >> 1) == 0) plan[nplan++] = x;
    }
    
    int *prev = dp[0], *cur = dp[1];
    for (int i = 0; i < nplan; i++) cur[plan[i]] = 1;
    for (int m = M - 1; m >= 0; m--) {
        swap(prev, cur);
        for (int i = 0; i < nplan; i++) cur[plan[i]] = 0;
        int f = fertile[m];
        for (int i = 0; i < nplan; i++) {
            int pi = plan[i], inc = prev[pi];
            if ((pi | f) != f) continue;
            for (int j = 0; j < nplan; j++) {
                int pj = plan[j];
                if ((pi & pj) == 0) cur[pj] += inc, cur[pj] %= mod;
            }
        }
    }
    cout << cur[0] << endl;

    return 0;
}
