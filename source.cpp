// Author Ömer Alperen Kati
// Date 29/05/2020

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <math.h>
#include <stdlib.h>
using namespace std;

void mycounter(ifstream* fid, double* temp, int* counter) {
  /*
  This function counts the number of elements in Matrix A. It takes elements
  from the file one by one, and
  each time increments "size" by 1. If this operation fails, it
  doesn't increment and breaks
  the do-while loop. Finally, it closes the file.
  */
  do {
    *fid >> *temp;  // Every time, as a formality, stores the element in "*mult"
    if (!fid->fail()) {  // Tests if the operation fails. If it fails,
                         // take->fail() returns 1.
      (*counter)++;      // If it doesn't fail, "size" is
                         // incremented.
      // cout << size << endl;
      // system("pause");
    }
  } while (!fid->fail());
  fid->close();  // we close the file for now.
  //  cout << size << endl;
}

int opening_file_and_counting(void (*mycounter)(ifstream*, double*, int*),
                              char*& input_fileName, double* temp,
                              int* counter) {
  /*
  This function opens the file whose name is entered by user, and counts the
  number of elements in it.
  */
  ifstream fid(input_fileName);      // , and open it.
  if (!fid.is_open()) {              // If it can't opened
    system("pause");                 // we pause the code, and
    cout << "file doesn't exist!";   // inform the user.
    return 0;                        // For this case, it returns 0 to function.
  } else {                           // if it is opened,
    mycounter(&fid, temp, counter);  // we count the number of
                                     // elements in this file
                                     // to find the dimension
                                     // of Matrix A.
    return 1;  // And in order to inform that file is successfully opened, it
               // returns 1.
  }
}

void _2D_matrix_maker(int size, double** matrixA) {
  /*
  This function is specialized to convert an array one dimensional to 2D before
  storing Matrix A in it.
  */
  for (int i = 0; i < size; i++) {
    matrixA[i] = new double[size];
  }
}
void readMatrixA(char* input_fileName, int size, double** matrixA) {
  ifstream take1(input_fileName);  // opening the file
  for (int i = 0; i < size;
       (i)++) {  // nested 2 for loops for locating each element of Matrix A to
                 // correct locations.
    for (int j = 0; j < size; (j)++) {
      take1 >> matrixA[i][j];
    }
  }
  take1.close();  // closing the file again.
}

void power_iteration(double** matrixA, double* tol, double* x_new,
                     double* x_old, int size, double* lambda) {
  // Consecutive iterations for Eigenvalue#1 start here.
  double error;
  do {
    double largest_component;
    int index;
    for (int i = 0; i < size; (i)++) {
      x_new[i] =
          0;  // Firstly, we make sure each component is zero before filling it.
      for (int j = 0; j < size; (j)++) {
        x_new[i] += matrixA[i][j] * x_old[j];  // We are doing corresponding one
                                               // by one multiplications, and
                                               // collecting them in the right
                                               // place of resulting vector.
      }
      if (i == 0) {  // When we finish the first component,
        largest_component =
            x_new[0];  // we are assuming that it is the largest one.
        index = 0;     // Also index of it is saved.
      } else if (abs(largest_component) <
                 abs(x_new[i])) {  // After completing each element, it is
                                   // compared to the largest in magnitude until
                                   // now.
        largest_component = x_new[i];  // If the new one is bigger in magnitude,
                                       // it is substituted.
        index = i;                     // And also, its index is saved.
      }
      // The resulting component will be used below for calculating the
      // approximate eigenvalue after each iteration.
    }

    *lambda = largest_component / x_old[index];  // Approximate eigenvalue is
                                                 // found taking the ratio of
                                                 // the resulting largest
                                                 // component to the counterpart
                                                 // in previous vector.

    // Below, error is calculated after each iteration.
    error = 0;  // Firstly, it is refreshed to 0.
    for (int i = 0; i < size; (i)++) {
      error += pow(x_new[i] - (*lambda) * x_old[i],
                   2);  // Previous vector is multiplied with Eigenvalue#1, then
                        // the result is subtracted from new vector
      x_new[i] /= largest_component;  // Eigenvector is normalized by dividing
                                      // each element with the largest, and
                                      // ensured that the largest is 1 from now.
      x_old[i] = x_new[i];
    }
    error = sqrt(error);

  } while (error >= *tol);
  // Consecutive iterations for Eigenvalue#1 end here.
}

int main(int argc, char* argv[]) {
  int index, i, j, size = 0;
  double largest_component, error = 0, x_old_T_x = 0;
  double* temp = new double;  // This variable will be used while reading the
                              // matrix just for counting number of elements,
  double* lambda = new double;

  int* counter =
      new int;   // and *counter will be incremented for each element counted,
  *counter = 0;  //*counter is started from 0.

  // Memories for command line arguments are allocated.
  char* input_filename = new char[1];
  double* tol = new double;
  char* output_file = new char[1];
  // Memories for command line arguments are allocated.

  // Command line arguments are assigned.
  input_filename = argv[1];
  *tol = strtod(argv[2], NULL);
  output_file = argv[3];
  // Command line arguments are assigned.

  i = opening_file_and_counting(
      mycounter, input_filename, temp,
      counter);  // we open the file of Matrix A, and count the
                 // number of elements in it.
  if (i == 0) {  // By the way, we return a value to notice whether opening is
                 // successful.
    return 0;    // If it is not, program is terminated.
  }

  size = sqrt(*counter);

  double** matrixA = new double*[size];  // by using the size, we
                                         // declare an array, and
  _2D_matrix_maker(
      size,
      matrixA);  // we convert this one dimensional array to a 2D one.

  readMatrixA(input_filename, size,
              matrixA);  // operation of reading and storing Matrix A.

  // Since we know what the size is, we can allocate memory for vectors going to
  // be used.
  double* x_old = new double[size];
  double* x_new = new double[size];
  // Since we know what the size is, we can allocate memory for vectors going to
  // be used.

  // As algorithm suggests, we can start with an arbitrary vector.
  for (i = 0; i < size; (i)++) {
    x_old[i] = 1;  // Why don't all components are 1?
  }
  // As algorithm suggests, we can start with an arbitrary vector.

  power_iteration(matrixA, tol, x_new, x_old, size, lambda);

  x_old_T_x = 0;
  for (i = 0; i < size; (i)++) {
    x_old_T_x += pow(
        x_old[i], 2);  // eigenvector tranpose times eigenvector is calculated.
  }

  for (i = 0; i < size; (i)++) {
    for (j = 0; j < size; (j)++) {
      matrixA[i][j] -= (*lambda) * x_old[i] * x_old[j] /
                       x_old_T_x;  // Deflation method is executed
    }
  }

  ofstream outputFile(output_file);  // We start the output stream.
  outputFile << "Eigenvalue#1: " << *lambda
             << endl;  // Eigenvalue#1 is written into text file.

  for (i = 0; i < size; (i)++) {
    outputFile << x_old[i] << endl;  // And also, corresponding eigenvector is
                                     // written element by element.
    x_old[i] = 1;
  }

  power_iteration(matrixA, tol, x_new, x_old, size, lambda);

  outputFile << "Eigenvalue#2: " << *lambda
             << endl;  // Eigenvalue#2 is written into text file.
  outputFile.close();  // After writing is completed, output file is closed.
  for (i = 0; i < size; i++) {
    delete[] matrixA[i];
  }
  delete[] x_old, x_new, input_filename, output_file;
  delete temp, lambda, counter, tol;
  return 1;
}
