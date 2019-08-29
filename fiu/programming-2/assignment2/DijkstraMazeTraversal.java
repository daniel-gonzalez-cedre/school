// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Spring 2013

import java.util.Stack;
import java.util.Scanner;
import java.util.PriorityQueue;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.IOException;

public class DijkstraMazeTraversal
{
	public static void main(String[] args) throws FileNotFoundException
	{
		int f = 0;
		PrintWriter writer = new PrintWriter("output.txt");

		//format checking for console arguments
		if(args.length == 0)
		{
			System.out.println("Please provide \"-p (...) -f (...)\" arguments.");
			return;
		}

		//format checking and reading console arguments
		if(args[0].equals("-p"))
		{
			while(f < args.length && !args[f].equals("-f"))
			{
				f = f + 1;
			}

			if(f == 1)
			{
				System.out.println("Error: no penalties provided");
				return;
			}

			if(f + 1 >= args.length)
			{
				System.out.println("Error: no files provided.");
				return;
			}
		} else {
			System.out.println("Error: no penalties provided.");
			return;
		}

		//executing files with penalties
		//iterates first over files, then over penalties for each file
		for(int i = f + 1; i < args.length; i++)
		{
			for(int j = 1; j < f; j++)
			{
				try
				{
					mazeTraversal(Integer.parseInt(args[j]), new File(args[i]), writer);
					System.out.printf("%s has been solved with penalty %d.\n", args[i], Integer.parseInt(args[j]));
				} catch(FileNotFoundException e) {
					System.out.printf("Error: %s does not exist.\n", args[i]);
				}
			}
		}

		System.out.println("Results are localed in \"output.txt\".");
		writer.close();
	}

	//mostly reading input and initializing variables
	public static void mazeTraversal(int penalty, File file, PrintWriter writer) throws FileNotFoundException
	{
		Scanner scanner = new Scanner(file);
		int line = 1;
		int row = scanner.nextInt();
		int col = scanner.nextInt();
		Room[][] maze = new Room[row][col];

		//initialize maze array
		for(int i = 0; i < row; i++)
		{
			for(int j = 0; j < col; j++)
			{
				maze[i][j] = new Room(i, j);
			}
		}

		//error checking
		if(scanner.hasNextLine())
		{
			scanner.nextLine();
		} else {
			System.out.printf("Error: %s is empty. Process aborted.", file);
			writer.printf("Error in %s: see console. Process aborted.\n\n", file);
			return;
		}

		//initialize rooms with interior walls
		while(scanner.hasNextLine())
		{
			Scanner lineScanner = new Scanner(scanner.nextLine());

			//format checking
			if(!lineScanner.hasNext())
			{
				System.out.printf("Error: Line %d is blank and has been ignored.\n", line);
				line = line + 1;
				continue;
			}

			//format checking and reading input
			if(lineScanner.hasNextInt())
			{
				row = lineScanner.nextInt();
			} else {
				System.out.printf("Error: Line %d contains ill-formatted coordinates. Process aborted.\n", line);
				break;
			}

			//format checking and reading input
			if(lineScanner.hasNextInt())
			{
				col = lineScanner.nextInt();
			} else {
				System.out.printf("Error: Line %d contains ill-formatted coordinates. Process aborted.\n", line);
				break;
			}

			//storing input
			try
			{
				if(lineScanner.hasNext())
				{
					if(row < maze.length && row >= 0 && col < maze[0].length && col >= 0)
					{
						maze[row][col].initialize(lineScanner.next().toCharArray(), line);
					} else {
						System.out.printf("Coordinates (%d, %d) are out of bounds in line %d. Line has been ignored.\n", row, col, line);
					}
				} else {
					System.out.printf("Cell (%d, %d) does not have any walls listed on line %d. Assumed to have no adjacent walls.\n", row, col, line);
				}
			} catch(IOException e) {
				System.out.println(e);
				writer.printf("Error in %s: see console. Process aborted.\n\n", file);
				return;
			}

			line = line + 1;
			lineScanner.close();
		}

		//perform Dijkstra's algorithm to find a shortest path
		writer.printf("Path for %s with penalty %d: ", file, penalty);
		dijkstra(maze, penalty, writer);

		scanner.close();
	}

	//performs Dijkstra's algorithm with a PriorityQueue
	public static void dijkstra(Room[][] maze, int penalty, PrintWriter writer)
	{
		int walls = 0;
		boolean[][] visited = new boolean[maze.length][maze[0].length];
		Stack<Character> path = new Stack<>();
		PriorityQueue<Room> queue = new PriorityQueue<>();
		Room room = maze[0][0];

		room.distance = 0;

		//calculate distances
		do
		{
			visited[room.row][room.col] = true;

			//update north
			if(room.row - 1 >= 0 && !visited[room.row - 1][room.col])
			{
				Room north = maze[room.row - 1][room.col];
				int tempDistance = room.distance + 1;
				boolean flag = false;

				//add penalty if there is a wall
				if(room.n)
				{
					flag = true;
					tempDistance = tempDistance + penalty;
				}

				if(north.distance == -1 || tempDistance < north.distance)
				{
					north.distance = tempDistance;
					north.previous = new Triplet(room, 'N', flag);
					queue.offer(north);
				}
			}

			//update south
			if(room.row + 1 < maze.length && !visited[room.row + 1][room.col])
			{
				Room south = maze[room.row + 1][room.col];
				int tempDistance = room.distance + 1;
				boolean flag = false;

				//add penalty if there is a wall
				if(room.s)
				{
					flag = true;
					tempDistance = tempDistance + penalty;
				}

				if(south.distance == -1 || tempDistance < south.distance)
				{
					south.distance = tempDistance;
					south.previous = new Triplet(room, 'S', flag);
					queue.offer(south);
				}
			}

			//update east
			if(room.col + 1 < maze[0].length && !visited[room.row][room.col + 1])
			{
				Room east = maze[room.row][room.col + 1];
				int tempDistance = room.distance + 1;
				boolean flag = false;

				//add penalty if there is a wall
				if(room.e)
				{
					flag = true;
					tempDistance = tempDistance + penalty;
				}

				if(east.distance == -1 || tempDistance < east.distance)
				{
					east.distance = tempDistance;
					east.previous = new Triplet(room, 'E', flag);
					queue.offer(east);
				}
			}

			//update west
			if(room.col - 1 >= 0 && !visited[room.row][room.col - 1])
			{
				Room west = maze[room.row][room.col - 1];
				int tempDistance = room.distance + 1;
				boolean flag = false;

				//add penalty if there is a wall
				if(room.w)
				{
					flag = true;
					tempDistance = tempDistance + penalty;
				}

				if(west.distance == -1 || tempDistance < west.distance)
				{
					west.distance = tempDistance;
					west.previous = new Triplet(room, 'W', flag);
					queue.offer(west);
				}
			}

			//select next closest room
			room = queue.poll();
		} while(!queue.isEmpty() && !room.equals(maze[maze.length - 1][maze[0].length - 1]));

		room = maze[maze.length - 1][maze[0].length - 1];

		//trace the shortest path starting at the end towards the beginning
		while(!room.equals(maze[0][0]))
		{
			if(room.previous.wall)
			{
				walls = walls + 1;
			}

			path.push(room.previous.direction);
			room = room.previous.room;
		}

		//return the path starting at the beginning
		while(!path.isEmpty())
		{
			writer.print(path.pop());
		}

		writer.printf("\nThe total cost was %d, with %d walls knocked down.\n\n", maze[maze.length - 1][maze[0].length - 1].distance, walls);
	}
}

//holds information about the individual cells in the maze
class Room implements Comparable<Room>
{
	Triplet previous;
	int distance;
	int row;
	int col;
	boolean n;
	boolean s;
	boolean e;
	boolean w;

	public Room(int row, int col)
	{
		previous = null;
		this.distance = -1;
		this.row = row;
		this.col = col;
		this.n = false;
		this.s = false;
		this.e = false;
		this.w = false;
	}

	//initialize wall values
	public void initialize(char[] walls, int line) throws IOException
	{
		for(int i = 0; i < walls.length; i++)
		{
			switch(walls[i])
			{
				case 'N': this.n = true;
						  continue;
				case 'n': this.n = true;
						  continue;
				case 'S': this.s = true;
						  continue;
				case 's': this.s = true;
						  continue;
				case 'E': this.e = true;
						  continue;
				case 'e': this.e = true;
						  continue;
				case 'W': this.w = true;
						  continue;
				case 'w': this.w = true;
						  continue;
				default: throw new IOException("Error: Improper format at line " + line + ". Process aborted.");
			}
		}
	}

	public boolean equals(Room room)
    {
		return this.row == room.row && this.col == room.col;
    }

	//so that objects can be ordered based, on distance from the start, for the PriorityQueue
	public int compareTo(Room room)
    {
		return this.distance - room.distance;
    }
}

class Triplet
{
	Room room;
	char direction;
	boolean wall;

	public Triplet(Room room, char direction, boolean wall)
	{
		this.room = room;
		this.direction = direction;
		this.wall = wall;
	}
}
