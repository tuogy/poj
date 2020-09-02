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

vector<int> num[1024];

void get_numbers(int digits, int cur, vector<int>& ret) {
    if (digits == 0) ret.push_back(cur);
    else {
        for (int i = 0; i < 10; i++) {
            int bit = 1 << i;
            if ((digits & bit) == 0 || i == 0 && cur == 0 && digits != 1) continue;
            get_numbers(digits ^ bit, cur * 10 + i, ret);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 0; i < 1024; i++) num[i].clear();
    int T, x;
    string line;
    cin >> T; cin.get();
    for (int i = 0; i < T; i++) {
        getline(cin, line);
        istringstream iss(line);
        int digits = 0, best = INT_MAX;
        while (iss >> x) digits |= 1 << x;
        for (int i = 1; i <= digits - i; i++) {
            int j = digits - i;
            if ((i | digits) != digits || __builtin_popcount(j) - __builtin_popcount(i) > 1) continue;

            if (num[i].empty()) {
                get_numbers(i, 0, num[i]);
                sort(num[i].begin(), num[i].end());
            }
            if (num[j].empty()) {
                get_numbers(j, 0, num[j]);
                sort(num[j].begin(), num[j].end());
            }
            for (int l = 0; l < num[i].size(); l++) {
                int n1 = num[i][l];
                vector<int>::iterator it = lower_bound(num[j].begin(), num[j].end(), n1);
                if (it != num[j].end()) best = min(best, *it - n1);
                if (it != num[j].begin()) best = min(best, n1 - *(it - 1));
            }
        }
        cout << best << endl;
    }

    return 0;
}