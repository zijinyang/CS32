# Sorting

## Merge Sort

* $T(N) = 2T(\frac{N}{2}) + O(N)$
* $T(N) = Nlog(N)$

## Quick Sort

    if (N>1)
    {
      pick a pivot
      partition around the pivot
      sort left of pivot
      sort right of pivot
    }

* use one of the array values as the partition
* partition with median is best
  * cannot find median with small time ~ can find median with first couple items(3)

* Best Case
  * Every pivot splits the array perfectly in half
  * $Nlog(N)$
* Worst Case
  * Every pivot doesn't split the array at all
  * $O(N^2)$

### Improvements (Qs)

* if sections are 9 or less, don't sort
  * one last pass using insertion sort to sort smaller sections
  * much faster as items are close to where they should be

* If recursion pass hits a limit, $2log(n)$, switch to merge sort for that section
  * Introsort - worst case $Nlog(N)$
  * most libraries use introsort
