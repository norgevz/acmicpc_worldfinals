import java.io.*;
import java.util.*;

public class Main 
{
    public class Edge{  
                
        public int v;
        public int w;
        
        public Edge(int _v , int _w){           
            v = _v;
            w = _w;
        }
    }
    
    public class Pair implements Comparable<Pair>{
        int w , u;
        
        public Pair(int _w , int _u){
            w = _w;
            u = _u;
        }

        @Override
        public int compareTo(Pair o) {
            return w - o.w;
        }
    }
    
    
    public final int oo = (int)1e9;
    public final long lloo = 1L << 60;
    
    
    int[] dikjstra(int src, int n, int b, List<Edge>[] g){
       boolean mk[] = new boolean[n + 1];
       int dist[] = new int[n + 1];    
       for( int i = 1; i <= n; i++ )
           dist[i] = oo;           
       dist[src] = 0;      
       PriorityQueue<Pair> Q = new PriorityQueue<Pair>();
       Q.add(new Pair(0 , src));
       
       while(!Q.isEmpty()){
           Pair top = Q.poll();        
           int u = top.u;                  
           if(mk[u])continue;
           mk[u] = true;
           
           for(Edge e : g[u]){
               if(!mk[e.v] && dist[e.v] > dist[u] + e.w){
                   dist[e.v] = dist[u] + e.w;                  
                   Q.add(new Pair(dist[e.v] , e.v));
               }
           }
       }
       
       return dist;
    }
    
   void run() throws NumberFormatException, IOException
   {       
       int n = nextInt();
       int b = nextInt();
       int s = nextInt();
       int m = nextInt();
       
       List<Edge>[] G = new ArrayList[n + 1];
       List<Edge>[] Gr = new ArrayList[n + 1];
       for( int i = 0; i <= n; i++ ){
           G[i] = new ArrayList<Edge>();
           Gr[i] = new ArrayList<Edge>();
       }           
           
       for(int i = 0; i < m; i++ )
       {
           int u = nextInt();
           int v = nextInt();
           int w = nextInt();
           G[u].add(new Edge(v , w));
           Gr[v].add(new Edge(u , w));
       }
       
       int[] from = dikjstra(b + 1, n, b, G);
       int[] to = dikjstra(b + 1, n, b, Gr);       
       
       
       int cost[] = new int[b + 1];
       for( int i = 1; i < cost.length; i++ ){
           cost[i] = from[i] + to[i];          
       }       
       
       Arrays.sort(cost);
       long pre[] = new long[b + 1];
       
       for( int i = 1; i < cost.length; i++ )
           pre[i] = pre[i - 1] + cost[i];
       
       long dp[][] = new long[s + 1][b + 1];
       for( int i = 0; i < dp.length; i++ ){
           Arrays.fill(dp[i], lloo);
       }
       
       dp[0][0] = 0;
       for( int group = 1; group <= s; group++ ){
           for( int pref = 1; pref <= b; pref++ ){
               for( int suf = pref - 1; suf >= 0; suf--){
                   if((pref - suf) * group > pref)break;
                   dp[group][pref] = Math.min(dp[group][pref], dp[group - 1][suf] + 1L * (pref - suf - 1) * (pre[pref] - pre[suf]));
               }
           }
       }
       
       out.println(dp[s][b]);
   }
   
   BufferedReader in;
   PrintStream out;
   StringTokenizer tok;
   public Main() throws NumberFormatException, IOException
   {
       in = new BufferedReader(new InputStreamReader(System.in));
       out = System.out;
       run();
   } 

      
   public static void main(String[] args) throws NumberFormatException, IOException 
   {
      new Main();
   }
   
   String nextToken() throws IOException
   {
      String line = "";
      while(tok == null || !tok.hasMoreTokens()) {
         if((line = in.readLine()) != null)
            tok = new StringTokenizer(line);
         else 
            return null;
      }
      return tok.nextToken();
   }
   int nextInt() throws NumberFormatException, IOException
   {
      return Integer.parseInt(nextToken());
   }
   long nextLong() throws NumberFormatException, IOException
   {
      return Long.parseLong(nextToken());
   }
   double nextDouble() throws NumberFormatException, IOException
   {
      return Double.parseDouble(nextToken());
   }   
}