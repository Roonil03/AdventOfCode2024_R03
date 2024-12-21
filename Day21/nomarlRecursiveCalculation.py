import os
from functools import cache

@cache
def keypad(x, y, dx, dy, pos, invalid):
    ret = None
    todo = [(x, y, "")]
    dirs = [(-1, 0, "<"), (1, 0, ">"), (0, -1, "^"), (0, 1, "v")]

    while len(todo) > 0:
        x, y, path = todo.pop(0)
        if (x, y) == (dx, dy):
            ret = minn(ret, bestMat(path + "A", pos - 1))
        elif (x, y) != invalid:
            for ox, oy, val in dirs:
                if isDir(x, dx, ox) or isDir(y, dy, oy):
                    todo.append((x + ox, y + oy, path + val))
    return ret

@cache
def bestMat(path, pos):
    if pos == 1:
        return len(path)

    ret = 0
    pad = decode(" ^A<v>", 3)
    x, y = pad["A"]

    for val in path:
        dx, dy = pad[val]
        ret += keypad(x, y, dx, dy, pos, pad[" "])
        x, y = dx, dy
    return ret

def minn(*vals):
    vals = [x for x in vals if x is not None]
    return vals[0] if len(vals) == 1 else min(*vals)

def decode(val, width):
    return {val: (x % width, x // width) for x, val in enumerate(val)}

def isDir(start, dest, change):
    return (change < 0 and dest < start) or (change > 0 and dest > start)

def cheapest(x, y, dx, dy, pos, invalid):
    ret = None
    todo = [(x, y, "")]
    dirs = [(-1, 0, "<"), (1, 0, ">"), (0, -1, "^"), (0, 1, "v")]

    while len(todo) > 0:
        x, y, path = todo.pop(0)
        if (x, y) == (dx, dy):
            ret = minn(ret, bestMat(path + "A", pos))
        elif (x, y) != invalid:
            for ox, oy, val in dirs:
                if isDir(x, dx, ox) or isDir(y, dy, oy):
                    todo.append((x + ox, y + oy, path + val))
    return ret

def calc(vals):
    ret = 0
    pad = decode("789456123 0A", 3)
    for row in vals:
        res = 0
        x, y = pad["A"]
        for val in row:
            dx, dy = pad[val]
            res += cheapest(x, y, dx, dy, 3, pad[" "])
            x, y = dx, dy
        ret += res * int(row[:-1].lstrip("0"))
    return ret

def run(vals):
    result = calc(vals)
    print(f"Result: {result}")

fn = 'Day21/input21.txt'
# filename = 'Day21/test21.txt'
with open(filename) as f:
    vals = [x.strip("\r\n") for x in f.readlines()]
run(vals)
