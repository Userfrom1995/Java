public class OddEvenPrinter {

  
    static class OddThread extends Thread {
        public void run() {
            for (int i = 1; i <= 50; i += 2) {
                System.out.println("Odd: " + i);
                try {
                    Thread.sleep(100);  
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    static class EvenThread extends Thread {
        public void run() {
            for (int i = 2; i <= 50; i += 2) {
                System.out.println("Even: " + i);
                try {
                    Thread.sleep(100);  
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
       
        Thread oddThread = new OddThread();
        Thread evenThread = new EvenThread();

       
        oddThread.start();
        evenThread.start();

      
        try {
            oddThread.join();
            evenThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Both threads have finished printing numbers.");
    }
}
