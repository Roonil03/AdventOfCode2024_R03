//package Day04;

import java.util.*;
import java.io.*;

public class xmasWordSearch{
    final static String word = "XMAS";

    static boolean validCoord(int x, int y, int m, int n) {
        return (x >= 0 && x < m && y >= 0 && y < n);
    }

    static boolean findWord(char[][] grid, int x, int y, int dirX, int dirY) {
        int m = grid.length;
        int n = grid[0].length;
        for (int i = 0; i < word.length(); i++) {
            if (!validCoord(x, y, m, n) || grid[x][y] != word.charAt(i)) {
                return false;
            }
            x += dirX;
            y += dirY;
        }
        return true;
    }

    static int searchWord(char[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        int count = 0;
        int[] x = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int[] y = { -1, 0, 1, -1, 1, -1, 0, 1 };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < 8; k++) {
                    if (findWord(grid, i, j, x[k], y[k])) {
                        count++;
                    }
                }
            }
        }

        return count;
    }

    public static void main(String[] args)
    {
        String filename = "input4.txt";
        //String filename = "test4.txt";
        char[][] grid = null;
        try{
            BufferedReader br = new BufferedReader(new FileReader(filename));
            List<String> lines = new ArrayList<>();
            String line;
            while ((line = br.readLine()) != null) {
                lines.add(line);
            }
            br.close();
            int rows = lines.size();
            int cols = lines.get(0).length();
            grid = new char[rows][cols];
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    grid[i][j] = lines.get(i).charAt(j);
                }
            }
            System.out.println("Number of times it occured is: " +searchWord(grid));

        }
        catch(IOException e)
        {
            System.out.println(e);
        }
        catch(Exception e)
        {
            System.out.println(e);
        }
        finally{
            System.exit(0);
        }
    }
}