#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void insertionSort(vector<int>& arr);
void sortAndSaveChunks(const string& inputFile, vector<string>& tempFiles, int chunkSize);
void mergeSortedChunks(const vector<string>& tempFiles, const string& outputFile);

int main() {
    const string inputFile = "input.txt";
    const string outputFile = "external_output.txt";
    const int chunkSize = 100; // 메모리에 한 번에 처리할 데이터 개수

    vector<string> tempFiles; // 임시 파일 리스트

    // 입력 파일을 작은 청크로 나누고 정렬
    sortAndSaveChunks(inputFile, tempFiles, chunkSize);

    // 임시 파일 병합
    mergeSortedChunks(tempFiles, outputFile);

    // 임시 파일 삭제
    for (const string& tempFile : tempFiles) {
        remove(tempFile.c_str());
    }

    cout << "" << outputFile << " 파일에 저장되었습니다." << endl;

    return 0;
}

// insertion sort
void insertionSort(vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        int current = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current;
    }
}

// 임시 저장 
void sortAndSaveChunks(const string& inputFile, vector<string>& tempFiles, int chunkSize) {
    ifstream input(inputFile);
    if (!input) {
        cerr << "파일 열기 오류: " << inputFile << endl;
        exit(EXIT_FAILURE);
    }

    vector<int> chunk; // 메모리에 올릴 데이터
    int num;
    int fileIndex = 0;

    while (input >> num) {
        chunk.push_back(num);
        if (chunk.size() == chunkSize) {
            // Chunk가 꽉 찼을 때 정렬하고 저장
            insertionSort(chunk);
            string tempFile = "temp_" + to_string(fileIndex++) + ".txt";
            ofstream tempOutput(tempFile);
            for (int value : chunk) {
                tempOutput << value << "\n";
            }
            tempOutput.close();
            tempFiles.push_back(tempFile);
            chunk.clear();
        }
    }

    // 남은 데이터 처리
    if (!chunk.empty()) {
        insertionSort(chunk);
        string tempFile = "temp_" + to_string(fileIndex++) + ".txt";
        ofstream tempOutput(tempFile);
        for (int value : chunk) {
            tempOutput << value << "\n";
        }
        tempOutput.close();
        tempFiles.push_back(tempFile);
    }

    input.close();
}

// 임시파일 병합합
void mergeSortedChunks(const vector<string>& tempFiles, const string& outputFile) {
    ofstream output(outputFile);
    if (!output) {
        cerr << "파일 쓰기 오류: " << outputFile << endl;
        exit(EXIT_FAILURE);
    }

    // Min-heap to merge sorted chunks
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    vector<ifstream> fileStreams(tempFiles.size());

    // 임시 파일 열기
    for (size_t i = 0; i < tempFiles.size(); i++) {
        fileStreams[i].open(tempFiles[i]);
        if (!fileStreams[i]) {
            cerr << "임시 파일 열기 오류: " << tempFiles[i] << endl;
            exit(EXIT_FAILURE);
        }

        int value;
        if (fileStreams[i] >> value) {
            minHeap.push({value, i});
        }
    }

    // 병합
    while (!minHeap.empty()) {
        auto [minValue, fileIndex] = minHeap.top();
        minHeap.pop();
        output << minValue << "\n";

        int nextValue;
        if (fileStreams[fileIndex] >> nextValue) {
            minHeap.push({nextValue, fileIndex});
        }
    }

    // Close all temp files
    for (size_t i = 0; i < fileStreams.size(); i++) {
        fileStreams[i].close();
    }

    output.close();
}
