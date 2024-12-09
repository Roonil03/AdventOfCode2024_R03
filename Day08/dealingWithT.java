import java.io.*;
import java.util.*;

public class dealingWithT {
    public static void main(String[] args) {
        String filename = "input8.txt";
        // String filename = "test8.txt";
        try {
            char[][] input = readFile(filename);
            int[][][] freqs = processChars(input);
            int[][] map = new int[input.length][input[0].length];
            uselessT(map, freqs);
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
        }
    }

    static char[][] readFile(String filename) throws IOException {
        List<String> lines = new ArrayList<>();
        BufferedReader reader = new BufferedReader(new FileReader(filename));
        String line;
        while ((line = reader.readLine()) != null) {
            lines.add(line);
        }
        reader.close();
        
        char[][] input = new char[lines.size()][lines.get(0).length()];
        for (int i = 0; i < lines.size(); i++) {
            input[i] = lines.get(i).toCharArray();
        }
        return input;
    }

    static int[][][] processChars(char[][] input) {
        int[][][] freqs = new int[62][30][2];
        for (int i = 0; i < 62; i++) {
            for (int j = 0; j < 30; j++) {
                freqs[i][j][0] = -1;
            }
        }
        for (int y = 0; y < input.length; y++) {
            for (int x = 0; x < input[0].length; x++) {
                char c = input[y][x];
                if (c == '.' || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                    int index = getIndex(c);
                    if (index != -1) {
                        int i = 0;
                        while (freqs[index][i][0] != -1) {
                            i++;
                        }
                        freqs[index][i][0] = y;
                        freqs[index][i][1] = x;
                    }
                }
            }
        }
        return freqs;
    }

    static int getIndex(char c) {
        if (c >= '0' && c <= '9') {
            return c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            return c - 'A' + 10;
        } else if (c >= 'a' && c <= 'z') {
            return c - 'a' + 36;
        }
        return -1;
    }

    static void uselessT(int[][] map, int[][][] freqs) {
        for (int i = 0; i < 62; i++) {
            if (freqs[i][0][0] != -1) {
                for (int j = 0; freqs[i][j][0] != -1; j++) {
                    for (int k = 0; freqs[i][k][0] != -1; k++) {
                        if (j == k) continue;
                        int X = freqs[i][j][1];
                        int Y = freqs[i][j][0];
                        int deltaX = X - freqs[i][k][1];
                        int deltaY = Y - freqs[i][k][0];
                        while (X >= 0 && X < map[0].length && Y >= 0 && Y < map.length) {
                            map[Y][X]++;
                            X += deltaX;
                            Y += deltaY;
                        }
                    }
                }
            }
        }
        int count = 0;
        for (int i = 0; i < map.length; i++) {
            for (int j = 0; j < map[0].length; j++) {
                if (map[i][j] > 0) {
                    count++;
                }
            }
        }
        System.out.println("Part 2: " + count);
    }
}
