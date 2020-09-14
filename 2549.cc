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

int s[1000];
ii diff[1000000];

bool ii_lb_lt(const ii& left, int right) {
    return left.first < right;
}
bool ii_ub_lt(int left, const ii& right) {
    return left < right.first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while (scanf("%d", &n), n) {
        for (int i = 0; i < n; i++) scanf("%d", s + i);
        int ndiff = 0, best_d = INT_MIN;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                diff[ndiff++] = make_pair(s[i] - s[j], s[i]);
            }
        }
        sort(diff, diff + ndiff);
        ndiff = unique(diff, diff + ndiff) - diff;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                int a = s[i], b = s[j];
                int l = lower_bound(diff, diff + ndiff, a + b, ii_lb_lt) - diff;
                int r = upper_bound(diff, diff + ndiff, a + b, ii_ub_lt) - diff;
                for (int k = r - 1; k >= l; k--) {
                    int d = diff[k].second, c = diff[k].second - diff[k].first;
                    if (a == c || a == d || b == c || b == d) continue;
                    best_d = max(best_d, d);
                    break;
                }
            }
        }
        if (best_d == INT_MIN) printf("no solution\n");
        else printf("%d\n", best_d);
    }


    return 0;
}