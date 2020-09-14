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

ll numsl[20], numsr[20];
pair<ll, int> ssum[300000];

bool li_lt(const pair<ll, int>& left, ll right) {
    return left.first < right;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    while (cin >> N, N) {
        int nl = N / 2, nr = N - nl, nss = (1 << nl) - 1;
        for (int i = 0; i < nl; i++) cin >> numsl[i];
        for (int i = 0; i < nr; i++) cin >> numsr[i];
        for (int i = 1; i < 1 << nl; i++) {
            ll tot = 0;
            for (int j = 0; j < nl; j++) {
                if (i >> j & 1) tot += numsl[j];
            }
            ssum[i - 1].first = tot;
            ssum[i - 1].second = __builtin_popcount(i);
        }
        sort(ssum, ssum + nss);
        for (int i = 1; i < nss; i++) {
            if (ssum[i].first == ssum[i - 1].first)
                ssum[i].second = ssum[i - 1].second;
        }
        ll best = LLONG_MAX;
        int best_c = INT_MAX;
        for (int i = 0; i < 1 << nr; i++) {
            ll tot = 0, s;
            for (int j = 0; j < nr; j++) {
                if (i >> j & 1) tot += numsr[j];
            }
            if (i && (s = tot < 0 ? -tot : tot) <= best) {
                best_c = s < best ? __builtin_popcount(i) : min(best_c, __builtin_popcount(i));
                best = s;
            }
            int p = lower_bound(ssum, ssum + nss, -tot, li_lt) - ssum;
            if (p < nss && (s = ssum[p].first + tot, s = s < 0 ? -s : s) <= best) {
                best_c = s < best ? ssum[p].second + __builtin_popcount(i) : min(best_c, ssum[p].second + __builtin_popcount(i));
                best = s;
            }
            if (p && (s = ssum[p - 1].first + tot, s = s < 0 ? -s : s) <= best) {
                best_c = s < best ? ssum[p - 1].second + __builtin_popcount(i): min(best_c, ssum[p - 1].second + __builtin_popcount(i));
                best = s;
            }   
        }
        cout << best << " " << best_c << endl;
    }

    return 0;
}