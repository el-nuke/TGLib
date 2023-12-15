#include <iostream>
#include <string>
#include <chrono>

using namespace std;

struct resultados
{
    string tipodecarrera;
    int sizearreglo;
    chrono::microseconds selection, bubble, insertion, shell, merge, quick, heap;
    bool selectionW, bubbleW, insertionW, shellW, mergeW, quickW, heapW;

    void reset() {
        chrono::microseconds zeroms = chrono::microseconds(0);
        selection = bubble = insertion = shell = merge = quick = heap = zeroms;
        selectionW = bubbleW = insertionW = shellW = mergeW = quickW = heapW = false;
    }

    void printAll(){
        cout << "\n-- Resultados de " << tipodecarrera << " (size: " << sizearreglo << ")" <<endl;
        cout << "Selection: " << selection.count() << " microsecs" << endl;
        cout << "Bubble: " << bubble.count() << " microsecs" << endl;
        cout << "Insertion: " << insertion.count() << " microsecs" << endl;
        cout << "Shell: " << shell.count() << " microsecs" << endl;
        cout << "Merge: " << merge.count() << " microsecs" << endl;
        cout << "Quick: " << quick.count() << " microsecs" << endl;
        cout << "Heap: " << heap.count() << " microsecs" << endl;
    }
};

resultados* crearResultados(){
    resultados* ts = new resultados();
    ts->reset();
    return ts;
}


void printArray(int inArray[], int size){
    for (int c=0;c<size;c++){
        cout << inArray[c] << " ";
    }
    cout << endl;
    
}

//Busca el valor mas pequeño desde el principio y lo reubica al principio, avanzando hasta reubicar todo el arreglo
//- *sortedarray = selectionSort(array, size)
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

//Avanza por el arreglo por pares, reubicando al menor del par a la izq. del par y al mayor a la der. del par
//- *sortedarray = bubbleSort(array, size)
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
//- *sortedarray = insertionSort(array, size)
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

//Similar a Insertion, que compara e intercambia elementos distantes en lugar de elementos directamente adyacentes. 
//El gap se reduce con cada iteración hasta 1, donde itera por una ultima vez de forma idéntica a insertion.
//- *sortedarray = shellSort(array, size)
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
//- *sortedarray = mergesort(array, 0, size-1)
int* mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);

        return arr;
    }
}

int getRandomPivot(int low, int high) {
    return rand() % (high - low + 1) + low;
}

int partition(int inArray[], int low, int high) {
    int pivotIndex = getRandomPivot(low, high);
    int temp = inArray[pivotIndex];
    inArray[pivotIndex] = inArray[high];
    inArray[high] = temp;

    int pivot = inArray[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (inArray[j] <= pivot) {
            i++;
            temp = inArray[i];
            inArray[i] = inArray[j];
            inArray[j] = temp;
        }
    }

    temp = inArray[i + 1];
    inArray[i + 1] = inArray[high];
    inArray[high] = temp;

    return i + 1;
}

//Elige un elemento pivote de la lista y particiona la lista en dos subconjuntos: elementos menores que el pivote y elementos mayores que el pivote.
//Una vez ordenados, se elige otro pivote y se repite el proceso
//Para evitar stack overflows, cambia a insertion para los subarreglos mas pequeños.
//- quickSort(array, 0, size-1)
void quickSort(int inArray[], int low, int high) {
    const int INSERTION_THRESHOLD = 10;

    if (low < high) {
        if (high - low + 1 <= INSERTION_THRESHOLD) {
            inArray = insertionSort(inArray + low, high - low + 1);
        } else {
            int pivotIndex = partition(inArray, low, high);

            quickSort(inArray, low, pivotIndex - 1);
            quickSort(inArray, pivotIndex + 1, high);
        }
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

//Convierte la lista en un arbole binario Heap y extrae repetidamente el valor mas alto
//reconstruyendo el heap hasta ordenar el arreglo
//- heapSort(array, size)
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

void carrera(int inArray[], int inSize, string tipo){
    resultados *res = crearResultados();
    int size = inSize;
    int* sortedarray;
    int array[size];

    res->tipodecarrera = tipo;
    res->sizearreglo = size;

    cout << "Iniciado " << res->tipodecarrera << " (size: " << res->sizearreglo << ")" << endl;
    
    for (int c=0; c<7; c++){
        for (int i=0; i<size; i++){
            array[i] = inArray[i];
        }
                
        auto tStart = chrono::high_resolution_clock::now();
        auto tStop = chrono::high_resolution_clock::now();
        
        //printArray(array, size);
        switch (c)
        {
        case 0:
            cout << "testing selection" << endl;
            tStart = chrono::high_resolution_clock::now();
            sortedarray = selectionSort(array, size);
            tStop = chrono::high_resolution_clock::now();
            //cout << "-- Timer stop --" << endl;
            res->selection = chrono::duration_cast<chrono::microseconds>(tStop - tStart);
            break;

        case 1:
            cout << "testing bubble" << endl;
            tStart = chrono::high_resolution_clock::now();
            sortedarray = bubbleSort(array, size);
            tStop = chrono::high_resolution_clock::now();
            //cout << "-- Timer stop --" << endl;
            res->bubble = chrono::duration_cast<chrono::microseconds>(tStop - tStart);
            break;

        case 2:
            cout << "testing insertion" << endl;
            tStart = chrono::high_resolution_clock::now();
            sortedarray = insertionSort(array, size);
            tStop = chrono::high_resolution_clock::now();
            //cout << "-- Timer stop --" << endl;
            res->insertion = chrono::duration_cast<chrono::microseconds>(tStop - tStart);
            break;
        
        case 3:
            cout << "testing shell" << endl;
            tStart = chrono::high_resolution_clock::now();
            sortedarray = shellSort(array, size);
            tStop = chrono::high_resolution_clock::now();
            //cout << "-- Timer stop --" << endl;
            res->shell = chrono::duration_cast<chrono::microseconds>(tStop - tStart);
            break;
        
        case 4:
            cout << "testing merge" << endl;
            tStart = chrono::high_resolution_clock::now();
            mergeSort(array, 0, size-1);
            tStop = chrono::high_resolution_clock::now();
            //cout << "-- Timer stop --" << endl;
            res->merge = chrono::duration_cast<chrono::microseconds>(tStop - tStart);
            break;

        case 5:
            cout << "testing quick" << endl;
            tStart = chrono::high_resolution_clock::now();
            quickSort(array, 0, size-1);
            tStop = chrono::high_resolution_clock::now();
            //cout << "-- Timer stop --" << endl;
            res->quick = chrono::duration_cast<chrono::microseconds>(tStop - tStart);
            break;
        
        case 6:
            cout << "testing heap" << endl;
            tStart = chrono::high_resolution_clock::now();
            heapSort(array, size);
            tStop = chrono::high_resolution_clock::now();
            //cout << "-- Timer stop --" << endl;
            res->heap = chrono::duration_cast<chrono::microseconds>(tStop - tStart);
            break;
        
        default:
            break;
        }
        //printArray(array, size);
    }
    
    
    res->printAll();
}

void vaciarArray(int arr[], int size){
    for (int i=0; i<size; i++){
        arr[i] = 0;
    }
}

void arrayAleatorio(int arr[], int size){
    //Llena el array ordenado
    for (int i=0; i<size; i++){
        arr[i] = i;
    }
    //Reordena aleatoriamente n veces
    for (int i=0; i<(size/2); i++){
        int x = rand()%size;
        int y = rand()%size;
        int temp = arr[x];
        arr[x] = arr[y];
        arr[y] = temp;  
    }
}

void arrayAleatorioConDuplicados(int arr[], int size){
    for (int i=0; i<size; i++){
        arr[i] = arr[rand()%size] = rand()%100;
    }
}

void arrayOrdenado(int arr[], int size){
    //Llena el array ordenado
    for (int i=0; i<size; i++){
        arr[i] = i;
    }
}

void arrayInversamenteOrdenado(int arr[], int size){
    //Llena el array ordenado
    for (int i=0; i<size; i++){
        arr[i] = size - i;
    }
}

int main(){
    srand(time(0));
    
    //int arreglo[22500];
    int sizearr = rand()%(110000 - 100000 + 1) + 100000;
    int input=0;
    string strinput;
    bool loop=true;

    do{
        sizearr=0;
        input=0;
        cout << "-- Comparar algoritmos usando: -- " << endl;
        cout << "1: Colas de espera" << endl;
        cout << "2: Trazabilidad de objetos" << endl;
        cout << "3: Eventos de cada escenario" << endl;
        cout << "4: Ninguno (Salir)" << endl;

        cin >> strinput;
        int input = stoi(strinput);

        if (input == 1){
            sizearr = 100000 + rand()%10000;
            int arreglo[sizearr];
            arrayAleatorioConDuplicados(arreglo,sizearr);  
            carrera(arreglo, sizearr, "Colas de espera"); 
        }
        if (input == 2){
            sizearr = (1000 + rand()%500) * 15;
            int arreglo[sizearr];
            arrayAleatorioConDuplicados(arreglo,sizearr);
            carrera(arreglo, sizearr, "Trazabilidad de objetos");
        }
        if (input == 3){
            sizearr = 60000 + rand()%20000;
            int arreglo[sizearr];
            arrayInversamenteOrdenado(arreglo,sizearr);
            carrera(arreglo, sizearr, "Eventos de cada escenario");
        }
        if (input == 4){
            loop = false;
            cout << "chao" << endl;
        }
    }while(loop);

    return 0;
}