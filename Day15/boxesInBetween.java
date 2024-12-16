import java.io.*;
import java.util.*;

public class boxesInBetween {
    static int rX = -1, rY = -1, dR, dC;
    static List<int[]> walls = new ArrayList<>();
    static List<int[]> boxes = new ArrayList<>();
    static String directions = "";

    public static void main(String[] args) throws IOException {
        // readInput("test15_1.txt");
        readInput("input15.txt");
        processDirections();
        System.out.println(calculateResult());
    }

    static void readInput(String fileName) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(fileName));
        boolean isDirections = false;
        int row = 0;
        String line;
        while ((line = br.readLine()) != null) {
            line = line.trim();
            if (line.isEmpty()) {
                isDirections = true;
                continue;
            }
            if (isDirections) {
                directions += line;
            } else {
                parseRow(line, row);
                row++;
            }
        }
        br.close();
    }

    static void parseRow(String line, int row) {
        int col = 0;
        for (char ch : line.toCharArray()) {
            if (ch == '@') {
                rX = row;
                rY = col;
            }
            if (ch == '#') {
                walls.add(new int[]{row, col});
                walls.add(new int[]{row, col + 1});
            }
            if (ch == 'O') {
                boxes.add(new int[]{row, col});
            }
            col += 2;
        }
    }

    static void processDirections() {
        for (char dir : directions.toCharArray()) {
            setDirection(dir);
            if (dR != -2) {
                moveRobot();
            }
        }
    }

    static void setDirection(char dir) {
        dR = -2;
        if (dir == '^') { dR = -1; dC = 0; }
        if (dir == 'v') { dR = 1; dC = 0; }
        if (dir == '<') { dR = 0; dC = -1; }
        if (dir == '>') { dR = 0; dC = 1; }
    }

    static void moveRobot() {
        int nR = rX + dR, nC = rY + dC;
        if (hitsWall(nR, nC)) return;

        int[] boxInWay = null;
        for (int[] box : boxes) {
            if (nR == box[0] && nC == box[1]) {
                boxInWay = box;
                break;
            }
        }

        if (boxInWay == null) {
            rX = nR;
            rY = nC;
            return;
        }

        if (moveBoxes(boxInWay)) {
            rX = nR;
            rY = nC;
        }
    }

    static boolean moveBoxes(int[] startBox) {
        boolean canMove = true;
        Queue<int[]> toCheck = new LinkedList<>();
        List<int[]> toMove = new ArrayList<>();
        toCheck.add(startBox);

        while (!toCheck.isEmpty()) {
            int[] box = toCheck.poll();
            if (toMove.contains(box)) continue;

            int nBX = box[0] + dR, nBY = box[1] + dC;
            if (hitsWall(nBX, nBY) || hitsWall(nBX, nBY + 1)) {
                canMove = false;
                break;
            }

            toMove.add(box);
            for (int[] other : boxes) {
                if (!toMove.contains(other) && nBX == other[0] && Math.abs(nBY - other[1]) <= 1) {
                    toCheck.add(other);
                }
            }
        }

        if (canMove) {
            for (int[] box : toMove) {
                box[0] += dR;
                box[1] += dC;
            }
        }
        return canMove;
    }

    static boolean hitsWall(int row, int col) {
        for (int[] wall : walls) {
            if (row == wall[0] && col == wall[1]) return true;
        }
        return false;
    }

    static int calculateResult() {
        int total = 0;
        for (int[] box : boxes) {
            total += 100 * box[0] + box[1];
        }
        return total;
    }
}
