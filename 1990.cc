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

const int mxn = 20000;
ii vx[mxn], xv[mxn];
ll bit_count[mxn + 1];
ll bit_csum[mxn + 1];

bool ii_lt(const ii& left, int right) {
    return left.first < right;
}

ll prefix(ll* bit, int i) {
    ll tot = 0;
    for (int k = i + 1; k; k -= k & -k) tot += bit[k];
    return tot;
}

void insert(ll* bit, ll val, int i) {
    for (int k = i + 1; k <= mxn; k += k & -k) bit[k] += val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d%d", &vx[i].first, &vx[i].second);
    memset(bit_count, 0, (N + 1) * sizeof(ll));
    memset(bit_csum, 0, (N + 1) * sizeof(ll));
    for (int i = 0; i < N; i++) {
        xv[i].first = vx[i].second;
        xv[i].second = vx[i].first;
    }
    sort(vx, vx + N);
    sort(xv, xv + N);
    ll ret = 0, tot_v = 0;
    for (int i = 0; i < N; i++) {
        int x = xv[i].first, v = xv[i].second;
        int idx_vx = lower_bound(vx, vx + N, v, ii_lt) - vx;
        ll count_left = prefix(bit_count, idx_vx);
        ll sum_right = tot_v - prefix(bit_csum, idx_vx);
        ret += x * (sum_right + count_left * v);
        insert(bit_count, 1, idx_vx);
        insert(bit_csum, v, idx_vx);
        tot_v += v;
    }
    memset(bit_count, 0, (N + 1) * sizeof(ll));
    memset(bit_csum, 0, (N + 1) * sizeof(ll));
    tot_v = 0;
    for (int i = N - 1; i >= 0; i--) {
        int x = xv[i].first, v = xv[i].second;
        int idx_vx = lower_bound(vx, vx + N, v, ii_lt) - vx;
        ll count_left = prefix(bit_count, idx_vx);
        ll sum_right = tot_v - prefix(bit_csum, idx_vx);
        ret -= x * (sum_right + count_left * v);
        insert(bit_count, 1, idx_vx);
        insert(bit_csum, v, idx_vx);
        tot_v += v;
    }
    printf("%lld\n", ret);

    return 0;
}