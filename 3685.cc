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

const ll K = 100000;
ll N, M;

bool feasible(ll x) {
    ll tot = 0;
    for (ll j = 1; j <= N && tot < M; j++) {
        ll rhs = x + K * j - j * j;
        if (N * N + (K + j) * N <= rhs) tot += N;
        else if (1 + K + j <= rhs) {
            ll l = 1, r = N;
            while (l < r - 1) {
                ll c = (l + r) / 2;
                if (c * c + (K + j) * c <= rhs) l = c;
                else r = c;
            }
            tot += l;
        }
    }
    return tot >= M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T; cin >> T;
    for (; T; T--) {
        cin >> N >> M;
        ll l = N * -K - 1, r = N * (K + N) + 1;
        while (l < r - 1) {
            ll c = (l + r) / 2;
            if (feasible(c)) r = c;
            else l = c;
        } 
        cout << r << endl;
    }

    return 0;
}