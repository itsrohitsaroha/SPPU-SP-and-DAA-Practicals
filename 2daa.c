#include<stdio.h>
#include<stdlib.h>

struct single_job{
	int job_id;
	int running_time;
};

void printList(struct single_job a[], int length){

	printf("\n\n%-15s%-15s%-15s\n", "Job Id", "Length", "Retrieval Time");
	int previous_sum = 0, total = 0;

	for(int i = 0 ; i < length ; i++ ){

		previous_sum = a[i].running_time + previous_sum;
		total = total+previous_sum;

		printf("%-15d%-15d%-15d\n", a[i].job_id, a[i].running_time, previous_sum);

	}

	printf("\nRETRIEVAL TIME AVERAGE: %.2f\n\n", (float)total/length);
}

void merge(struct single_job *a, int start, int mid, int end){

	int i, j, k, temp;
	int n1 = mid-start+1;
	int n2 = end-mid;

	struct single_job left[n1], right[n2];

	for(int i = 0, temp = start; i < n1 ; i++, temp++){
		left[i].job_id = a[temp].job_id;
		left[i].running_time = a[temp].running_time;
	}
	for(int i = 0, temp = mid+1; i < n2 ; i++, temp++){
		right[i].job_id = a[temp].job_id;
		right[i].running_time = a[temp].running_time;
	}

	i = 0, j = 0, k = start;
	do{
		if(left[i].running_time <= right[j].running_time){
			a[k].job_id = left[i].job_id;
			a[k++].running_time = left[i++].running_time;
		}
		else{
			a[k].job_id = right[j].job_id;
			a[k++].running_time = right[j++].running_time;
		}		
	}while(i < n1 && j < n2);

	while(i < n1){
			a[k].job_id = left[i].job_id;
			a[k++].running_time = left[i++].running_time;
	}

	while(j < n2){
			a[k].job_id = right[j].job_id;
			a[k++].running_time = right[j++].running_time;
	}
}

void mergeSort(struct single_job *a, int start, int end){
	if(start < end){
		int mid = (start+end)/2;
		mergeSort(a, start, mid);
		mergeSort(a, mid+1, end);
		merge(a, start, mid, end);
	}
}

int main(){

	int length;
	printf("%s", "Enter the total number of jobs: ");
	scanf("%d", &length);

	struct single_job *job_list=(struct single_job *)malloc(sizeof(struct single_job)*length);

	for(int i = 0 ; i < length ; i++){
		job_list[i].job_id = i+1;
		printf("Enter  Length of Job %d: ", i+1);
		scanf("%d", &job_list[i].running_time);
	}

	mergeSort(job_list, 0, length-1);

	printList(job_list, length);

	free(job_list);

	return 0;
}
