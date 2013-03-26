/*  Copyright 2002 Sun Microsystems, Inc.  All Rights Reserved
 *
 * SortThread.c
 *
 * This program is meant to be used to illustrate use of the
 * debugger for multi-threaded debugging. It is not meant as
 * an example of C coding or Swing programming.
 */

#include <stdio.h>
#include <jni.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <thread.h>

#define SORT_CT 7
#define SORT_ELEMENT_NO 200
#define TRUE 1
#define FALSE 0

static int sort_values[SORT_CT][SORT_ELEMENT_NO];
enum sort_state
{ SORT_NONE, SORT_SELECTED};
enum sort
{BubbleSort, Binary_Insertion_Sort, HeapSort, QuickSort,
 ShakerSort, Straight_Insertion_Sort, Straight_Selection_Sort};
 static enum sort_state sort_status[SORT_CT] = { SORT_NONE };
 static void setup_sort_table(int sort_type, int elements);
 static int sorts_in_progress();
 static int entry(int sort_type, int pos);
 static void swap_entry(int sort_type, int pos1, int pos2);
 static void set_entry(int sort_type, int pos, int new_value);
 static void print_entry(int sort_type);
 
 /* Sort routines */
 void* bubblesort(void *sort_args);
 void* binary_insertion_sort(void *sort_args);
 void* heapsort(void *sort_args);
 void* quicksort_stub(void *sort_args);
 void* shakersort(void *sort_args);
 void* straight_insertion_sort(void *sort_args);
 void* straight_selection_sort(void *sort_args);
 
 void *(*sort_func[SORT_CT])(void*) =
 {bubblesort, binary_insertion_sort, heapsort, quicksort_stub,
  shakersort, straight_insertion_sort, straight_selection_sort};
  
  JNIEXPORT void JNICALL Java_SortThread_sort_1num
  (JNIEnv * env, jclass cl, jint sort_no) {
      if (sort_status[sort_no-1] == SORT_NONE)
          sort_status[sort_no-1] = SORT_SELECTED;

      if (sort_status[sort_no-1] == SORT_SELECTED) {
          int sen = SORT_ELEMENT_NO;
          setup_sort_table((sort_no-1), sen);
      }
  }
  
  /*
   * setup_sort_table()
   *
   */
  static void setup_sort_table(int sort_type, int elements) {
      int i, j;
      
      for (i = 0; i < elements; i++)
          sort_values[sort_type][i] = -1;
      
      switch (sort_type) {
          case 0: printf("\n bubblesort: random generated data \n");
          break;
          case 1: printf("\n binary_insertion_sort: random generated data \n");
          break;
          case 2: printf("\n heapsort: random generated data \n");
          break;
          case 3: printf("\n quicksort: random generated data \n");
          break;
          case 4: printf("\n shakersort: random generated data \n");
          break;
          case 5: printf("\n straight_insertion_sort: random generated data \n");
          break;
          case 6: printf("\n straight_selection_sort: random generated data \n");
          break;
          default: printf("\n no selection \n");
          break;
      }
      
      for (i = 0; i < elements; i++) {
          j = (int) (rand() % elements) ;
          while (sort_values[sort_type][j] > -1)
              j = (int) (rand() % elements);
          sort_values[sort_type][j] = i;
      }
      
      print_entry(sort_type);
  }
  
  /*
   * sort_proc()
   *
   */
  JNIEXPORT void JNICALL Java_SortThread_sort_1proc(JNIEnv* env, jobject obj) {
      int i;
      
      for (i = 0; i < SORT_CT; i++) {
          if (sort_status[i] == SORT_SELECTED) {
              thr_create(NULL, 0, sort_func[i], (void *)SORT_CT, 0, NULL);
              sort_status[i] = SORT_NONE;
          }
      }
      
      while (sorts_in_progress())
          thr_join(NULL, NULL, NULL);
  }
  
  /*
   * sorts_in_progress()
   *
   */
  int sorts_in_progress() {
      int running_sorts = 0;
      int i;
      
      for (i = 0; i < SORT_CT; i++)
          if (sort_status[i] == SORT_SELECTED)
              running_sorts++;
      
      return running_sorts;
  }
  
  JNIEXPORT void JNICALL Java_SortThread_sort_1reset(JNIEnv* env, jclass c1) {
      int i;
      
      for (i = 0; i < SORT_CT; i++) {
          sort_status[i] = SORT_NONE;
      }
  }
  
  /*
   * bubblesort()
   *
   */
  void* bubblesort(void *sort_args) {
      int i, j, tmp;
      
      for (i = 1; i < SORT_ELEMENT_NO; i++) {
          for (j = SORT_ELEMENT_NO - 1; j >= i; j--) {
              if (entry(BubbleSort, j) < entry(BubbleSort, j - 1))
                  swap_entry(BubbleSort, j - 1, j);
          }
      }
      
      printf("\n bubblesort: sorting result\n");
      print_entry(BubbleSort);
      return NULL;
  }
  
  /*
   * binary_insertion_sort()
   *
   */
  void* binary_insertion_sort(void *sort_args) {
      int i, j, l, r, m, x;
      
      for (i = 1; i < SORT_ELEMENT_NO; i++) {
          x = entry(Binary_Insertion_Sort, i);
          l = 0;
          r = i - 1;
          while (l <= r) {
              m = (l + r) / 2;
              if (x < entry(Binary_Insertion_Sort, m))
                  r = m - 1;
              else
                  l = m + 1; }
          for (j = i - 1; j >= l; j--)
              set_entry(Binary_Insertion_Sort, j + 1, entry(Binary_Insertion_Sort, j));
          set_entry(Binary_Insertion_Sort, l, x);
      }
      
      printf("\nbinary_insertion_sort: sorting result\n");
      print_entry(Binary_Insertion_Sort);
      return NULL;
  }
  
  /*
   * heapsort_sift()
   *
   */
  void heapsort_sift(int l, int r) {
      int i, j, x;
      i = l;
      j = i * 2;
      
      x = entry(HeapSort, i);
      
      while (j <= r) {
          if (j < r)
              if (entry(HeapSort, j) < entry(HeapSort, j + 1))
                  j++;
          if (x >= entry(HeapSort, j))
              break;
          set_entry(HeapSort, i, (entry(HeapSort, j)));
          i = j;
          j = i * 2;
      }
      set_entry(HeapSort, i, x);
  }
  /*
   * heapsort()
   *
   */
  void* heapsort(void *sort_args) {
      int l, r;
      l = SORT_ELEMENT_NO / 2;
      r = SORT_ELEMENT_NO - 1;
      
      while (l != 0) {
          l--;
          heapsort_sift(l, r);
      }
      while (r != 0) {
          swap_entry(HeapSort, 0, r);
          r--;
          heapsort_sift(l, r);
      }
      
      printf("\nheapsort: sorting result\n");
      print_entry(HeapSort);
      return NULL;
  }
  
  /*
   * quicksort()
   *
   */
  void quicksort(int l, int r) {
      int i, j, x;
      i = l;
      j = r;
      
      x = entry(QuickSort, (l + r) / 2);
      
      do {
          while (entry(QuickSort, i) < x)
              i++;
          while (x < entry(QuickSort, j))
              j--;
          if (i <= j) {
              swap_entry(QuickSort, i, j);
              i++;
              j--;
          }
      } while (i <= j);
      if (l < j)
          quicksort(l, j);
      if (i < r)
          quicksort(i, r);
  }
  
  /*
   * quicksort_stub()
   *
   */
  void* quicksort_stub(void *sort_args) {
      quicksort(0, SORT_ELEMENT_NO - 1);
      printf("\nquicksort: sorting result\n");
      print_entry(QuickSort);
      return NULL;
  }
  
  /*
   * shakersort()
   *
   */
  void* shakersort(void *sort_args) {
      int j, k, l, r;
      l = 1;
      r = k = SORT_ELEMENT_NO - 1;
      
      while (TRUE) {
          for (j = r; j >= l; j--)
              if (entry(ShakerSort, j) < entry(ShakerSort, j - 1)) {
                  swap_entry(ShakerSort, j - 1, j);
                  k = j;
              }
          l = k + 1;
          for (j = l; j <= r; j++)
              if (entry(ShakerSort, j) < entry(ShakerSort, j - 1)) {
                  swap_entry(ShakerSort, j - 1, j);
                  k = j;
              }
          r = k - 1;
          if (l > r) {
              printf("\nshakersort: sorting result\n");
              print_entry(ShakerSort);
              return NULL;
          }
      }
  }
  
  /*
   * straight_insertion_sort()
   *
   */
  void* straight_insertion_sort(void *sort_args) {
      int j, x, i;
      
      for (i = 0; i < SORT_ELEMENT_NO; i++) {
          x = entry(Straight_Insertion_Sort, i);
          j = i - 1;
          while (j >= 0 && x < entry(Straight_Insertion_Sort, j)) {
              set_entry(Straight_Insertion_Sort, j + 1, entry(Straight_Insertion_Sort, j));
              j--;
          }
          set_entry(Straight_Insertion_Sort, j + 1, x);
      }
      
      printf("\nstraight_insertion_sort: sorting result\n");
      print_entry(Straight_Insertion_Sort);
      return NULL;
  }
  
  /*
   * straight_selection_sort()
   *
   */
  void* straight_selection_sort(void *sort_args) {
      int i, j, k, x;
      
      for (i = 0; i < SORT_ELEMENT_NO - 1; i++) {
          k = i;
          x = entry(Straight_Selection_Sort, i);
          for (j = i + 1; j < SORT_ELEMENT_NO; j++)
              if (entry(Straight_Selection_Sort, j) < x) {
                  k = j;
                  x = entry(Straight_Selection_Sort, j);
              }
          set_entry(Straight_Selection_Sort, k, entry(Straight_Selection_Sort, i));
          set_entry(Straight_Selection_Sort, i, x);
      }
      
      printf("\nstraight_selection_sort: sorting result\n");
      print_entry(Straight_Selection_Sort);
      return NULL;
  }
  
  /*
   * entry()
   *
   */
  int entry(int sort_type, int pos) {
      return sort_values[sort_type][pos];
  }
  
  /*
   * swap_entry()
   *
   */
  void swap_entry(int sort_type, int pos1, int pos2)
  { int temp = entry(sort_type, pos1);
    set_entry(sort_type, pos1, entry(sort_type, pos2));
    set_entry(sort_type, pos2, temp);
  }
  
  /*
   * set_entry_internal()
   *
   */
  void set_entry(int sort_type, int pos, int new_value) {
      sort_values[sort_type][pos] = new_value;
  }
  
  void print_entry(int sort_type) {
      int i;
      printf("[");
      for (i = 0; i < SORT_ELEMENT_NO; i++) {
          printf("%d ", sort_values[sort_type][i]);
      }
      printf("]\n\n");
  }
