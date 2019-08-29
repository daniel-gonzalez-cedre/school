// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Fall 2013
// Codeforces 230: Tower of Hanoi

import java.util.Scanner;
import java.lang.Math;

public class TowerOfHanoi
{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		int t[][] = new int[3][3];

		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				t[i][j] = scanner.nextInt();

        //dynamic programming approach
		int n = scanner.nextInt();
		long dp[][][] = new long[n + 1][3][3];

		/*
         * p: quantity rings to move
         * s: start peg
         * d: destination peg
         */
		for(int p = 1; p <= n; p++)
			for(int s = 0; s < 3; s++)
				for(int d = 0; d < 3; d++)
					if(s != d)
						dp[p][s][d] = Math.min(dp[p-1][s][3-s-d] + t[s][d] + dp[p-1][3-s-d][d], dp[p-1][s][d] + t[s][3-s-d] + dp[p-1][d][s] + t[3-s-d][d] + dp[p-1][s][d]);

		System.out.println(dp[n][0][2]);
	}
}
