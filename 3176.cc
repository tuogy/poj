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

int v[350][350];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) cin >> v[i][j];
    }
    for (int i = N - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            v[i][j] += max(v[i + 1][j], v[i + 1][j + 1]);
        }
    }
    cout << v[0][0] << endl;
    

    return 0;
}