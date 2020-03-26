#include <stdio.h>

int vals[] = { 12, 3, 6, 5, 7, 9, 11, 3, 1, 4, 5 };
int vals_len = 11;

void print_a(void)
{
  int i;

  for (i = 0; i < vals_len; i++)
    printf("%d ", vals[i]);
  putchar('\n');
}

void swap(int v[], int i, int j)
{
  int temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;

  print_a();
}
  
void quicksort(int v[], int left, int right)
{
  int last, i;

  if (left >= right)
    return;

  swap(v, left, (left + right) / 2);
  last = left;
  
  for (i = left + 1; i <= right; i++)
    if (v[i] < v[left])
      swap(v, ++last, i);

  swap(v, left, last);
  quicksort(v, left, last-1);
  quicksort(v, last+1, right);
}

int main()
{
  quicksort(vals, 0, vals_len-1);
  print_a();
  return 0;
}
