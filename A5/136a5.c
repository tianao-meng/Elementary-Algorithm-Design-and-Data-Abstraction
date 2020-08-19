#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

const int IS_EMPTY = 1;
const int PUSH = 2;
const int POP = 3;
const int TOP = 4;
const int QUIT = 5;
void fatal_error() {
    printf("FATAL ERROR\n");
    exit(0);
}

struct stack;

// stack_create() creates a new stack
// effects: allocates memory (client must call stack_destroy)
struct stack *stack_create(void);

// stack_is_empty(s) determines if the stack s contains no items
bool stack_is_empty(const struct stack *s);

// stack_top(s) returns the item on the top of the stack s
// requires: s is not empty
int stack_top(const struct stack *s);

// stack_pop(s) removes the top item on the stack s and returns it
// requires: s is not empty
// effects:  modifies s
int stack_pop(struct stack *s);

// stack_push(item, s) puts the item on top of the stack s
// effects: modifies s
void stack_push(int item, struct stack *s);

// stack_destroy(s) destroys the stack s
// requires: The stack must be empty (all items popped)
// effects:  frees memory
void stack_destroy(struct stack *s);

// This is a fun maze module

// you MUST use these constants for the directions
// these are absolute directions (could also be NORTH, SOUTH, etc.)

extern const int UP;
extern const int DOWN;
extern const int LEFT;
extern const int RIGHT;

struct maze;

// read_maze() reads in a maze from input and returns a pointer
//   to a new maze structure with the initial position 'S'tart
// effects:  if the maze is invalid, exits the program
//           reads input
struct maze *read_maze(void);

// is_wall(m, direction) determines if there is a wall in the
//   given direction in maze m (based on the current position)
// requires: direction is one of: UP, DOWN, LEFT, RIGHT
bool is_wall(const struct maze *m, int direction);

// moves(m, direction) moves in the given direction in maze m
//   (based on the current position) and prints the direction (U/D/L/R).
//   If the 'E'xit is reached, prints E and then exits the program
// requires: direction is one of: UP, DOWN, LEFT, RIGHT
// effects: modifies the maze *m (to store the new position)
//          displays output
//          if attempting to move through a wall, exits the program
void move(struct maze *m, int direction);

int right_direction(int direction){
    if (direction == UP){
        return RIGHT;
    }
    if (direction == DOWN){
        return LEFT;
    }
    if (direction == LEFT){
        return UP;
    }
    if (direction == RIGHT){
        return DOWN;
    }
}
int left_direction(int direction){
    if (direction == UP){
        return LEFT;
    }
    if (direction == DOWN){
        return RIGHT;
    }
    if (direction == LEFT){
        return DOWN;
    }
    if (direction == RIGHT){
        return UP;
    }
}
// find_min(a, len) returns the index of the min (smallest) element in a.
//   (if the min occurs more than once, the lowest index is returned)
int find_min(const int a[], int len){
    int min = INT_MAX;
    int index = 0;
    for (int i = 0; i <= len -1; i++){
        if (a[i] < min){
            min = a[i];
            index = i;
        }
    }
    return index;
}
//int i = 0;
//i++    i = i+1;
//++i
//printf("%d", i+=3);

int find_max(const int a[], int len){
    int max = INT_MIN;
    int index = 0;
    for (int i = 0; i <= len -1; i++){
        if (a[i] > max){
            max = a[i];
            index = i;
        }
    }
    return index;
}
// min_max(a, len, min, max) modifies *min and *max to be the min and max
//   value in a, respectively
// effects: modifies *min, *max
void min_max(const int a[], int len, int *min, int *max){
    int min_index = find_min(a, len);
    int max_index = find_max(a, len);
    *min = a[min_index];
    *max = a[max_index];
}

// longest_seq(a, len) returns the length of the longest consecutive sequence
//   of identical elements that appears in a
int longest_seq(const int a[], int len){
    int count = 1;
    int longest_cur = 1;
    int previous = a[0];
    for (int i = 1; i <= len - 1; i++){
        if (a[i] == previous){
            count += 1;
            if (count >= longest_cur){
                longest_cur = count;
            }
        } else {
            count = 1;
            previous = a[i];
        }
    }
    return longest_cur;

}

1 2 3 2
// is_sorted(a, len) determines if a is sorted
//   (either in ascending or descending order)
bool is_sorted(const int a[], int len) {
    int previous = a[0];
    int i = 1;
    if (a[i] > previous) {
        int j = i + 1;
        while (j <= len - 1) {
            if (a[j] < a[i]) {
                return false;
            }
            i++;
            j++;
        }
    } else if (a[i] < previous) {
        int j = i + 1;
        while (j <= len - 1) {
            if (a[j] > a[i]) {
                return false;
            }
            i++;
            j++;
        }
        previous = a[i];
        i++;
    }


    return true;
}

//    for (int i = 1; i <= len -2; i++){
//        if (a[i] <= previous){
//            if (a[i+1] > a[i]){
//                return false;
//            }
//            previous = a[i];
//        } else {
//            if (a[i+1] < a[i]){
//                return false;
//            }
//            previous = a[i];
//        }
//
//    }
//    return true;
//}

// charfreq(freqs) reads in all characters from input,
//   and updates freqs[1] to be the number of 'A's and 'a's
//   freqs[2] to be the number of 'B's and 'b's, etc.
//   freqs[0] stores the number of non-letter characters,
//   including whitespace characters
// requires: freqs is an array of size 27
// effects:  modifies freqs
//           reads input
void charfreq(int freqs[]){
    char c;
    while (scanf ("%c", &c) == 1){
        if ('a'<= c && c <= 'z'){
            int dif = c - 'a';
            freqs[dif+1]+=1;
        } else if ('A' <=c && c <= 'Z'){
            int dif = c - 'A';
            freqs[dif+1]+=1;
        } else {
            freqs[0]+=1;
        }
    }
}
// read_doubles(arr, maxlen) reads in up to maxlen doubles from input
//   and returns the number of successfully read in values
// requires: arr is an array with length (at least) maxlen
// effects:  modifies arr
//           reads input
int read_doubles(double arr[], int maxlen){
    double d;
    int count = 1;
    while ((scanf("%lf", &d) == 1) && (count <= maxlen)){
        arr[count - 1] = d;
        count ++;
    }
    return count - 1;
}


// stats(arr, len, mean, variance) calculates the mean and variance
//   of the values in arr (storing the results in *mean and *variance)
//   the mean is the sum of arr[i] / len
//   the variance is the sum of (arr[i] - mean)^2 / len
// requires: len > 0
// effects:  modifies *mean and *variance
void stats(const double arr[], int len, double *mean, double *variance){
    double sum_m = 0;
    double sum_v = 0;
    for (int i = 0; i < len; i++){
        sum_m+=arr[i];
    }
    *mean = sum_m / len;
    for (int i = 0; i < len; i++){
        sum_v+=(arr[i] - *mean) * (arr[i] - *mean);
    }
    *variance = sum_v /len;

}

int main() {

//    Q2

//      struct maze * m = read_maze();
//      int cur_dir = DOWN;
//      while(1){
//          cur_dir = right_direction(cur_dir);
//          while (is_wall(m, cur_dir)){
//              cur_dir = left_direction(cur_dir);
//          }
//          move(m, cur_dir);
//      }





//    Q1
//    struct stack *s = stack_create();
//    int quit = -1;
//    while (1){
//        if (quit == 1) {
//            break;
//        }
//        int symbol = read_symbol();
//        switch(symbol){
//            case IS_EMPTY:
//                stack_is_empty(s);
//                break;
//            case PUSH:
//                int r = read_int();
//                stack_push(r, s);
//                break;
//            case POP:
//                int p = stack_pop(s);
//                printf("%d", p);
//                break;
//            case TOP:
//                int p = stack_top(s);
//                printf("%d", p);
//                break;
//            case QUIT:
//                quit = 1;
//
//                break;
//            default:
//                fatal_error();
//        }
//    }
//    while (!stack_is_empty(s)) {
//        stack_pop(s);
//    }
//    stack_destroy(s);
//}
//
//    return 0;
//}
//
//    s->val;
//    s = NULL;
//    s->val;
//
//
//    int a = 0;
//    switch (a) {
//        case A:
//            break;
//        case B:


}
