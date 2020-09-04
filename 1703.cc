#include <cstdio>
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

const int mxn = 100000, dragon = 0, snake = 1;
int uf_pa[mxn << 1], uf_rank[mxn << 1];

int uf_find(int i) {
    if (uf_pa[i] != uf_pa[uf_pa[i]]) uf_pa[i] = uf_find(uf_pa[i]);
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
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T; scanf("%d", &T); getchar();
    for (; T; T--) {
        int N, M; scanf("%d %d", &N, &M); getchar();
        for (int i = 0; i < (N << 1); i++) uf_pa[i] = i;
        char op; int a, b;
        for (int i = 0; i < M; i++) {
           scanf("%c %d %d", &op, &a, &b); getchar();
             a--, b--;
            if (op == 'D') {
                uf_union(a << 1 | 1, b << 1);
                uf_union(a << 1, b << 1 | 1);
            }
            else {
                if (uf_find(a << 1) == uf_find(b << 1)) cout << "In the same gang." << endl;
                else if (uf_find(a << 1) == uf_find(b << 1 | 1)) cout << "In different gangs." << endl;
                else cout << "Not sure yet." << endl;
            }
        }
    }

    return 0;
}