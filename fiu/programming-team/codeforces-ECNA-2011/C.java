// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Fall 2013
// Codeforces Eastern Central North America (ECNA) 2011: Condorcet Winners

import java.util.Scanner;
import java.io.*;

public class C
{
    public static void main(String args[]) throws Exception
    {
        Scanner scanner = new Scanner(System.in);
        
        String result = "";
        
        int cases = 1;
        int counter = 0;
        int b = scanner.nextInt();
        int c = scanner.nextInt();
        
        while(b != 0 && c != 0)
        {
            boolean flag = true;
            
            int[][] ranks = new int[b][c];
            int currentWinner = 0;
            
            for(int i = 0; i < b; i++)
                for(int j = 0; j < c; j++)
                {
                    int test = scanner.nextInt();
                    ranks[i][test] = j;
                }
            
            for(int i = 0; i < c; i++)
                if(i != currentWinner)
                    currentWinner = winningCandidate(currentWinner, i, ranks);
            
            for(int i = 0; i < c; i++)
                if(i != currentWinner)
                    if(winningCandidate(currentWinner, i, ranks) != currentWinner)
                    {
                        flag = false;
                        break;
                    }
            
            if(flag)
                result = result + "Case " + cases + ": " + currentWinner + "\n";
            else
                result = result + "Case " + cases + ": No Condorcet winner\n";
            
            cases++;
            b = scanner.nextInt();
            c = scanner.nextInt();
        }
        
        System.out.println(result);
        scanner.close();
    }
    
    public static int winningCandidate(int candidateA, int candidateB, int[][] ranks)
    {
        int counterA = 0;
        int counterB = 0;
        
        for(int i = 0; i < ranks.length; i++)
            if(ranks[i][candidateA] <= ranks[i][candidateB])
                counterA++;
            else
                counterB++;
        
        if(counterA > counterB)
            return candidateA;
        
        return candidateB;
    }
}
