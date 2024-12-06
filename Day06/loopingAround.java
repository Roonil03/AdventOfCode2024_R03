import java.util.*;
import java.io.*;

public class loopingAround {
    public static void main(String[] args) {
        String filename = "input6.txt"; 
        // String filename = "test6.txt";
        List<char[]> inputMat = new ArrayList<>();
        try{
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String line;
            while(((line = br.readLine()) != null))
            {
                inputMat.add(line.toCharArray());
            }
            br.close();
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        catch(Exception g)
        {
            g.printStackTrace();
            System.out.println("There was an error");
            System.exit(0);
        }
        char[][] mat = inputMat.toArray(new char[0][]);
        System.out.println("The number of loops are: " + loopsFormed(mat));
    }

    static int loopsFormed(char[][] mat)
    {
        int count = 0;
        int m = mat.length;
        int n = mat[0].length;
        for(int i = 0; i< m; i++)
        {
            for(int j = 0; j< n; j++)
            {
                //char mat2[][] = copy(mat);
                System.out.println(i + " " + j + "\t" + count);
                if(mat[i][j] == '.')
                {
                    mat[i][j] = 'O';
                    //printArray(mat);
                    if(distinctPositions(mat))
                    {
                        count++;
                    }
                    mat[i][j] = '.';
                }
            }
        }
        return count;
    }

    static boolean distinctPositions(char[][]mat)
    {
        int m = mat.length;
        int n = mat[0].length;
        int times[][] = new int[m][n];
        int dx[] = {0, 1, 0, -1};
        int dy[] = {-1, 0, 1, 0};
        int posX = 0, posY = 0;
        for(int i = 0; i< m; i++){
            for(int j = 0; j< n; j++)
            {
                if(mat[i][j] == '^')
                {
                    posY = i;
                    posX = j;
                    break;
                }
            }
        }
        times[posY][posX]++;
        int ind = 0;
        //printArray(mat);
        while(times[posX][posY] <= 5551)
        {;
            if(!validCoords(posY+dy[ind], posX+dx[ind], m,n))
            {
                return false;
            }
            else if(mat[posY+dy[ind]][posX+dx[ind]] == '#' || mat[posY + dy[ind]][posX+dx[ind]] == 'O')
            {
                ind = (ind+1)%4;
                times[posX][posY]++;
            }
            else{
                posX += dx[ind];
                posY += dy[ind];
                times[posY][posX]++;
            }
            //printArray(mat);
        }
        return true;
    }

    static boolean validCoords(int x, int y, int m, int n)
    {
        return (x>=0 && x<m && y>= 0 && y<n);
    }

    static void printArray(char[][]  mat)
    {
        for(char c[] : mat)
        {
            for(char s: c)
            {
                System.out.print(s + " ");
            }
            System.out.println("");
        }
        System.err.println("\n");
    }

    // static char[][] copy(char[][] mat)
    // {
    //     char [][] copy = new char[mat.length][mat[0].length];
    //     for(int i = 0; i< mat.length; i++)
    //     {
    //         for(int j = 0; j< mat[i].length; j++)
    //         {
    //             copy[i][j] = mat[i][j];
    //         }
    //     }
    //     return copy;
    // }
}