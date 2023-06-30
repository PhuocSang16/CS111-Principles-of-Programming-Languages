#include<iostream>

using namespace std;

int dp[1001][1000];

int main(){
    short n, x, a[1000];
    cin >> n >> x;
    for(int i = 1; i <= n; ++i)
    {
        int k;
        cin >> k;
        a[i] = k % x;
    }
    for (int i = 1; i < x - 1; i++) dp[1][i] = -1;
    dp[1][a[1]] = 1;
    for(int i = 2; i <= n; i++)
    {
        for(int j = 0; j < x; j++){
            if(dp[i-1][j] >= 0)
            {
                dp[i][j] = max(dp[i-1][j], dp[i-1][(j-a[i]+x)%x] + 1);
            }
        }
    }
    cout << dp[n][0];
    return 0;
}
