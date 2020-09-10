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

int N, M, money[100000];

bool feasible(int x) {
    int cur = 0, c = 1;
    for (int i = 0; i < N && c <= M; i++) {
        if (money[i] > x) return false;
        else if (cur + money[i] <= x) cur += money[i];
        else c++, cur = money[i];
    }
    return c <= M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++) cin >> money[i];
    int l = 0, r = 1e9+1;
    while (l < r - 1) {
        int c = l + (r - l) / 2;
        if (feasible(c)) r = c;
        else l = c;
    }
    cout << r << endl;

    return 0;
}