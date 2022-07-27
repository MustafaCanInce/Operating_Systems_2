# Operating Systems Assigments

## 0)
 Our C codes were built, compiled and run with 'Ubuntu 21.10 GNM 40.4.0_64-bit' and macOS Monterey 12.1.

## 1)
 We checked if the number of arguments in the main method is 4.

## 2)
 In the "readA(void *fnA)" method, we opened the file named "argv[1]" in read mode with the command "fopen(<filename>, 'r')". We have assigned the first element in the file as the row number ["fscanf(p, "%d", &rA)"] of matrix A , and the second element as the column number ["fscanf(p, "%d", &cA)"] of matrix A. We have assigned the remaining elements in the file to the appropriate fields in the matrixA[10][10] multidimensional array, which we have defined globally before. We have closed this file [fclose(p)];

## 3)
 In the "readB(void *fnB)" method, we opened the file named "argv[2]" in read mode with the command "fopen(<filename>, 'r')". We have assigned the first element as the row number ["fscanf(p, "%d", &rB)"] of matrix B and the second element as the column number ["fscanf(p, "%d", &cB)"] of matrix B. We assigned the remaining elements in the file to the appropriate fields in the matrixB[10][10] multidimensional array, which we defined as global before. We closed this file [fclose(p);].

## 4)
 If there are no files named argv[1] and argv[2], if the number of arguments is not enough or the multiply condition is not met, we have assigned the value 0 to the variable "flag" in our code. We ensured that if the "flag" variable is 0, the program exits, and if it is 1, the necessary actions are performed.

## 5)
 If the multiplication condition is met, we have multiplied the A and B matrices in the productMatrix() method and assigned them to the appropriate fields in the matrixAB[10][10] multidimensional array, which we have defined as global.

## 6)
 In order to better understand the output of our codes, we ensured that each element of the matrices related to the printing methods [printMatrixA(), printMatrixB() and printMatrixAB()] is printed on the screen.

## 7)
 We created a file named "argv[3]" in the main method and opened the file in write mode with the command "fopen(<filename>, 'w')". Into this file, enter the number of rows of matrix A, the number of columns of matrix B [fprintf(p, "%d %d\n", rA, cB);] and each element of matrix A.B [fprintf(p, "%d ", matrixAB[]. i][j]);].
