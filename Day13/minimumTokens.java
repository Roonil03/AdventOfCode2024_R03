// package Day13;

import java.util.*;
import java.io.*;

public class minimumTokens{
    public static void main(String[] args) {
        int claws[][] = readingFile();
        long sum = 0;
        int count = 1;
        for(int i[] : claws)
        {
            int ax = i[0];
            int ay = i[1];
            int bx = i[2];
            int by = i[3];
            int px = i[4];
            int py = i[5];
            sum += totalCost(ax, ay, bx, by, px, py);
            System.out.println(count++ +"\t" + sum);
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

    static long totalCost(int Ax, int Ay, int Bx, int By, int posX, int posY)
    {
        long minCost = Long.MAX_VALUE;
        for(int i = 0; i<= 1000; i++)
        {
            for(int j = 0; j<= 1000; j++)
            {
                if(i*Ax + Bx*j == posX && j*By + Ay*i == posY)
                {
                    System.out.println(i + " " + j + ": " + posX + " " + posY);
                    if(minCost > i*3 + j)
                    {
                        minCost = i*3 + j;
                    }
                }
            }
        }
        return minCost == Long.MAX_VALUE?0:minCost;
    }
}
