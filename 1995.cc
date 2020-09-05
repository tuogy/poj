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

const int mxn = 45000;
int M, H;
ll A[mxn], B[mxn];

void solve() {
    int ret = 0;
    for (int i = 0; i < H; i++) {
        int a = A[i] % M;
        ll cur = 1;
        for (ll b = B[i], aa = a; b; b >>= 1, aa = aa * aa % M) {
            if (b & 1) cur = cur * aa % M;
        }
        ret = (ret + cur) % M;
    }
    cout << ret << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    for (scanf("%d", &T); T; T--) {
        scanf("%d%d", &M, &H);
        for (int i = 0; i < H; i++) scanf("%lld%lld", A + i, B + i);
        solve();
    }

    return 0;
}