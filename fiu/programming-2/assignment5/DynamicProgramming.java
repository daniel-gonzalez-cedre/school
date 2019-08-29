// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Spring 2013

import java.util.Scanner;
import java.lang.Math;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.IOException;

public class DynamicProgramming
{
	public static void main(String args[]) throws IOException
	{
		PrintWriter writer = new PrintWriter("output.txt");

		if(args.length == 0)
		{
			writer.println("Error: no files provided. Provide full path address.");
			System.out.println("Error: no files provided. Provide full path address.");
			return;
		}

		if(args.length < 2)
		{
			writer.println("Error: not enough files provided.\nPlease provide 2 files.");
			System.out.println("Error: not enough files provided.\nPlease provide 2 files.");
			return;
		}

		largest_submatrix(new File(args[0]), writer);
		longest_subsequence(new File(args[1]), writer);
		optimal_change(writer);
		writer.close();
	}

	public static void largest_submatrix(File file, PrintWriter writer) throws FileNotFoundException
	{
		writer.printf("Largest Submatrix for %s:\n", file);
		Scanner scanner = new Scanner(file);

		int[][] input = new int[500][150];
		int[][] dp = new int[500][150];
		int max = 0;
		int row = -1;
		int col = -1;

		//reading input
		for(int i = 0; i < 500; i++)
		{
			char[] line = scanner.nextLine().toCharArray();

			for(int j = 0; j < 150; j++)
			{
				if(line.length != 150)
				{
					writer.println("\tError: malformed input, process aborted");
					return;
				}

				input[i][j] = line[j] - 48;

				//error-checking
				if(input[i][j] != 0 && input[i][j] != 1)
				{
					System.out.println(i + " " + j);
					writer.println("\tError: malformed input, process aborted.");
					return;
				}
			}
		}

		//initializing first column
		for(int i = 0; i < 500; i++)
		{
			dp[i][0] = input[i][0];

			if(dp[i][0] > max)
			{
				max = 1;
				row = i;
				col = 1;
			}
		}

		//initializing first row
		for(int j = 0; j < 150; j++)
		{
			dp[0][j] = input[0][j];

			if(dp[0][j] > max)
			{
				max = 1;
				row = 0;
				col = j;
			}
		}

		//dynamic programming
		for(int i = 1; i < 500; i++)
		{
			for(int j = 1; j < 150; j++)
			{
				if(input[i][j] == 0)
				{
					dp[i][j] = 0;
				} else {
					dp[i][j] = Math.min(dp[i - 1][j - 1], Math.min(dp[i - 1][j], dp[i][j - 1])) + 1;

					if(dp[i][j] > max)
					{
						max = dp[i][j];
						row = i;
						col = j;
					}
				}
			}
		}

		if(row == -1 || col == -1)
		{
			writer.println("\tMatrix was all 0s; largest submatrix of 1s is empty.\n");
			return;
		}

		writer.printf("\tThe largest square submatrix of 1s is %d x %d and has bottom right corner located at (%d, %d).\n\n", max, max, row, col);
	}

	public static void longest_subsequence(File file, PrintWriter writer) throws FileNotFoundException
	{
		writer.printf("Longest Common Subsequence for %s:\n", file);
		Scanner scanner = new Scanner(file);

		String sequence = "";
		char[] line1 = scanner.nextLine().toCharArray();
		char[] line2 = scanner.nextLine().toCharArray();
		int[][] dp = new int[line1.length][line2.length];
		int max = 0;
		int row = -1;
		int col = -1;

		//initializing first row
		for(int i = 0; i < line1.length; i++)
		{
			if(line1[i] == line2[0])
			{
				dp[i][0] = 1;

				if(dp[i][0] > max)
				{
					max = dp[i][0];
					row = i;
					col = 0;
				}
			}
		}

		//initializing first column
		for(int j = 0; j < line2.length; j++)
		{
			if(line1[0] == line2[j])
			{
				dp[0][j] = 1;

				if(dp[0][j] > max)
				{
					max = dp[0][j];
					row = 0;
					col = j;
				}
			}
		}

		//dynamic programming
		for(int i = 1; i < line1.length; i++)
		{
			for(int j = 1; j < line2.length; j++)
			{
				if(line1[i] == line2[j])
				{
					dp[i][j] = dp[i - 1][j - 1] + 1;
				} else {
					dp[i][j] = Math.max(dp[i][j - 1], dp[i - 1][j]);

					if(dp[i][j] > max)
					{
						max = dp[i][j];
						row = i;
						col = j;
					}
				}
			}
		}

		if(row == -1 || col == -1)
		{
			writer.println("\tThe sequences have no subsequence in common.\n");
			return;
		}

		sequence = sequence + line1[row];

		//building the subsequence
		while(row >= 0 && col >= 0 && dp[row][col] > 0)
		{
			if(line1[row] == line2[col])
				sequence = line1[row] + sequence;

			if(row == 0 || col == 0)
				break;

			row = row - 1;
			col = col - 1;

			while(row > 0 && col > 0 && line1[row] != line2[col])
			{
				if(dp[row][col - 1] > dp[row - 1][col])
					col = col - 1;
				else
					row = row - 1;
			}
		}

		writer.printf("\tA longest common subsequence is \'%s\'.\n", sequence);
		writer.printf("\tThis sequence is %d characters long.\n\n", max);
	}

	public static void optimal_change(PrintWriter writer) throws FileNotFoundException
	{
		writer.print("Optimal Change for {1, 2, ... 100}:\n\tThe minimum number of coins needed are as follows:");

		int[] dp = new int[101];
		dp[0] = 0;

		//dynamic programming
		for(int i = 1; i <= 100; i++)
		{
			if(i < 5)
				dp[i] = dp[i - 1] + 1;
			else if(i < 10)
				dp[i] = Math.min(dp[i - 1], dp[i - 5]) + 1;
			else if(i < 18)
				dp[i] = Math.min(dp[i - 1], Math.min(dp[i - 5], dp[i - 10])) + 1;
			else if(i < 25)
				dp[i] = Math.min(dp[i - 1], Math.min(dp[i - 5], Math.min(dp[i - 10], dp[i - 18]))) + 1;
			else
				dp[i] = Math.min(dp[i - 1], Math.min(dp[i - 5], Math.min(dp[i - 10], Math.min(dp[i - 18], dp[i - 25])))) + 1;
		}

		for(int i = 1; i <= 100; i++)
		{
			if(dp[i] > 1)
				writer.printf("\n\t%d:\t%d coins", i, dp[i]);
			else
				writer.printf("\n\t%d:\t%d coin", i, dp[i]);
		}
	}
}
