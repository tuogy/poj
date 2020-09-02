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
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, S;
    ll C, Y, best = INT_MAX, tot = 0;
    cin >> N >> S;
    for (int i = 0; i < N; i++) {
        best += S;
        cin >> C >> Y;
        best = min(best, C);
        tot += best * Y;
    }
    cout << tot << endl;

    return 0;
}