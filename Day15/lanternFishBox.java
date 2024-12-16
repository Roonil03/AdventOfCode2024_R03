import java.io.*;
import java.util.*;

public class lanternFishBox {
    static final int dirs = 4;
    static final int[] dRow = {-1, 0, 1, 0};
    static final int[] dCol = {0, -1, 0, 1};
    static final char[] dName = {'^', '<', 'v', '>'};

    public static void main(String[] args) throws IOException {
        List<char[]> board = new ArrayList<>();
        String filename = "input15.txt";
        // String filename = "test15_1.txt";
        BufferedReader br = new BufferedReader(new FileReader(filename));
        String line;
        while ((line = br.readLine()) != null && !line.isEmpty()) {
            board.add(line.toCharArray());
        }
        String commands = br.readLine();
        int rows = board.size();
        int cols = board.get(0).length;
        int row = 0, col = 0;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (board.get(r)[c] == '@') {
                    board.get(r)[c] = '.';
                    row = r;
                    col = c;
                }
            }
        }

        for (char dir : commands.toCharArray()) {
            int d = findDir(dir);
            int nRow = row, nCol = col;
            do {
                nRow += dRow[d];
                nCol += dCol[d];
            } while (board.get(nRow)[nCol] == 'O');
            if (board.get(nRow)[nCol] == '#') continue;
            do {
                swap(board, nRow, nCol, nRow - dRow[d], nCol - dCol[d]);
                nRow -= dRow[d];
                nCol -= dCol[d];
            } while (row != nRow || col != nCol);
            row += dRow[d];
            col += dCol[d];
        }

        int res = 0;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (board.get(r)[c] == 'O') {
                    res += 100 * r + c;
                }
            }
        }
        System.out.println(res);
    }

    static int findDir(char dir) {
        for (int i = 0; i < dirs; i++) {
            if (dName[i] == dir) return i;
        }
        return -1;
    }

    static void swap(List<char[]> board, int r1, int c1, int r2, int c2) {
        char temp = board.get(r1)[c1];
        board.get(r1)[c1] = board.get(r2)[c2];
        board.get(r2)[c2] = temp;
    }
}
