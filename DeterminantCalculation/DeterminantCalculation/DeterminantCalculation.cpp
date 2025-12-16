
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

vector<vector<int>> get_matrix() {
    int N;
    cout << "Enter the dimension of the square matrix (N): ";
    cin >> N;

    // Initialize the N x N matrix with default values
    vector<vector<int>> matrix(N, vector<int>(N));

    cout << "Enter the matrix elements (row by row):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "Element [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

vector<vector<int>> get_minor_matrix(const vector<vector<int>>& original, int row_to_skip, int col_to_skip) {
    int N = original.size();
    // The new minor matrix will be (N-1) x (N-1)
    vector<vector<int>> minor(N - 1, vector<int>(N - 1));

    int minor_r = 0;
    for (int i = 0; i < N; ++i) {
        // Skip the specified row
        if (i == row_to_skip) continue;

        int minor_c = 0;
        for (int j = 0; j < N; ++j) {
            // Skip the specified column
            if (j == col_to_skip) continue;

            // Copy the element to the minor matrix
            minor[minor_r][minor_c] = original[i][j];
            minor_c++;
        }
        minor_r++;
    }
    return minor;
}
int calculate_determinant(const vector<vector<int>>& matrix) {
    int N = matrix.size();

    
    if (N == 1) {
        return matrix[0][0];
    }

    
    if (N == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }

    
    int det = 0;
    
    for (int j = 0; j < N; ++j) { 

        int sign = (j % 2 == 0) ? 1 : -1;

        
        vector<vector<int>> minor = get_minor_matrix(matrix, 0, j);

      
        det += sign * matrix[0][j] * calculate_determinant(minor);
    }

    return det;
}

int main() {
    cout << "--- N x N Matrix Determinant Calculator ---\n";
    cout << "This program calculates the determinant of a square matrix (N x N).\n\n";

    // 1. Get the matrix from the user
    vector<vector<int>> matrix = get_matrix();

    // Check if the matrix is valid (non-empty and square)
    if (matrix.empty() || matrix.size() != matrix[0].size()) {
        cerr << "Error: The matrix must be a square matrix (N x N)." << endl;
        return 1; // Return with an error code
    }

    // Display the input matrix for confirmation
    cout << "\n--- Input Matrix (" << matrix.size() << "x" << matrix.size() << ") ---" << endl;
    for (const auto& row : matrix) {
        for (int element : row) {
            cout << setw(5) << element; // setw(5) formats output nicely
        }
        cout << endl;
    }
    cout << "------------------------------------------" << endl;


    // 2. Calculate the determinant
    try {
        int determinant = calculate_determinant(matrix);

        // 3. Display the result
        cout << "\nRESULT:\n";
        cout << "The Determinant of the Matrix is: " << determinant << endl;

    }
    catch (const exception& e) {
        // Simple error handling in case something goes wrong
        cerr << "An error occurred during calculation: " << e.what() << endl;
        return 1;
    }


    return 0;
}

