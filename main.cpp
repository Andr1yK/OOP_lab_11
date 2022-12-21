#include <iostream>
#include "cmath"
#include "array"

using namespace std;

class Base {
  public:
    virtual double norm() = 0;
};

class ComplexNumber: public Base {
  private:
    int real;
    int i;

  public:
    ComplexNumber(int real, int i) : real(real), i(i) {}

    double norm() override {
      return pow(abs(real), 2);
    }
};

class Vector: public Base {
  private:
    array<int, 10> l;

  public:
    explicit Vector(const array<int, 10> &l) : l(l) {}

    double norm() override {
      int sum = 0;

      for_each(
          l.begin(),
          l.end(),
          [&sum](int n) { sum += n * n; }
      );

      return sqrt(sum);
    }
};

class Matrix: public Base {
  private:
    array<array<int, 2>, 2> matrix;

  public:
    explicit Matrix(array<array<int, 2>, 2> &matrix) : matrix(matrix) {}

    double norm() override {
      int max = abs(matrix[0][0]);

      for (array<int, 2> row : matrix) {
        for (int item: row) {
          max = max < abs(item)
            ? abs(item)
            : max;
        }
      }

      return max;
    }
};

int main() {
  array<array<int, 2>, 2> arr{5, -7, -3, -4};
  Base* items[3] = {
    new Matrix{arr}, // norm = 7
    new Vector{{1,2,3,4,5,6,7,8,9,10}}, // norm ≈ 19.6214
    new ComplexNumber{-10, 2} // norm = 100
  };

  for (Base* item : items) {
    cout << typeid(*item).name()
      << " -> " << typeid(item).name()
      << " -> " << item->norm()
      << endl;
  }

  return 0;
}
