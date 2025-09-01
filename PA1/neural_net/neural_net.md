### Task 1E: Confusion Hi Confusion He!!

#### Runtime Analysis

| ![loop overhead vs stride](../Task1/images/Reordered,%20Unrolled,%20Tiled%20and%20SIMD.svg) |
|-|
*Fig 1. Speedup achieved by different optimizations*

For smaller matrices, gains are limited, though SIMD still provides a noticeable boost. As the matrix size increases, all techniques show higher speedup, with SIMD leading for medium sizes and Tiling/Unrolling catching up for larger ones. At the largest size, all methods converge near 6× speedup, while Reordering alone remains slightly behind.

#### Operations per second
| ![loop overhead vs stride](../Task1/images/Giga%20Operations%20per%20Second.svg) |
|-|
*Fig 2. Speedup achieved by different optimizations*

Calculated as:
$$
giga\ operations\ per\ second = \frac{2n^2}{T * 10^{12}}
$$
where, $T=runtime\ in\ ms$. 

We see that as we increase matrix size `ops/sec` decreases because we are being more memory limited due to page faults. 

#### Memory Access Pattern and Cache Efficiency
Please check the analysis of 1A to 1D :pray: nothing meaningful to add here.  