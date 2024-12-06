//package Day06;

import java.util.*;
import java.io.*;

public class forwardGuard{
    public static void main(String[] args) {
        // String filename = "input6.txt";
        String filename = "test6.txt";
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
        System.out.println("The number of positions  are: " + distinctPositions(mat));
    }

    static int distinctPositions(char[][]mat)
    {
        int m = mat.length;
        int n = mat[0].length;
        boolean touched[][] = new boolean[m][n];
        int dx[] = {0, 1, 0, -1};
        int dy[] = {-1, 0, 1, 0};
        int count = 0;
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
        touched[posY][posX] = true;
        count++;
        int ind = 0;
        //printArray(mat);
        while(validCoords(posX, posY, m, n))
        {
            //System.out.println(dx[ind] + " " + dy[ind]);
            if(!validCoords(posY+dy[ind], posX+dx[ind], m,n))
            {
                return count;
            }
            else if(mat[posY+dy[ind]][posX+dx[ind]] == '#')
            {
                ind = (ind+1)%4;
            }
            else{
                mat[posY][posX] = '.';
                posX += dx[ind];
                posY += dy[ind];
                mat[posY][posX] = '^';
                if(!(touched[posY][posX]))
                {
                    count++;
                    touched[posY][posX] = true;
                }
            }
            //printArray(mat);
        }
        return -1;
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
        System.out.println("\n");
    }
}