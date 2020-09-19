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

const int mxn = 100;
int m, n, k;

int lp[mxn], ppow[mxn], ptmp[mxn];
ll lc[mxn], cpow[mxn], ctmp[mxn];

void smatmul(int* p1, ll* c1, int* p2, ll* c2, int* p, ll* c) {
    memcpy(ptmp, p2, n * sizeof(int));
    memcpy(ctmp, c2, n * sizeof(ll));
    for (int i = 0; i < n; i++) {
        c[i] = c1[i] + (p1[i] >= 0 ? ctmp[p1[i]] : 0);
        p[i] = p1[i] >= 0 ? ptmp[p1[i]] : -1;
    }
}

void smatpow(int* pbase, ll* cbase, int m) {
    for (int i = 0; i < n; i++) ppow[i] = i, cpow[i] = 0;
    for (; m; m >>= 1) {
        if (m & 1) smatmul(ppow, cpow, pbase, cbase, ppow, cpow);
        smatmul(pbase, cbase, pbase, cbase, pbase, cbase);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    char x; int i, j;
    while (scanf("%d%d%d", &n, &m, &k), n || m || k) {
        for (int i = 0; i < n; i++) lp[i] = i, lc[i] = 0;
        for (int kk = 0; kk < k; kk++) {
            scanf(" %c%d", &x, &i); i--;
            if (x == 'g') {
                lc[i]++;
            }
            else if (x == 'e') {
                lp[i] = -1, lc[i] = 0;
            }
            else {
                scanf("%d", &j); j--;
                swap(lp[i], lp[j]), swap(lc[i], lc[j]);
            }
        }
        smatpow(lp, lc, m);
        for (int i = 0; i < n; i++) cout << cpow[i] << (i == n - 1 ? '\n' : ' ');
    }


    return 0;
}
