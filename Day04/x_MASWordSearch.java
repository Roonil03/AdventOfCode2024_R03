//package Day04;

import java.util.*;
import java.io.*;
public class x_MASWordSearch {
    //final static String word = "MAS";

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

    static boolean valid(int x, int y, int m, int n) {
        return (x >= 1 && x < m-1 && y >= 1 && y < n-1);
    }

    static int searchWord(char[][] grid)
    {
        int count = 0;
        int m = grid.length;
        int n = grid[0].length;
        for(int i = 0; i<m; i++)
        {
            for(int j = 0; j<n;j++)
            {
                if(grid[i][j] == 'A' && isTwitter(grid,i,j))
                {
                    count++;
                }
            }
        }
        return count;
    }

    // 
    
    static boolean isTwitter(char[][] grid, int x, int y) {
        int m = grid.length;
        int n = grid[0].length;
        if (valid(x, y, m, n)) {
            return (checkDirection(grid, x, y, -1, -1) && checkDirection(grid, x, y, -1, 1)|| 
                    checkDirection(grid, x, y, -1, 1) && checkDirection(grid, x, y, 1, -1)||
                    checkDirection(grid, x, y, 1, -1) && checkDirection(grid, x, y, 1, 1)||
                    checkDirection(grid, x, y, 1, 1) && checkDirection(grid, x, y, -1, -1) ||
                    checkDirection(grid, x, y, -1, -1) && checkDirection(grid, x, y, 1, -1) ||
                    checkDirection(grid, x, y, -1, 1) && checkDirection(grid, x, y, 1, 1)
                    );
                //4 C 2 combinations possible = 6 possible combinations
        }
        return false;
    }

    static boolean checkDirection(char[][] grid, int x, int y, int dirX, int dirY) {
        if (grid[x + dirX][y + dirY] == 'M' && grid[x][y] == 'A' && grid[x - dirX][y - dirY] == 'S') {
            return true;
        }
        return false;
    }
}
