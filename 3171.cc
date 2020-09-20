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

const int mxe = 90000;
vector<ii> TS[mxe];
int rmq[mxe << 1], N, M, E;

void update(int i, int val) {
    i += E + 1;
    if (rmq[i] > val) {
        rmq[i] = val;
        for (; i>>1; i >>= 1) {
            rmq[i>>1] = min(rmq[i], rmq[i^1]);
        }
    }
}

int query(int L, int R) {  // min[L, R]
    int tot = INT_INF;
    for (int l = L + E + 1, r = R + E + 2; l < r; l >>= 1, r >>= 1) {
        if (l & 1) tot = min(tot, rmq[l++]);
        if (r & 1) tot = min(tot, rmq[--r]);
    }
    return tot;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t1, t2, s;
    scanf("%d%d%d", &N, &M, &E);
    M--; E -= M;
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d", &t1, &t2, &s);
        t1 -= M, t2 -= M;
        TS[t2].push_back(make_pair(t1, s));
    }
    memset(rmq, 0x3f, sizeof(int) * (E + 1) << 1);
    update(0, 0);
    for (t2 = 1; t2 <= E; t2++) {
        for (int i = 0; i < TS[t2].size(); i++) {
            t1 = TS[t2][i].first, s = TS[t2][i].second;
            update(t2, s + query(t1 - 1, t2 - 1));
        }
    }
    int ret = rmq[E + E + 1];
    if (ret >= INT_INF) ret = -1;
    printf("%d\n", ret);

    return 0;
}
