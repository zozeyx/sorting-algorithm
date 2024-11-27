#include <stdio.h>
#include <stdlib.h>

void heapSort(int arr[], int n);
void buildMaxHeap(int arr[], int n);
void downHeap(int arr[], int n, int i);
void swap(int *a, int *b);
void readInputFile(const char *filename, int **arr, int *size);
void writeOutputFile(const char *filename, int arr[], int size);

int main() {
    const char *inputFile = "input.txt";
    const char *outputFile = "heap_output.txt";
    int *arr = NULL;
    int size = 0;

    // 파일에서 입력 읽기
    readInputFile(inputFile, &arr, &size);

    // Heap Sort 수행
    heapSort(arr, size);

    // 정렬된 데이터를 파일에 저장
    writeOutputFile(outputFile, arr, size);

    printf("%s 파일에 저장되었습니다.\n", outputFile);

    // 동적 메모리 해제
    free(arr);

    return 0;
}

// Heap Sort
void heapSort(int arr[], int n) {
    // 최대 힙 구성
    buildMaxHeap(arr, n);

    // 힙의 크기를 줄이며 정렬
    for (int i = n - 1; i > 0; i--) {
        // 루트와 마지막 원소 교환
        swap(&arr[0], &arr[i]);

        // 힙 크기를 줄이고 DownHeap 호출
        downHeap(arr, i, 0);
    }
}

// 최대 힙 구성
void buildMaxHeap(int arr[], int n) {
    // 마지막 노드의 부모부터 시작하여 DownHeap 호출
    for (int i = n / 2 - 1; i >= 0; i--) {
        downHeap(arr, n, i);
    }
}

// DownHeap 
void downHeap(int arr[], int n, int i) {
    int largest = i;           // 루트를 가장 큰 값으로 가정
    int left = 2 * i + 1;      // 왼쪽 자식
    int right = 2 * i + 2;     // 오른쪽 자식

    // 왼쪽 자식이 더 크면 largest 갱신
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // 오른쪽 자식이 더 크면 largest 갱신
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // largest가 루트가 아니면 교환 후 재귀 호출
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        downHeap(arr, n, largest);
    }
}

// 두 원소 교환
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void readInputFile(const char *filename, int **arr, int *size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("파일 열기 오류");
        exit(EXIT_FAILURE);
    }

    
    int *tempArr = malloc(1000 * sizeof(int));
    int count = 0;

    while (fscanf(file, "%d", &tempArr[count]) == 1) {
        count++;
    }

    fclose(file);

    *arr = realloc(tempArr, count * sizeof(int)); 
    *size = count;
}


void writeOutputFile(const char *filename, int arr[], int size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("파일 쓰기 오류");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);
}
