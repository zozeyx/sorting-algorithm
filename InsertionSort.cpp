#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

void insertionSort(std::vector<int> &arr);
std::vector<int> readInputFile(const std::string &filename);
void writeOutputFile(const std::string &filename, const std::vector<int> &arr);

int main() {
    std::string inputFile = "input.txt";
    std::string outputFile = "insertion_output.txt";

    // Step 1: 파일에서 데이터 읽기
    std::vector<int> numbers = readInputFile(inputFile);

    // Step 2: Insertion Sort 수행
    insertionSort(numbers);

    // Step 3: 정렬된 데이터를 파일에 저장
    writeOutputFile(outputFile, numbers);

    std::cout << "" << outputFile << " 파일에 저장되었습니다.\n";

    return 0;
}

// Insertion Sort 구현
void insertionSort(std::vector<int> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int currentElement = arr[i];
        int j = i - 1;

        // 정렬된 부분에서 currentElement가 들어갈 위치 찾기
        while (j >= 0 && arr[j] > currentElement) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = currentElement;
    }
}

// 파일에서 데이터를 읽어 벡터로 반환
std::vector<int> readInputFile(const std::string &filename) {
    std::vector<int> arr;
    std::ifstream inputFile(filename);

    if (!inputFile) {
        std::cerr << "파일 열기 오류: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    int num;
    while (inputFile >> num) {
        arr.push_back(num);
    }

    inputFile.close();
    return arr;
}

// 벡터 데이터를 파일로 저장
void writeOutputFile(const std::string &filename, const std::vector<int> &arr) {
    std::ofstream outputFile(filename);

    if (!outputFile) {
        std::cerr << "파일 쓰기 오류: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int num : arr) {
        outputFile << num << "\n";
    }

    outputFile.close();
}
