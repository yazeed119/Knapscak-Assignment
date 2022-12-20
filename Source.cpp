#include <iostream>
#include <vector>

using namespace std;

// Represents an item with a weight and a value
struct Item {
    int weight;
    int value;
};

// Finds the maximum value that can be achieved with the given items and sack capacity
// using dynamic programming
int knapsack(int capacity, vector<Item> items) {
    // Create a matrix to store the maximum value that can be achieved with each
    // weight and number of items
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1));

    // Fill the matrix
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            // Check if the current item can be included
            if (items[i - 1].weight <= w) {
                // The maximum value is the maximum of either:
                // - the value achieved without including the current item
                // - the value achieved by including the current item
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            }
            else {
                // The current item cannot be included, so the maximum value is the value
                // achieved without including it
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Print the matrix
    cout << "Matrix:" << endl;
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            cout << dp[i][w] << " ";
        }
        cout << endl;
    }

    // Print the selected items
    cout << "Selected items:" << endl;
    int w = capacity;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << "Item " << i << ": weight = " << items[i - 1].weight << ", value = " << items[i - 1].value << endl;
            w -= items[i - 1].weight;
        }
    }

    // Return the maximum value
    return dp[n][capacity];
}

int main() {
    // Example input: sack capacity = 7, 3 items with weights [4, 5, 1] and values [10, 20, 5]
    int capacity = 7;
    vector<Item> items = { {4, 10}, {5, 20}, {1, 5} };

    cout << "Maximum value: " << knapsack(capacity, items) << endl;

    return 0;
}
