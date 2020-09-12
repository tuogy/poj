#include <iostream>
#include <sstream>
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

const int mxN = 20000;
int X[mxN], Y[mxN], Z[mxN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int il = 0;
    char line[50];
    do {
        cin.getline(line, 50);
        if (!cin.fail() && strlen(line) > 0) {
            sscanf(line, "%d%d%d", X + il, Y + il, Z + il);
            il++;
        }
        else {
            if (il > 0) {
                int l = INT_MAX, r = INT_MIN, n = il, tot = 0;
                for (int i = 0; i < n; i++) 
                    l = min(l, X[i]), r = max(r, Y[i]), tot ^= ((Y[i] - X[i]) / Z[i] & 1) ^ 1;
                l--;
                if (!tot) printf("no corruption\n");
                else {
                    while (l < r - 1) {
                        int c = l + (r - l) / 2;
                        tot = 0;
                        for (int i = 0; i < n; i++) {
                            if (c >= X[i])
                                tot ^= ((min(c, Y[i]) - X[i]) / Z[i] & 1) ^ 1;
                        } 
                        if (tot) r = c;
                        else l = c;
                    }
                    tot = 0;
                    for (int i = 0; i < n; i++) 
                        tot += (r >= X[i] && r <= Y[i] && (r - X[i]) % Z[i] == 0);
                    printf("%d %d\n", r, tot);
                } 
                il = 0;
            }
        }
    } while (!cin.fail());

    return 0;
}