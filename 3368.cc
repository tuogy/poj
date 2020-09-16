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

const int mxn = 100001;
int segt_v[mxn << 2] ,segt_f[mxn << 2];
int freq[mxn << 1 | 1], minv, maxv, maxf;

void update(int i) {
    // cout << segt_v[i] << ": " << freq[segt_v[i]] << "| " << minv << " " << maxv << endl;
    int v = segt_v[i];
    if (v > minv && v < maxv) maxf = max(maxf, freq[v + mxn]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, N, q, L, R, l, r, a, d;
    while (scanf("%d", &n), n) {
        scanf("%d", &q);
        if (n == (n & -n)) N = n;
        else N = 1 << (32 - __builtin_clz(n));
        // TODO: use segment forest

        memset(freq, 0, sizeof(freq));
        for (int i = 0; i < n; i++) {
            scanf("%d", &a);
            segt_v[N + i] = a;
            segt_f[N + i] = 1;
            freq[a + mxn]++;
        }
        for (int i = n; i < N; i++) segt_v[N + i] = mxn + 1, segt_f[N + i] = 1;

        for (int i = N - 1; i; i--) {
            if (segt_v[i<<1] == segt_v[i<<1|1]) {
                segt_v[i] = segt_v[i<<1], segt_f[i] = segt_f[i<<1] + segt_f[i<<1|1];
            }
            else {
                int f, v;
                if (segt_f[i<<1] > segt_f[i<<1|1]) f = segt_f[i<<1], v = segt_v[i<<1];
                else f = segt_f[i<<1|1], v = segt_v[i<<1|1];
                d = __builtin_clz(i) - __builtin_clz(N);
                int lr = ((i<<1|1) << (d - 1)) - 1, rl = lr + 1;
                if (segt_v[lr] == segt_v[rl]) {
                    int ll = i << d, rr = (i + 1) << d;
                    int c_mid = upper_bound(segt_v + ll, segt_v + rr, segt_v[lr]) - lower_bound(segt_v + ll, segt_v + rr, segt_v[lr]);
                    if (c_mid > f) {
                        f = c_mid, v = segt_v[lr];
                    }
                }
                segt_f[i] = f, segt_v[i] = v;
            }
        }

        for (; q; q--) {
            scanf("%d%d", &L, &R); L--;
            minv = segt_v[N + L], maxv = segt_v[N + R - 1];
            maxf = 0, d = 0;
            for (int l = N + L, r = N + R; l < r; l >>= 1, r >>= 1, d++) {
                if (l & 1) {
                    update(l);
                    if (d > 0) {
                        update(l << d);
                        update(((l + 1) << d) - 1);
                    }
                    l++;
                }
                if (r & 1) {
                    r--;
                    update(r);
                    if (d > 0) {
                        update(r << d);
                        update(((r + 1) << d) - 1);
                    }
                }
            }
            maxf = max(maxf, (int)(upper_bound(segt_v + N + L, segt_v + N + R, minv) - (segt_v + N + L)));
            maxf = max(maxf, (int)(segt_v + N + R - lower_bound(segt_v + N + L, segt_v + N + R, maxv)));
            printf("%d\n", maxf);
        }
    }

    return 0;
}