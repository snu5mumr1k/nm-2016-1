#!/usr/bin/python3


import numpy as np
import math


EPS = 1e-6


def solve(A, b):
    if np.linalg.matrix_rank(A) < len(A):
        return np.array([np.nan] * len(A))
    return np.linalg.solve(A, b)


def system_from_file(filename):
    fin = open(file=filename, mode="r")
    n = int(fin.readline())
    data = np.array([list(map(float, fin.readline().split())) for i in range(n)])
    A = data[:, :n]
    b = data[:, n]
    return A, b


def generate(n, m, x):
    Q = 1.001 - 2 * m * 0.001
    A = np.eye(n)
    b = np.zeros(n)
    for i in range(n):
        b[i] = x * math.exp(x / (i + 1)) * math.cos(x / (i + 1))
        for j in range(n):
            if i == j:
                A[i][j] = (Q - 1) ** (i + j + 2)
            else:
                A[i][j] = Q ** (i + j + 2) + 0.1 * (j - i)

    return A, b


def equal(arr1, arr2):
    if len(arr1) != len(arr2):
        return False

    if np.isnan(arr1[0]) and np.isnan(arr2[0]):
        return True

    for i in range(len(arr1)):
        if math.fabs(arr1[i] - arr2[i]) > EPS:
            return False

    return True


def check_solution(systems, filename):
    fin = open(file=filename, mode="r")
    solutions = np.array([list(map(float, s.split())) for s in fin.readlines()])
    fin.close()
    print("Running small tests")
    all_passed = True
    count_passed = 0
    for i in range(len(systems["small_tests"])):
        print(i, "test ", end='')
        A, b = systems["small_tests"][i]
        if np.linalg.norm(A.dot(solutions[i]) - b) > EPS:
            all_passed = False
            print("failed -")
        else:
            count_passed += 1
            print("passed +")

    len_small = len(systems["small_tests"])
    if not all_passed:
        print("Small tests block failed (", count_passed, "/", len_small, ")", sep="")
    else:
        print("Small tests block passed")

    print("Running big tests")
    all_passed = True
    count_passed = 0
    for i in range(len(systems["big_tests"])):
        print(i, "test ", end='')
        A, b = systems["big_tests"][i]
        if np.linalg.norm(A.dot(solutions[i + len_small]) - b) > EPS:
            all_passed = False
            print("failed -")
        else:
            count_passed += 1
            print("passed +")

    len_big = len(systems["big_tests"])
    if not all_passed:
        print("Big tests block failed (", count_passed, "/", len_big, ")", sep="")
    else:
        print("Big tests block passed")


if __name__ == "__main__":
    systems = {
        "small_tests": [],
        "big_tests": []}

    fin = open(file="data/inputs_small", mode="r")
    for filename in map(lambda x: x.strip(), fin.readlines()):
        systems["small_tests"].append(system_from_file(filename))
    fin.close()

    fin = open(file="data/inputs_big", mode="r")
    n, M = map(int, fin.readline().split())
    for x in map(float, fin.readlines()):
        A, b = generate(n, M, x)
        systems["big_tests"].append((A, b))
    fin.close()

    print("Ordinary gauss method:")
    check_solution(systems, "data/gauss_out")
    print("Gauss method with pivoting:")
    check_solution(systems, "data/gauss_pivot_out")
