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

const int mxn = 1000;
int segt[mxn << 1], segt_d[mxn], a[mxn];
char segt_h[mxn << 1];

int get_random() {
    return rand() % 10000 - 5000;
}

void propag_up_addmax(int p) {
    for (; p >> 1; p >>= 1) {
        segt[p>>1] = max(segt[p], segt[p ^ 1]) + segt_d[p>>1];
    }
}

void propag_down_addmax(int p, int N) {
    int h = sizeof(int) * 8 - __builtin_clz(p);
    for (int s = h - 1; s; s--) {
        int q = p >> (s - 1);
        if (segt_d[q>>1] == 0) continue;
        if (q < N) segt_d[q] += segt_d[q>>1], segt_d[q^1] += segt_d[q>>1];
        segt[q] += segt_d[q>>1], segt[q^1] += segt_d[q>>1];
        segt_d[q>>1] = 0;
    }
}

void range_add_range_max() {
    srand(time(0));
    memset(segt_d, 0, sizeof(segt_d));
    int N = 1 + rand() % mxn;
    int Q = 100;

    for (int i = 0; i < N; i++) a[i] = get_random();
    for (int i = 0; i < N; i++) segt[i + N] = a[i];
    for (int i = N - 1; i; i--) segt[i] = max(segt[i<<1], segt[i<<1|1]);

    int I, J, v, L, R, qret_a, qret_segt;
    for (; Q; Q--) {
        I = rand() % N, J = rand() % N, v = get_random();
        L = min(I, J), R = max(I, J);
        // printf("add %d: [%d, %d]\n", v, L, R);
        for (int i = L; i <= R; i++) a[i] += v;
        for (int l = L + N, r = R + N + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                segt[l] += v;
                if (l < N) segt_d[l] += v;
                l++;
            }
            if (r & 1) {
                --r;
                segt[r] += v;
                if (r < N) segt_d[r] += v;
            }
        }
        propag_up_addmax(L + N);
        propag_up_addmax(R + N);

        I = rand() % N, J = rand() % N;
        L = min(I, J), R = max(I, J);
        qret_a = qret_segt = INT_MIN;
        // printf("query: [%d, %d]\n", L, R);
        for (int i = L; i <= R; i++) qret_a = max(qret_a, a[i]);
        propag_down_addmax(L + N, N);
        propag_down_addmax(R + N, N);
        for (int l = L + N, r = R + N + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) qret_segt = max(qret_segt, segt[l++]);
            if (r & 1) qret_segt = max(qret_segt, segt[--r]);
        }
        if (qret_a != qret_segt) printf("diff: %d %d\n", qret_a, qret_segt);
    }
}

void propag_up_addsum(int p) {
    for (; p >> 1; p >>= 1) {
        segt[p>>1] = segt[p] + segt[p^1] + segt_d[p>>1] * (1 << segt_h[p>>1]);
    }
}

void propag_down_addsum(int p, int N) {
    int h = sizeof(int) * 8 - __builtin_clz(p);
    for (int s = h - 1; s; s--) {
        int q = p >> (s - 1);
        if (q < N) segt_d[q] += segt_d[q>>1], segt_d[q^1] += segt_d[q>>1];
        segt[q] += segt_d[q>>1] * (1 << segt_h[q]);
        segt[q^1] += segt_d[q>>1] * (1 << segt_h[q^1]);
        segt_d[q>>1] = 0;
    }
}

void range_add_range_sum() {
    srand(time(0));
    memset(segt_d, 0, sizeof(segt_d));
    int N = rand() % mxn + 1;
    int Q = 100;

    for (int i = 0; i < N; i++) a[i] = get_random();
    for (int i = 0; i < N; i++) segt[N + i] = a[i], segt_h[N + i] = 0;
    for (int i = N - 1; i; i--) {
        segt[i] = segt[i<<1] + segt[i<<1|1];
        segt_h[i] = segt_h[i<<1] + 1;
    }

    int I, J, v, L, R, qret_a, qret_segt;
    for (; Q; Q--) {
        I = rand() % N, J = rand() % N, v = get_random();
        L = min(I, J), R = max(I, J);
        // printf("add %d: [%d, %d]\n", v, L, R);
        for (int i = L; i <= R; i++) a[i] += v;
        for (int l = L + N, r = R + N + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                if (l < N) segt_d[l] += v;
                segt[l] += v * (1 << segt_h[l]);
                l++;
            }
            if (r & 1) {
                --r;
                if (r < N) segt_d[r] += v;
                segt[r] += v * (1 << segt_h[r]);
            }
        }
        propag_up_addsum(L + N);
        propag_up_addsum(R + N);

        qret_a = qret_segt = 0;
        I = rand() % N, J = rand() % N;
        L = min(I, J), R = max(I, J);
        // printf("query: [%d, %d]\n", L, R);
        for (int i = L; i <= R; i++) qret_a += a[i];
        propag_down_addsum(L + N, N);
        propag_down_addsum(R + N, N);
        for (int l = L + N, r = R + N + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) qret_segt += segt[l++];
            if (r & 1) qret_segt += segt[--r];
        }
        if (qret_a != qret_segt) printf("diff: %d %d\n", qret_a, qret_segt);
    }
}

int main() {
    for (int i = 0; i < 10; i++)
        range_add_range_sum();
}