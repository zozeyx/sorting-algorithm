#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;


void radixSortLSD(vector<int>& arr);
void radixSortMSD(vector<int>& arr, int exp);
void readInputFile(const string& filename, vector<int>& arr);
void writeOutputFile(const string& filename, const vector<int>& arr);

int main() {
    const string inputFile = "input.txt";
    const string outputLSD = "radix_lsd_output.txt";
    const string outputMSD = "radix_msd_output.txt";

    vector<int> arrLSD, arrMSD;

    // 파일에서 데이터 읽기
    readInputFile(inputFile, arrLSD);

    arrMSD = arrLSD;

    // LSD Radix Sort 
    radixSortLSD(arrLSD);
    writeOutputFile(outputLSD, arrLSD);

    // MSD Radix Sort 
    int maxNumber = *max_element(arrMSD.begin(), arrMSD.end());
    int maxDigits = log10(maxNumber) + 1; // 최대 자릿수 계산
    radixSortMSD(arrMSD, pow(10, maxDigits - 1));
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

// MSD Radix Sort 
void radixSortMSDUtil(vector<int>& arr, int start, int end, int exp) {
    if (start >= end - 1 || exp == 0) {
        return;
    }

    vector<int> count(10, 0);

    // Count occurrences of each digit
    for (int i = start; i < end; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Calculate starting index for each bucket
    vector<int> bucketStart(10, start);
    for (int i = 1; i < 10; i++) {
        bucketStart[i] = bucketStart[i - 1] + count[i - 1];
    }

    // Build sorted order in a temporary array
    vector<int> temp(end - start);
    for (int i = start; i < end; i++) {
        int digit = (arr[i] / exp) % 10;
        temp[bucketStart[digit] - start] = arr[i];
        bucketStart[digit]++;
    }

    // Copy sorted order back to the original array
    for (int i = start; i < end; i++) {
        arr[i] = temp[i - start];
    }

    // Restore bucketStart values
    bucketStart[0] = start;
    for (int i = 1; i < 10; i++) {
        bucketStart[i] = bucketStart[i - 1] + count[i - 1];
    }

    // Recursively sort each bucket
    for (int i = 0; i < 10; i++) {
        radixSortMSDUtil(arr, bucketStart[i], bucketStart[i] + count[i], exp / 10);
    }
}

// MSD Radix Sort
void radixSortMSD(vector<int>& arr, int exp) {
    radixSortMSDUtil(arr, 0, arr.size(), exp);
}
