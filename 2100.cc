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


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll tot;
    vector<pair<ll, ll> > res;
    scanf("%lld", &tot);
    for (ll l = 1, r = 1, sum = 0; ; sum -= l * l, l++) {
        while (r * r <= tot && sum < tot) sum += r * r, r++;
        if (sum < tot) break;
        else if (sum == tot) res.push_back(make_pair(l, r - 1));
    }

    printf("%d\n", (int)res.size());
    for (int i = 0; i < res.size(); ++i) {
        printf("%lld", res[i].second - res[i].first + 1);
        for (int j = res[i].first; j <= res[i].second; ++j) printf(" %d", j);
        printf("\n");
    }

    return 0;
}