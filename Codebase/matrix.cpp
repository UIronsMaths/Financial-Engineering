#include"matrix.h"

void matrix::set(const int& row, const int& col, const double& value) {
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols) {
        throw std::runtime_error("Error in matrix::set(). Index out of bounds.");
    }
    m_data[row][col] = value;
}
double matrix::get(const int& row, const int& col) const {
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols) {
        throw std::runtime_error("Error in matrix::get(). Index out of bounds.");
    }
    return m_data[row][col];
}
void matrix::display() const {
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            std::cout << m_data[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
std::pair<int, int> matrix::size() const {
    return { m_rows, m_cols };
}
matrix matrix::operator+(const matrix& other) const {
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw std::runtime_error("Error in matrix::operator+(). Matrices must have the same dimensions for addition.");
    }

    matrix res(m_rows, m_cols);
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            res.m_data[i][j] = m_data[i][j] + other.m_data[i][j];
        }
    }
    return res;
}
matrix matrix::operator-(const matrix& other) const {
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw std::runtime_error("Error in matrix::operator+(). Matrices must have the same dimensions for subtraction.");
    }

    matrix res(m_rows, m_cols);
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            res.m_data[i][j] = m_data[i][j] - other.m_data[i][j];
        }
    }
    return res;
}
matrix& matrix::operator+=(const matrix& other) {
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw std::runtime_error("Matrices must have the same dimensions for addition.");
    }

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            m_data[i][j] += other.m_data[i][j];
        }
    }

    return *this;
}
matrix& matrix::operator-=(const matrix& other) {
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw std::runtime_error("Matrices must have the same dimensions for subtraction.");
    }

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            m_data[i][j] -= other.m_data[i][j];
        }
    }

    return *this;
}
matrix matrix::operator*(const matrix& other) const {
    if (m_cols != other.m_rows) {
        throw std::runtime_error("Error in matrix::operator*(). Matrices must have compatable dimensions for multiplication.");
    }

    matrix res(m_rows, other.m_cols);
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < other.m_cols; ++j) {
            for (int k = 0; k < m_cols; ++k) {
                res.m_data[i][j] += m_data[i][k] * other.m_data[k][j];
            }
        }
    }
    return res;
}
bool matrix::operator==(const matrix& other) const {
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            if (m_data[i][j] != other.m_data[i][j]) {
                return false;
            }
        }
    }
    return true;
}
bool matrix::operator!=(const matrix& other) const {
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            if (m_data[i][j] != other.m_data[i][j]) {
                return true;
            }
        }
    }
    return false;
}
std::ostream& operator<<(std::ostream& os, const matrix& mat) {
    for (int i = 0; i < mat.m_rows; ++i) {
        for (int j = 0; j < mat.m_cols; ++j) {
            os << mat.m_data[i][j] << "\t";
        }
        os << std::endl;
    }
    return os;
}
void matrix::LU_decomposition(matrix& L, matrix& U) const {
    if (m_rows != m_cols) {
        throw std::runtime_error("Matrix must be square for LU decomposition");
    }

    // Initialize matrices L and U
    L = matrix(m_rows, m_cols);
    U = matrix(m_rows, m_cols);

    for (int i = 0; i < m_rows; ++i) {
        // Upper triangular matrix
        for (int k = i; k < m_rows; ++k) {
            double sum = 0.0;
            for (int j = 0; j < i; ++j) {
                sum += (L.get(i, j) * U.get(j, k));
            }
            U.set(i, k, m_data[i][k] - sum);
        }

        // Lower triangular matrix
        for (int k = i; k < m_rows; ++k) {
            if (i == k)
                L.set(i, i, 1); // Diagonal elements are 1
            else {
                double sum = 0.0;
                for (int j = 0; j < i; ++j) {
                    sum += (L.get(k, j) * U.get(j, i));
                }
                L.set(k, i, (m_data[k][i] - sum) / U.get(i, i));
            }
        }
    }
}
void matrix::transpose() {
    matrix new_mat(m_cols, m_rows);
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            new_mat.set(j, i, m_data[i][j]);
        }
    }
    *this = new_mat;
}
double matrix::determinant() const {
    if (m_rows != m_cols) {
        throw std::runtime_error("Error in matrix::determinant(). Matrix is not square.");
    }
    matrix L(m_rows, m_cols);
    matrix U(m_rows, m_cols);
    LU_decomposition(L, U);
    double determinant = 1;
    for (int i = 0; i < m_rows; i++) {
        determinant *= U.get(i,i);
    }
    return determinant;
}
bool matrix::diagDominant() const {
    for (int i = 0; i < m_rows; i++) {
        double rowSum = 0;
        for (int j = 0; j < m_cols; j++) {
            if (j != i) {
                rowSum += abs(this->get(i, j));
            }
        }
        if (abs(this->get(i, i)) < rowSum) {
            return false;
        }
    }
    return true;
}



std::vector<double> ThomasAlgorithm::solve() {
    std::vector<double> x(size, 0.0); // Solution vector
    std::vector<double> c_prime(size - 1, 0.0); // Modified upper diagonal coefficients

    // Forward elimination
    c_prime[0] = c[0] / b[0];
    for (int i = 1; i < size - 1; ++i) {
        double m = 1.0 / (b[i] - a[i - 1] * c_prime[i - 1]);
        c_prime[i] = c[i] * m;
        d[i] = (d[i] - a[i - 1] * d[i - 1]) * m;
    }

    // Backward substitution
    x[size - 1] = (d[size - 1] - a[size - 2] * d[size - 2]) / (b[size - 1] - a[size - 2] * c_prime[size - 2]);
    for (int i = size - 2; i >= 0; --i) {
        x[i] = d[i] - c_prime[i] * x[i + 1];
    }

    return x;
}
std::ostream& operator<<(std::ostream& os, ThomasAlgorithm& solver) {
    std::vector<double> solution = solver.solve();
    for (int i = 0; i < solution.size(); ++i) {
        os << "x" << i << " = " << solution[i] << std::endl;
    }
    return os;
}