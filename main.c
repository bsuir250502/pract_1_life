#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define string_size 256

FILE *open_file(char*file,char*code)
{
    FILE*f;
    if(!(f = fopen(file,code))){
        puts("Error!");
        exit(1);
    }
    else return f;
}

int input_data(FILE * input)
{
    int number;
    char input_buffer[string_size];
    fgets(input_buffer, string_size, input);
    number = strtol(input_buffer, NULL, 10);
    return number;
}

void input_file(FILE * input, int **initial_matrix, int line, int columns)
{
    int i, j;
    for (i = 0; i < line; i++) {
        for (j = 0; j < columns; j++) {
            initial_matrix[i][j] = getc(input) - '0';
        }
        getc(input);
    }
}

int initialization_matrix(int**matrix, int line)
{
    int i;
    for(i = 0; i < line; i++) {
        matrix[i] = (int *) calloc(line, sizeof(int));
    }
    return 0;
}

int location_of_point (int i, int j, int line, int columns, int** initial_matrix)
{
    if (i < 0) 
        i = line - 1;
    if (j < 0)
        j =  columns - 1;
    if (i > line - 1)
        i = 0;
    if (j > columns - 1)
        j= 0;
    if (initial_matrix[i][j] == 1)
        return 1;
    else return 0;
}

void filling_matrix(int **finite_matrix, int  **initial_matrix, int columns, int line, int i, int j, int number_of_units)
{
    if ((number_of_units == 3) || (initial_matrix[i][j] && number_of_units == 2)) {
        finite_matrix[i][j] = 1;
    } else
        finite_matrix[i][j] = 0;
}

void overwrite_file(int **initial_matrix, int **finite_matrix, int line,int columns)
{
    int i, j;
    for (i = 0; i < line; i++) {
        for (j = 0; j < columns; j++) {
            initial_matrix[i][j] = finite_matrix[i][j];
        }
    }
}

void second_generation(int **initial_matrix, int **finite_matrix, int columns, int line)
{
    int i,j;
    int flag, number_of_units=0;
    for(i = 0; i < line; i ++) {
        for(j = 0; j < columns; j++) {
            flag = location_of_point(i, j + 1, line, columns, initial_matrix);
            if(flag == 1)
                number_of_units ++;
            flag = location_of_point(i + 1, j + 1, line, columns, initial_matrix);
            if(flag == 1)
                number_of_units ++;
            flag = location_of_point(i + 1, j, line, columns, initial_matrix);
            if(flag == 1)
                number_of_units ++;
            flag = location_of_point(i + 1, j - 1, line, columns, initial_matrix);
            if(flag == 1)
                number_of_units ++;
            flag = location_of_point(i , j - 1, line, columns, initial_matrix);
            if(flag == 1)
                number_of_units ++;
            flag = location_of_point(i - 1, j - 1, line, columns, initial_matrix);
            if(flag == 1)
                number_of_units ++;
            flag = location_of_point(i - 1, j, line, columns, initial_matrix);
            if(flag == 1)
                number_of_units ++;
            flag = location_of_point(i - 1, j + 1, line, columns, initial_matrix);
            if(flag == 1)
                number_of_units ++; 
            filling_matrix(finite_matrix,initial_matrix,columns,line,i,j,number_of_units);
            number_of_units = 0;
        }
    }
}



void output_field(int **initial_matrix, int line, int columns)
{
    int i, j;
    for (i = 0; i < line; i++) {
        printf("\n");
        for (j = 0; j < columns; j++) {
            if (initial_matrix[i][j])
                printf("*");
            else
                printf(" ");
        }
    }
}
int main(int argc, char* argv[])
{
    FILE *input, *output;
    int columns, line, number_of_generations, i = 0;
    int **initial_matrix, **finite_matrix;
    input = open_file("input","r");
    output = open_file("output","w");
    line = input_data(input);
    columns = input_data(input);
    number_of_generations = input_data(input);
    initial_matrix = (int **) calloc(line, sizeof(int*));
    initialization_matrix(initial_matrix, line);
    input_file(input, initial_matrix, line, columns);
    output_field( initial_matrix,line,columns);
    finite_matrix = (int **) calloc(columns, sizeof(int*));
    initialization_matrix(finite_matrix, line);
    while(i != number_of_generations) {
        second_generation(initial_matrix, finite_matrix, columns, line);            
        output_field(finite_matrix, line,columns);
        Sleep(800);
        system("cls");
        overwrite_file(initial_matrix, finite_matrix, line,columns);
        i++;
    }
    return 0;
}