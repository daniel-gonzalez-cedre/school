// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Spring 2014

import java.util.Scanner;
import java.lang.Math;

public class A
{
	public static void main(String args[])
	{
		Scanner scanner = new Scanner(System.in);
		boolean[][] board = new boolean[8][8];

		for(int i = 0; i < 8; i++)
		{
			char[] line = scanner.nextLine().toCharArray();

			for(int j = 0; j < 8; j++)
				if(line[j] == '*')
					board[i][j] = true;
				else
					board[i][j] = false;
		}

		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				if(board[i][j])
				{
					for(int k = 0; k < 8; k++)
					{
						if(board[k][j] && k != i)
						{
							System.out.print("invalid");
							return;
						}
						
						if(board[i][k] && k != j)
						{
							System.out.print("invalid");
							return;
						}
					}

					int k = 0;
					int l = 0;

					while(i + k < 8 && j + k < 8 && i + k >= 0 && j + k >= 0)
					{
						if(board[i + k][j + k] && k != 0)
						{
							System.out.print("invalid");
							return;
						}

						k = k + 1;
					}

					k = 0;

					while(i - k >= 0 && j - k >= 0 && i - k < 8 && j - k < 8)
					{
						if(board[i - k][j - k] && k != 0)
						{
							System.out.print("invalid");
							return;
						}

						k = k - 1;
					}

					k = 0;

					while(i + k < 8 && i + k >= 0 && j - l < 8 && j - l >= 0)
					{
						if(board[i + k][j - l] && k != 0 && l != 0)
						{
							System.out.print("invalid");
							return;
						}

						k = k + 1;
						l = l - 1;
					}

					k = 0;
					l = 0;

					while(i - k >= 0 && i - k < 8 && j + l >= 0 && j + l < 8)
					{
						if(board[i - k][j + l] && k != 0 && l != 0)
						{
							System.out.print("invalid");
							return;
						}

						k = k - 1;
						l = l + 1;
					}
				}
			}
		}

		System.out.print("valid");
	}
}
