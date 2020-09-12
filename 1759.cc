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


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    double A, B;
    cin >> N >> A;

    double l = 0, r = A + pow(N - 1, 2.);
    for (int k = 0; k < 100; k++) {
        double c = (l + r) / 2.;
        double d = (c - A - (N - 1) * (N - 2)) / (N - 1);
        double ax = (3 - d) / 2.;
        if (ax <= 1 || ax >= N) r = c;
        else {
            int xl = ax, xr = xl + 1;
            double miny = min((xl - 1) * (xl - 2 + d), (xr - 1) * (xr - 2 + d)) + A; 
            if (miny <= 0) l = c;
            else r = c;
        }
    }
    cout << fixed << setprecision(2) << l << endl;

    return 0;
}