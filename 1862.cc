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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, x;
    cin >> N;
    priority_queue<double> pq;
    for (int i = 0; i < N; i++) {
        cin >> x;
        pq.push(x);
    }
    while (pq.size() > 1) {
        double a = pq.top(); pq.pop();
        double b = pq.top(); pq.pop();
        pq.push(2. * sqrt(a * b));
    }
    cout << fixed << setprecision(3) << pq.top() << endl;

    return 0;
}