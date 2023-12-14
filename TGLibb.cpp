#include <iostream>
#include <chrono>

using namespace std;

void printArray(int inArray[], int size){
    for (int c=0;c<size;c++){
        cout << inArray[c] << " ";
    }
    cout << endl;
    
}

//Busca el valor mas pequeño desde el principio y lo reubica al principio, avanzando hasta reubicar todo el arreglo
int* selectionSort(int inArray[], int size){
    for (int i=0; i<size; i++){
        for (int j=i+1; j<size; j++){
            if (inArray[j] < inArray[i]){
                int temp = inArray[i];
                inArray[i], inArray[j];
                inArray[j] = temp;
            }
        }
    }
    return inArray;
}

//Avanza por el arreglo por pares, reubicando al menor del par a la izq. y al mayor a la der.
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

//Avanza por el arreglo desde el principio, ordenando cada valor a medida que lo recorre
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

//Similar a insertion, pero empieza usando un gap de n, con el cual compara y ordena valores adyacentes en n espacios, el gap se 
//reduce con cada iteración hasta 1, donde itera por una ultima vez de forma idéntica a insertion.
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

//Divide el arreglo en mitades cada vez mas pequeñas, luego los junta mitad por mitad mientras los ordena hasta volver al tamaño del arreglo original
//- mergesort(array, 0, size-1)
int* mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);

        return arr;
    }
}

int partition(int inArray[], int low, int high){
    int i = low-1;
    int pivot = inArray[high];

    for (int j=low; j < high; j++){
        if (inArray[j] <= pivot){
            i++;
            int temp = inArray[i];
            inArray[i] = inArray[j];
            inArray[j] = temp;
        }
    }

    int temp = inArray[i+1];
    inArray[i+1] = inArray[high];
    inArray[high] = temp;

    return i+1;
}

//Elige un pivote y lo mueve al final, luego busca el primer valor desde el principio mayor al pivote, y el primer valor menor desde el final (excluyendo el pivote)
//Una vez ordenados, se elige otro pivote y se repite el proceso
//- quickSort(array, 0, size-1)
void quickSort(int inArray[], int low, int high){
    if (low < high){
        //divide el array y obtiene un pivote
        int pivot_index = partition(inArray, low, high);

        //ordena recursivamente los subarreglos de antes y despues del pivote
        quickSort(inArray, low, pivot_index-1);
        quickSort(inArray, pivot_index+1, high);
    }
}

void heapify(int inArray[], int n, int i){
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if (left < n && inArray[left] > inArray[largest]){
        largest = left;
    }

    if (right < n && inArray[right] > inArray[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = inArray[i];
        inArray[i] = inArray[largest];
        inArray[largest] = temp;

        heapify(inArray, n, largest);
    }
}

void heapSort(int inArray[], int size){
    int s = size;
    
    for (int i=(s/2)-1; i>=0; i--){
        heapify(inArray, s, i);
    }

    for (int i=s-1; i>=0; i--) {
        int temp = inArray[0];
        inArray[0] = inArray[i];
        inArray[i] = temp;

        heapify(inArray, i, 0);
    }
}

int main(){
    int size = 500;
    int myArray[size];
    for (int c=0;c<size;c++){
        myArray[c] = rand()%100;
    }


    cout << "Original array: ";
    printArray(myArray, size);
    

    //EMPIEZA TIMER -------------------------------------------------------------------------------------------------
    auto tStart = chrono::high_resolution_clock::now();
    cout << "-- Timer start --" << endl;
    //---------------------------------------------------------------------------------------------------------------
    
    //int* sorted = shellSort(myArray, size);
    quickSort(myArray, 0, size-1);

    //DETIENE TIMER Y GUARDA EL TIEMPO TRANSCURRIDO ------------------------------------------------------------------
    auto tStop = chrono::high_resolution_clock::now();
    cout << "-- Timer stop --" << endl;
    auto timeTaken = chrono::duration_cast<chrono::milliseconds>(tStop - tStart);
    //---------------------------------------------------------------------------------------------------------------

    cout << "Sorted array: ";
    printArray(myArray, size);
    

    //prints time elapsed
    cout << "Time elapsed: " << timeTaken.count() << " ms" << endl;

    return 0;
}