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
const int INT_INF = 0x3f3f3f3f;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

ii coin[20];
int cost[20];
int ret;

bool probe(int target, int i) {
    int c = min(coin[i].second, target / coin[i].first);
    target -= c * coin[i].first;
    cost[i] = c;
    if (target == 0 || i && probe(target, i - 1)) return true;
    else if (coin[i].second > c) {
        cost[i]++;
        return true;
    }
    else {
        cost[i] = 0;
        return false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, C;
    cin >> N >> C;
    for (int i = 0; i < N; i++) cin >> coin[i].first >> coin[i].second;
    sort(coin, coin + N);
    ret = 0;
    memset(cost, 0, N * sizeof(int));
    while (probe(C, N - 1)) {
        int d = INT_MAX;
        for (int i = 0; i < N; i++) {
            if (cost[i]) d = min(d, coin[i].second / cost[i]);
        }
        ret += d;
        for (int i = 0; i < N; i++) coin[i].second -= d * cost[i];
        memset(cost, 0, N * sizeof(int));
    }
    cout << ret << endl;
    

    return 0;
}