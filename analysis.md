# Analysis of the algorithm

The algorithm described in the paper should run in `O(nlogn)` where n is the number of rectangles. Below, we describe the time and space complexities of our algorithm.

# Time Complexitiy

Our implementation of the algorithm appears to be `O(n*n)`. This is because sub-algorithms like `partition` have been implemented in `O(n*n)`, making the overall time complexity to be also `O(n*n)`.

# Growth with number of rectangles

As the number of rectanlges grow, the time taken by the algorithm also grows in `O(n*n)` time. Below is a plot that illustrates this. We ran the algorithm for rectangles placed in a matrix-like figure, with half of the width overlapping with the adjacent rectangles. We stress tested the algorithm for number of rectangles ranging from 1 to 100,000.

![](../plot-n.png)

Here is the data used to plot the graph, the first column is the number of rectangles, and the second column is the time taken ( in seconds ):

```
10 0.0036690235137939453
20 0.006414890289306641
40 0.00960850715637207
80 0.022288084030151367
160 0.045068979263305664
320 0.08584141731262207
640 0.21498799324035645
1280 0.568976640701294
2560 1.0894064903259277
5120 3.3861186504364014
10240 9.240248203277588
20480 28.82716155052185
40960 87.81760168075562
81920 285.21946835517883
```

# Growth with size of rectangles

The algorithm's time complexity does not appear to depend reliably on the dimensions of the input rectangles. Below is a plot that illustrates this.

![](../plot-dim.png)

# Verification of Correctness

A testing script was written to automatically check the implementation for correctness for inputs of various sizes. Here is a demonstration of the script in action:

![](../auto-test.png)


## General Discussion on the Algorithm

The research paper presents the complete algorithm ( for calculating measure and contour ) as an extension of a common algorithm called `STRIPES`. The stripes algorithm itself depends on two sub algorithms - `copy` and `blacken`. 

**Divide and Conquer**

The main algorithm used in the paper, `STRIPES` is uses the divide-and-conquer method. It recursively divides the problem into two smaller parts, and then combines the solution to solve
the original problem.

However, the paper does not any information about optimal implementation of several smaller algorithms used such as `partition` which are expected to be implemented in `O(n)`. However, we found it difficult to do it in `O(n)` and our initial implementation was `O(n*n)` which we later managed to reduce to `O(nlogn)`.

The paper solves the following problems:

1. Finding all intersections in a set of horizontal and vertical line segments.
2. Finding all point enclosures in a mixed set of points and rectangles.
3. The rectangle intersection problem, by combining 1) and 2).
4. The measure problem.
5. The contour problem.

## Problems Faced

We faced several problems while implementing the algorithm. The major problem was in understanding the research paper. This is because the explaination of the algorithm was mostly in textual manner and a lot of the terminology was unfamiliar to us. Also, the paper gives only a formal descreption of the algorithm, and no examples were provided, that would have helped us to understand it.

## References

- Optimal Divide-and-Conquer to Compute Measure and Contour for a Set of Iso-Rectangles by Ralf Hartmut Giiting (1984)
- Introduction to Algorithms by Thomas H. Cormen, Charles E. Leiserson, and Ronald L. Rivest, Chaper 2 "Growth of Functions" (1990)