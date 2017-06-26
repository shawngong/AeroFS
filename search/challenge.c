#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    LessThan = 0,
    LessThanEquals = 1,
    Equals = 2,
    GreaterThanEquals = 3,
    GreaterThan = 4
} SearchType;

typedef enum {
    NotFound = 0, // do not change this order.
    FoundExact = 1,
    FoundGreater = 2,
    FoundLess = 3,
    Error = 4
} SearchResult;

/* Search an array of sorted numbers.
*
* items    : An array of sorted ints, with no duplicates
* n_items  : Number of elements in the items array
* ascending: non-zero if the array is sorted in ascending order
* key      : the key to search for
* type     : the type of match to find
*
* This function finds the element in the array
* that best fits the search criteria. It returns
* the match type and the index of the matching item.
*
* LessThan
* --------
*  Finds the largest item which is less than the key.
*  It returns FoundLess if a match is found, NotFound
*  if no match is found.
*
* LessThanEquals
* --------------
*  Finds the item which is equal to the key, or the
*  largest item which is less than the key. Returns
*  FoundExact if an item that exactly matches the key
*  is found, FoundLess if a non-exact match is found
*  and NotFound if no match is found.
*
* Equals
* ------
*  Finds an item which is equal to the key. Returns
*  FoundExact if an item if found, NotFound otherwise.
*
* GreaterThanEquals
* -----------------
*  Finds the item which is equal to the key, or the
*  smallest item which is greater than the key. Returns
*  FoundExact if an item that exactly matches the key
*  is found, FoundGreater if a non-exact match is found
*  and NotFound if no match is found.
*
* GreaterThan
* -----------
*  Finds the smallest item which is greater than the
*  key. Returns FoundGreater if a match if found, NotFound
*  if no match is found.
*
* Examples
* --------
*  Given the input array [0, 2, 4, 6, 8] (ascending order)
*
*  +-----+-------------------+--------------+-------+
*  | Key | Type              | Returns      | Index |
*  +-----+-------------------+--------------+-------+
*  | -1  | LessThanEquals    | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  0  | LessThan          | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  0  | Equals            | FoundExact   | 0     |
*  +-----+-------------------+--------------+-------+
*  |  1  | Equals            | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  2  | GreaterThanEquals | FoundExact   | 1     |
*  +-----+-------------------+--------------+-------+
*  |  2  | GreaterThan       | FoundGreater | 2     |
*  +-----+-------------------+--------------+-------+
*
*  Given the input array [8, 6, 4, 2, 0] (descending order)
*
*  +-----+-------------------+--------------+-------+
*  | Key | Type              | Returns      | Index |
*  +-----+-------------------+--------------+-------+
*  | -1  | LessThan          | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  0  | LessThan          | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  4  | LessThanEquals    | FoundExact   | 2     |
*  +-----+-------------------+--------------+-------+
*  |  8  | Equals            | FoundExact   | 0     |
*  +-----+-------------------+--------------+-------+
*  |  5  | GreaterThanEquals | FoundGreater | 1     |
*  +-----+-------------------+--------------+-------+
*  |  2  | GreaterThanEquals | FoundExact   | 3     |
*  +-----+-------------------+--------------+-------+
*  |  8  | GreaterThan       | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  9  | GreaterThan       | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*
* Assumptions
* -----------
*  The items are sorted
*  Items will be non-NULL
*  There are no duplicate items
*  n_items will be > 0
*/

int greaterThanOrEqualComparator(
  const int a,
  const int b)
{
  return a >= b;
}

int greaterThanComparator(
  const int a,
  const int b)
{
  return a > b;
}

int equalComparator(
  const int a,
  const int b)
{
  return a == b;
}

void SearchHelper(
  const int * const ascending_items,
  const int n_items,
  const int key,
  int* const index,
  int (*comparator) (int, int))
{
  int i;
  for (i = 0; i < n_items; i++) {
    if (comparator(ascending_items[i], key)) {
      break;
    }
  }
  *index = i;
}

int inBounds(
  int n_items,
  int index
) {
  return (index >= 0 && index < n_items);
}

SearchResult SearchLessThan(
  const int * const ascending_items,
  const int n_items,
  const int key,
  int* const index)
{
  SearchHelper(ascending_items, n_items, key, index, &greaterThanOrEqualComparator);
  if (inBounds(n_items, *index - 1)) {
    *index = *index - 1;
    return FoundLess;
  } else {
    *index = -1;
    return NotFound;
  }
}

SearchResult SearchGreaterThan(
  const int * const ascending_items,
  const int n_items,
  const int key,
  int* const index)
{
  SearchHelper(ascending_items, n_items, key, index, &greaterThanComparator);
  if (inBounds(n_items, *index)) {
    return FoundGreater;
  } else {
    *index = -1;
    return NotFound;
  }
}

SearchResult SearchEquals(
  const int * const ascending_items,
  const int n_items,
  const int key,
  int* const index)
{
  SearchHelper(ascending_items, n_items, key, index, &equalComparator);
  return inBounds(n_items, *index) ? FoundExact : NotFound;
  // assuming an out of bounds index is an "X" - could set to -1
}

SearchResult SearchGreaterThanEquals(
  const int * const ascending_items,
  const int n_items,
  const int key,
  int* const index)
{
  if (SearchEquals(ascending_items, n_items, key, index) == FoundExact) {
    return FoundExact;
  } else {
    return SearchGreaterThan(ascending_items, n_items, key, index);
  }
}

SearchResult SearchLessThanEquals(
  const int * const ascending_items,
  const int n_items,
  const int key,
  int* const index)
{
  if (SearchEquals(ascending_items, n_items, key, index) == FoundExact){
    return FoundExact;
  } else {
    return SearchLessThan(ascending_items, n_items, key, index);
  }
}

const int *reverseArray(const int * const items, const int n_items)
{
    int (*ret) = malloc(n_items * sizeof(int));
    int i;
    int n = n_items - 1;
    for (i = n; i >= 0; i--) {
      ret[n - i] = items[i];
    }
    return ret;
}

SearchResult Search(
    const int * const items,
    const int n_items,
    const int ascending,
    const int key,
    const SearchType type,
    int* const index)
{
  const int *always_ascending_array;
  always_ascending_array = (ascending) ? items : reverseArray(items, n_items);

  SearchResult ret;
  switch(type) {
    case LessThan:
      ret = SearchLessThan(always_ascending_array, n_items, key, index);
      break;
    case LessThanEquals:
      ret = SearchLessThanEquals(always_ascending_array, n_items, key, index);
      break;
    case Equals:
      ret = SearchEquals(always_ascending_array, n_items, key, index);
      break;
    case GreaterThanEquals:
      ret = SearchGreaterThanEquals(always_ascending_array, n_items, key, index);
      break;
    case GreaterThan:
      ret = SearchGreaterThan(always_ascending_array, n_items, key, index);
      break;
    default: // in case there's extra enums added.
      ret = Error;
  }
  if (!ascending && inBounds(n_items, *index)) {
    // printf("hit\n");
    *index = n_items - 1 - *index;
  }
  return ret;
  // dealloc(always_ascending_array);
  //this might not be the intended behaviour - i.e. if we don't want to free the inital items array.
  // so it's commented out for now.
}

int main() {
  /* Test Plan
  Unit Tests for each function defined bar Search.
  Integration test for Search function, and for functions that use SearchHelper.
  */
  // greaterThanComparator testing
  const int a = 1;
  const int b = 2;
  const int c = 1;
  const int d = -1;
  assert(greaterThanComparator(a, b) == 0);
  assert(greaterThanComparator(b, a) == 1);
  assert(greaterThanComparator(a, c) == 0);
  assert(greaterThanComparator(a, d) == 1);
  assert(greaterThanComparator(d, d) == 0);
  // equalComparator
  assert(equalComparator(a, b) == 0);
  assert(equalComparator(d, d) == 1);
  // greaterThanOrEqualComparator
  assert(greaterThanOrEqualComparator(d, d) == 1);
  assert(greaterThanOrEqualComparator(b, c) == 1);
  assert(greaterThanOrEqualComparator(a, b) == 0);

  // in bounds
  const int n = 10;
  assert(inBounds(n, a) == 1);
  assert(inBounds(n, 0) == 1);

  // search helper
  const int ascendingArray1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 18, 19};
  const int ascendingArray1_items = 16;
  int index;
  SearchHelper(ascendingArray1, ascendingArray1_items, 10, &index, &equalComparator);
  assert(index == 10);
  SearchHelper(ascendingArray1, ascendingArray1_items, 20, &index, &equalComparator);
  assert(index == 16);
  SearchHelper(ascendingArray1, ascendingArray1_items, -1, &index, &equalComparator);
  assert(index == 16);
  SearchHelper(ascendingArray1, ascendingArray1_items, 10, &index, &greaterThanComparator);
  assert(index == 11);
  SearchHelper(ascendingArray1, ascendingArray1_items, 30, &index, &greaterThanComparator);
  assert(index == 16);
  SearchHelper(ascendingArray1, ascendingArray1_items, -1, &index, &greaterThanComparator);
  assert(index == 0);
  SearchHelper(ascendingArray1, ascendingArray1_items, 10, &index, &greaterThanOrEqualComparator);
  assert(index == 10);
  SearchHelper(ascendingArray1, ascendingArray1_items, 30, &index, &greaterThanOrEqualComparator);
  assert(index == 16);
  SearchHelper(ascendingArray1, ascendingArray1_items, -1, &index, &greaterThanOrEqualComparator);
  assert(index == 0);

  const int integrationTestArray1[] = {0, 2, 4, 6, 8};
  const int intTestArray1Length = 5;
  assert(NotFound == Search(integrationTestArray1, intTestArray1Length, 1, -1, LessThanEquals, &index));
  assert(NotFound == Search(integrationTestArray1, intTestArray1Length, 1, 0, LessThan, &index));
  assert(FoundExact == Search(integrationTestArray1, intTestArray1Length, 1, 0, Equals, &index));
  assert(index == 0);
  assert(NotFound == Search(integrationTestArray1, intTestArray1Length, 1, 1, Equals, &index));
  assert(FoundExact == Search(integrationTestArray1, intTestArray1Length, 1, 2, GreaterThanEquals, &index));
  assert(index == 1);
  assert(FoundGreater == Search(integrationTestArray1, intTestArray1Length, 1, 2, GreaterThan, &index));
  assert(index == 2);
  //[8, 6, 4, 2, 0]
  const int integrationTestArray2[] = {8, 6, 4, 2, 0};
  const int intTestArray2Length = 5;
  assert(NotFound == Search(integrationTestArray2, intTestArray2Length, 0, -1, LessThan, &index));
  assert(NotFound == Search(integrationTestArray2, intTestArray2Length, 0, 0, LessThan, &index));
  assert(FoundExact == Search(integrationTestArray2, intTestArray2Length, 0, 4, LessThanEquals, &index));
  assert(index == 2);
  assert(FoundExact == Search(integrationTestArray2, intTestArray2Length, 0, 8, Equals, &index));
  assert(index == 0);
  assert(FoundGreater == Search(integrationTestArray2, intTestArray2Length, 0, 5, GreaterThanEquals, &index));
  assert(index == 1);
  assert(FoundExact == Search(integrationTestArray2, intTestArray2Length, 0, 2, GreaterThanEquals, &index));
  assert(index == 3);
  assert(NotFound == Search(integrationTestArray2, intTestArray2Length, 0, 8, GreaterThan, &index));
  assert(NotFound == Search(integrationTestArray2, intTestArray2Length, 0, 9, GreaterThan, &index));
  return 0;
}
