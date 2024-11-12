import java.util.Scanner;

public class MatrixRowSum {
    
    
    static class RowSumThread extends Thread {
        private int[] row;
        private int rowIndex;
        
        public RowSumThread(int[] row, int rowIndex) {
            this.row = row;
            this.rowIndex = rowIndex;
        }
        
        @Override
        public void run() {
            
            int sum = 0;
            for (int num : row) {
                sum += num;
            }
            
            System.out.println("Sum of row " + rowIndex + ": " + sum);
        }
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        
        System.out.print("Enter the number of rows (m): ");
        int m = scanner.nextInt();
        
        System.out.print("Enter the number of columns (n): ");
        int n = scanner.nextInt();
        
        
        int[][] matrix = new int[m][n];
        
        
        System.out.println("Enter the elements of the matrix:");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = scanner.nextInt();
            }
        }
        
       
        Thread[] threads = new Thread[m];
        
        for (int i = 0; i < m; i++) {
           
            threads[i] = new RowSumThread(matrix[i], i);
           
            threads[i].start();
        }
        
        
        try {
            for (int i = 0; i < m; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        
       
        scanner.close();
    }
}
