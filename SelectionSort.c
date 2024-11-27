#include <stdio.h>
#include <stdlib.h>

void selectionSort(int arr[], int n);
void readInputFile(const char *filename, int **arr, int *size);
void writeOutputFile(const char *filename, int arr[], int size);

int main() {
    const char *inputFile = "input.txt";
    const char *outputFile = "selection_output.txt";
    int *arr = NULL;
    int size = 0;

    // 파일에서 입력 읽기
    readInputFile(inputFile, &arr, &size);

    // Selection Sort 수행
    selectionSort(arr, size);

    // 정렬된 배열을 파일에 쓰기
    writeOutputFile(outputFile, arr, size);

    printf("%s 파일에 저장되었습니다.\n", outputFile);

    // 동적 메모리 해제
    free(arr);

    return 0;
}

// Selection Sort 구현
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i; // 최솟값의 인덱스
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        // i와 min 위치의 원소를 교환
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

// 파일에서 데이터를 읽어 배열로 변환
void readInputFile(const char *filename, int **arr, int *size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("파일 열기 오류");
        exit(EXIT_FAILURE);
    }

    // 최대 1000개의 숫자를 읽는다고 가정
    int *tempArr = malloc(1000 * sizeof(int));
    int count = 0;

    while (fscanf(file, "%d", &tempArr[count]) == 1) {
        count++;
    }

    fclose(file);

    *arr = realloc(tempArr, count * sizeof(int)); // 정확한 크기로 재조정
    *size = count;
}

// 배열을 파일로 출력
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
