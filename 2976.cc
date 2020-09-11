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

const int mxn = 1000;
int n, k;
ll a[mxn], b[mxn];
double d[mxn];

bool feasible(double x) {
    for (int i = 0; i < n; i++) d[i] = a[i] - x * b[i];
    sort(d, d + n);
    double tot = 0;
    for (int i = n - 1; i >= k; --i) tot += d[i];
    return tot >= 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (true) {
        scanf("%d%d", &n, &k);
        if (n == 0 && k == 0) break;
        for (int i = 0; i < n; ++i) scanf("%lld", a + i);
        for (int i = 0; i < n; ++i) scanf("%lld", b + i);
        double l = 0., r = 1.01;
        for (int j = 0; j < 20; j++) {
            double c = (l + r) / 2.;
            if (feasible(c)) l = c;
            else r = c;
        }
        printf("%d\n", (int)(l * 100. + 0.5));
    }

    return 0;
}