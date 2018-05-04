import java.io.*;
import java.util.*;

public class Main 
{
    public boolean test(int n , int k , int[] arr){
        int lo = 0, hi = n - 1;
        int[] cpy = new int[n];
        for( int i = 0; i < n; i++ ){
            cpy[i] = arr[i];
        }
        
        for( int i = k; i >= 1; i-- ){
            if(lo > hi)return false;
            if(Math.min(cpy[lo], cpy[hi]) < i )return false;
            cpy[lo] -= i;
            cpy[hi] -= i;
            if(cpy[lo] == 0)lo++;
            if(cpy[hi] == 0)hi--;           
        }
        
        int sum = 0;
        for(int i = 0; i < n; i++ ){
            sum += cpy[i];
        }
        if(k == 1)return sum == 0;
        return sum % 2 == 0;
    }
    void run() throws NumberFormatException, IOException
    {   
        int n = in.nextInt();
        int[] arr = new int[n];
        
        int sum = 0;
        for( int i = 0; i < n; i++ ){
            arr[i] = in.nextInt();
            sum += arr[i];
        } 
        
        int k = sum;
        for( ; k >= 1; k-- ){
            if(test(n , k , arr)){
                out.println(k);
                return;
            }               
        }
        out.println("no quotation");        
    }
    
    Scanner in;
    PrintStream out;
    
    public Main() throws NumberFormatException, IOException
    {
        in = new Scanner(new InputStreamReader(System.in));
        out = System.out;
        run();
    }
        
    public static void main(String[] args) throws NumberFormatException, IOException 
    {
        new Main();
    }       
}