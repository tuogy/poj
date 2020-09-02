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

const int mxn = 100000;
ii cow[mxn]; // T, D
ll cost[mxn];

bool compare(const ii& a, const ii& b) {
    return a.second * b.first > a.first * b.second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    for (int i = 0; i < N; i++) cin >> cow[i].first >> cow[i].second;
    sort(cow, cow + N, compare);
    cost[N - 1] = 0;
    for (int i = N - 2; i >= 0; i--) cost[i] = cost[i + 1] + cow[i + 1].second;
    ll ret = 0;
    for (int i = 0; i < N; i++) ret += 2LL * cow[i].first * cost[i];
    cout << ret << endl;


    return 0;
}