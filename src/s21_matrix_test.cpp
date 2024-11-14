#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(test_class, uctor_0) {
  S21Matrix m;
  EXPECT_EQ(m.GetCols(), 1);
  EXPECT_EQ(m.GetRows(), 1);
}

TEST(test_class, uctor_1) {
  S21Matrix m(100, 100);
  EXPECT_EQ(m.GetRows(), 100);
  EXPECT_EQ(m.GetCols(), 100);
}

TEST(test_class, uctor_2) {
  S21Matrix m(25, 25);
  S21Matrix copy(m);
  EXPECT_EQ(1, 1);
  EXPECT_EQ(copy.GetCols(), 25);
  EXPECT_EQ(copy.GetRows(), 25);
}

TEST(test_class, uctor_3) {
  S21Matrix m(43, 43);
  S21Matrix moved(std::move(m));
  EXPECT_EQ(m.GetCols(), 0);
  EXPECT_EQ(m.GetRows(), 0);
  EXPECT_EQ(moved.GetCols(), 43);
  EXPECT_EQ(moved.GetRows(), 43);
}

TEST(test_class, operator_0) {
  S21Matrix m(10, 10);
  EXPECT_EQ(m(0, 0), 0);

  m(0, 1) = 100;
  EXPECT_EQ(m(0, 1), 100);

  m(2, 4) = -100.5;
  EXPECT_EQ(m(2, 4), -100.5);
}

TEST(test_setters, setRows_0) {
  S21Matrix m(2, 2);
  m(1, 1) = -24;

  m.SetRows(5);
  EXPECT_EQ(m.GetRows(), 5);
  EXPECT_EQ(m(1, 1), -24);
}

TEST(test_setters, setRows_1) {
  S21Matrix m(2, 2);
  m(0, 0) = 32;

  m.SetRows(1);
  EXPECT_EQ(m.GetRows(), 1);
  EXPECT_EQ(m(0, 0), 32);
}

TEST(test_setters, setRows_2) {
  S21Matrix m(1, 1);
  EXPECT_ANY_THROW(m.SetRows(0));
}

TEST(test_setters, setCols_0) {
  S21Matrix m(2, 2);
  m(1, 1) = 5645;

  m.SetCols(5);
  EXPECT_EQ(m.GetCols(), 5);
  EXPECT_EQ(m(1, 1), 5645);
}

TEST(test_setters, setCols_1) {
  S21Matrix m(2, 2);
  m(0, 0) = 23233;
  m.SetCols(1);
  EXPECT_EQ(m.GetCols(), 1);
  EXPECT_EQ(m(0, 0), 23233);
}

TEST(test_setters, setCols_2) {
  S21Matrix m(1, 1);
  EXPECT_ANY_THROW(m.SetCols(0));
}

TEST(test_overload, equal_0) {
  S21Matrix m;
  S21Matrix x(3, 6);
  x(1, 2) = 45;
  x(2, 2) = 32;

  m = x;

  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 6);
  EXPECT_EQ(m(1, 2), 45);
  EXPECT_EQ(m(2, 2), 32);
}

TEST(test_overload, equal_1) {
  S21Matrix m(2, 2);
  S21Matrix n;

  n = std::move(m);

  EXPECT_EQ(n.GetCols(), 2);
  EXPECT_EQ(n.GetRows(), 2);
}

TEST(test_overload, equal_2) {
  S21Matrix m(2, 2);
  S21Matrix n(std::move(m));

  EXPECT_EQ(n.GetCols(), 2);
  EXPECT_EQ(n.GetRows(), 2);
}

TEST(test_functional, equal_3) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  ASSERT_TRUE(m == n);
}

TEST(test_functional, equal_4) {
  S21Matrix m(3, 2);
  S21Matrix n;

  m(0, 0) = -4343.5;
  n = m;

  ASSERT_TRUE(m == n);
}

TEST(test_functional, equal_5) {
  S21Matrix m(3, 2);
  S21Matrix n(1, 2);

  ASSERT_FALSE(m.EqMatrix(n));
}

TEST(test_functional, equal_6) {
  S21Matrix m(3, 2);
  S21Matrix n(3, 2);

  n(0, 0) = -1;

  ASSERT_FALSE(m.EqMatrix(n));
}

TEST(test_functional, sum_0) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = -1;
  n(0, 0) = -1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m.SumMatrix(n);

  EXPECT_EQ(m(0, 0), -2);
  EXPECT_EQ(m(1, 1), 2);
}

TEST(test_functional, sum_1) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 3;
  n(1, 1) = 3;

  m = m + n;

  EXPECT_EQ(m(0, 0), 2);
  EXPECT_EQ(m(1, 1), 6);
}

TEST(test_functional, sum_2) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 4;
  n(0, 0) = 4;

  m(1, 1) = -41;
  n(1, 1) = -431;

  m += m + n;

  EXPECT_EQ(m(0, 0), 12);
  EXPECT_EQ(m(1, 1), -513);
}

TEST(test_functional, sum_3) {
  S21Matrix m(2, 2);
  S21Matrix n(1, 2);

  EXPECT_THROW(m.SumMatrix(n), std::invalid_argument);
}

TEST(test_functional, sub_0) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m.SubMatrix(n);

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, sub_1) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m -= n;

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, sub_2) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m = m - n;

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, sub_3) {
  S21Matrix m(2, 2);
  S21Matrix n(1, 2);

  EXPECT_THROW(m.SubMatrix(n), std::invalid_argument);
}

TEST(test_functional, mul_0) {
  int rows = 2;
  int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m(i, j) = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) n(i, j) = c++;

  m.MulMatrix(n);

  S21Matrix res(2, 2);
  res(0, 0) = 58;
  res(0, 1) = 64;
  res(1, 0) = 139;
  res(1, 1) = 154;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, mul_1) {
  int rows = 2;
  int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m(i, j) = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) n(i, j) = c++;

  m *= n;

  S21Matrix res(2, 2);
  res(0, 0) = 58;
  res(0, 1) = 64;
  res(1, 0) = 139;
  res(1, 1) = 154;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, mul_2) {
  int rows = 2;
  int cols = 3;

  S21Matrix m(rows, cols);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m(i, j) = c++;

  m *= 2;

  S21Matrix res(2, 3);
  res(0, 0) = 2;
  res(0, 1) = 4;
  res(0, 2) = 6;
  res(1, 0) = 8;
  res(1, 1) = 10;
  res(1, 2) = 12;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, mul_4) {
  int rows = 2;
  int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m(i, j) = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) n(i, j) = c++;

  m = m * n;

  S21Matrix res(2, 2);
  res(0, 0) = 58;
  res(0, 1) = 64;
  res(1, 0) = 139;
  res(1, 1) = 154;

  ASSERT_TRUE(m == res);
}

TEST(test_functional, mul_5) {
  int rows = 2;
  int cols = 3;

  S21Matrix m(rows, cols);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m(i, j) = c++;

  m = m * 2;

  S21Matrix res(2, 3);
  res(0, 0) = 2;
  res(0, 1) = 4;
  res(0, 2) = 6;
  res(1, 0) = 8;
  res(1, 1) = 10;
  res(1, 2) = 12;

  ASSERT_TRUE(m == res);
}

TEST(test_functional, mul_6) {
  int rows = 2;
  int cols = 3;

  S21Matrix m(rows, cols);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m(i, j) = c++;

  m = m * 2;

  S21Matrix res(2, 3);
  res(0, 0) = 2;
  res(0, 1) = 4;
  res(0, 2) = 6;
  res(1, 0) = 8;
  res(1, 1) = 10;
  res(1, 2) = 12;

  ASSERT_TRUE(m == res);
}

TEST(test_functional, mul_7) {
  S21Matrix m(2, 2);
  S21Matrix n(1, 2);

  EXPECT_ANY_THROW(m.MulMatrix(n));
}

TEST(test_functional, transpose) {
  int rows = 2;
  int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix res(cols, rows);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++, c++) {
      m(i, j) = c;
      res(j, i) = c;
    }

  m = m.Transpose();
  ASSERT_TRUE(m == res);
}

TEST(test_functional, determinant_0) {
  S21Matrix m(2, 3);

  EXPECT_ANY_THROW(m.Determinant());
}

TEST(test_functional, determinant_1) {
  int size = 5;
  S21Matrix m(5, 5);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m(i, j) = j;

  ASSERT_NEAR(0, m.Determinant(), 1e-06);
}

TEST(test_functional, determinant_2) {
  S21Matrix m(2, 2);

  m(0, 0) = -677700.0;
  m(0, 1) = 654.0;
  m(1, 0) = 2.0;
  m(1, 1) = -0.00001;

  double res = m.Determinant();
  ASSERT_NEAR(res, -1301.223, 1e-6);
}

TEST(test_functional, determinant_3) {
  double number = 0.0;
  S21Matrix m(8, 8);

  for (int x = 0; x < m.GetRows(); x += 1) {
    for (int y = 0; y < m.GetCols(); number += 1.0, y += 1) m(x, y) = number;
  }

  double res = m.Determinant();
  ASSERT_NEAR(res, 0, 1e-6);
}

TEST(test_functional, determinant_4) {
  int size = 2;
  S21Matrix m(size, size);

  m(0, 0) = -66;
  m(0, 1) = -754;
  m(1, 0) = -34643;
  m(1, 1) = -732363;

  double res = m.Determinant();
  ASSERT_NEAR(res, 22215136, 1e-6);
}

TEST(test_functional, complements_0) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;

  B(0, 0) = -3;
  B(0, 1) = 6;
  B(0, 2) = -3;
  B(1, 0) = 6;
  B(1, 1) = -12;
  B(1, 2) = 6;
  B(2, 0) = -3;
  B(2, 1) = 6;
  B(2, 2) = -3;

  S21Matrix res = A.CalcComplements();

  ASSERT_TRUE(res == B);
}

TEST(test_functional, complements_1) {
  S21Matrix m(1, 10);
  EXPECT_ANY_THROW(m.CalcComplements());
}

TEST(test_functional, complements_2) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);

  A(0, 0) = -1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 7.0;
  A(0, 3) = 9.0;
  A(1, 0) = 1.0;
  A(1, 1) = 0.0;
  A(1, 2) = 0.0;
  A(1, 3) = 0.0;
  A(2, 0) = 47.0;
  A(2, 1) = 13.0;
  A(2, 2) = 17.0;
  A(2, 3) = 21.0;
  A(3, 0) = 22.0;
  A(3, 1) = 7.0;
  A(3, 2) = 1.0;
  A(3, 3) = 3.0;

  B(0, 0) = 0.0;
  B(0, 1) = -30.0;
  B(0, 2) = -108.0;
  B(0, 3) = 106.0;
  B(1, 0) = 138.0;
  B(1, 1) = -726.0;
  B(1, 2) = -1137.0;
  B(1, 3) = 1061.0;
  B(2, 0) = 0.0;
  B(2, 1) = 12.0;
  B(2, 2) = 57.0;
  B(2, 3) = -47.0;
  B(3, 0) = 0.0;
  B(3, 1) = 6.0;
  B(3, 2) = -75.0;
  B(3, 3) = 57.0;

  S21Matrix res = A.CalcComplements();

  ASSERT_TRUE(res == B);
}

TEST(test_functional, complements_3) {
  int rows = 3;
  int cols = 3;

  S21Matrix A(rows, cols);
  S21Matrix B(rows, cols);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 1) = 4;
  A(1, 2) = 2;
  A(2, 0) = 5;
  A(2, 1) = 2;
  A(2, 2) = 1;

  B(0, 1) = 10;
  B(0, 2) = -20;
  B(1, 0) = 4;
  B(1, 1) = -14;
  B(1, 2) = 8;
  B(2, 0) = -8;
  B(2, 1) = -2;
  B(2, 2) = 4;

  S21Matrix res = A.CalcComplements();
  ASSERT_TRUE(res == B);
}

TEST(test_functional, complements_4) {
  int rows = 1;
  int cols = 1;

  S21Matrix A(rows, cols);
  S21Matrix B(rows, cols);

  A(0, 0) = 2;

  B(0, 0) = 1;

  S21Matrix res = A.CalcComplements();
  ASSERT_TRUE(res == B);
}

TEST(test_class, zero_size) { EXPECT_ANY_THROW(S21Matrix(0, 1)); }

TEST(test_functional, inverese_1) {
  int size = 3;
  S21Matrix A(size, size);
  S21Matrix B(size, size);
  B(0, 0) = 1.0;
  B(0, 1) = -1.0;
  B(0, 2) = 1.0;
  B(1, 0) = -38.0;
  B(1, 1) = 41.0;
  B(1, 2) = -34.0;
  B(2, 0) = 27.0;
  B(2, 1) = -29.0;
  B(2, 2) = 24.0;

  A(0, 0) = 2.0;
  A(0, 1) = 5.0;
  A(0, 2) = 7.0;
  A(1, 0) = 6.0;
  A(1, 1) = 3.0;
  A(1, 2) = 4.0;
  A(2, 0) = 5.0;
  A(2, 1) = -2.0;
  A(2, 2) = -3.0;

  ASSERT_TRUE(A.InverseMatrix() == B);
}

TEST(test_functional, inverese_2) {
  S21Matrix m(2, 3);
  EXPECT_ANY_THROW(m.InverseMatrix());

  S21Matrix n(2, 2);
  EXPECT_ANY_THROW(n.InverseMatrix());
}

TEST(test_functional, inverese_3) {
  S21Matrix m(1, 1);
  m(0, 0) = 69.420;
  double B = 1 / m(0, 0);
  double result = m.InverseMatrix()(0, 0);
  ASSERT_NEAR(B, result, 1e-06);
}

TEST(test_functional, inverese_4) {
  int size = 3;
  S21Matrix A(size, size);
  S21Matrix B(size, size);

  A(0, 0) = 2;
  A(0, 1) = 5;
  A(0, 2) = 7;
  A(1, 0) = 6;
  A(1, 1) = 3;
  A(1, 2) = 4;
  A(2, 0) = 5;
  A(2, 1) = -2;
  A(2, 2) = -3;

  B(0, 0) = 1;
  B(0, 1) = -1;
  B(0, 2) = 1;
  B(1, 0) = -38;
  B(1, 1) = 41;
  B(1, 2) = -34;
  B(2, 0) = 27;
  B(2, 1) = -29;
  B(2, 2) = 24;
  ASSERT_TRUE(A.InverseMatrix() == B);
}

TEST(test_functional, inverese_5) {
  int size = 3;
  S21Matrix A(size, size);
  S21Matrix B(size, size);

  A(0, 0) = 2;
  A(0, 1) = 5;
  A(0, 2) = 7;
  A(1, 0) = 6;
  A(1, 1) = 3;
  A(1, 2) = 4;
  A(2, 0) = 5;
  A(2, 1) = -2;
  A(2, 2) = -3;

  B(0, 0) = 1;
  B(0, 1) = -1;
  B(0, 2) = 1;
  B(1, 0) = -38;
  B(1, 1) = 41;
  B(1, 2) = -34;
  B(2, 0) = 27;
  B(2, 1) = -29;
  B(2, 2) = 24;
  ASSERT_TRUE(A.InverseMatrix() == B);
}

TEST(test_functional, index_0) {
  S21Matrix m(2, 3);
  EXPECT_ANY_THROW(m(-1, 0) = 1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
