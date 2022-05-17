//ye package name hata dena tumhare code me.
package Assignments;

import java.util.*;

public class Assignment11_InJava {

    // sare function k name mene java k priority queue se matching rakhe hai.

    // min heap banega. agar max heap banana hai toh input lete time bus negative
    // kar do sari values.
    static class Heap {
        private int[] arr = new int[100];

        private int size;
        private int emptyValue;

        public Heap() {
            this.emptyValue = Integer.MAX_VALUE;
            setArray();
            this.size = 0;
        }

        public Heap(int type) {
            this.emptyValue = Integer.MAX_VALUE;
            setArray();
            this.size = 0;
        }

        private void setArray() {
            for (int i = 0; i < 100; i++) {
                arr[i] = emptyValue;
            }
        }

        private void swap(int pos1, int pos2) {
            int temp = this.arr[pos1];
            this.arr[pos1] = this.arr[pos2];
            this.arr[pos2] = temp;
        }

        private void reheapifyUp(int ind) {
            if (ind == 0) {
                return;
            }
            int parentInd = (ind - 1) >> 1;
            if (this.arr[parentInd] > this.arr[ind]) {
                swap(parentInd, ind);
                reheapifyUp(parentInd);
            }
        }

        private void reheapifyDown(int pos) {
            int leftChild = (pos * 2) + 1;
            int rightChild = (pos * 2) + 2;

            boolean canHaveLeftChild = leftChild < 100;
            boolean canHaveRightChild = rightChild < 100;

            int minChildInd = -1;
            if (canHaveLeftChild && canHaveRightChild) {
                // check karo dono me se konsa min hai 3 cases.
                if (this.arr[leftChild] == emptyValue) {
                    // dono empty honge
                    return;
                } else if (this.arr[rightChild] == emptyValue) {
                    // right wala is empty but vala is not vacant
                    minChildInd = leftChild;
                } else {
                    int min = Math.min(this.arr[leftChild], this.arr[rightChild]);
                    if (this.arr[leftChild] == min) {
                        minChildInd = leftChild;
                    } else {
                        minChildInd = rightChild;
                    }
                }
            } else if (canHaveLeftChild) {
                if (this.arr[leftChild] == emptyValue) {
                    // empty hai
                    return;
                } else {
                    minChildInd = leftChild;
                }
            } else {
                return;
            }
            if (minChildInd == -1)
                return;
            if (this.arr[pos] > this.arr[minChildInd]) {
                swap(pos, minChildInd);

                reheapifyDown(minChildInd);
            }

        }

        public void put(int value) {
            if (size == 0) {

                this.arr[0] = value;
                this.size++;

                return;
            }

            if (size >= 99) {
                System.out.println("Heap is full");
            } else {
                this.arr[size] = value;
                reheapifyUp(this.size);
                this.size++;

            }

        }

        public int peek() {
            if (size == 0) {
                System.out.println("The heap is empty");
                return -1;
            }
            return arr[0];
        }

        public int poll() {
            if (size == 0) {
                System.out.println("The heap is empty");
                return -1;
            }
            int rootValue = this.arr[0];
            deleteRoot();
            return rootValue;
        }

        private void deleteRoot() {
            if (size == 0) {
                System.out.println("The heap is empty");
                return;
            }
            this.arr[0] = this.arr[size - 1];
            this.arr[size - 1] = emptyValue;
            this.size--;
            reheapifyDown(0);
        }

        public void print() {
            for (int i = 0; i < size; i++) {
                System.out.print(arr[i] + " ");
            }
        }

    }

    static class Sorting {
        Heap heap;

        public Sorting(Heap heap) {
            this.heap = heap;
        }

        public void sort() {
            ArrayList<Integer> arr = new ArrayList<>();
            int size = heap.size;
            for (int i = 0; i < size; i++) {
                int v = heap.poll();
                arr.add(v);
            }

            System.out.println("The sorted array is " + arr);
        }
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        Heap heap = new Heap();
        // minHeap.put(50);
        // minHeap.put(100);
        // minHeap.put(10);
        // minHeap.put(40);
        // minHeap.put(130);
        // minHeap.put(90);
        // minHeap.put(80);
        // minHeap.put(150);
        // minHeap.put(120);
        // minHeap.put(110);
        // minHeap.put(70);

        while (true) {
            System.out.println("MENU:\n1. Insert\n2. Get min\n3. Peek\n4. Print Heap\n5. Sort");
            System.out.print("Enter the choice code: ");
            int x = sc.nextInt();
            switch (x) {
                case 1:
                    System.out.print("Enter the value to be added: ");
                    int input = sc.nextInt();
                    heap.put(input);
                    System.out.println("Value Inserted!");
                    break;

                case 2:
                    int minVal = heap.poll();
                    System.out.println("The minimum value in the heap is: " + minVal);
                    break;
                case 3:
                    int minValPeek = heap.peek();
                    System.out.println("The value present at the root is : " + minValPeek);
                    break;

                case 4:
                    System.out.println("The heap is:");
                    heap.print();
                    System.out.println();
                    break;
                case 5:
                    Sorting sorting = new Sorting(heap);
                    sorting.sort();
                default:
                    break;
            }

            System.out.println("Do you want to continue? 1/0: ");
            int con = sc.nextInt();
            if (con == 0) {
                break;
            }
        }
        sc.close();
        System.out.println("End of Program!");
    }
}
