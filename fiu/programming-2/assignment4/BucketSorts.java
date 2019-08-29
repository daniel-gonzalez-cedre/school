// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Spring 2013

import java.util.Scanner;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.TreeSet;
import java.lang.Math;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.IOException;

public class BucketSorts
{
	public static void main(String args[]) throws FileNotFoundException
	{
		PrintWriter writer = new PrintWriter("output.txt");

		if(args.length == 0)
		{
			writer.println("Error: no files provided. Provide full path address.");
			System.out.println("Error: no files provided. Provide full path address.");
			return;
		}

		writer.println("The problem with First-Fit looks like it is continuously adding to the fourth bucket and refusing to create more, causing integer overflow and giving weird values. I do not know why more buckets are not created in the tournament tree, as when I hard-code the bucket-creating piece of the code that runs in my while-loop, new buckets are created and the algorithm works as intended, but if left to run in the loop (as it should) it refuses to create more than 4 buckets. The tournament tree was implemented using an array as explained in class. I tried the similar code using a TournamentTree class I made and the same problem occured.\n");

		for(String s : args)
		{
			Scanner scanner = new Scanner(new File(s));
			int[] weights;
			long sum = 0l;

			//counting how many weights there are in the file
			//ignores anything in the file which is not an integer
			//checks to make sure weights fall within the specified range and that there are enough weights
			while(scanner.hasNextInt())
			{
				int n = scanner.nextInt();

				//error checking
				if(n < 1 || n > 999999999)
				{
					writer.printf("Error: out of bounds value in %s. File ignored.\n", s);
					sum = -1l;
					break;
				}

				sum = sum + 1;
			}

			//error checking
			if(sum == -1l)
			{
				continue;
			}

			//error checking
			if(sum == 0)
			{
				writer.printf("Error: file %s contains no numbers. File ignored.");
				continue;
			}

			//error checking
			if(sum < 10 || sum > 1000000000)
			{
				writer.printf("Error: too many or too few weights in %s. File ignored.\n", s);
				continue;
			}

			scanner = new Scanner(new File(s));
			weights = new int[(int) sum];
			sum = 0;

			//reading input and populating the array of weights
			for(int i = 0; i < weights.length; i++)
			{
				int in = scanner.nextInt();
				weights[i] = in;
				sum = sum + in;
			}

			sum = sum / 1000000000;

			writer.printf("Analysis for file %s\nThe ideal number of bins is %d.\n", s, sum);

			//online algorithms
			writer.println("\nOnline algorithms:");
			writer.println("\tNext fit:");
			next_fit_online(weights, writer);
			writer.println("\tWorst fit:");
			worst_fit_online(weights, writer);
			writer.println("\tBest fit:");
			best_fit_online(weights, writer);
			writer.println("\tFirst fit (tournament tree):");
			first_fit_online(weights, writer);

			Arrays.sort(weights);

			//offline algorithms
			writer.println("\nOffline algorithms:");
			writer.println("\tNext fit:");
			next_fit_offline(weights, writer);
			writer.println("\tWorst fit:");
			worst_fit_offline(weights, writer);
			writer.println("\tBest fit:");
			best_fit_offline(weights, writer);
			writer.println("\tFirst fit (tournament tree):");
			first_fit_offline(weights, writer);

			writer.println();
		}

		writer.close();
	}

	//online algorithms
	public static void next_fit_online(int[] weights, PrintWriter writer)
	{
		long time = System.nanoTime();
		int bucketsize;
		ArrayList<Integer> buckets = new ArrayList<>();
		buckets.add(0);

		//next-fit algorithm
		for(int i = 0; i < weights.length; i++)
		{
			if(buckets.get(buckets.size() - 1) + weights[i] <= 1000000000)
				buckets.set(buckets.size() - 1, buckets.get(buckets.size() - 1) + weights[i]);
			else
				buckets.add(weights[i]);
		}

		bucketsize = buckets.size();
		writer.printf("\t\t%d bucket(s) used.\n", bucketsize);
		writer.print("\t\tFirst ten buckets' contents:");

		//prints first 10 buckets' contents, or all of the buckets if there are less than 10 buckets
		for(int i = 0; i < Math.min(bucketsize, 10); i++)
			writer.printf(" %d", buckets.get(i));

		long total_time = System.nanoTime() - time;
		writer.println("\n\t\tTime elapsed: " + total_time + " nanoseconds.");
	}

	public static void worst_fit_online(int[] weights, PrintWriter writer)
	{
		long time = System.nanoTime();
		int name = 0;
		int heapsize;
		PriorityQueue<WorstBin> heap = new PriorityQueue<>();
		heap.add(new WorstBin(name, weights[0]));

		//worst-fit algorithm
		for(int i = 0; i < weights.length; i++)
		{
			WorstBin worst = heap.poll();

			//if the bin with the most space can fit weights[i] then add it
			//else create a new bin
			if(worst.contents + weights[i] <= WorstBin.capacity)
			{
				worst.contents = worst.contents + weights[i];
				heap.add(worst);
			} else {
				name = name + 1;
				heap.add(worst);
				heap.add(new WorstBin(name, weights[i]));
			}
		}

		heapsize = heap.size();
		writer.printf("\t\t%d bucket(s) used.\n", heapsize);
		writer.print("\t\tFirst ten buckets' contents:");

		//prints first 10 buckets' contents, or all of the buckets if there are less than 10 buckets
		for(int i = 0; i < Math.min(heapsize, 10); i++)
			writer.printf(" %d", heap.poll().contents);

		long total_time = System.nanoTime() - time;
		writer.println("\n\t\tTime elapsed: " + total_time + " nanoseconds.");
	}

	public static void best_fit_online(int[] weights, PrintWriter writer)
	{
		long time = System.nanoTime();
		int name = 0;
		int bucketsize;
		TreeSet<BestBin> buckets = new TreeSet<>();
		buckets.add(new BestBin(name, weights[0]));

		//best-fit algorithm
		for(int i = 0; i < weights.length; i++)
		{
			boolean flag = false;
			BestBin best = buckets.first();

			//finds the heaviest bucket which can fit the next weight
			while(best.contents + weights[i] > BestBin.capacity)
			{
				BestBin better = buckets.lower(best);

				if(better == null)
				{
					flag = true;
					break;
				} else {
					best = better;
				}
			}

			//if no bucket was found, create a new bucket
			if(flag)
			{
				name = name + 1;
				buckets.add(new BestBin(name, weights[i]));
			} else {
				buckets.remove(best);
				best.contents = best.contents + weights[i];
				buckets.add(best);
			}
		}

		bucketsize = buckets.size();
		writer.printf("\t\t%d bucket(s) used.\n", bucketsize);
		writer.print("\t\tFirst ten buckets' contents:");

		//prints first 10 buckets' contents, or all of the buckets if there are less than 10 buckets
		for(int i = 0; i < Math.min(bucketsize, 10); i++)
			writer.printf(" %d", buckets.pollFirst().contents);

		long total_time = System.nanoTime() - time;
		writer.println("\n\t\tTime elapsed: " + total_time + " nanoseconds.");
	}

	public static void first_fit_online(int[] weights, PrintWriter writer)
	{
		long time = System.nanoTime();
		ArrayList<Bin> buckets = new ArrayList<>();
		ArrayList<Bin> tournament = new ArrayList<>();
		buckets.add(new Bin(weights[0]));
		tournament.add(null);
		tournament.add(new Bin());
		tournament.add(buckets.get(0));
		tournament.add(tournament.get(1));

		//first-fit algorithm
		for(int i = 0; i < weights.length; i++)
		{
			int root = 1; 
			int value = Bin.capacity - weights[i];
			boolean flag = false;

			//traverse the tree until a leaf is found
			while(4 * (root / 2) < tournament.size())
			{
				if(root == 1)
					root = 2;
				else
					root = 4 * (root / 2);

				//if the child to the left is greater than the target value, go to the right 
				if(tournament.get(root).contents > value)
				{
					//if no existing buckets are found, add to the zero bucket and create a new one
					if(root + 1 >= tournament.size())
					{
						buckets.add(new Bin());
						tournament.add(buckets.get(buckets.size() - 1));
					}

					root = root + 1;
				}
			}

			if(tournament.get(root).contents > value)
				root = root + 1;

			//if no match found, create a new bin
			if(tournament.get(root).contents == 0)
			{
				buckets.add(new Bin());
				tournament.add(buckets.get(buckets.size() - 1));
			}

			tournament.get(root).contents = tournament.get(root).contents + weights[i];

			while(root > 1)
			{
				root = root / 2;

				if(tournament.get(2 * root).contents < tournament.get(2 * root + 1).contents)
					tournament.set(root, tournament.get(2 * root));
				else
					tournament.set(root, tournament.get(2 * root + 1));
			}
		}

		writer.printf("\t\t%d bucket(s) used.\n", buckets.size() - 1);
		writer.print("\t\tFirst ten buckets' contents:");

		//prints first 10 buckets' contents, or all of the buckets if there are less than 10 buckets
		for(int i = 0; i < Math.min(buckets.size(), 10); i++)
			if(buckets.get(i).contents != 0)
				writer.printf(" %d", buckets.get(i).contents);

		long total_time = System.nanoTime() - time;
		writer.println("\n\t\tTime elapsed: " + total_time + " nanoseconds.");
	}

	//offline algorithms
	public static void next_fit_offline(int[] weights, PrintWriter writer)
	{
		long time = System.nanoTime();
		int bucketsize;
		ArrayList<Integer> buckets = new ArrayList<>();
		buckets.add(0);

		//next-fit algorithm
		for(int i = weights.length - 1; i >= 0; i--)
		{
			if(buckets.get(buckets.size() - 1) + weights[i] <= 1000000000)
				buckets.set(buckets.size() - 1, buckets.get(buckets.size() - 1) + weights[i]);
			else
				buckets.add(weights[i]);
		}

		bucketsize = buckets.size();
		writer.printf("\t\t%d bucket(s) used.\n", bucketsize);
		writer.print("\t\tFirst ten buckets' contents:");

		//prints first 10 buckets' contents, or all of the buckets if there are less than 10 buckets
		for(int i = 0; i < Math.min(bucketsize, 10); i++)
			writer.printf(" %d", buckets.get(i));

		long total_time = System.nanoTime() - time;
		writer.println("\n\t\tTime elapsed: " + total_time + " nanoseconds.");
	}

	public static void worst_fit_offline(int[] weights, PrintWriter writer)
	{
		long time = System.nanoTime();
		int name = 0;
		int heapsize;
		PriorityQueue<WorstBin> heap = new PriorityQueue<>();
		heap.add(new WorstBin(name, weights[weights.length - 1]));

		//worst-fit algorithm
		for(int i = weights.length - 2; i >= 0; i--)
		{
			WorstBin worst = heap.peek();

			//if the bin with the most space can fit weights[i] then add it
			//else create a new bin
			if(worst.contents + weights[i] <= WorstBin.capacity)
			{
				heap.poll();
				worst.contents = worst.contents + weights[i];
				heap.add(worst);
			} else {
				name = name + 1;
				heap.add(new WorstBin(name, weights[i]));
			}
		}

		heapsize = heap.size();
		writer.printf("\t\t%d bucket(s) used.\n", heapsize);
		writer.print("\t\tFirst ten buckets' contents:");

		//prints first 10 buckets' contents, or all of the buckets if there are less than 10 buckets
		for(int i = 0; i < Math.min(heapsize, 10); i++)
			writer.printf(" %d", heap.poll().contents);

		long total_time = System.nanoTime() - time;
		writer.println("\n\t\tTime elapsed: " + total_time + " nanoseconds.");
	}

	public static void best_fit_offline(int[] weights, PrintWriter writer)
	{
		long time = System.nanoTime();
		int name = 0;
		int bucketsize;
		TreeSet<BestBin> buckets = new TreeSet<>();
		buckets.add(new BestBin(name, weights[weights.length - 1]));

		//best-fit algorithm
		for(int i = weights.length - 2; i >= 0; i--)
		{
			boolean flag = false;
			BestBin best = buckets.first();

			//finds the heaviest bucket which can fit the next weight
			while(best.contents + weights[i] > BestBin.capacity)
			{
				BestBin better = buckets.lower(best);

				if(better == null)
				{
					flag = true;
					break;
				} else {
					best = better;
				}
			}

			//if no bucket was found, create a new bucket
			if(flag)
			{
				name = name + 1;
				buckets.add(new BestBin(name, weights[i]));
			} else {
				buckets.remove(best);
				best.contents = best.contents + weights[i];
				buckets.add(best);
			}
		}

		bucketsize = buckets.size();
		writer.printf("\t\t%d bucket(s) used.\n", bucketsize);
		writer.print("\t\tFirst ten buckets' contents:");

		//prints first 10 buckets' contents, or all of the buckets if there are less than 10 buckets
		for(int i = 0; i < Math.min(bucketsize, 10); i++)
			writer.printf(" %d", buckets.pollFirst().contents);

		long total_time = System.nanoTime() - time;
		writer.println("\n\t\tTime elapsed: " + total_time + " nanoseconds.");
	}

	public static void first_fit_offline(int[] weights, PrintWriter writer)
	{
		long time = System.nanoTime();
		ArrayList<Bin> buckets = new ArrayList<>();
		ArrayList<Bin> tournament = new ArrayList<>();
		buckets.add(new Bin(weights[weights.length - 1]));
		tournament.add(null);
		tournament.add(new Bin());
		tournament.add(buckets.get(0));
		tournament.add(tournament.get(1));

		//first-fit algorithm
		for(int i = weights.length - 2; i >= 0; i--)
		{
			int root = 1; 
			int value = Bin.capacity - weights[i];
			boolean flag = false;

			//traverse the tree until a leaf is found
			while(4 * (root / 2) < tournament.size())
			{
				if(root == 1)
					root = 2;
				else
					root = 4 * (root / 2);

				//if the child to the left is greater than the target value, go to the right 
				if(tournament.get(root).contents > value)
				{
					//if no existing buckets are found, add to the zero bucket and create a new one
					if(root + 1 >= tournament.size())
					{
						buckets.add(new Bin());
						tournament.add(buckets.get(buckets.size() - 1));
					}

					root = root + 1;
				}
			}

			if(tournament.get(root).contents > value)
				root = root + 1;

			//if no match found, create a new bin
			if(tournament.get(root).contents == 0)
			{
				buckets.add(new Bin());
				tournament.add(buckets.get(buckets.size() - 1));
			}

			tournament.get(root).contents = tournament.get(root).contents + weights[i];

			while(root > 1)
			{
				root = root / 2;

				if(tournament.get(2 * root).contents < tournament.get(2 * root + 1).contents)
					tournament.set(root, tournament.get(2 * root));
				else
					tournament.set(root, tournament.get(2 * root + 1));
			}
		}

		writer.printf("\t\t%d bucket(s) used.\n", buckets.size() - 1);
		writer.print("\t\tFirst ten buckets' contents:");

		//prints first 10 buckets' contents, or all of the buckets if there are less than 10 buckets
		for(int i = 0; i < Math.min(buckets.size(), 10); i++)
			if(buckets.get(i).contents != 0)
				writer.printf(" %d", buckets.get(i).contents);

		long total_time = System.nanoTime() - time;
		writer.println("\n\t\tTime elapsed: " + total_time + " nanoseconds.");
	}
}

class Bin
{
	int contents;
	static int capacity = 1000000000;

	public Bin()
	{
		this.contents = 0;
	}

	public Bin(int contents)
	{
		this.contents = contents;
	}
}

class WorstBin implements Comparable<WorstBin>
{
	int name;
	int contents;
	static int capacity = 1000000000;

	public WorstBin(int name)
	{
		this.name = name;
		this.contents = 0;
	}

	public WorstBin(int name, int contents)
	{
		this.name = name;
		this.contents = contents;
	}

	//compares based on which bin has more space left
	//ties are broken by which bin has the lower name
	public int compareTo(WorstBin bin)
	{
		int difference = (WorstBin.capacity - bin.contents) - (WorstBin.capacity - this.contents);

		if(difference == 0)
			return this.name - bin.name;

		return difference;
	}
}

class BestBin implements Comparable<BestBin>
{
	int name;
	int contents;
	static int capacity = 1000000000;

	public BestBin(int name)
	{
		this.name = name;
		this.contents = 0;
	}

	public BestBin(int name, int contents)
	{
		this.name = name;
		this.contents = contents;
	}

	//compares based on which bin has less space left
	//ties are broken by which bin has the lower name
	public int compareTo(BestBin bin)
	{
		int difference = (BestBin.capacity - this.contents) - (BestBin.capacity - bin.contents);

		if(difference == 0)
			return this.name - bin.name;

		return difference;
	}
}
