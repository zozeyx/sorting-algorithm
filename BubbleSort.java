import java.io.*;
import java.util.*;

public class BubbleSort {
    public static void main(String[] args) {
        String inputFileName = "input.txt";
        String outputFileName = "bubble_output.txt";
        
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
            
            // Bubble Sort 알고리즘 적용
            bubbleSort(array);
            
            // 정렬된 배열을 파일에 출력
            BufferedWriter writer = new BufferedWriter(new FileWriter(outputFileName));
            for (int num : array) {
                writer.write(num + "\n");
            }
            writer.close();
            
            System.out.println("정렬 완료! 결과는 " + outputFileName + " 파일에 저장되었습니다.");
        } catch (IOException e) {
            System.err.println("파일 처리 중 오류 발생: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.err.println("파일에 잘못된 숫자 형식이 포함되어 있습니다.");
        }
    }

    // Bubble Sort 메서드
    public static void bubbleSort(int[] A) {
        int n = A.length;
        for (int pass = 1; pass < n; pass++) {
            for (int i = 0; i < n - pass; i++) {
                if (A[i] > A[i + 1]) {
                    // 자리 바꿈
                    int temp = A[i];
                    A[i] = A[i + 1];
                    A[i + 1] = temp;
                }
            }
        }
    }
}
