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

ll m;
int N, x[100000];

bool feasible(int diff) {
    queue<int> q;
    ll tot = 0;
    for (int i = 0; i < N; i++) {
        while (!q.empty() && x[i] - q.front() > diff) q.pop();
        tot += q.size();
        q.push(x[i]);
    }
    return tot >= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (scanf("%d", &N) != -1) {
        ll NN = (ll)N * (N - 1) / 2;
        m = (NN >> 1) + (NN & 1);
        for (int i = 0; i < N; ++i) scanf("%d", x + i);
        sort(x, x + N);
        int l = x[0] - x[N - 1] - 1, r = x[N - 1] - x[0] + 1;
        while (l < r - 1) {
            int c = (l + r) / 2;
            if (feasible(c)) r = c;
            else l = c;
        }
        printf("%d\n", r);
    }

    return 0;
}