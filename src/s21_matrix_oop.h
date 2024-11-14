#ifndef S21_MATRIX_OOP
#define S21_MATRIX_OOP

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated
  void memory(int rows, int cols, double**& matrix_);
  double multi(int i, int j, const S21Matrix& other);

 public:
  S21Matrix();                        // дефолтный
  S21Matrix(int rows, int cols);      //параметризированный
  S21Matrix(const S21Matrix& other);  //копирования
  S21Matrix(S21Matrix&& other);       // перенос
  ~S21Matrix();                       // Destructor
  // гетерры
  int GetRows(void);
  int GetCols(void);
  // сетеры
  void SetRows(int rows);
  void SetCols(int cols);

  void Print();  // другое
  void del(void);
  void cutMatrix(int m, int n);

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  // перегрузка операторов
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int rows, int cols);
};

#endif