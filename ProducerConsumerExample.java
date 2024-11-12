import java.util.concurrent.*;
import java.util.*;

class Producer implements Runnable {
    private final BlockingQueue<String> stack;
    private final int producerId;
    private static final int ITEMS_TO_PRODUCE = 7;

    public Producer(BlockingQueue<String> stack, int producerId) {
        this.stack = stack;
        this.producerId = producerId;
    }

    @Override
    public void run() {
        try {
            for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
                String item = "Item-" + producerId + "-" + (i + 1);
                System.out.println("Producer " + producerId + " pushing: " + item);

               
                stack.put(item);

                
                Thread.sleep(500);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

class Consumer implements Runnable {
    private final BlockingQueue<String> stack;
    private static final int TOTAL_ITEMS_TO_CONSUME = 14; 

    public Consumer(BlockingQueue<String> stack) {
        this.stack = stack;
    }

    @Override
    public void run() {
        try {
            int itemsConsumed = 0;
            while (itemsConsumed < TOTAL_ITEMS_TO_CONSUME) {
               
                String item = stack.take();
                System.out.println("Consumer popping: " + item);

                
                Thread.sleep(600);

                itemsConsumed++;
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

public class ProducerConsumerExample {
    public static void main(String[] args) {
        
        BlockingQueue<String> stack = new ArrayBlockingQueue<>(10);

        
        Thread producer1 = new Thread(new Producer(stack, 1));
        Thread producer2 = new Thread(new Producer(stack, 2));

        
        Thread consumer = new Thread(new Consumer(stack));

      
        producer1.start();
        producer2.start();
        consumer.start();

        
        try {
            producer1.join();
            producer2.join();
            consumer.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
