// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Fall 2013
// Codeforces 228: Fox & Number Game

import java.util.Scanner;
import java.util.Arrays;

public class A
{
    public static void main(String args[])
    {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int input[] = new int[n];
        
        for(int i = 0; i < n; i++)
            input[i] = scanner.nextInt();
        
        System.out.println(n * gcdList(input));
    }
    
    static int gcdList(int[] list)
    {
        if(list.length == 2)
            return gcd(list[0], list[1]);
        else
            return gcd(gcdList(Arrays.copyOf(list, list.length - 1)), list[list.length - 1]);
    }
    
    static int gcd(int a, int b)
    {
        int t;
        
        while(b != 0)
        {
            t = b;
            b = a % b;
            a = t;
        }
        
        return a;
    }
}
