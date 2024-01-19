#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HISTORY 100
void add_history(char history[100][30], char* command){
    for(int i=99; i>=0; i--){
        strcpy(history[i], history[i - 1]);
    } 
    strcpy(history[0], command);
}
void print_history(char history[100][30]){
    for(int i=0; i<100; i++){
        if(strlen(history[i])==0){
            break;
        } else{
            printf("%s\n", history[i]);
        }
    }
}
int main() {
    int num_commands;
    scanf("%d", &num_commands);
    char history[100][30]={""};
    char commands[5][19]={"add_matrix", "mult_matrix", "scalar_mult_matrix", "transpose_matrix", "determinant"};
    for(int z=0; z<num_commands; z++){
        char command[19];
        int tail;
        scanf("%[^ ]%*c %d", command, &tail);
        Matrix* m1;
        Matrix* m2;
        long long int s;
        if (tail==0){
            if(strcmp(commands[0],command)==0){
                scan_matrix(m1);
                scan_matrix(m2);
                print_matrix(add_matrix(m1,m2));
            }
            else if(strcmp(commands[1],command)==0){
                scan_matrix(m1);
                scan_matrix(m2);
                print_matrix(mult_matrix(m1,m2));
            }
            else if(strcmp(commands[2],command)==0){
                scanf("%lld", &s);
                scan_matrix(m1);
                print_matrix(scalar_mult_matrix(s,m1));
            }
            else if(strcmp(command, commands[3])==0){
                scan_matrix(m1);
                print_matrix(transpose_matrix(m1));
            }
            else if(strcmp(commands[4], command)==0){
                scan_matrix(m1);
                printf("%lld", determinant(m1));
            }
            destroy_matrix(m1);
            destroy_matrix(m2);
        } 
        else if(tail==1){
            char filename1[50];
            char filename2[50];
            char outputfile[50];
            if(strcmp(commands[0],command)==0){
                scanf("%s", filename1);
                scanf("%s", filename2);
                scanf("%s", outputfile);
                m1=read_matrix_from_file(filename1);
                m2=read_matrix_from_file(filename2);
                write_matrix_to_file(add_matrix(m1,m2),outputfile);
            }
            else if(strcmp(commands[1],command)==0){
                scanf("%s", filename1);
                scanf("%s", filename2);
                scanf("%s", outputfile);
                m1=read_matrix_from_file(filename1);
                m2=read_matrix_from_file(filename2);
                write_matrix_to_file(mult_matrix(m1,m2),outputfile);
            }
            else if(strcmp(commands[2],command)==0){
                scanf("%s", filename1);
                scanf("%s", outputfile);
                scanf("%lld", &s);
                m1=read_matrix_from_file(filename1);
                write_matrix_to_file(scalar_mult_matrix(s,m1),outputfile);
            }
            else if(strcmp(command, commands[3])==0){
                scanf("%s", filename1);
                scanf("%s", outputfile);
                m1=read_matrix_from_file(filename1);
                write_matrix_to_file(transpose_matrix(m1), outputfile);
            }
            else if(strcmp(commands[4], command)==0){
                scanf("%s", filename1);
                scanf("%s", outputfile);
                m1=read_matrix_from_file(filename1);
                FILE* ptr;
                ptr=fopen(filename1, "r");
                if (ptr==NULL) {
                    printf("Unable to open file \n");
                    return;
                }
                fprintf(ptr, "lld", determinant(m1));
                fclose(ptr);
            }
            destroy_matrix(m1);
            destroy_matrix(m2);
        }
        if (strcmp(command,"history")==0){
            print_history(history);
        }
}
return 0;
}
