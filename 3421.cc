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

ll factorial[21];
int nfactors[10];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    factorial[0] = 1;
    for (int i = 1; i <= 20; i++) factorial[i] = factorial[i - 1] * i;
    int x;
    while (cin >> x) {
        int n = 0;
        memset(nfactors, 0, sizeof(nfactors));
        for (int p = 2; p * p <= x; p++) {
            if (x % p == 0) {
                for (; x % p == 0; x /= p) nfactors[n]++;
                n++;
            }
        }
        if (x > 1) nfactors[n++] = 1;
        // for (int i = 0; i < n; i++) cout << nfactors[i] << ' ';
        ll down = 1, tot = 0;
        for (int i = 0; i < n; i++) {
            down *= factorial[nfactors[i]]; tot += nfactors[i];
        }
        cout << tot << " " << factorial[tot] / down << endl;
    }

    return 0;
}