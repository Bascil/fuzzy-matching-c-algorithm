# Levenshtein Distance Calculation Algorithm

The Levenshtein distance, also known as the edit distance, is a measure of the similarity between two strings. It represents the minimum number of single-character edits (insertions, deletions, or substitutions) required to change one string into another.

## Algorithm Overview

The Levenshtein distance between two strings `s1` and `s2` is calculated using a dynamic programming approach. The algorithm iterates over a matrix and fills it with the minimum edit distances for each pair of substrings. Finally, it returns the distance between the full strings.

## Detailed Algorithm

1. **Input**: Two strings `s1` and `s2`.

2. **Initialization**:

   - Calculate the lengths of strings `s1` and `s2`, denoted as `len1` and `len2`, respectively.
   - Initialize a matrix `matrix` of size `(len1 + 1) x (len2 + 1)` to store results of distance calculations.

3. **Initialize the Matrix**:

   - Iterate over each cell of the matrix using nested loops:
     - For cell `(i, j)`, set the following values:
       - If `i == 0` and `j == 0`, set `matrix[i][j] = 0`.
       - If `i == 0`, set `matrix[i][j] = j`.
       - If `j == 0`, set `matrix[i][j] = i`.

4. **Main Calculation**:

   - Iterate over each cell of the matrix (excluding the first row and column) using nested loops:
     - For cell `(i, j)`:
       - If the characters at positions `i-1` in `s1` and `j-1` in `s2` are equal, set `matrix[i][j] = matrix[i-1][j-1]`.
       - Else, calculate the minimum of the three adjacent cells and set `matrix[i][j]` to the calculated minimum.

5. **Output**: Return `matrix[len1][len2]`, which represents the Levenshtein distance between `s1` and `s2`.

## Example

For example, given the strings `"kitten"` and `"sitting"`, the algorithm would calculate the following memoization matrix:

```css
        "" s  i  t  t  i  n  g
   ""   0  1  2  3  4  5  6  7
   k    1  1  2  3  4  5  6  7
   i    2  2  1  2  3  4  5  6
   t    3  3  2  1  2  3  4  5
   t    4  4  3  2  1  2  3  4
   e    5  5  4  3  2  2  3  4
   n    6  6  5  4  3  3  2  3
   g    7  7  6  5  4  4  3  2
```
