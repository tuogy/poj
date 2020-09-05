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

int frac[9], pow10[10];

ll __gcd(ll a, ll b) {
    ll tmp;
    while (b) {
        tmp = a; a = b; b = tmp % b;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 0, pow = 1; i < 10; i++, pow *= 10) pow10[i] = pow;
    char x;
    while (true) {
        cin >> x;
        int n = 0, r = 0;
        if (cin >> x) {
            while (true) {
                cin >> x;
                if (x == '.') {
                    cin >> x >> x; 
                    break;
                }
                else {
                    frac[n++] = x - '0', r = r * 10 + x - '0';
                }
            }
            ll best_top = 0, best_down = LLONG_MAX;
            for (int dk = 0, dr = n, k = 0; dk < n; dk++, dr--) {
                ll top = k * (pow10[dr] - 1) + r;
                ll down = pow10[dk] * (pow10[dr] - 1);
                ll gcd = __gcd(top, down);
                down /= gcd, top /= gcd;
                if (down < best_down) {
                    best_down = down, best_top = top;
                }
                k = k * 10 + frac[dk];
                r %= pow10[dr - 1];
            }
            cout << best_top << '/' << best_down << endl;
        }
        else {
            break;
        }
    }

    return 0;
}