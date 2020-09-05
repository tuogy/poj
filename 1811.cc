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
const int witness[] = {2, 3, 5, 7, 11, 13};
const int sz_witness = sizeof(witness) / sizeof(int);

ll factor[50];

ll __gcd(ll a, ll b) {
    ll tmp;
    while (b) {
        tmp = a; a = b; b = tmp % b;
    }
    return a;
}

ll mul(ll a, ll b, ll c, ll p) {
    for (; b; b >>= 1, a <<= 1, a %= p) {
        if (b & 1) c += a, c %= p;
    }
    return c;
}

bool ptest(ll p) {
    ll d = p - 1;
    while (!(d & 1)) d >>= 1;
    for (int i = 0; i < sz_witness && witness[i] < p; i++) {
        ll a = witness[i], r = 1;
        for (ll dd = d; dd; dd >>= 1, a = mul(a, a, 0, p)) {
            if (dd & 1) r = mul(r, a, 0, p);
        }
        if (r == 1) goto success;
        for (; d < p - 1 && r != 1; d <<= 1) {
            if (r == p - 1) goto success;
            r = mul(r, r, 0, p);
        }
        return false;
        success:;
    }
    return true;
}

ll brent_rho(ll n) {
    if (!ptest(n)) {
        for (ll x, y, c, p, len = 1; ;) {
            x = y = rand(), c = rand(), p = 1;
            for (; p == 1; len <<= 1, y = x) {
                for (ll i = 0; i < len && p == 1; i++) {
                    x = mul(x, x, c, n);
                    p = __gcd(x < y ? y - x : x - y, n);
                }
                if (1 < p && p < n) return brent_rho(p);
            }
        }
    }
    return n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    ll n;
    for (cin >> T; T; T--) {
        cin >> n;

        if (ptest(n)) cout << "Prime" << endl;
        else {
            int pp = INT_MAX;
            for (int i = 0; i < sz_witness && pp == INT_MAX; i++) {
                if (n % witness[i] == 0) {
                    pp = witness[i];
                    for (; n % pp == 0; n /= pp); 
                }
            }
            if (pp < INT_MAX) {
                cout << pp << endl; continue;
            }

            int nf = 0;
            while (n > 1) {
                ll p = brent_rho(n);
                factor[nf++] = p;
                for (; n % p == 0; n /= p);
            }
            cout << *min_element(factor, factor + nf) << endl;
        }
    }

    return 0;
}