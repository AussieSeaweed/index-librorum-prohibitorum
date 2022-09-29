import java.util.*;

public class Main {
    static Scanner input = new Scanner(System.in);
    static int[] coords;

    public static void main(String[] args) {
        int N = input.nextInt(), T = input.nextInt();
        coords = new int[N];
        for (int i = 0; i < N; i++) coords[i] = input.nextInt();
        Arrays.sort(coords);
        int ans = Integer.MAX_VALUE;
        for (int i = 0; i <= N - T; i++) {
            int lo = coords[i];
            int hi = coords[i + T - 1];
            int dist = Math.min(Math.abs(lo), Math.abs(hi)) + (hi - lo);
            ans = Math.min(ans, dist);
        }
        System.out.println(ans);
    }
}