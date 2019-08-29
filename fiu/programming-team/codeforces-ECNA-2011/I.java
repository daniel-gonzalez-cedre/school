// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Fall 2013
// Codeforces Eastern Central North America (ECNA) 2011: Wally World

import java.util.Scanner;
import java.lang.Math;

public class I
{
    public static void main(String args[])
    {
        Scanner scanner = new Scanner(System.in);
        String result = "";
        int counter = 1;
        
        int x1 = scanner.nextInt();
        int y1 = scanner.nextInt();
        int x2 = scanner.nextInt();
        int y2 = scanner.nextInt();
        
        while(x1 != 0 && x2 != 0 && y1 != 0 && y2 != 0)
        {
            Point lover1 = new Point(x1, y1);
            Point lover2 = new Point(x2, y2);
            Line lovers = new Line(x1, y1, x2, y2);
            Line wall = new Line(scanner.nextInt(), scanner.nextInt(), scanner.nextInt(), scanner.nextInt());
            Point wall1 = new Point(wall.x1, wall.y1);
            Point wall2 = new Point(wall.x2, wall.y2);
            
            if(wall.intersects(lovers))
            {
                double distance = Math.min(lover1.distanceToPoint(wall1) + lover2.distanceToPoint(wall1), lover1.distanceToPoint(wall2) + lover2.distanceToPoint(wall2));
                result = result + String.format("Case %d: %.3f\n", counter, distance/2.0);
            } else {
                result = result + String.format("Case %d: %.3f\n", counter, (lover1.distanceToPoint(lover2))/2.0);
            }
            
            counter = counter + 1;
            x1 = scanner.nextInt();
            y1 = scanner.nextInt();
            x2 = scanner.nextInt();
            y2 = scanner.nextInt();
        }
        
        System.out.print(result.substring(0, result.length() - 1));
    }
}

class Point
{
    double x;
    double y;
    
    public Point(double x, double y)
    {
        this.x = x;
        this.y = y;
    }
    
    public double distanceToPoint(Point p)
    {
        return Math.sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }
}

class Line
{
    double x1;
    double y1;
    double x2;
    double y2;
    
    public Line(double x1, double y1, double x2, double y2)
    {
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
    }
    
    public boolean intersects(Line l)
    {
        if((leftTurnTest(this, l.x1, l.y1) * leftTurnTest(this, l.x2, l.y2) < 0) && (leftTurnTest(l, x1, y1) * leftTurnTest(l, x2, y2) < 0))
            return true;
        
        return false;
    }
    
    /*
     * <0 if point on right
     * =0 if point on line
     * >0 if point on left
     */
    public int leftTurnTest(Line l, double px, double py)
    {
        double dx1 = l.x2 - l.x1;
        double dy1 = l.y2 - l.y1;
        double dx2 = px - l.x1;
        double dy2 = py - l.y1;
        
        double c = dx1 * dy2 - dy1 * dx2;
        
        return (int) c;
    }
}
