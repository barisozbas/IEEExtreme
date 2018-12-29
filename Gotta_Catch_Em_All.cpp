#include <iostream>

using namespace std;

int main() {
    int dp[202][202];
    int points[202][202];
    
    int row,column;
    cin >> row >> column;
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            cin >> points[i][j];
        }
    }
    dp[row-1][column-1]=1;
    for (int i = row-2; i >= 0; i--)
         dp[i][column-1] = max(dp[i+1][column-1] - points[i][column-1], 1);
    for (int j = column-2; j >= 0; j--)
         dp[row-1][j] = max(dp[row-1][j+1] - points[row-1][j], 1);
    for (int i=row-2; i>=0; i--){
        for (int j=column-2; j>=0; j--){
            int minPoint = min(dp[i+1][j], dp[i][j+1]);
            dp[i][j] = max(minPoint - points[i][j], 1);
        }
     }
    cout << dp[0][0];
}