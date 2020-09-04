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
#define cin fin
std::ifstream cin("__sample.in");
#endif

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
const int INT_INF = 0x3f3f3f3f, INT_NINF = 0xc0c0c0c0;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

const int mxn = 1001;
ii pos[mxn];
bool status[mxn];
int uf_pa[mxn], uf_rank[mxn];

int uf_find(int i) {
    if (uf_pa[i] != i) uf_pa[i] = uf_find(uf_pa[i]);
    return uf_pa[i];
}

void uf_union(int i, int j) {
    int pi = uf_find(i), pj = uf_find(j);
    if (pi != pj) {
        if (uf_rank[pi] < uf_rank[pj]) swap(pi, pj);
        else if (uf_rank[pi] == uf_rank[pj]) uf_rank[pi]++;
        uf_pa[pj] = pi;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, d; cin >> N >> d;
    for (int i = 0; i < N; i++) cin >> pos[i].first >> pos[i].second;
    vector<vector<int> > adj(N);
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int dx = abs(pos[i].first - pos[j].first);
            int dy = abs(pos[i].second - pos[j].second);
            if (dx * dx + dy * dy <= d * d) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    for (int i = 0; i < N; i++) uf_pa[i] = i, status[i] = false;

    char op; int p, q;
    while (cin >> op) {
        if (op == 'O') {
            cin >> p; p--;
            if (status[p]) continue;
            status[p] = true;
            for (int k = 0; k < adj[p].size(); k++) {
                if (status[adj[p][k]]) uf_union(p, adj[p][k]);
            }
        }
        else {
            cin >> p >> q; p--, q--;
            if (uf_find(p) == uf_find(q)) cout << "SUCCESS" << endl;
            else cout << "FAIL" << endl;
        }
    }


    return 0;
}