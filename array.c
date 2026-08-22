#include <stdio.h>
void print_array(int arr[],int size){
    puts("Array Value are : ");
    for(int i = 0 ; i<size; i++){
        printf("%d\t",arr[i]);
    }
}
void Scan_array(int arr[],int size){
    puts("Enter array Values ");
    for(int i = 0 ; i<size ; i++){
        scanf("%d",&arr[i]);
    }

}