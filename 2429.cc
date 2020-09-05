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
#include <ctime>
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
typedef unsigned long long ull;
const int INT_INF = 0x3f3f3f3f, INT_NINF = 0xc0c0c0c0;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

const int mxnf = 100;
const int witness[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
const int sz_witness = 12;
const ull A_MAX = 1ULL << 32;

int nf;
ull factor[mxnf];
ull rest[mxnf];
ull best;

ull mul(ull a, ull b, ull p) {
    ull ret = 0;
    for (ull base = a; b; b >>= 1) {
        if (b & 1) {
            ret = (ret + base) % p; 
        }
        base = (base + base) % p;
    }
    return ret;
}

bool ptest(ull p) {
    ull d = p - 1;
    while (!(d & 1)) d >>= 1;
    for (int i = 0; i < sz_witness && witness[i] < p; i++) {
        ull a = witness[i], r = 1;
        for (ll dd = d; dd; dd >>= 1, a = mul(a, a, p)) {
            if (dd & 1) r = mul(r, a, p);
        }
        if (r == 1) goto success;
        for (ll dd = d; dd < p - 1; dd <<= 1, r = mul(r, r, p)) {
            if (r == p - 1) goto success;
        }
        return false;
        success:;
    }
    return true;
}

ull __gcd(ull a, ull b) {
    ull tmp;
    while (b) {
        tmp = a; a = b; b = tmp % b;
    }
    return a;
}

ull pollard_rho(ull n) {
    while (!ptest(n)) {
        while (true) {
            ull fast = rand() % 10000, slow = fast, p = 1, c = rand() % 100;
            while (p == 1) {
                slow = (mul(slow, slow, n) + c) % n;
                fast = (mul(fast, fast, n) + c) % n;
                fast = (mul(fast, fast, n) + c) % n;
                p = __gcd(fast < slow ? slow - fast : fast - slow, n);
            }
            if (p < n) {
                return pollard_rho(p);
            }
        }
    }
    return n;
}

ull brent_rho(ull n) {
    while (!ptest(n)) {
        while (true) {
            ull y = rand() % 10000, x = y, p = 1, c = rand() % 100;
            for (ull len = 1; p == 1; len <<= 1) {
                y = x, p = 1;
                for (ull i = 0; i < len && p == 1; i++) {
                    x = (mul(x, x, n) + c) % n;
                    p = __gcd(x < y ? y - x : x - y, n);
                }
                if (1 < p && p < n) return brent_rho(p);
            }
        }
    }
    return n;
}

void dfs(int i, ull cur, ull n) {
    if (cur >= A_MAX || cur * cur > n || cur * rest[i] <= best) return;
    best = max(best, cur);
    if (i == nf) return;
    dfs(i + 1, cur, n);
    dfs(i + 1, cur * factor[i], n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ull gcd, lcm;
    while (cin >> gcd >> lcm) {
        ull N = lcm / gcd, n = N;
        nf = 0;
        for (int i = 0; i < sz_witness; i++) {
            ull p = witness[i];
            if (n % p == 0) {
                ull r = 1;
                for (; n % p == 0; n /= p) r *= p;
                factor[nf++] = r;
            }
        }
        for (; n > 1; nf++) {
            ull p = brent_rho(n);
            ull r = 1;
            for (; n % p == 0; n /= p) r *= p;
            factor[nf] = r;
        }
        rest[nf] = 1;
        for (int i = nf - 1; i >= 0; i--) {
            rest[i] = rest[i + 1] * factor[i];
        }
        best = 1;
        dfs(0, 1, N);
        cout << best * gcd << " " << N / best * gcd << endl;
    }

    return 0;
}