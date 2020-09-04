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

const int mxn = 2001;

struct road {
    int u, v, w;
};
static bool road_lt(const road&a, const road& b) { return a.w < b.w; }

road r[10000];
int uf_pa[mxn], uf_rank[mxn];

int uf_find(int i) {
    if (uf_pa[i] != i) uf_pa[i] = uf_find(uf_pa[i]);
    return uf_pa[i];
}

void uf_union(int i, int j) {
    int pi = uf_find(i), pj = uf_find(j);
    if (pi != pj) {
        if (uf_rank[pi] < uf_rank[pj]) swap(pi, pj);
        if (uf_rank[pi] == uf_rank[pj]) uf_rank[pi]++;
        uf_pa[pj] = pi;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> r[i].u >> r[i].v >> r[i].w;
    }
    sort(r, r + M, road_lt);
    for (int i = 1; i <= N; i++) uf_pa[i] = i, uf_rank[i] = 0;

    int best = 0;
    for (int i = 0; i < M; i++) {
        if (uf_find(r[i].u) != uf_find(r[i].v)) {
            best = r[i].w;
            uf_union(r[i].u, r[i].v);
        }
    }
    cout << best << endl;

    return 0;
}