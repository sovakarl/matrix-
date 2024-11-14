#include "s21_matrix_oop.h"
// конструкторы
S21Matrix::~S21Matrix() {
  if (matrix_) this->del();
}

S21Matrix::S21Matrix() : S21Matrix(1, 1){};

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  double**& url = {matrix_};
  memory(rows_, cols_, url);
};

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) matrix_[i][j] = other.matrix_[i][j];
  }
};

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
};

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool flag = true;
  if (other.rows_ == rows_ && other.cols_ == cols_) {
    for (int i = 0; i < rows_; i++) {
      if (!flag) break;
      for (int j = 0; j < cols_; j++)
        if (other.matrix_[i][j] != matrix_[i][j]) {
          flag = 0;
          break;
        }
    }
  } else
    flag = false;
  return flag;
};

void S21Matrix::SumMatrix(const S21Matrix& other) {
  try {
    if (rows_ == other.rows_ && cols_ == other.cols_) {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
      }
    } else
      throw std::invalid_argument("Invalid_argument");
  } catch (std::invalid_argument const& e) {
    cout << e.what() << endl;
    throw;
  }
};

void S21Matrix::SubMatrix(const S21Matrix& other) {
  try {
    if (rows_ == other.rows_ && cols_ == other.cols_) {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
      }
    } else
      throw std::invalid_argument("Invalid_argument");
  } catch (std::invalid_argument const& e) {
    cout << e.what() << endl;
    throw;
  }
};

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
  }
};

void S21Matrix::MulMatrix(const S21Matrix& other) {
  try {
    if (cols_ != other.rows_) throw std::invalid_argument("Invalid_argument");
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < result.rows_; i++) {
      for (int j = 0; j < result.cols_; j++)
        result.matrix_[i][j] = multi(i, j, other);
    }
    *this = result;
  } catch (std::invalid_argument const& e) {
    cout << e.what() << endl;
    throw;
  }
};

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) result.matrix_[i][j] = matrix_[j][i];
  }
  return result;
};

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(rows_, cols_);
  int sign = 0;
  try {
    if (rows_ != cols_) throw std::invalid_argument("invalid_argument");
    if (rows_ == 1)
      result(0, 0) = 1;
    else {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          sign = ((j + i) & 1) ? -1 : 1;
          S21Matrix tmp(*this);
          tmp.cutMatrix(i, j);
          result(i, j) = sign * tmp.Determinant();
          tmp.del();
        }
      }
    }
  } catch (const std::invalid_argument& e) {
    cout << e.what() << endl;
    throw;
  }

  return result;
};

double S21Matrix::Determinant() {
  int sign = 0;
  double result = 0;
  double tempResult = 0;
  try {
    if (rows_ != cols_) throw std::invalid_argument("Invalid_argument");
    if (rows_ == 1)
      result = matrix_[0][0];
    else if (rows_ == 2)
      result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    else {
      for (int j = 0; j < cols_; j++) {
        S21Matrix tmp(*this);
        sign = (j & 1) ? -1 : 1;
        tmp.cutMatrix(0, j);
        tempResult += tmp.Determinant() * (sign)*matrix_[0][j];
        tmp.del();
      }
      result = tempResult;
    }
  } catch (std::invalid_argument const& e) {
    cout << e.what() << endl;
    throw;
  }
  return result;
};

S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  S21Matrix result;
  try {
    if (rows_ != cols_ || rows_ < 1)
      throw std::invalid_argument("invalid_argument");
    else if (!det)
      throw std::invalid_argument("invalid_argument");
  } catch (const std::invalid_argument& e) {
    cout << e.what() << endl;
    throw;
  }

  result = this->Transpose();
  result = result.CalcComplements();
  result *= 1 / det;
  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
};

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
};

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
};

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
};

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); };

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_];

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
  }
  return *this;
};

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
};

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
};

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
};

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
};

double& S21Matrix::operator()(int rows, int cols) {
  try {
    if ((cols < 0 || rows < 0) || (cols > cols_ || rows > rows_))
      throw std::invalid_argument("Invalid_argument");
    return matrix_[rows][cols];
  } catch (std::invalid_argument const& e) {
    cout << e.what() << endl;
    throw;
  }
};

void S21Matrix::del(void) {
  for (int i = 0; i < rows_; i++) delete[] matrix_[i];
  delete matrix_;
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}
// помогаторы

void S21Matrix::cutMatrix(int m, int n) {
  int y = 0;
  int x = 0;
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    x = 0;
    if (i == m) continue;
    for (int j = 0; j < cols_; j++) {
      if (j == n) continue;
      result.matrix_[y][x] = matrix_[i][j];
      x++;
    }
    y++;
  }
  *this = result;
};
void S21Matrix::Print() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) cout << " " << matrix_[i][j];
    cout << endl;
  }
  cout << endl;
};

void S21Matrix::memory(int rows, int cols, double**& matrix_) {
  try {
    if (rows <= 0 || cols <= 0) throw std::invalid_argument("invalid_argument");
    matrix_ = new double*[rows];
    for (int i = 0; i < rows; i++) matrix_[i] = new double[cols];
  } catch (std::invalid_argument const& e) {
    cout << e.what() << endl;
    matrix_ = nullptr;
    throw;
  }
};

double S21Matrix::multi(int i, int j, const S21Matrix& other) {
  double result = 0;
  for (int k = 0; k < cols_; k++) result += matrix_[i][k] * other.matrix_[k][j];
  return result;
};

int S21Matrix::GetRows(void) { return rows_; }

int S21Matrix::GetCols(void) { return cols_; }

void S21Matrix::SetRows(int rows) {
  try {
    if (rows < 1) throw std::invalid_argument("invalid_argument");
    S21Matrix result(rows, cols_);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols_; j++) {
        if (i >= rows_)
          result(i, j) = 0;
        else
          result(i, j) = matrix_[i][j];
      }
    }
    *this = result;
  } catch (std::invalid_argument const& e) {
    cout << e.what() << endl;
    throw;
  }
}
void S21Matrix::SetCols(int cols) {
  try {
    if (cols < 1) throw std::invalid_argument("invalid_argument");
    S21Matrix result(rows_, cols);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols; j++) {
        if (j >= cols_)
          result(i, j) = 0;
        else
          result(i, j) = matrix_[i][j];
      }
    }
    *this = result;
  } catch (std::invalid_argument const& e) {
    cout << e.what() << endl;
    throw;
  }
}