// package Day11;

import java.util.*;
import java.io.*;

public class blinkingRocks{
    public static void main(String[] args) {
        // String filename = "test11.txt";
        String filename = "input11.txt";
        ArrayList<Long> list = new ArrayList<>();
        try{
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String line = br.readLine();
            long[] n = {0};
            if(line != null)
            {
                String[] nums = line.split(" ");
                n = Arrays.stream(nums).mapToLong(Long::parseLong).toArray();
            }
            for(int i = 0; i< n.length; i++)
            {
                list.add(n[i]);
            }
            br.close();
        }
        catch(IOException e)
        {
            System.out.println("There was an error in reading the file.");
            System.exit(0);;
        }
        catch(NumberFormatException e)
        {
            System.out.println("The numbers are not in the proper format");
            System.exit(0);
        }
        int blinks = 25;
        for(int i = 0; i< blinks; i++)
        {
            list = modifyingList(list);
            //printArrayList(list);
        }
        System.out.println("There are " + list.size() + " stones.");
    }

    static ArrayList<Long> modifyingList(ArrayList<Long> list)
    {
        ArrayList<Long> temp = new ArrayList<>();
        Iterator<Long> trav = list.iterator();
        while(trav.hasNext())
        {
            long n = trav.next();
            if(n == 0)
            {
                temp.add(1L);
            }
            else if((Long.toString(n)).length()% 2 == 0)
            {
                int len = Long.toString(n).length();
                int pow = (int)Math.pow(10, len/2);
                long n1 = n/pow;
                long n2 = n%pow;
                temp.add(n1);
                temp.add(n2);
            }
            else{
                temp.add(n * 2024);
            }
        }
        return temp;
    }

    static void printArrayList(ArrayList<Long> list)
    {
        Iterator<Long> i = list.iterator();
        while(i.hasNext())
        {
            System.out.print(i.next() + " ");
        }
        System.out.println();
        return;
    }
}