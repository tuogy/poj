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

const int mxn = 50010;
int rmq[mxn << 1];

int query(int l, int r) {
    int q = INT_INF;
    for (l += mxn, r += mxn + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) q = min(q, rmq[l++]);
        if (r & 1) q = min(q, rmq[--r]);
    }
    return q;
}

void update(int p, int val) {
    if (rmq[p + mxn] > val) {
        rmq[p + mxn] = val;
        for (p += mxn; p>>1; p >>= 1) {
            rmq[p>>1] = min(rmq[p], rmq[p^1]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, a, b, c; 
    scanf("%d", &n);
    vector<ii> adj[mxn];
    memset(rmq, 0, sizeof(rmq));
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &a, &b, &c);
        adj[b + 1].push_back(make_pair(a, c));
    }
    int vj = 0;
    for (int pj = mxn - 1; pj >= 0; pj--) {
        vj = min(vj, pj + query(0, pj));
        update(pj, vj - pj);
        for (int i = 0; i < adj[pj].size(); i++) {
            int pi = adj[pj][i].first, k = adj[pj][i].second;
            update(pi, vj - k - pi);
        }
    }
    printf("%d\n", -vj);

    return 0;
}
