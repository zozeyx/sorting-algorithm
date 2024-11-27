#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Function prototypes
void radixSortLSD(vector<int>& arr);
void radixSortMSD(vector<int>& arr, int exp, int maxDigits);
void readInputFile(const string& filename, vector<int>& arr);
void writeOutputFile(const string& filename, const vector<int>& arr);

int main() {
    const string inputFile = "input.txt";
    const string outputLSD = "radix_lsd_output.txt";
    const string outputMSD = "radix_msd_output.txt";

    vector<int> arrLSD, arrMSD;

    // Step 1: 파일에서 데이터 읽기
    readInputFile(inputFile, arrLSD);

    // arrLSD를 arrMSD로 복사 (원본 데이터 유지)
    arrMSD = arrLSD;

    // Step 2: LSD Radix Sort 수행
    radixSortLSD(arrLSD);
    writeOutputFile(outputLSD, arrLSD);

    // Step 3: MSD Radix Sort 수행
    int maxNumber = *max_element(arrMSD.begin(), arrMSD.end());
    int maxDigits = log10(maxNumber) + 1; // 최대 자릿수 계산
    radixSortMSD(arrMSD, pow(10, maxDigits - 1), maxDigits);
    writeOutputFile(outputMSD, arrMSD);

    cout << outputLSD << " 및 " << outputMSD << " 파일에 저장되었습니다." << endl;

    return 0;
}

// Read input file
void readInputFile(const string& filename, vector<int>& arr) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "파일 열기 오류: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    int num;
    while (inputFile >> num) {
        arr.push_back(num);
    }

    inputFile.close();
}

// Write output file
void writeOutputFile(const string& filename, const vector<int>& arr) {
    ofstream outputFile(filename);
    if (!outputFile) {
        cerr << "파일 쓰기 오류: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    for (int num : arr) {
        outputFile << num << "\n";
    }

    outputFile.close();
}

// LSD Radix Sort
void radixSortLSD(vector<int>& arr) {
    int n = arr.size();
    int maxNumber = *max_element(arr.begin(), arr.end());
    int exp = 1; // 자릿수 시작 (1의 자리부터)

    vector<int> output(n);

    while (maxNumber / exp > 0) {
        vector<int> count(10, 0); // 0~9 카운트

        // Count occurrences of each digit
        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        // Accumulate counts
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Build the output array
        for (int i = n - 1; i >= 0; i--) {
            output[--count[(arr[i] / exp) % 10]] = arr[i];
        }

        // Copy output back to arr
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }

        exp *= 10; // Move to next digit
    }
}

// MSD Radix Sort Helper Function
void radixSortMSDUtil(vector<int>& arr, int start, int end, int exp) {
    if (start >= end || exp == 0) {
        return;
    }

    vector<int> count(10, 0);
    vector<int> output(end - start);

    // Count occurrences of each digit
    for (int i = start; i < end; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // Accumulate counts
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = end - 1; i >= start; i--) {
        int digit = (arr[i] / exp) % 10;
        output[--count[digit]] = arr[i];
    }

    // Copy output back to arr
    for (int i = 0; i < output.size(); i++) {
        arr[start + i] = output[i];
    }

    // Recursively sort each bucket
    int prev = start;
    for (int i = 0; i < 10; i++) {
        int curr = start + count[i];
        radixSortMSDUtil(arr, prev, curr, exp / 10);
        prev = curr;
    }
}

// MSD Radix Sort
void radixSortMSD(vector<int>& arr, int exp, int maxDigits) {
    radixSortMSDUtil(arr, 0, arr.size(), exp);
}
