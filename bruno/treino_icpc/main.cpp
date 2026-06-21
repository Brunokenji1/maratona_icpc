#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cout << "Enter the number of items and the maximum weight: ";
    cin >> n >> m;
    vector<int> a(n);
    cout << "Enter the weights of the items: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] <= m) {
            ans++;
            m -= a[i];
        } else {
            break;
        }
    }
    cout << ans << endl;
    return 0;
}