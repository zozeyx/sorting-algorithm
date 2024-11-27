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

    // 입력 파일에서 데이터 읽기
    readInputFile(inputFile, arrLSD);

    // input 배열 복사
    arrMSD = arrLSD;

    // LSD 수행
    radixSortLSD(arrLSD);
    writeOutputFile(outputLSD, arrLSD);

    // MSD 수행
    int maxNumber = *max_element(arrMSD.begin(), arrMSD.end()); // 배열의 최대값
    int maxDigits = log10(maxNumber) + 1; // 최대 자릿수 계산
    radixSortMSD(arrMSD, pow(10, maxDigits - 1)); // MSD 정렬 시작
    writeOutputFile(outputMSD, arrMSD);

    cout << outputLSD << " 및 " << outputMSD << " 파일에 저장되었습니다." << endl;

    return 0;
}

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

// LSD 
void radixSortLSD(vector<int>& arr) {
    int n = arr.size();
    int maxNumber = *max_element(arr.begin(), arr.end()); 
    int exp = 1; // 정렬 시작 자릿수 (1의 자리)

    vector<int> output(n);

    // 가장 큰 자릿수까지 반복
    while (maxNumber / exp > 0) {
        vector<int> count(10, 0); 
        // 각 숫자의 현재 자릿수를 카운트
        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        // 누적 합으로 카운트 배열을 업데이트
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // 정렬된 배열을 임시 배열에 저장
        for (int i = n - 1; i >= 0; i--) {
            output[--count[(arr[i] / exp) % 10]] = arr[i];
        }

        // 임시 배열 데이터를 원래 배열로 복사
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }

        exp *= 10; // 다음 자릿수로 이동
    }
}

// MSD 
void radixSortMSDUtil(vector<int>& arr, int start, int end, int exp) {
    if (start >= end - 1 || exp == 0) { 
        return;
    }

    vector<int> count(10, 0); 

    // 각 숫자의 현재 자릿수를 카운트
    for (int i = start; i < end; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // 각 버킷의 시작 인덱스 계산
    vector<int> bucketStart(10, start);
    for (int i = 1; i < 10; i++) {
        bucketStart[i] = bucketStart[i - 1] + count[i - 1];
    }

    // 정렬된 데이터를 임시 배열에 저장
    vector<int> temp(end - start);
    for (int i = start; i < end; i++) {
        int digit = (arr[i] / exp) % 10;
        temp[bucketStart[digit] - start] = arr[i];
        bucketStart[digit]++;
    }

    // 임시 배열 데이터를 원래 배열로 복사
    for (int i = start; i < end; i++) {
        arr[i] = temp[i - start];
    }

    // 버킷 시작 인덱스 복구
    bucketStart[0] = start;
    for (int i = 1; i < 10; i++) {
        bucketStart[i] = bucketStart[i - 1] + count[i - 1];
    }

    // 각 버킷을 재귀적으로 정렬
    for (int i = 0; i < 10; i++) {
        radixSortMSDUtil(arr, bucketStart[i], bucketStart[i] + count[i], exp / 10);
    }
}

// MSD 기수 정렬
void radixSortMSD(vector<int>& arr, int exp) {
    radixSortMSDUtil(arr, 0, arr.size(), exp);
}
