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

    // 파일에서 데이터 읽기
    std::vector<int> numbers = readInputFile(inputFile);

    // Insertion Sort 수행
    insertionSort(numbers);

    // 정렬된 데이터를 파일에 저장
    writeOutputFile(outputFile, numbers);

    std::cout << "" << outputFile << " 파일에 저장되었습니다.\n";

    return 0;
}

// Insertion Sort 
void insertionSort(std::vector<int> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int currentElement = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > currentElement) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = currentElement;
    }
}


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
