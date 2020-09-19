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

const int nd = 4, ns = 1 << nd;
int M;
ll A[ns][ns], A1[ns][ns], Apow[ns][ns], tmp[ns][ns];

void matmul(ll left[ns][ns], ll right[ns][ns], ll prod[ns][ns]) {
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < ns; i++) {
        for (int j = 0; j < ns; j++) {
            for (int k = 0; k < ns; k++) {
                tmp[i][j] += left[i][k] * right[k][j];
                tmp[i][j] %= M;
            }
        }
    }
    memcpy(prod, tmp, sizeof(tmp));
}

void matpow(ll base[ns][ns], int N, ll ret[ns][ns]) {
    memset(ret, 0, sizeof(ll) * ns * ns);
    for (int i = 0; i < ns; i++) ret[i][i] = 1;
    for (; N; N >>= 1) {
        if (N & 1) matmul(ret, base, ret);
        matmul(base, base, base);
    }
}

void dfs(int cur, int tgt, int prev) {
    if (cur == tgt) {
        A[tgt][prev]++;
        return;
    }
    for (int i = 0; i < nd; i++) {
        if (tgt >> i & 1 && !(cur >> i & 1)) {
            dfs(cur | 1 << i, tgt, prev ^ 1 << i);
            if (i < nd - 1 && tgt >> (i + 1) & 1 && !(cur >> (i + 1) & 1)) {
                dfs(cur | 3 << i, tgt, prev);
            }
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(A, 0, sizeof(A));
    for (int tgt = 0; tgt < ns; tgt++) dfs(0, tgt, (1 << nd) - 1);

    int N;
    while (cin >> N >> M, N || M) {
        memcpy(A1, A, sizeof(A));
        matpow(A1, N, Apow);
        cout << Apow[ns - 1][ns - 1] << endl;
    }

    return 0;
}
