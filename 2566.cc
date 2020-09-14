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

const int mxn = 100000, mxk = 1000;
int nums[mxn], ks[mxn];
int best_diff[mxk], best_v[mxk], best_l[mxk], best_r[mxk];

void update(map<int, int>::iterator it, int sum, int i, int j) {
    int diff = abs(abs(sum - it->first) - ks[j]);
    if (diff < best_diff[j])
        best_diff[j] = diff, best_v[j] = abs(sum - it->first), best_l[j] = it->second + 1, best_r[j] = i + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    while (scanf("%d%d", &n, &k), n || k) {
        for (int i = 0; i < n; ++i) scanf("%d", nums + i);
        for (int i = 0; i < k; ++i) scanf("%d", ks + i), best_diff[i] = INT_MAX;
        map<int, int> pfx; map<int, int>::iterator it;
        pfx[0] = 0;
        for (int i = 0, sum = 0; i < n; ++i) {
            sum += nums[i];
            for (int j = 0; j < k; j++) {
                it = pfx.lower_bound(sum - ks[j]);
                if (it != pfx.end()) update(it, sum, i, j);
                if (it != pfx.begin()) update(--it, sum, i, j);
                it = pfx.lower_bound(sum + ks[j]);
                if (it != pfx.end()) update(it, sum, i, j);
                if (it != pfx.begin()) update(--it, sum, i, j);
            }
            pfx[sum] = i + 1;
        }
        for (int j = 0; j < k; ++j) printf("%d %d %d\n", best_v[j], best_l[j], best_r[j]);
    }

    return 0;
}