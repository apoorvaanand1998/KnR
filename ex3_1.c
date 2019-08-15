#include <stdio.h>

int binary_search(int x, int arr[], int n)
{
  int low = 0;
  int high = n - 1;

  while (low <= high) {
    int mid = (low + high) / 2;

    if (arr[mid] == x)
      return mid;
    else
      (arr[mid] > x) ? (high = mid - 1) : (low = mid + 1);
  }
  return -1;
}

int main()
{
  int pos;
  int arr[] = {1, 2, 4, 9, 10};
  
  pos = binary_search(9, arr, 5);
  printf("%d\n", pos+1);
  
  return 0;
}
