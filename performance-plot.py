import matplotlib.pyplot as plt
import numpy as np
import math
import os
import sys
import time
import subprocess
from pathlib import Path

ALGO_LOC = "./build/algo"


def gen_tcs_mtx(num_rect) -> [int]:
    ret = []
    ret.append(num_rect)
    lim = int(math.sqrt(num_rect)+1)

    for h in range(0, lim):
        for x in range(0, lim):
            ret.extend([x, x+1, h, h+1])

    return ret


def gen_tcs_dim(dim: int) -> [int]:
    n = 1000
    ret = [n]
    for i in range(n):
        ret.extend([i, i+dim, -dim, dim])

    return ret


def compile():
    os.system("make>/dev/null")


def mtx_plot(order: int):
    sizes = []
    times = []
    ord = 10000
    lim = 20000
    while ord <= lim:
        print("{}%".format(100*ord/lim), end='\r')
        sizes.append(ord)
        tc = " ".join([str(int) for int in gen_tcs_mtx(ord)])
        with open("input.txt", "w") as inp:
            inp.write(tc)
        beg_time = time.time()
        os.system("./build/algo<input.txt>/dev/null")
        end_time = time.time()
        times.append(end_time-beg_time)
        print(ord, end_time-beg_time)
        ord += 100

    ret = [sizes, times]
    return ret


def dim_plot():
    sizes = []
    times = []

    for dim in range(1, 1000, 10):
        print("{}%".format(100*dim/1000), end='\r')
        tc = " ".join([str(int) for int in gen_tcs_dim(dim)])
        with open("input.txt", "w") as inp:
            inp.write(tc)
        sizes.append(dim)
        beg_time = time.time()
        os.system("./build/algo<input.txt>/dev/null")
        end_time = time.time()
        times.append(end_time-beg_time)

    ret = [sizes, times]
    return ret


def do_mtx():
    plot_num = mtx_plot(4)
    _fig, ax = plt.subplots()  # Create a figure containing a single axes.
    ax.plot(plot_num[0], plot_num[1])
    ax.plot([0, 1], [0, 1], transform=ax.transAxes)
    plt.xlabel("Number of Rectangles")
    plt.ylabel("Time taken for computation (seconds)")
    plt.show()


def do_dim():
    plot_num = dim_plot()
    _fig, ax = plt.subplots()  # Create a figure containing a single axes.
    ax.plot(plot_num[0], plot_num[1])
    ax.plot([0, 1], [0, 1], transform=ax.transAxes)
    plt.xlabel("Dimension of rectangle")
    plt.ylabel("Time taken for computation (seconds)")
    plt.show()


if __name__ == "__main__":
    # compile()
    do_mtx()
    # do_dim()
