// package Day13;

import java.util.*;
import java.io.*;

public class deltaMax{    
    final static long del = 10000000000000L;

    public static void main(String[] args) {
        int claws[][] = readingFile();
        long sum = 0;
        for(int i[] : claws)
        {
            int ax = i[0];
            int ay = i[1];
            int bx = i[2];
            int by = i[3];
            int px = i[4];
            int py = i[5];
            sum += totalCost(ax, ay, bx, by, px+del, py+del);
            //System.out.println(count++ +"\t" + sum);
        }
        System.out.println("The total cost is: " + sum);
    }
    static int[][] readingFile()
    {
        List<int[]> claws = new ArrayList<>();
        // String filename = "test13.txt";
        String filename = "input13.txt";
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) 
        {
            String line;
            int[] claw = new int[6];
            int index = 0;    
            while ((line = br.readLine()) != null) {
                line = line.trim();    
                if (line.isEmpty()) 
                {
                    claws.add(claw);
                    claw = new int[6];
                    index = 0;
                } 
                else if (line.startsWith("Button A:")) 
                {
                    String[] parts = line.split(",");
                    claw[0] = Integer.parseInt(parts[0].split("\\+")[1].trim()); 
                    claw[1] = Integer.parseInt(parts[1].split("\\+")[1].trim()); 
                } 
                else if (line.startsWith("Button B:")) 
                {
                    String[] parts = line.split(",");
                    claw[2] = Integer.parseInt(parts[0].split("\\+")[1].trim()); 
                    claw[3] = Integer.parseInt(parts[1].split("\\+")[1].trim()); 
                } 
                else if (line.startsWith("Prize:")) 
                {
                    String[] parts = line.split(",");
                    claw[4] = Integer.parseInt(parts[0].split("=")[1].trim()); 
                    claw[5] = Integer.parseInt(parts[1].split("=")[1].trim());
                }
            }
            if (index > 0) 
            {
                claws.add(claw);
            }

        } 
        catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
        return claws.toArray(new int[0][]);
    }

    static long totalCost(int Ax, int Ay, int Bx, int By, long posX, long posY)
    {
        long minCost = 0;
        double a = ((double)posX* By - (double)posY * Bx)/ ((double)Ax*By - (double)Ay*Bx);
        double b = ((double)posY*Ax - (double)posX*Ay) / ((double)Ax*By - (double)Ay*Bx);
        if(a == (long)a && b == (long)b)
            minCost += (long)(3*a + b);
        return minCost;
    }
}
