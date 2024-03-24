#pragma once
#include<iostream>
#include<vector>

class matrix {
	friend class testing_matrix;
public:
	matrix(const std::vector<std::vector<double>>& mat)
		:m_data(mat), m_rows(mat.size()), m_cols(mat[0].size())
	{};
    matrix(const int& rows, const int& cols) : m_rows(rows), m_cols(cols) {
        // Initialize matrix with zeros
        m_data.resize(rows, std::vector<double>(cols, 0.0));
    }

    // Function to set value at specific position
    void set(const int& row, const int& col, const double& value);

    // Function to get value at specific position
    double get(const int& row, const int& col) const;

    // Function to display matrix
    void display() const;

    // Function to return the size of the matrix.
    std::pair<int, int> size() const;


    // Matrix operations
    matrix operator+(const matrix& other) const;
    template<typename T>
    matrix operator+(const T& scalar) const {
        matrix res(m_rows, m_cols);
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                res.m_data[i][j] = m_data[i][j] + scalar;
            }
        }
        return res;
    }
    matrix operator-(const matrix& other) const;
    template<typename T>
    matrix operator-(const T& scalar) const {
        matrix res(m_rows, m_cols);
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                res.m_data[i][j] = m_data[i][j] - scalar;
            }
        }
        return res;
    }
    template<typename T>
    matrix operator*(const T& scalar) const {
        matrix res(m_rows, m_cols);
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                res.m_data[i][j] = m_data[i][j] * scalar;
            }
        }
        return res;
    }

    // Matrix operations in place.
    matrix& operator+=(const matrix& other);
    template<typename T>
    matrix& operator+=(const T& scalar) {
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                m_data[i][j] += scalar;
            }
        }

        return *this;
    }
    matrix& operator-=(const matrix& other);
    template<typename T>
    matrix& operator-=(const T& scalar) {
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                m_data[i][j] -= scalar;
            }
        }

        return *this;
    }
    template<typename T>
    matrix& operator*=(const T& scalar) {
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                m_data[i][j] *= scalar;
            }
        }
        return *this;
    }

    // Matrix multiplication.
    matrix operator*(const matrix& other) const;

    // Matrix comparison operators.
    bool operator==(const matrix& other) const;
    bool operator!=(const matrix& other) const;

    // Matrix getter operator.
    std::vector<double> operator[](const int& index);

    // Matrix output overload.
	friend std::ostream& operator<<(std::ostream& os, const matrix& mat);

    // LU Decomposition.
    void LU_decomposition(matrix& L, matrix& U) const;

    // Transposition.
    void transpose();

    // Determinant.
    double determinant() const;

    // Inverse.
    void inverse();

    // Matrix Norms.
    double oneNorm() const;
    double infNorm() const;
    double eucNorm() const;
    double froNorm() const;

    // Diagonal Dominance.
    bool diagDominant() const;

    // Eigenvalues.
    double eValues() const;

private:
    std::vector<std::vector<double>> m_data;
    int m_rows;
    int m_cols;
};

class ThomasAlgorithm {
private:
    std::vector<double> a; // Lower diagonal
    std::vector<double> b; // Main diagonal
    std::vector<double> c; // Upper diagonal
    std::vector<double> d; // Right-hand side vector
    int size;

public:
    // Constructor
    ThomasAlgorithm(const std::vector<double>& lower_diagonal,
        const std::vector<double>& main_diagonal,
        const std::vector<double>& upper_diagonal,
        const std::vector<double>& rhs_vector)
        : a(lower_diagonal), b(main_diagonal), c(upper_diagonal), d(rhs_vector), size(b.size()) {
        if (a.size() != size - 1 || c.size() != size - 1 || d.size() != size) {
            throw std::invalid_argument("Error in ThomasAlgorithm constructor. Invalid input sizes.");
        }
    }

    // Function to solve the tridiagonal linear system using Thomas algorithm
    std::vector<double> solve();

    friend std::ostream& operator<<(std::ostream& os, ThomasAlgorithm& solver);
};