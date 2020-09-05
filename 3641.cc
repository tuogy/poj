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

void solve(int p, int a) {
    ll r = 1, powa = a;
    for (int pp = p; pp; pp >>= 1, powa = powa * powa % p) {
        if (pp & 1) r = r * powa % p;
    }
    if (r == a) cout << "yes" << endl;
    else cout << "no" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int p, a;
    while (cin >> p >> a, p || a) {
        bool foundf = false;
        for (int q = 2; q * q <= p && !foundf; q++) {
            if (p % q == 0) foundf = true;
        }
        if (foundf)
            solve(p, a);
        else cout << "no" << endl;
    }

    return 0;
}