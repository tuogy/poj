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

const int mxn = 50000;
int N, segt_min[mxn << 1], segt_max[mxn << 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int Q, h, l, r;
    scanf("%d%d", &N, &Q);
    for (int i = 0; i < N; i++) {
        scanf("%d", &h);
        segt_max[N + i] = segt_min[N + i] = h;
    }
    for (int i = N - 1; i; i--) {
        segt_max[i] = max(segt_max[i << 1], segt_max[i << 1 | 1]);
        segt_min[i] = min(segt_min[i << 1], segt_min[i << 1 | 1]);
    }
    for (; Q; Q--) {
        scanf("%d%d", &l, &r); l--;
        int cur_min = INT_MAX, cur_max = 0;
        for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) cur_min = min(cur_min, segt_min[l]), cur_max = max(cur_max, segt_max[l]), l++;
            if (r & 1) --r, cur_min = min(cur_min, segt_min[r]), cur_max = max(cur_max, segt_max[r]);
        }
        printf("%d\n", cur_max - cur_min);
    }
    return 0;
}