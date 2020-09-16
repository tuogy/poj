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

const int mxn = 500000;
char names[mxn + 1][11];
int A[mxn + 1], pmin[mxn + 1], nf[mxn + 1], nf0[mxn + 1], primes[mxn];

int prefix(int* bit, int i) {
    int tot = 0;
    for (; i; i -= i & -i) tot += bit[i];
    return tot;
}

void add(int* bit, int i, int val, int N) {
    for (; i <= N; i += i & -i) bit[i] += val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(pmin, 0, sizeof(pmin));
    pmin[1] = 1, nf[1] = 1, nf0[1] = 0;
    int nprimes = 0;
    for (int p = 2; p <= mxn; p++) {
        if (pmin[p] == 0) {
            pmin[p] = p; primes[nprimes++] = p;
        }
        for (int i = 0; i < nprimes && primes[i] <= pmin[p] && p * primes[i] <= mxn; i++) pmin[p * primes[i]] = primes[i];
    }
    for (int p = 2; p <= mxn; p++) {
        if (pmin[p] == p) nf[p] = 1, nf0[p] = 1;
        else {
            int q = p / pmin[p];
            if (pmin[q] == pmin[p]) nf[p] = nf[q], nf0[p] = nf0[q] + 1;
            else nf[p] = nf[q] * (1 + nf0[q]), nf0[p] = 1;
        }
    }
    int* F = nf, *bit = pmin;
    for (int p = 1; p <= mxn; p++) F[p] = nf[p] * (nf0[p] + 1);
    
    int N, K;
    while (scanf("%d%d", &N, &K) == 2) {
        for (int i = 1; i <= N; i++) {
            scanf(" %s%d", names[i], A + i);
        }
        bit[0] = 0;
        for (int i = 1; i <= N; i++) bit[i] = 1;
        for (int i = N; i; i--) {
            for (int j = i + (i & -i); j <= N; j += j & -j) bit[j] += bit[i];
        }
        int best = 0, bestp = 0, cur;
        for (int i = 0, p = K; i < N; i++) {
            if (F[i + 1] > best) {
                best = F[i + 1], bestp = p;
            }
            if (i == N - 1) break;
            int d = (abs(A[p]) - 1) % (N - i - 1) + 1, l = 0, r = N - 1;
            while (l < r - 1) {
                int c = l + (r - l) / 2;
                int pp = A[p] > 0 ? (p - 1 + c) % N + 1 : (p - 1 - c + N) % N + 1;
                if (A[p] > 0) {
                    cur = prefix(bit, pp) - prefix(bit, p);
                    if (pp < p) cur += N - i;
                }
                else {
                    cur = prefix(bit, p - 1) - prefix(bit, pp - 1);
                    if (pp > p) cur += N - i;
                }
                if (cur >= d) r = c;
                else l = c;
            }
            add(bit, p, -1, N);
            p = A[p] > 0 ? (p - 1 + r) % N + 1 : (p - 1 - r + N) % N + 1;
        }
        printf("%s %d\n", names[bestp], best);
    }

    return 0;
}