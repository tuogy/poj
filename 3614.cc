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

ii cow[2500];
ii lotion[2500];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int C, L; cin >> C >> L;
    for (int i = 0; i < C; i++) cin >> cow[i].first >> cow[i].second;
    for (int i = 0; i < L; i++) cin >> lotion[i].first >> lotion[i].second;
    sort(cow, cow + C);
    sort(lotion, lotion + L);
    priority_queue<int, vector<int>, greater<int> > q;
    int ret = 0;
    for (int i = 0, j = 0; i < L; i++) {
        while (j < C && cow[j].first <= lotion[i].first) {
            q.push(cow[j++].second); 
        }
        for (int k = lotion[i].second; !q.empty() && k; ) {
            if (q.top() < lotion[i].first) q.pop();
            else k--, ret++, q.pop();
        }
    }
    cout << ret << endl;

    return 0;
}