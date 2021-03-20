# Analysis of the algorithm

The algorithm described in the paper should run in `O(nlogn)` where n is the number of rectangles. Below, we describe the time and space complexities of our algorithm.

# Time Complexitiy

Our implementation of the algorithm is in `O(nlogn)` time complexity -  This is because sub-algorithms like `partition` have been implemented in `O(n)`, making the overall time complexity to be also `O(nlogn)`.

# Growth with number of rectangles

As the number of rectanlges grow, the time taken by the algorithm also grows in `O(nlogn)` time. Below is a plot that illustrates this. We ran the algorithm for rectangles placed in a matrix-like figure, with half of the width overlapping with the adjacent rectangles. We stress tested the algorithm for number of rectangles ranging from 1 to more than 500,000.

![](../plot-n.png)

Here is the data used to plot the graph, the first column is the number of rectangles, and the second column is the time taken ( in seconds ):

```
2 0.003069162368774414
4 0.0027382373809814453
8 0.0038232803344726562
16 0.0027337074279785156
32 0.01347494125366211
64 0.010357141494750977
128 0.0045928955078125
256 0.010653257369995117
512 0.010597467422485352
1024 0.01896047592163086
2048 0.03151130676269531
4096 0.053960323333740234
8192 0.09728717803955078
16384 0.1972658634185791
32768 0.44367241859436035
65536 0.9343554973602295
131072 1.5861904621124268
262144 3.722468852996826
```

# Growth with size of rectangles

The algorithm's time complexity does not appear to depend reliably on the dimensions of the input rectangles. Below is a plot that illustrates this.

![](../plot-dim.png)

# Verification of Correctness

A testing script was written to automatically check the implementation for correctness for inputs of various sizes. Here is a demonstration of the script in action:

![](../auto-test.gif)


## General Discussion on the Algorithm

The research paper presents the complete algorithm ( for calculating measure and contour ) as an extension of a common algorithm called `STRIPES`. The stripes algorithm itself depends on two sub algorithms - `copy` and `blacken`. 

**Divide and Conquer**

The main algorithm used in the paper, `STRIPES` is uses the divide-and-conquer method. It recursively divides the problem into two smaller parts, and then combines the solution to solve
the original problem.

However, the paper does not any information about optimal implementation of several smaller algorithms used such as `partition` which are expected to be implemented in `O(n)`. However, we managed to implement them in `O(n)` using techniques like 2-pointers. Our initial implementation was a naive`O(n*n)` using nested loops,  which we later managed to reduce to `O(n*logn)`.

The paper solves the following problems:

1. Finding all intersections in a set of horizontal and vertical line segments.
2. Finding all point enclosures in a mixed set of points and rectangles.
3. The rectangle intersection problem, by combining 1) and 2).
4. The measure problem.
5. The contour problem.

## Problems Faced

We faced several problems while implementing the algorithm. The major problem was in understanding the research paper. This is because the explaination of the algorithm was mostly in textual manner and a lot of the terminology was unfamiliar to us. Also, the paper gives only a formal descreption of the algorithm, and no examples were provided, that would have helped us to understand it.

Finally, the smaller sub-algorithms like concat, blacken, and copy were difficult to implement in `O(n)`, which is necessary for the entire algorithm to be `O(nlogn)`.

## References

- Optimal Divide-and-Conquer to Compute Measure and Contour for a Set of Iso-Rectangles by Ralf Hartmut Giiting (1984)
- Introduction to Algorithms by Thomas H. Cormen, Charles E. Leiserson, and Ronald L. Rivest, Chaper 2 "Growth of Functions" (1990)