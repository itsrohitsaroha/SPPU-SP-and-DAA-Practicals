#include <stdio.h>
#include <stdlib.h>

void return_maxmin(int *array, int i, int j, int *max, int *min){
	
	int mid, max1, min1;

	if(i == j){
		*max = *min = array[i];
	}
	else{
		mid = (i+j)/2;
		return_maxmin(array, i, mid, max, min);
		max1 = *max;
		min1 = *min;
		return_maxmin(array, mid+1, j, max, min);
		if(*max < max1){
			*max = max1;
		}
		if(*min > min1){
			*min = min1;
		}
	}
}

int main(){
	
	int size_of_array, min, max;
	printf("Enter the Size of array: ");
	scanf("%d", &size_of_array);

	int *array = (int *)malloc(sizeof(int)*size_of_array);
	printf("Elements: ");
	for(int i = 0 ; i < size_of_array ; i++){
		scanf("%d", &array[i]);
	}

	return_maxmin(array, 0, size_of_array-1, &max, &min);

	printf("\nMinimum Element of array is :%d \n Maximum Element of array is:%d\n \n", min, max);

	free(array);
	return 0;
}
