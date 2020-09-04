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

const int mxn = 100000;
ii cow[mxn];
int dp_l[mxn], dp_r[mxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, C, F; cin >> N >> C >> F;
    for (int i = 0; i < C; i++) cin >> cow[i].first >> cow[i].second;
    sort(cow, cow + C);
    memset(dp_l, 0x3f, C * sizeof(int));
    memset(dp_r, 0x3f, C * sizeof(int));

    int nside = N >> 1;
    {
        priority_queue<int> maxq; int tot = 0;
        for (int i = 0; i < nside; i++) maxq.push(cow[i].second), tot += cow[i].second;
        for (int i = nside; i < C; i++) {
            dp_l[i] = tot;
            tot += cow[i].second; maxq.push(cow[i].second);
            tot -= maxq.top(); maxq.pop();
        }
    }
    {
        priority_queue<int> maxq; int tot = 0;
        for (int i = C - 1; i > C - 1 - nside; i--) maxq.push(cow[i].second), tot += cow[i].second;
        for (int i = C - 1 - nside; i >= 0; i--) {
            dp_r[i] = tot;
            tot += cow[i].second; maxq.push(cow[i].second);
            tot -= maxq.top(); maxq.pop();
        }
    }
    int ret = -1;
    for (int i = C - 1; i >= 0 && ret < 0; i--) {
        if (dp_l[i] + dp_r[i] + cow[i].second <= F) {
            ret = cow[i].first;
        }
    }
    cout << ret << endl;

    return 0;
}