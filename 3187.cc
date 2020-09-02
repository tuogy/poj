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

#ifdef __APPLE__
#define cin fin
std::ifstream cin("__sample.in");
#endif

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;
const int INT_INF = 0x3f3f3f3f;
const int d4r[] = {0, 1, 0, -1}, d4c[] = {1, 0, -1, 0};

ll coeff[11], factorial[11];
int perm[10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    factorial[0] = 1;
    for (int i = 1; i <= 10; i++) factorial[i] = factorial[i - 1] * i;

    int N, sum;
    cin >> N >> sum;
    for (int i = 0; i < N; i++) perm[i] = i + 1;
    for (int r = 0; r < N; r++) {
        coeff[r] = factorial[N - 1] / factorial[r] / factorial[N - 1 - r];
    }
    do {
        ll tot = 0;
        for (int i = 0; i < N; i++) tot += coeff[i] * perm[i];
        if (tot == sum) {
            for (int i = 0; i < N; i++) cout << perm[i] << (i == N - 1 ? '\n' : ' ');
            break;
        }
    } while (next_permutation(perm, perm + N));

    return 0;
}