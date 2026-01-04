# Algo Lib

A library containing competitive programming algorithms that I have implemented. The implementations are mostly in C++ but some alternative versions may appear from problems that I have solved in Python. 

## Documentation

### Bellman-Ford

@brief The Bellman-Ford algorithm. Finds the shortest path from the given start node to all other nodes in the given negative-weight graph.

@param n: The number of nodes in the graph.

@param edges: The edges in the graph.

@param st: The start node.

@return A pair containing 1. a vector with the distances to each node, and 2. a vector with the immediate parent of each node in their shortest path. In the firstnamed vector, nodes that are not reachable from the start node are marked with `INF`, and nodes that can utilize a negative cycle in their shortest path are marked with `-INF`.

@note Time complexity: `O(n * m)`, where `n` is the number of nodes and `m` is the number of edges.

---

The algorithm works as follows:

- We maintain a distance and parent vector, which respectively contain the shortest distance found and the immediate parent in the corresponding path, for each node.
- We first perform as many iterations as the number of nodes.
  - In each iteration, we:
    - Go through all edges in the graph, and if we find a new shortest path for a target node, we update the designated distance and parent vectors.
- Then, we perform the same number of iterations again, to propogate the effect of any potential negative cycles.
- Once the algorithm is finished, our distance vector tells us the shortest distance to each node from the start node, and the parent vector can be used to backtrack the shortest path to each node.

### Bridges

@brief Tarjan's bridge algorithm. Finds all bridges in the given undirected graph.

@param adj: The graph's adjacency list.

@return A vector containing node pairs of edges that are bridges, with each node pair in sorted order.

@note Time complexity: `O(n + m)`, where `n` is the number of nodes and `m` is the number of edges.

### Chinese Remainder Theorem, Relative Prime

@brief Applies the Chinese Remainder Theorem:

- Let `n` and `m` be relative prime.

- Then the system of equations `x = a (mod n), x = b (mod m)` has a unique solution `x` for modulo `nm`.

@param a, b, n, m: See equation system.

@return The solution `x`.

### Closest Pair, Uniform

@brief Finds the closest pair in the given set of points.

@param pts: The vector of points.

@return: A pair containing the two points that are closest to each other.

@note Time complexity: `Oam(n * log(n))`, where `n` is the number of points.

---

The algorithm works as follows:

- First, we sort the points in ascending order.
- We maintain a pair containing the closest point pair (so far), as well as the distance between this closest pair.
  - We initialize these using the first and second point in the sorted vector.
- Then, for each point `pt1` after the first two points (2 <= i < n), we:
  - For each preceeding point `pt2` (i - 1 >= j >= 0):
    - Calculate the distance between `pt1` and `pt2`.
    - If this distance is smaller than the current minimum, we update the closest pair and closest distance.
    - Otherwise, if the difference in the x coordinates of the two points is greater than the current minimum distance, we can move on to the next `pt1` (as the set of points is sorted, we know that no subsequent point `pt2` will give a closer distance for the current `pt1`).

### Convex Hull

@brief Finds the convex hull for the given set of points, using the Monotone Chain algorithm.

@param pts: The vector of points.

@return A vector containing the points in the convex hull in CCW order.

@note Time complexity: `O(n * log(n))`, where `n` is the number of points.

---

The algorithm works as follows:

- First, we sort the set of points in ascending order, and remove any duplicate points.
- After this, if there are two points or less, we can stop early, as the given set is the convex hull itself in CCW order.
- We initialize a vector to store the convex hull, with the size `2n` (to fit the maximum intermediate state size during the algorithm), as well as a counter `k` to keep track of the number of points currently added to the hull.
- Then, we start by constructing the lower hull.
  - For each point from left to right (0 <= i < n):
    - As long as we have at least two points in the hull (k >= 2), and the cross product between the latest added line segment
      and the line segment formed by the current point and the second-to-last point added to the hull, is not positive
      (which would indicate a turn that is not to the left), we discard the point that was last added to the hull.
- Next, we construct the upper hull
  - The logic remains the same as for the lower hull, expect that we iterate through the points from right to left (n - 2 >= i >= 0), excluding the rightmost point which was just added in the lower hull.
- The convex hull result vector will contain a duplicate of the leftmost starting point, as it is processed in both the upper and lower hull, thus we have to resize the result vector to remove it (as well as to truncate the buffer assigned at initialization).
- The convex hull will inherently be in CCW order once the algorithm is finished.

### Dijkstra

@brief Dijkstra's algorithm. Finds the shortest path from the given start node to all other nodes in the given non-negative-weight graph.

@param G: The graph.

@param st: The start node.

@return A pair containing 1. a vector with the distances to each node, and 2. a vector with the immediate parent of each node in their shortest path.

@note Time complexity: `O(m * log(n))`, where `m` is the number of edges and `n` is the number of nodes in the graph.

@note Memory complexity: `O(n)`, where `n` is the number of nodes in the graph.

@note Good for sparse graphs.

---

The algorithm works as follows:

- We maintain a priority queue, or in this case a set, containing {dist, node} pairs.
  - It is initialized to contain the pair representing the distance from the start node to itself.
- We also maintain a distance and parent vector, which respectively contain the shortest distance found and the immediate parent in the corresponding path, for each node.
- As long as the queue is not empty, we:
  - Take the first element in the queue, i.e., the element with the shortest distance from the start node.
  - Look at the edges from this node, and if we find a distance to any neighboring node that is shorter than any previously found path, we store the new distance and the parent node in the designated vectors, and enqueue the new {dist, node} pair.
- Once the algorithm is finished, our distance vector tells us the shortest distance to each node from the start node, and the parent vector can be used to backtrack the shortest path to each node.

#### Dense-Graph Version

@brief Dijkstra's algorithm. Finds the shortest path from the given start node to all other nodes in the given non-negative-weight graph.

@param G: The graph.

@param st: The start node.

@return A pair containing 1. a vector with the distances to each node, and 2. a vector with the immediate parent of each node in their shortest path.

@note Time complexity: `O(n ^ 2 + m)`, where `m` is the number of edges and `n` is the number of nodes in the graph.

@note Good for dense graphs (when `m` approaches `n ^ 2`, i.e., almost all possible edges exist).

### Dinic

@brief A class for Dinic's algorithm.
Initialize with the number of nodes `n`, the source node `s`, and the sink node `t`.
Populate the graph using `add_edge()`.

#### Max Flow

@brief Finds the maximum flow from the source node to the sink node using Dinic's algorithm.

@return The maximum flow.

@note Time complexity: `O(n ^ 2 * m)`, where `n` is the number of nodes and `m` is the number of edges. For unit networks, this algorithm works in `O(sqrt(n) * m)`.

### Edmonds-Karp

@brief Finds the maximum flow from a given source to sink node in the provided graph, using the Edmonds-Karp algorithm. Edmonds-Karp is an implementation of Ford-Fulkerson that uses BFS to find augmenting paths.

@param G: The graph.

@param s: The source node.

@param t: The sink node.

@return A pair containing 1. the maximum flow, and 2. the edges used in the flow graph, where each entry contains (from, to, flow).

@note Time complexity: `O(n * m ^ 2)`, where `n` is the number of nodes and `m` is the number of edges.

@note The input Graph will be updated in-place, thus containing the final state of the graph after the algorithm is complete.

### Fenwick Tree

@brief For a given vector of numbers, the Fenwick Tree allows for efficient prefix sum queries and updates.

@note Memory complexity: `O(n)`, where `n` is the number of elements.

@note Uses 1-based indexing.

#### Add

@brief Adds a value to an element in the tree, and updates the tree accordingly.

@param i: The index of the element.

@param d: The value to be added to the element.

@note Time complexity: `O(log(n))`, where `n` is the number of elements in the tree.

#### Sum

@brief Calculates the prefix sum from 1 up to the given upper-bound index `i` (inclusive).

@param i: The index of the upper bound.

@return The prefix sum.

@note Time complexity: `O(log(n))`, where `n` is the number of elements in the tree.

#### Sum, Specified Lower Bound

@brief Calculates the sum from the lower-bound index `i` to the given upper-bound index `j` (inclusive).

@param i: The index of the lower bound.

@param j: The index of the upper bound.

@return The desired range sum.

@note Time complexity: `O(log(n))`, where `n` is the number of elements in the tree.

---

The naive approach for prefix sums is simply to iterate through the array and add up the number one by one, which takes `O(n)` time. The Fenwick Tree improves this by maintaining cumulative subrange sums for the the array, using binary representations for the indices to effectively construct the total desired sum. Similarily, the tree can use the binary index representations to propogate the update of an element to the affected subrange sums in the tree.

For every (2^1) 2nd index, we maintain a sum of (2^0) a single element.
For every (2^2) 4th index, we maintain a sum of (2^1) 2 consecutive elements.
For every (2^3) 8th index, we maintain a sum of (2^2) 4 consecutive elements,
and so on.

Example for intuition:
Let's say we have the following array:
\[1, 2, 3, 4, 5, 6, 7],

then we would get the following tree array:
\[1, 3, 3, 10, 5, 11, 7],

which as the name suggests can be visualized as a tree:

```
          10
    3            11
1      3      5      7
```

For the query 7, assuming 1-based indexing, we would compute the sum as:
sum(7) = tree\[7] + tree\[6] + tree\[4] = 7 + 11 + 10 = 28.

### Fast Fourier Transform

@brief Applies the Fast Fourier Transform (FFT) or its inverse on the given vector of complex numbers.

@param v: A vector of complex numbers (e.g., coefficients of a polynomial).

@param inv: A boolean value indicating if the inverse (true) or regular (false) FFT should be applied.
It defaults to false.

@note Time complexity: `O(n * log(n))`, where `n` is the size of the vector.

@note The transform is done in-place, i.e., the input object `v` will be altered.

### Floyd-Warshall

@brief Calculates the shortest path between each pair of nodes in the given adjacency matrix, using the Floyd-Warshall algorithm.

@param adj: An adjacency matrix containing the weight of each edge that exists in the graph, filled with `INF` if no edge exists between two nodes.

@return A matrix containing the shortest path between each node pair. If no shortest path exists between two nodes, their cell will contain `INF`, and if an arbitrarily short path exists due to a negative cycle, their cell will contain `-INF`.

@note Time complexity: `O(n ^ 3)`, where `n` is the number of nodes in the graph.

### Gaussian Elimination

@brief Solves a linear equation system for a given left-side matrix `A` and right-side vector `b`, using Gaussian Elimination.

@param A: A matrix containing the coeffiecients of the left-side of the equation system.

@param b: A vector containing the coeffiecients of the right-side of the equation system.

@return A pair containing

1. an integer representing the solvability of the system (0 = inconsistent, 1 = single solution, 2 = multiple solutions), and
2. A vector containing the solution in case 1, otherwise it is empty.

@note Time complexity: `O(min(n, m) * n * m)`, where `n` is the number of equations and `m` is the number of variables. If `n` = `m`, it is `O(n ^ 3)`.

---

It works as follows:

Starting from the top left of the matrix, we look for the value in the column with the highest absolute value to turn into a pivot element. Then, we swap the corresponding row with the current row, and subtract the product of the current row and each factor needed to turn all other values in the column to zero. This is then repeated for subsequent rows and columns, until the bottom and/or the right of the matrix is reached. After this, we simply iterate through each column, and extract the values of the (solvable) variables by dividing the right side value with the pivot element. If a column is missing a pivot element, the equation has multiple solutions. If the sum of a row that is produced by plugging in the extracted variable values does not match the right side value, then the system is deemed inconsistent.

#### Partial Linear Equation

@brief Solves a partial linear equation system for a given left-side matrix `A` and right-side vector `b`.

@param A: A matrix containing the coeffiecients of the left-side of the equation system.

@param b: A vector containing the coeffiecients of the right-side of the equation system.

@return A pair containing

1. an integer representing the solvability of the system (0 = inconsistent, 1 = valid solution, either single or multiple), and
2. a vector containing the solution if the linear equation is valid, filling any free variables with NAN; otherwise, it is empty.

@note Time complexity: `O(min(n, m) * n * m)`, where `n` is the number of equations and `m` is the number of variables. If `n` = `m`, it is `O(n ^ 3)`.

---

It works as follows:

Starting from the top left of the matrix, we look for the value in the column with the highest absolute value to turn into a pivot element. If all values are zero, we continue to the next column. Then, we swap the corresponding row with the current row, and subtract the product of the current row and each factor needed to turn all other values in the column to zero. This is then repeated for subsequent rows and columns, until the bottom and/or the right of the matrix is reached. After this, we simply iterate through each column, and extract the values of the (solvable) variables by dividing the right side value with the pivot element. If a column is missing a pivot element, the equation has multiple solutions. If the sum of a row that is produced by plugging in the extracted variable values does not match the right side value, then the system is deemed inconsistent.

### Interval Cover

@brief Finds the minimal set of the given intervals that covers the desired target interval.

@param target: A (start, end) pair of the interval to be covered.

@param intervals: A vector of interval (start, end) pairs.

@return A vector with the indices of the chosen intervals, if a valid solution exists.
Otherwise, it returns an empty vector.

@note Time complexity: `O(n * log(n))`, where `n` is the number of intervals.

### Knapsack

@brief Finds the optimal way to fill a capacity limited knapsack, maximizing the total value for the packed items.

@param capacity: The capacity of the knapsack.

@param items: A vector of item (weight, value) pairs.

@return A vector with the indices of the items present in the optimal solution.

@note Time complexity: `O(n * capacity)`, where `n` is the number of items.

### Knuth-Morris-Pratt

@brief Finds each occurence of the given pattern in the given string, using the Knuth-Morris-Pratt algorithm.

@param s: The string.

@param p: The pattern.

@return A vector containing the start index of each occurence of the pattern.

@note Time complexity: `O(n + m)`, where `n` is the length of the pattern and `m` is the length of the string.

### Kruskal

@brief Finds the Minimum Spanning Tree (MST) for a given set of edges, using Kruskal's algorithm.

@param n: The number of nodes.

@param edges: A vector containing the edges.

@return A pair containing 1. the cost of the MST, and 2. the edges in the MST, if a valid solution exists.
Otherwise, 1. the cost as -1, and 2. an empty vector.

@note Time complexity: `O(m * log(n))`, where `m` is the number of edges and `n` is the number of nodes.

---

The algorithm works as follows:

- First, we sort the given vector of edges based on their weights.
- We initialize a UnionFind struct, which we use to efficiently keep track of which nodes belong to the same set, as well as to merge these sets.
- We also initialize a variable to store the total cost of the MST, as well as a vector to store the edges present in the MST.
- Then, for each edge in the sorted edges, we:
  - Check if the nodes share the same set, and if they do not, we:
    - Merge / take the union of the sets that the respective nodes belong to.
    - Check if the size of the MST vector is equal to the number of nodes minus 1, and if it is, we interrupt the loop.
- If the size of the MST vector is less than the number of nodes minus 1 after we finish the loop, then we can determine that no solution exists for the given set of edges.
- Otherwise, we have our solution.

### Line Segment Distance

@brief Calculates the shortest distance between two line segments.

@param s1: Start point of the first segment.

@param e1: End point of the first segment.

@param s2: Start point of the second segment.

@param e2: End point of the second segment.

@return The minimum Euclidian distance between any point on the first segment and any point on the second segment.

---

It works as follows:

- First, we check if the line segments intersect, as that would mean that their minimum distance is zero.
- Otherwise, we know that the shortest distance must be from a start or end point of one line segment to the other segment, so we simply calculate these distances and take the minimum value as our answer.

### Line Segment Intersect

@brief Finds the intersection point/segment between two line segments, if one exists.

@param s1: Start point of the first segment.

@param e1: End point of the first segment.

@param s2: Start point of the second segment.

@param e2: End point of the second segment.

@return A vector containing:

- Nothing, if no intersection exists.
- One point, if the segments intersect in a single point.
- Two points, representing the start and end of the intersecting segment, if the segments overlap over a length.

---

The algorithm works as follows:

- First, we calculate the cross product between the respective line segments' vector and the vector that their respective starting point creates with the other segments' start and end point. This tells us which "side" the start and end point of each line segment is on relative to the other line segment (positive = "left", negative = "right", zero = "colinear").
- If the start and end point of the respective line segments lie on different sides of the other line segment, we can determine that the lines intersect at a single point (as they cross each other).
- Otherwise, we check if the respective segments' start and end point lie on the other segment. This can be none, a single point, or two points (i.e., a line segment) if the lines overlap over a length.

### Longest Common Prefix

@brief Kasai's algorithm. Computes the Longest Common Prefix (LCP) array for the given string and its corresponding suffix array. The LCP array will at each index `i` contain the LCP between the suffix at index `i` and the subsequent index `i + 1` in the suffix array.

@param s: The string.

@param suf_arr: The string's suffix array.

@return The LCP array.

@note Time complexity: `O(n)`, where `n` is the length of the string.

### Longest Increasing Subsequence

@brief Finds the longest increasing subsequence for a given sequence of numbers.

@param nums: The sequence of numbers.

@return A vector containing the indices of the elements in the longest increasing subsequence.

@note Time complexity: `O(n * log(n))`, where `n` is the number of elements in the total sequence.

### Maximum Number of Colinear Points

@brief Finds the maximum number of colinear points in the given set.

@param pts: The set of points.

@return The maximum number of colinear points.

@note Time complexity: `O(n ^ 2 * log(n))`, where `n` is the number of points in the set.

---

It works as follows:

- For each point in the set, we:
  - Set the point as origin.
  - Calculate the angle that each other point creates with the current origin/reference point.
  - We store these angles in a vector and sort it in ascending order.
  - Then, we iterate through the angles and maintain a counter for the longest streak of consecutive items with the same angle to the reference point.
- The longest streak that we have found after performing these steps for all points, is the answer.

### Minimum Cut

@brief Finds the minimum cut in the given graph, for the given source and sink node.
A minimal cut is a subset `U` of the nodes `V` where the sum of the capacities from U to the rest of the nodes `U \ V` is minimal.

@param G: The graph.

@param s: The source node.

@param t: The sink node.

@return A set containing the nodes in the minimal cut.

@note Time complexity: `O(n * m ^ 2)`, where `n` is the number of nodes and `m` is the number of edges.

@note The input Graph will be updated in-place, thus containing the final state of the graph after the algorithm is complete.

### Modular Arithmetic

@brief A class for modular arithmetic operations.

### Point

@brief 2D point class. Defaults to (0, 0) if x and y are not provided.

### Point in Polygon

@brief Checks if the given point is inside the given polygon or not, using the Winding Number algorithm (angle version).

@param p: The point.

@param polygon: A vector containing the vertices of the polygon, in CW or CCW order.

@return An integer where -1 = out, 0 = on, and 1 = in.

@note Time complexity: `O(n)`, where `n` is the number of vertices.

---

The algorithm works as follows:

- First, we check if the point lies on the boundary of the polygon.
  - For each pair of adjacent vertices in the polygon, we:
    - Check if the vectors that they respectively form with the given point are colinear, and if they are, we check:
      - If the given point lies between the two vertices, i.e., on the line segment formed by the vertices (which would mean that the point lies on the boundary).
- If it is not on the boundary of the polygon, we:
  - For each pair of adjacent vertices in the polygon:
    - Calculate the angle that they respectively form with the given point.
    - Calculate the difference between these two angles, normalize it to lie between (-PI, PI], and add it to a running sum.
  - In the end, if the running sum is (close to) +-2 \* PI, the point lies inside the polygon, but if it is (close to) zero it lies on the outside.

### Polygon Area

@brief Calculates the area for a polygon with the given vector of vertices, using the trapezoid formula.

@param pts: A vector containing the polygon's vertices in CW or CCW order.

@return The polygon's signed area (< 0 means CW, >= 0 means CCW).

@note Time complexity: `O(n)`, where `n` is the number of vertices.

---

The trapezoid formula works by taking the sum of the signed areas of the trapezoids that can be formed by each polygon edge and the x-axis. Each edge is defined by consecutive vertices. We save the division by 2 until the sum is complete, to avoid unnecessary operations.

### Polynomial Multiplication

@brief Multiplies two given polynomials using the FFT.

@param a: The coefficients of the first polynomial.

@param b: The coefficients of the second polynomial.

@return The coefficients of the resulting polynomial.

@note Time complexity: `O(n * log(n))`, where `n` is the order of the resulting polynomial.

---

The naive approach for polynomial multiplication takes `O(n ^ 2)` time, as we have to multiply each pair of coefficients in the two polynomials. This can be improved by applying the FFT to the two polynomials, and multiplying the representations in the frequency domain instead.

### Prime Sieve

@brief Sieve of Erathostenes. Finds all prime numbers from 1 up to a given upper bound `n`.

@note Time complexity (initialization): `O(n * log(log(n)))`, where `n` is the upper bound.

---

The algorithm works as follows:

- We maintain a 1-indexed boolean vector which contains if a number is prime or not, for each number in our sequence.
  - Each number is initialized as prime/true, apart from 0 and 1.
- For each number from 2 to `n`, we:
  - Check if it has been marked as non-prime, and if it has not, then it is prime, and we can then mark each multuple of the number up to `n` as non-prime.
- Once the algorithm is finished, the boolean vector can be used to query if a number is prime, for any number in the sequence.

#### Is Prime

@brief Returns if the given number is prime or not.

@param The number to check.

@return A boolean value representing if the number is prime.

@note Time complexity: `O(1)`.

### Rational Arithmetic

@brief A class for rational numbers, supporting common arithmetic operations and comparison operators. Initialization defaults to numerator = 0 and denominator = 1.

### Strongly Connected Components

@brief Kosaraju's algorithm. Identifies the Strongly Connected Components (SCCs) in the graph, and creates the corresponding condensation graph.

A subset of nodes `C` is called an SCC if 1. for all `u`, `v` in `C` (`u` != `v`) there exists a path from `u` to `v` and from `v` to `u`, and 2. `C` is maximal, i.e., no node can be added without violating the above condition.

@return A pair containing 1. the SCCs, and 2. the adjacency list of the condensation graph.

@note Time complexity: `O(n + m)`, where `n` is the number of nodes and `m` is the number of edges.

### Suffix Array

@brief Suffix array. It sorts a provided string's suffixes in lexicographical order, storing the starting index of each suffix in the sorted array.

@note Time complexity (initialization): `O(n * log(n))`, where `n` is the length of the string.

@note Memory complexity: `O(n)`, where `n` is the length of the string.

---

The naive approach is to get all suffixes and sort them using quicksort or mergesort, while retaining their original indices. Sorting would on average take `O(n * log(n))` time, and the comparison of two strings `O(n)` time, granting a total complexity of `O(n ^ 2 * log(n))` (where `n` is the string length).

The suffix array can be formed in `O(n * log(n))`. This is done by sorting suffixes by their prefixes iteratively, first with prefix length 1, then 2, 4, ..., up to `n`, where we can continously reuse the sorting results from previous iterations.

A major benefit with the suffix array compared to the suffix trie/tree, is that it does not save the suffixes themselves, but rather the index at which they begin in the original string, making it more memory efficient.

#### Get Suffix

@brief Retrieves the starting index of the suffix ranked at the given index/rank in the suffix array.

@param i: The index/rank of the suffix.

@return The starting index of the suffix in the original string.

@note Time complexity: `O(1)`.

### Union-Find

@brief Given an initial number of elements, each belonging to a distinct set, Union-Find provides efficient union and find operations.

@note Memory complexity: `O(n)`, where `n` is the number of elements.

#### Find

@brief Finds the root parent for a given element. This indicates which set the element belongs to.

@param a: The element whose set we want to identify.

@return The root element representing the set.

@note Time complexity: `Oam(a(n))` ~= `Oam(1)`, where `a` is the inverse ackermann function, and `n` is the number of elements.

#### Union

@brief Merges the two sets containing the two given elements.

@param a: The first element.

@param b: The second element.

@note Time complexity: `Oam(a(n))` ~= `Oam(1)`, where `a` is the inverse ackermann function, and `n` is the number of elements.

#### Same

@brief Checks if the two given elements belong to the same set.

@param a: The first element.

@param b: The second element.

@return A boolean value representing if the elements share the same set.

@note Time complexity: `Oam(a(n))` ~= `Oam(1)`, where `a` is the inverse ackermann function, and `n` is the number of elements.

### Extras

#### Calculate Divisors

@brief Calculates all the divisors of a number given its prime factorization.

@param pfs: A vector containing (prime factor, exponent) pairs.

@return A vector containing the divisors.

#### Prime Factorization

@brief Computes the prime factorization for a given number.

@param n: The number to factorize.

@param primes: The prime numbers up to the square root of `n`.

@return The prime factorization in the form of (prime factor, exponent) pairs.

@note The primes can suggestively be found using a Prime Sieve.

#### Reconstruct Shortest Path

@brief Reconstructs the shortest path from the given start to end node.

@param par: A vector containing the immediate parent of each node in
their shortest path, which can be backtracked to retreive the full path.

@return A vector containing the shortest path in the order from start to end.
This vector is empty if no shortest path exists for the start-end pair.
