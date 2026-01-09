#include <bits/stdc++.h> 
// This header is a common shortcut in competitive programming.
// It includes <vector>, <algorithm> (for sort), <iostream>, etc.

/*
 * Complete the 'medians' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 * 1. INTEGER_ARRAY values
 * 2. INTEGER k
 */

vector<int> medians(vector<int> values, int k) {
    
    // Get the total number of elements in the input array.
    int n = values.size();

    // --- Step 1: Sort the array ---
    // The core idea is that the min/max medians must come from
    // the subsequences built from the smallest/largest elements.
    // Sorting allows us to easily find these.
    // This sort operation is the most time-consuming part, O(n log n).
    sort(values.begin(), values.end());

    // --- Step 2: Calculate the median's position ---
    // For any sorted list of 'k' elements, the median is at
    // index (k-1) / 2. We use integer division, which
    // automatically handles the 'floor' operation.
    // Example (k=5): (5-1)/2 = 2. Median is at index 2.
    // Example (k=2): (2-1)/2 = 0. Median is at index 0.
    int median_position = (k - 1) / 2;

    // --- Step 3: Find the Minimum Median ---
    // The smallest possible median will come from the subsequence
    // formed by the *first k* elements of the sorted array
    // (i.e., values[0]...values[k-1]).
    // The median of *that* subsequence is at our calculated position.
    int min_median = values[median_position];

    // --- Step 4: Find the Maximum Median ---
    // The largest possible median will come from the subsequence
    // formed by the *last k* elements of the sorted array
    // (i.e., values[n-k]...values[n-1]).
    // The median of *that* subsequence is at 'median_position'
    // *relative to its start*.
    // The start index is (n-k).
    // So, the absolute index in the 'values' array is:
    int max_median_index = (n - k) + median_position;
    int max_median = values[max_median_index];

    // --- Step 5: Format the return value ---
    // The function must return {maximum median, minimum median}.
    vector<int> result;
    result.push_back(max_median);
    result.push_back(min_median);
    
    return result;

    // Alternative C++11 way to return:
    // return {max_median, min_median};
}


// The main() function is just for handling input/output.
// The problem logic is entirely contained in the 'medians' function above.
// This part would be provided by the testing environment.
int main()
{
    // This is just a placeholder to make the file runnable.
    // The online judge will call the 'medians' function directly.
    
    // Example from Sample Case 0:
    // int n = 2;
    // vector<int> values = {56, 21};
    // int k = 1;
    
    // Example from Sample Case 1:
    // int n = 5;
    // vector<int> values = {16, 21, 9, 2, 78};
    // int k = 5;

    // Example from problem description:
    int n = 3;
    vector<int> values = {1, 2, 3};
    int k = 2;

    // Call the function
    vector<int> result = medians(values, k);

    // Print the result
    cout << result[0] << endl; // max_median
    

    return 0;
}