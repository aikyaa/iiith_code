#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Matrix {
    int num_rows;
    int num_cols;
    long long int** data;
} Matrix;
Matrix* create_matrix(int r, int c) {
    Matrix* m = (Matrix*) malloc(sizeof(Matrix));
    m->num_rows = r;
    m->num_cols = c;
    m->data = (long long int**) calloc(r, sizeof(long long int*));
    for (int i =0; i < r; i++) {
        m->data[i] = (long long int*) calloc(c, sizeof(long long int));
    }
    return m;
}
void destroy_matrix(Matrix* m) {
    // 1: Write code here to free all memory used by the matrix stored in m
    for (int i =0; i < m->num_rows; i++) {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}
Matrix* add_matrix(Matrix* A, Matrix* B) {
// 2: write code here to add the matrices A and B and return a new matrix with the results.
// A, B should remain unmodified. If dimensions don't match, it should return NULL.
    if(A->num_cols!=B->num_cols || A->num_rows!=B->num_rows){
        printf("ERROR: INVALID ARGUMENT\n");
        return NULL;
    } else {
        Matrix* C=create_matrix(A->num_rows, A->num_cols);
        for(int i=0; i<A->num_rows; i++){
            for(int j=0; j<A->num_cols; j++){
                C->data[i][j]=A->data[i][j]+B->data[i][j];
            }
        }
        return C;
    }
}
Matrix* mult_matrix(Matrix* A, Matrix* B) {
// 3: write code here to multiply the matrices A and B and return a new matrix with the results.
// A, B should remain unmodified. If the dimensions don't match, it should return NULL.
    if(A->num_cols!=B->num_rows){
        printf("ERROR: INVALID ARGUMENT\n");
        return NULL;
    } else {
        Matrix* C=create_matrix(A->num_rows, B->num_cols);
        for(int i=0; i<A->num_rows; i++){
            for(int j=0; j<B->num_cols; j++){
                C->data[i][j]=0;
                for(int k=0; k<B->num_cols; k++){
                    C->data[i][j]+=A->data[i][k]*B->data[k][j];
                }
            }
        }
        return C;
    }
    }
Matrix* scalar_mult_matrix(long long int s, Matrix* M) {
// 4: write code here to multiply the matrix A with a scalar s and return a new matrix with the results.
// M should remain unmodified.
    Matrix* C=create_matrix(M->num_rows, M->num_cols);
    for(int i=0; i<M->num_rows; i++){
        for(int j=0; j<M->num_cols; j++){
            C->data[i][j]=s*(M->data[i][j]);
        }
    }
    return C;
}
Matrix* transpose_matrix(Matrix* A) {
// 5: write code here to find the transpose of given matrix A and return a new matrix with the results.
// A should remain unmodified.
    Matrix* C=create_matrix(A->num_rows, A->num_cols);
    for(int i=0; i<A->num_rows; i++){
        for(int j=0; j<A->num_cols; j++){
            C->data[j][i]=A->data[i][j];
        }
    }
    return C;
}
long long int determinant(Matrix* M) {
// 6: Write code here to calculate the determinant of the given matrix M (if not a square matrix, return -1).
// Return the determinant value.
    int determinantval;
    if (M->num_cols!=M->num_rows){
        printf("ERROR: INVALID ARGUMENT\n");
        return -1;
    }
    if(M->num_rows==2){
        return (M->data[0][0]*M->data[1][1])-(M->data[0][1]*M->data[1][0]);
    }
    else if(M->num_rows==1){
        return M->data[0][0];
    }
    else{
        Matrix* M1;
        M1=create_matrix(M->num_rows-1, M->num_cols-1);
        int crossed=0;
        for(int o=0;o<M->num_cols; o++){
            for(int m=1; m<M->num_rows; m++){
                for(int n=0;n<M->num_cols; n++){
                    if(n==o){
                        n++;
                        crossed=1;
                    } else {
                        if (crossed==0){
                            M1->data[m-1][n]=M->data[m][n];
                        } else{
                            M1->data[m-1][n]=M->data[m][n-1];
                        }
                    }
                }
            }
            if(M->num_cols%2==0){
                determinantval+=M->data[0][o]*determinant(M1);
            } else{
                determinantval-=M->data[0][o]*determinant(M1);
            }
        }
    return determinantval;
    }
}
// DO NOT MODIFY THE OUTPUT FORMAT of this function. Will be used for grading
void print_matrix(Matrix* m) {
    printf("%d %d\n", m->num_rows, m->num_cols);
    for (int i = 0; i < m->num_rows; i++) {
        for (int j = 0; j < m->num_cols; j++) {
            printf("%lld ", m->data[i][j]);
        }
        printf("\n");
    }
}
void scan_matrix(Matrix* m){
    int num_cols,num_rows;
    scanf("%d %d", num_rows, num_cols);
    create_matrix(num_rows, num_cols);
    for(int i=0; i<m->num_rows; i++){
        for(int j=0; j<m->num_cols; j++){
            scanf(" %lld", &m->data[i][j]);
        }
    }
}
Matrix* read_matrix_from_file(char* filename){
    Matrix* m;
    FILE* ptr;
    ptr=fopen(filename, "r");
    if (ptr==NULL) {
        printf("Unable to open file \n");
        return NULL;
    }
    int num_rows, num_cols;
    fscanf(ptr, "%d %d", num_rows, num_cols);
    m=create_matrix(num_rows, num_cols);
    for(int i=0; i<m->num_rows; i++){
        for(int j=0; j<m->num_cols; j++){
            fscanf(ptr, " %lld", &m->data[i][j]);
        }
    }
    fclose(ptr);
    return m;
}
void write_matrix_to_file(char* filename, Matrix* m){
    FILE* ptr;
    ptr=fopen(filename, "r");
    if (ptr==NULL) {
        printf("Unable to open file \n");
        return;
    }
    fprintf(ptr, "%d %d\n", m->num_rows, m->num_cols);
    for(int i=0; i<m->num_rows; i++){
        for(int j=0; j<m->num_cols; j++){
            fprintf(ptr, "%lld ", m->data[i][j]);
        }
    }
    fclose(ptr);
}