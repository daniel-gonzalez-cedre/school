// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Fall 2013
// Codeforces Waterloo 2012: Room Painting

import java.util.Scanner;
import java.util.Arrays;

public class C
{
    public static void main(String args[])
    {
        Scanner scanner = new Scanner(System.in);
        
        int numSizes = scanner.nextInt();
        int numCans = scanner.nextInt();
        int[] sizes = new int[numSizes];
        Long total = 0l;
        
        for(int i = 0; i < numSizes; i++)
            sizes[i] = scanner.nextInt();
        
        Arrays.sort(sizes);
        
        for(int i = 0; i < numCans; i++)
        {
            int paint = scanner.nextInt();
            int index = Arrays.binarySearch(sizes, paint);
            
            if(index < 0)
                index = 0 - index - 1;
            
            total = total + sizes[index] - paint;
        }
        
        System.out.println(total + "");
        
        scanner.close();
    }
}
