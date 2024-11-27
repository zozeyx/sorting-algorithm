import java.io.*;
import java.util.*;

public class ShellSort {
    public static void main(String[] args) {
        String inputFileName = "input.txt";
        String outputFileName = "shell_output.txt";

        try {
            // 파일에서 데이터 읽기
            List<Integer> numbers = new ArrayList<>();
            BufferedReader reader = new BufferedReader(new FileReader(inputFileName));
            String line;
            while ((line = reader.readLine()) != null) {
                numbers.add(Integer.parseInt(line.trim()));
            }
            reader.close();

            // 리스트를 배열로 변환
            int[] array = numbers.stream().mapToInt(i -> i).toArray();

            // Shell Sort 수행
            shellSort(array);

            // 정렬된 데이터를 파일로 출력
            BufferedWriter writer = new BufferedWriter(new FileWriter(outputFileName));
            for (int num : array) {
                writer.write(num + "\n");
            }
            writer.close();

            System.out.println("" + outputFileName + " 파일에 저장되었습니다.");
        } catch (IOException e) {
            System.err.println("파일 처리 중 오류 발생: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.err.println("파일에 잘못된 숫자 형식이 포함되어 있습니다.");
        }
    }

    // Shell Sort
    public static void shellSort(int[] A) {
        int n = A.length;
        int[] gaps = {100, 50, 10, 5, 1}; // 간격 h 배열 (100 -> 50 -> 10 -> 5 -> 1 순으로)

        for (int gap : gaps) {
            // Gap만큼 떨어진 요소들을 삽입 정렬
            for (int i = gap; i < n; i++) {
                int currentElement = A[i];
                int j = i;

                // 현재 요소보다 큰 값을 gap만큼 이동
                while (j >= gap && A[j - gap] > currentElement) {
                    A[j] = A[j - gap];
                    j -= gap;
                }
                A[j] = currentElement;
            }
        }
    }
}
