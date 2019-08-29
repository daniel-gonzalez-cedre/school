// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Spring 2013

import java.util.Stack;
import java.util.Scanner;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.LinkedHashSet;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class TopSort
{
	public static void main(String[] args) throws FileNotFoundException
	{
		PrintWriter writer = new PrintWriter("output.txt"); 

		for(String s : args)
		{
			try
			{
				writer.printf("%s: \n", s);
				topSort(new File(s), writer);
				System.out.printf("%s has been sorted.\n", s);
			} catch(FileNotFoundException e) {
				System.out.printf("Problem processing file \"%s\"\n", s);
			}
		}

		System.out.println("Results are located in \"output.txt\".");
		writer.close();
	}

	//topologically sorts a file, returning a string of the sorted data
	public static void topSort(File file, PrintWriter writer) throws FileNotFoundException
	{
		//this is used to time how long it takes to sort the file
		long startTime = System.nanoTime();
		long endTime;

		HashMap<String, VertexData> vertices = new HashMap<String, VertexData>();
		LinkedList<String> sorted = new LinkedList<String>();
		Stack<String> zeroes = new Stack<String>();
		Scanner scanner = new Scanner(file);
		int lineCounter = 0;

		//read input from file 
		while(scanner.hasNextLine())
		{
			Scanner line = new Scanner(scanner.nextLine());
			lineCounter = lineCounter + 1;

			String v;
			String w;

			//checks for and ignores blank lines
			if(line.hasNext())
			{
				v = line.next();
			} else {
				System.out.printf("Format Error (blank line): Line %d has been ignored in %s.\n", lineCounter, file);
				continue;
			}

			//checks for and ignores lines with a missing vertex
			if(line.hasNext())
			{
				w = line.next();
			} else {
				System.out.printf("Format Error (not enough arguments): Line %d has been ignored in %s.\n", lineCounter, file);
				continue;
			}

			//checks for and ignores lines with more than 2 vertices
			if(line.hasNext())
			{
				System.out.printf("Format Error (too many arguments): Line %d has been ignored in %s.\n", lineCounter, file);
				continue;
			}

			if(vertices.containsKey(v))
			{
				vertices.get(v).children.push(w);
			} else {
				vertices.put(v, new VertexData(0, w));
			}

			if(vertices.containsKey(w))
			{
				vertices.get(w).parents.push(v);
				vertices.get(w).degree = vertices.get(w).degree + 1;
			} else {
				vertices.put(w, new VertexData(v, 1));
			}
		}

		//search for and accumulate vertices of in-degree = 0
		for(String v : vertices.keySet())
			if(vertices.get(v).degree == 0)
				zeroes.push(v);

		//perform a breadth-first analysis on the vertices of in-degree = 0
		while(!zeroes.isEmpty())
		{
			String v = zeroes.pop();
			VertexData vData = vertices.get(v);

			//decrease children's in-degree and add to stack if in-degree = 0
			while(!vData.children.isEmpty())
			{
				String w = vData.children.pop();
				VertexData wData = vertices.get(w);

				wData.degree = wData.degree - 1;

				if(wData.degree == 0)
					zeroes.push(w);
			}

			//output = output + v + ", ";
			sorted.add(v);
			vertices.remove(v);
		}

		//if there remain vertices, then they must have strictly positive in-degree; there must be a cycle
		if(!vertices.isEmpty())
		{
			findCycle(vertices, writer);
		} else {
			writer.print(sorted.poll());

			while(!sorted.isEmpty())
				writer.printf(", %s", sorted.poll());
		}

		endTime = System.nanoTime();
		writer.printf("\nRunning time (nanoseconds): %d\n\n", endTime - startTime);
	}

	//find and return a cycle by a depth-first traversal of the data from (child -> parent)
	public static void findCycle(HashMap<String, VertexData> vertices, PrintWriter writer) 
	{
		LinkedList<String> cycle = new LinkedList<String>();
		HashSet<String> marked = new HashSet<String>();
		String vertex = vertices.keySet().toArray(new String[vertices.size()])[0];
		String[] cycleArray;

		writer.print("Graph has a cycle: ");
		cycle.add(vertex);

		while(!marked.contains(vertex))
		{
			marked.add(vertex);
			String parent = vertices.get(vertex).parents.pop();

			while(!vertices.containsKey(parent))
				parent = vertices.get(vertex).parents.pop();

			vertex = parent;
			cycle.add(vertex);
		}

		cycleArray = cycle.toArray(new String[cycle.size()]);
		writer.print(vertex);

		for(int i = cycle.indexOf(vertex) + 1; i < cycleArray.length; i++)
			writer.printf(" -> %s", cycleArray[i]);
	}
}

class VertexData
{
	public int degree;
	public Stack<String> parents;
	public Stack<String> children;
	
	//constructor for vertices (v) of the form (v -> w)
	public VertexData(int degree, String w)
	{
		this.degree = degree;
		this.parents = new Stack<String>();
		this.children = new Stack<String>();

		this.children.push(w);
	}

	//constructor for vertices (w) of the form (v -> w)
	public VertexData(String v, int degree)
	{
		this.degree = degree;
		this.parents = new Stack<String>();
		this.children = new Stack<String>();

		this.parents.push(v);
	}
}
