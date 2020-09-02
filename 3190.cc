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

int t_start[50005], t_end[50005];

bool compare(int a, int b) {
    return t_start[a] < t_start[b];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> t_start[i] >> t_end[i];
    }
    vector<int> v(N), assign(N);
    for (int i = 0; i < N; i++) {
        v[i] = i;
    }
    sort(v.begin(), v.end(), compare);
    priority_queue<ii, vector<ii>, greater<ii> > pq;
    for (int i = 0; i < N; i++) {
        if (pq.empty() || pq.top().first >= t_start[v[i]]) {
            int sz = pq.size();
            pq.push(make_pair(t_end[v[i]], sz + 1));
            assign[v[i]] = sz + 1;
        }
        else {
            ii top = pq.top(); pq.pop();
            pq.push(make_pair(t_end[v[i]], top.second));
            assign[v[i]] = top.second;
        }
    }
    cout << pq.size() << endl;
    for (int i = 0; i < N; i++) {
        cout << assign[i] << endl;
    }

    return 0;
}