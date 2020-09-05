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

const int mxn = 10000, pow10[] = {1, 10, 100, 1000}, sign[] = {-1, 1};
int digits[4];
bool isprime[mxn];
bool vis[mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(isprime, 0xff, sizeof(isprime));
    for (int p = 2; p < mxn; p++) {
        if (!isprime[p]) continue;
        else {
            for (int j = p * p; j < mxn; j += p) isprime[j] = false;
        }
    }
    vector<int> adj[mxn];
    for (int p = 1000; p < mxn; p++) {
        if (isprime[p]) {
            for (int i = 0, pp = p; i < 4; i++, pp /= 10) digits[i] = pp % 10;
            for (int d = 0; d < 4; d++) {
                for (int j = -digits[d]; j + digits[d] < 10; j++) {
                    if (j == 0) continue;
                    adj[p].push_back(p + j * pow10[d]);
                }
            }
        }
    }

    int T, p, q; cin >> T;
    for (; T; T--) {
        memset(vis, 0, sizeof(vis));
        cin >> p >> q;
        queue<int> bfs, bfs_next;
        queue<int> *cur = &bfs, *next = &bfs_next;
        int step = 0; bool found = false;
        cur->push(p);
        while (!cur->empty() && !found) {
            while (!cur->empty() && !found) {
                int pp = cur->front(); cur->pop();
                vis[pp] = true;
                if (pp == q) found = true;
                else {
                    for (int i = 0; i < adj[pp].size(); i++) {
                        int qq = adj[pp][i];
                        if (!vis[qq]) next->push(qq);
                    }
                }
            }
            if (found) cout << step << endl;
            step++, swap(cur, next);
        }
        if (!found) cout << "Impossible" << endl;
    }

    return 0;
}