#include <iostream>
#include <chrono>

using namespace std;

void printArray(int inArray[], int size){
    for (int c=0;c<size;c++){
        cout << inArray[c] << " ";
    }
    cout << endl;
    
}

int* selectionSort(int inArray[], int size){
    for (int i=0; i<size; i++){
        for (int j=i+1; j<size; j++){
            if (inArray[j] < inArray[i]){
                int temp = inArray[i];
                inArray[i] = inArray[j];
                inArray[j] = temp;
            }
        }
    }
    return inArray;
}

int* bubbleSort(int inArray[], int size){
    for (int i=1; i<size; i++){
        for (int j=0; j<size-1; j++){
            if (inArray[j] > inArray[j+1]){
                int temp = inArray[j+1];
                inArray[j+1] = inArray[j];
                inArray[j] = temp;
            }
        }
    }
    return inArray;
}

int* insertionSort(int inArray[], int size){
    for (int i=1; i<=size-1; i++){
        int j = i;
        while (j>0 && inArray[j-1] > inArray[j]){
            int temp = inArray[j];
            inArray[j] = inArray[j-1];
            inArray[j-1] = temp;

            j = j-1;
        }
    }
    return inArray;
}

int* shellSort(int inArray[], int size){
    for (int gap = size/2; gap>0; gap/=2){
        for (int i=gap; i<size; i++){
            int temp = inArray[i];
            int j;
            for (j=i; j>=gap && inArray[j-gap]>temp; j-=gap)
            inArray[j] = inArray[j-gap];
            inArray[j] = temp;
        }
    }
    return inArray;
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];


    int i = 0;     
    int j = 0;     
    int k = left;  

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

int* mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);

        return arr;
    }
}

void quickSort(int inArray[], int size){

}

void heapSort(int inArray[], int size){

}

int main(){
    int size = 500;
    int myArray[size];
    for (int c=0;c<size;c++){
        myArray[c] = rand()%100;
    }


    cout << "Original array: ";
    printArray(myArray, size);
    

    //STARTS TIMER --------------------------------------------------------------------------------------------------
    auto tStart = chrono::high_resolution_clock::now();
    cout << "-- Timer start --" << endl;
    //---------------------------------------------------------------------------------------------------------------
    
    int* sorted = mergeSort(myArray, 0, size-1);

    //STOPS TIMER AND STORES ELAPSED TIME ---------------------------------------------------------------------------
    auto tStop = chrono::high_resolution_clock::now();
    cout << "-- Timer stop --" << endl;
    auto timeTaken = chrono::duration_cast<chrono::milliseconds>(tStop - tStart);
    //---------------------------------------------------------------------------------------------------------------

    cout << "Sorted array: ";
    //printArray(sorted, size);
    printArray(myArray, size);

    //prints time elapsed
    cout << "Time elapsed: " << timeTaken.count() << " ms" << endl;

    return 0;
}