#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool check(int row, int col, int *arr){
    int i;
    for(i = 0; i < row; i++){
        if(arr[i] == col || (abs(arr[i] - col) == abs(i - row))){
            return 0;
        }
    }
    return 1;
}

void print(int n, int *arr)
{
	for(int i = 0; i < 2 * n; i++)
        printf("--");
    printf("-");
    printf("\n");
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
            if(j == arr[i])
                printf("| %c ", 'Q');
            else
                printf("| %c ", '*');
        }
        printf("|");
        printf("\n");
        for(int j = 0; j < 2 * n; j++)
            printf("--");
        printf("-\n");
	}
}

//Recursive solution to N Queen problem.
void recursivenq(int n, int arr[], int no, int row, bool *f, int *cnt){
    if(no == 1 && (*f) == 1)
        return;
    for(int i = 0; i < n; i++){
        arr[row] = i;
        if(check(row, arr[row], arr)){
            if(row == n - 1){
                (*cnt)++;
                printf("\nSolution %d : \n", (*cnt));
                print(n, arr);
                (*f) = 1;
            }
            else
                recursivenq(n, arr, no, row + 1, f, cnt);
        }
    }
}

//Iterative solution to N Queen problem.
void iterativenq(int n, int *arr, int no, int *cnt){
	int i, j, row = 0;
    for(i = 0; i < n; i++)
		arr[i] = -1;

	while(row != -1){
		arr[row] += 1;
		if(arr[row] < n){
			if(check(row, arr[row], arr)){
				if(row == n - 1){
					printf("\nSolution %d :\n", ++(*cnt));
					print(n, arr);
						if(no == 1)
							return;
				}
				else
					row++;
			}
		}
		else{
            arr[row] = -1;
            row--;
        }
	}
	free(arr);
}

int main(){
    int n, cnt, ch, *arr;
    do{
        cnt = 0;
        printf("\n\t\t\t\tN Queen Problem");
        printf("\n\t\t\t\t---------------\n");
        printf("\nEnter the size of board : ");
        scanf("%d", &n);
        arr = (int*)malloc(sizeof(int) * n);
        for(int i = 0; i < n; i++){
            arr[i] = -1;
        }
        printf("\nEnter : 1. Iterative solution");
        printf("\n        2. Recursive solution");
        printf("\nChoice : ");
        scanf("%d", &ch);

        switch(ch){
            case 1: {
                int ch1;
                printf("\nEnter : 1. One solution");
                printf("\n        2. Many solution");
                printf("\nChoice : ");
                scanf("%d", &ch1);
                if(ch1 == 1){
                    if(n < 4){
                        printf("\nSolution not possible.");
                    }
                    else
                        iterativenq(n, arr, 1, &cnt);
                }
                else{
                    if(n < 4){
                        printf("\nSolution not possible.");
                    }
                    else{
                        iterativenq(n, arr, 0, &cnt);
                        printf("\nTotal number of solutions = %d", cnt);
                    }

                }
                break;
            }
            case 2: {
                int ch1;
                printf("\nEnter : 1. One solution");
                printf("\n        2. Many solution");
                printf("\nChoice : ");
                scanf("%d", &ch1);
                bool f = 0;
                if(ch1 == 1){
                    if(n < 4){
                        printf("\nSolution not possible.");
                    }
                    else{
                        recursivenq(n, arr, 1, 0, &f, &cnt);
                    }

                }
                else{
                    if(n < 4){
                        printf("\nSolution not possible.");
                    }
                    else{
                        recursivenq(n, arr, 0, 0, &f, &cnt);
                        printf("\nTotal number of solutions = %d", cnt);
                    }
                }
                break;
                free(arr);
            }
            default: break;
        }
    }
    while(1);

    return 0;
}

