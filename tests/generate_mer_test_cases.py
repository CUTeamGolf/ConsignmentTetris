#!/usr/bin/python3

import sys
import numpy as np

def make_grid(m, n, p):
    """ Makes a m x n boolean grid where approximately p * 100 % of
        the entries are true """
    return np.random.binomial(1, p=p, size=(m, n))

def is_mer(grid, llx, lly, urx, ury):
    """ Checks if the rectangle is a MER
        NOTE: exclusive ur """

    # (0, 2) (1, 3)
    def is_empty(lx, ly, ux, uy):
        # Check that all are 0s
        for x in range(lx, ux):
            for y in range(ly, uy):
                if grid[x][y]:
                   return False
        return True

    # Check that no expansion can be made
    return is_empty(llx, lly, urx, ury) and \
            (llx == 0 or not is_empty(llx - 1, lly, urx, ury)) and \
            (ury == len(grid[0]) or not is_empty(llx, lly, urx, ury + 1)) and \
            (urx == len(grid) or not is_empty(llx, lly, urx + 1, ury)) and \
            (lly == 0 or not is_empty(llx, lly - 1, urx, ury))

def print_cpp_code(grid, sols, m, n):
    # create a pretty diagram
    diagram = ""
    for y in range(n - 1, -1, -1):
        diagram += "// "
        for x in range(m):
            diagram += str(int(grid[x][y]))
        diagram += "\n"

    # create the boolean matrix
    matrix = f"bool occupied[{m}][{n}] = {{\n"
    for x in range(m):
        matrix += "\t{"
        for y in range(n):
            if y != 0:
                matrix += ", "
            matrix += str(int(grid[x][y]))
        matrix += "}"
        if x != m - 1:
            matrix += ","
        matrix += "\n"
    matrix += "};"

    # invoke the algorithm
    invoke = f"std::vector<MaximumEmptyRectangle> rects = find_all_maximum_empty_rectangles<{m}, {n}>(occupied);"

    # create the expected results
    results = f"MaximumEmptyRectangle expected_mers[{len(sols)}] = {{\n"
    for i in range(len(sols)):
        results += f"\t{{{sols[i][0]}, {sols[i][1]}, {sols[i][2]}, {sols[i][3]}}}"
        if i != len(sols) - 1:
            results += ","
        results += "\n"
    results += "};"

    print(diagram)
    print(matrix)
    print()
    print(invoke)
    print()
    print(results)



if __name__ == "__main__":
    # Read input arguments
    if len(sys.argv) != 4:
        print("Usage:\n\t./generate_mer_test_cases m n p")
        exit()

    try:
        m = int(sys.argv[1])
        n = int(sys.argv[2])
        p = float(sys.argv[3])

    except ValueError:
        print("Usage:\n\t./generate_mer_test_cases m n p")
        exit()

    # Make a random grid
    grid = make_grid(m, n, p)
    # Find the MERs
    sols = []
    for x in range(m):
        for y in range(n):
            for x2 in range(x + 1, m + 1):
                for y2 in range(y + 1, n + 1):
                    if is_mer(grid, x, y, x2, y2):
                        sols.append((x, y, x2, y2))

    # print the C++ code
    print_cpp_code(grid, sols, m, n)
