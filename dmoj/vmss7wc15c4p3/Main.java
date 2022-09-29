import java.util.*;
import java.io.*;

public class Main {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    static class Edge {
        int a, b, t;
        Edge(int a, int b, int t) {
            this.a = a;
            this.b = b;
            this.t = t;
        }
    }

    static class Event implements Comparable<Event> {
        int node, weight;
        Event(int node, int weight) {
            this.node = node;
            this.weight = weight;
        }

        public int compareTo(Event that) {
            return weight - that.weight;
        }
    }

    static ArrayList<Edge>[] graph;
    static int[] min1, min2;
    static int N, M;

    public static void main(String[] args) throws IOException {
        {
            String[] line = in.readLine().split(" ");
            N = Integer.parseInt(line[0]);
            M = Integer.parseInt(line[1]);
        }
        graph = (ArrayList<Edge>[]) new ArrayList[N];
        min1 = new int[N]; min2 = new int[N];
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<Edge>();
        while (M-- > 0) {
            String[] tokens = in.readLine().split(" ");
            int a, b, t;
            a = Integer.parseInt(tokens[0]);
            b = Integer.parseInt(tokens[1]);
            t = Integer.parseInt(tokens[2]);
            graph[a].add(new Edge(a, b, t));
            graph[b].add(new Edge(b, a, t));
        }

        dijkstra(0, min1);
        dijkstra(N - 1, min2);

        int ans = -1;

        for (int i = 0; i < N; i++) {
            ans = Integer.max(ans, min1[i] + min2[i]);
        }

        System.out.println(ans);
    }

    static void dijkstra(int s, int[] min) {
        for (int i = 0; i < N; i++) min[i] = Integer.MAX_VALUE;
        PriorityQueue<Event> pq = new PriorityQueue<>();
        boolean[] visited = new boolean[N];
        min[s] = 0;
        pq.add(new Event(s, 0));

        while (!pq.isEmpty()) {
            Event e = pq.poll();
            int node = e.node;
            if (visited[node]) continue;
            visited[node] = true;
            for (Edge adjEdge : graph[node]) {
                int ndist = min[node] + adjEdge.t;
                if (ndist < min[adjEdge.b]) {
                    min[adjEdge.b] = ndist;
                    pq.add(new Event(adjEdge.b, ndist));
                }
            }
        }
    }
}