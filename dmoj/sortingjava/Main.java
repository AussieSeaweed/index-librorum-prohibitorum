import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.*;
import java.util.Arrays;

public class Main {
    static int[] array;
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    static void swap(int[] arr, int i, int j) {
        int tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
    }

    static void shuffle(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            int j = i + (int) (Math.random() * (arr.length - i));
            swap(arr, i, j);
        }
    }

    public static void main(String[] args) throws IOException {
        int N = Integer.parseInt(in.readLine());
        array = new int[N];

        for (int i = 0; i < N; i++)
            array[i] = Integer.parseInt(in.readLine());

        shuffle(array);

        Arrays.sort(array);

        long ans = 0;

        for (int i = 0; i < array.length; i++) {
            ans = (3137 * ans + array[i]) % 1000000007;
        }

        System.out.println(ans);
    }
}