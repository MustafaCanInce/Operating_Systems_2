// Adem VAROL
// Mustafa Can İNCE
#include <stdio.h>
#include <pthread.h>
int rA, cA, rB, cB, i, j, k, c, flag = 1, matrixA[10][10], matrixB[10][10], matrixAB[10][10];

void *readA(void *fnA)
{
    FILE *p = NULL;
    // Checking the existence of the first martix file.
    if ((p = fopen(fnA, "r")) == NULL) // The file opens in read mode.
    {
        // If there is no first martix;
        flag = 0;
        printf("First file (%s) not found!!!\n", (char *)fnA);
        return 0;
    }
    else
    {
        // If there is first martix;
        if (flag == 1)
        {
            fscanf(p, "%d", &rA); // The first element in the file is assigned as the row number (rA) of the first matrix.
            fscanf(p, "%d", &cA); // The second element in the file is assigned as the column number (cA) of the first matrix.

            // Elements as many as the number of rows and columns of the first input matrix are added into the defined matrixA (10x10).
            for (i = 0; i < rA; i++)
            {
                for (j = 0; j < cA; j++)
                {
                    fscanf(p, "%d", &matrixA[i][j]);
                }
            }
            fclose(p); // The file has been closed.
            pthread_exit(0);
        }
    }
}

void *readB(void *fnB)
{
    FILE *p = NULL;
    // Checking the existence of the second martix file.
    if ((p = fopen(fnB, "r")) == NULL) // The file opens in read mode.
    {
        // If there is no second martix;
        flag = 0;
        printf("Second file (%s) not found!!!\n", (char *)fnB);
        return 0;
    }
    else
    {
        // If there is second martix;
        if (flag == 1)
        {
            fscanf(p, "%d", &rB); // The first element in the file is assigned as the row number (rB) of the second matrix.
            fscanf(p, "%d", &cB); // The second element in the file is assigned as the column number (cB) of the second matrix.

            if (cA != rB) // Checking whether the matrices have been multiplied.
            {
                flag = 0;
                printf("The number of columns in matrix A is not equal to the number of rows in matrix B.\nThese matrices cannot be multiplied.\n");
                return 0;
            }
            // Elements as many as the number of rows and columns of the second input matrix are added into the defined matrixB (10x10).
            for (i = 0; i < rB; i++)
            {
                for (j = 0; j < cB; j++)
                {
                    fscanf(p, "%d", &matrixB[i][j]);
                }
            }
            fclose(p); // The file has been closed.
            pthread_exit(0);
        }
    }
}

void printMatrixA()
{
    // Each element of matrix A is printed on the screen.
    for (i = 0; i < rA; i++)
    {
        printf("%s", (i == 0 ? "  A = |" : "      |")); // Corrects shifts in the screen output by printing "  A = |" if line number is 0, "      |" otherwise.
        for (j = 0; j < cA; j++)
        {
            // printf("%d ", matrixA[i][j]);
            // One, two digit and negative numbers are written as three digits with the ternary operator.
            int ss = matrixA[i][j];
            ss / 10 == 0 ? (ss < 0 ? printf("  %d", ss) : printf("   %d", ss)) : (ss / 100 == 0 ? (ss < 0 ? printf(" %d", ss) : printf("  %d", ss)) : printf(" %d", ss));
        }
        printf("|\n");
    }
}

void printMatrixB()
{
    // Each element of matrix B is printed on the screen.
    for (i = 0; i < rB; i++)
    {
        printf("%s", (i == 0 ? "  B = |" : "      |"));
        for (j = 0; j < cB; j++)
        {
            // printf("%d ", matrixB[i][j]);
            // One, two digit and negative numbers are written as three digits with the ternary operator.
            int ss = matrixB[i][j];
            ss / 10 == 0 ? (ss < 0 ? printf("  %d", ss) : printf("   %d", ss)) : (ss / 100 == 0 ? (ss < 0 ? printf(" %d", ss) : printf("  %d", ss)) : printf(" %d", ss));
        }
        printf("|\n");
    }
}

void *productMatrix()
{
    // The A and B matrices are multiplied.
    for (i = 0; i < rA; i++)
    {
        for (j = 0; j < cB; j++)
        {
            for (k = 0; k < rB; k++)
            {
                matrixAB[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    pthread_exit(0);
}

void printMatrixAB()
{
    // Each element of matrix (A.B) is printed on the screen.
    for (i = 0; i < rA; i++)
    {
        printf("%s", (i == 0 ? "A.B = |" : "      |"));
        for (j = 0; j < cB; j++)
        {
            // printf("%d\t", matrixAB[i][j]);
            int ss = matrixAB[i][j];
            // One, two digit and negative numbers are written as three digits with the ternary operator.
            ss / 10 == 0 ? (ss < 0 ? printf("  %d", ss) : printf("   %d", ss)) : (ss / 100 == 0 ? (ss < 0 ? printf(" %d", ss) : printf("  %d", ss)) : printf(" %d", ss));
        }
        printf("|\n");
    }
}

int main(int argc, char *argv[])
{
    printf("\n");
    if (argc != 4) // Checking number of arguments
    {
        printf("Please include three filenames.\nUsage Example: ./hw1 <arg1> <arg2> <arg3>\n");
    }
    else
    {
        // Creating thread1
        pthread_t thread1;
        pthread_create(&thread1, NULL, readA, (void *)argv[1]);
        pthread_join(thread1, NULL);

        // Creating thread2
        pthread_t thread2;
        pthread_create(&thread2, NULL, readB, (void *)argv[2]);
        pthread_join(thread2, NULL);

        // If there are files, if the number of arguments is sufficient, if the multiplication condition is meting;
        if (flag == 1)
        {
            printMatrixA(); // First matrix is printed to the screen
            printf("\n");

            printMatrixB(); // Second matrix is printed to the screen
            printf("\n");

            // Creating thread3
            pthread_t thread3;
            pthread_create(&thread3, NULL, productMatrix, NULL);
            pthread_join(thread3, NULL);

            printMatrixAB(); // The product matrix is printed on the screen

            // A file named 'argv[3]' is created and the product matrix is written into it.
            FILE *p;
            p = fopen(argv[3], "w"); // The file opens in write mode.

            // The row number of matrix A and column number of matrix B are printed to the output file.
            fprintf(p, "%d %d\n", rA, cB);

            // Each element of the product matrix is printed to the file.
            for (i = 0; i < rA; i++)
            {
                for (j = 0; j < cB; j++)
                {
                    fprintf(p, "%d ", matrixAB[i][j]);
                }
                fprintf(p, "\n");
            }
            fclose(p); // The file has been closed.
        }
    }
    printf("\n");
    return 0;
}