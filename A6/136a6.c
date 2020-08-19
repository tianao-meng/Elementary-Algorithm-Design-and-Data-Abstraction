#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

// swap(a, b) swaps the values of *a and *b
// effects: modifies *a and *b
//          updates the swap count
void swap(int *a, int *b);
void quick_sort_range(int *a, int first, int last) {
    if (last <= first) return; // length is <= 1
    int *pivot = a + first; // first element is the pivot
    int *pos = a + last; // where to put next larger
    for (int *i = a + last; i > a + first; --i) {
        if (*i > *pivot) {
            swap(pos, i);
            --pos;
        }
    }
    swap(a + first, pos); // put pivot in correct place
    quick_sort_range(a, first, pos - a - 1);
    quick_sort_range(a, pos + 1 - a, last);
}
void quick_sort(int *a, int len) {
    quick_sort_range(a, 0, len - 1);
}
void zigzag_sort(int a[], int len){
    int start_index = 0;
    int finnish_index = len - 2;
    int count =0;
    while(finnish_index >= start_index){
        count = 0;
        for (int i = start_index; i <= finnish_index; i++){
            if (a[i] > a[i+1]){
                swap(a+i+1, a+i);
                count += 1;
            }
            if (count == 0){
                break;
            }
            

        }
        finnish_index -= 1;
        count = 0;
        for (int i = finnish_index; i >= start_index; i--){
            if (a[i]<a[i-1]){
                swap(a+i-1, a+i);
                count += 1;
            }
            if (count == 0){
                break;
            }
            
        }
        start_index += 1;
    }

}

const int sequence_max_len = 1000;

// NOTE: This is a "transparent" structure, but should be treated
//        as opaque: clients should NOT access fields directly
struct sequence {
    int len;
    int maxlen;
    int data[1000];
};

// NOTE: All of the following functions REQUIRE:
//       pointers to a sequence (e.g., seq) are valid (not NULL)

// sequence_init(seq) initializes (or resets) seq to be empty
//   with maximum capacity sequence_max_len
// effects: modifies seq
// time:    O(1)
void sequence_init(struct sequence *seq){
    assert(seq != NULL);
    seq -> len = 0;
    seq -> maxlen = sequence_max_len;
}

// sequence_length(seq) returns the number of items in seq
// time: O(1)
int sequence_length(const struct sequence *seq){
    assert(seq != NULL);
    return seq -> len;
}

// sequence_item_at(seq, pos) returns the item in seq at position pos
// requires: 0 <= pos < sequence_length(seq)
// time:     O(1)
int sequence_item_at(const struct sequence *seq, int pos){
    assert(seq != NULL);
    assert(pos >= 0 && pos < seq -> len);
    return seq ->data[pos];
}

// sequence_insert_at(seq, pos, val) inserts a new item with value val
//   at position pos in seq
//   (changing the position of items at position >= pos)
// requires: 0 <= pos <= sequence_length(seq) < sequence_max_len
// effects:  modifies seq
// time:     O(n)
void sequence_insert_at(struct sequence *seq, int pos, int val){
    assert(seq != NULL);
    assert(pos >= 0);
    assert(pos <= seq -> len);
    assert(seq ->len < seq -> maxlen);
    for (int i = pos; i <= seq ->len; i++){
        int temp = seq ->data[i];
        seq -> data[i] = val;
        val = temp;
    }
    seq -> len += 1;
}

// sequence_remove_at(seq, pos) removes the item at position pos in seq
//   and returns the removed value
//   (changing the position of items > pos)
// requires: 0 <= pos < sequence_length(seq)
// effects:  modifies seq
// time:     O(n)
int sequence_remove_at(struct sequence *seq, int pos){
    assert(seq != NULL);
    assert(pos >= 0);
    assert(pos < seq -> len);
    int res = seq -> data[pos];
    for (int i = pos; i <= seq -> len - 2; i++){
        seq -> data[i] = seq -> data[i+1];
    }
    seq -> len -= 1;
    return res;
}

// sequence_print(seq) prints out the items in seq
//   using the format: "[item_0,item_1,...,item_last]\n"
//   or "[empty]\n"
// effects: displays output
// time :   O(n)
void sequence_print(const struct sequence *seq){
    assert(seq != NULL);
    if (seq -> len == 0){
        printf ("[empty]\n");
    } else {
        for (int i = 0; i <= seq -> len - 1; i++){
            if (i == 0){
                printf("[");
            }
            if (0 <= i && i < len -1){
            printf ("%d,", seq ->data[i]);
            }
            if (i == seq -> len -1){
                printf("]\n");
            }
        }
    }

}
// see arrayfun.h for documentation
// max_diff(a, len) finds the maximum difference between two elements in a
// requires: all array parameters are valid arrays of length len
int max_diff(const int a[], int len) {
    assert(a);
    assert(len > 0);

    int temp = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (abs(a[j] - a[i]) > temp) {
                temp = abs(a[j] - a[i]);
            }
        }
    }
    return temp;
}

// consec_sum(a, n, b, m) determines if an element of b is the sum
//   of any two consecutive elements in a
// requires: a and b are arrays of length n and m respectively
//           a is sorted in increasing order (b may not be sorted)
bool consec_sum(const int a[], int n, const int b[], int m) {
    assert(a);
    assert(n > 0);
    assert(b);
    assert(m > 0);

    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            if (b[j] == a[i] + a[i + 1]) {
                return true;
            }
        }
    }
    return false;
}

// even_first(a, len) puts all the even numbers before all of the odd numbers
//   in the array a
// effects: modifies a
// time: n2
void even_first(int a[], int len) {
    assert(a);
    assert(len > 0);

    int temp = 0;
    for (int i = 0; i < len; ++i) {
        if (a[i] % 2 == 0) {
            temp = a[i];
            for (int j = i; j > 0; --j) {
                a[j] = a[j - 1];
            }
            a[0] = temp;
        }
    }
}
// time: O(n), n is the len of a
int max_diff(const int a[], int len){
    const int INT_MAX = 2147483647;
    const int INT_MIN = -2147483648;
    int min = INT_MAX;
    int max = INT_MIN;
    for (int i = 0; i < len; i++){
        if (a[i] < min){
            min = a[i];
        }
        if (a[i] > max){
            max = a[i];
        }

    }
    return (max - min);

}

bool binary_search (const int a[], int start, int end, int sum){
    int mid = (end - start) / 2;
    if (end - start == 0){
        return false;
    }
    if (sum > (a[mid] + a[mid + 1])){
        start = mid + 1;
        binary_search(a, start, end, sum);
    } else if (sum < (a[mid] + a[mid + 1])){
        end = mid;
        binary_search(a, start, end, sum);
    } else {
        return true;
    }
}

// time: O(m*logn), n is len of a and m is len of b
bool consec_sum(const int a[], int n, const int b[], int m){
    int end = n - 1;
    int start = 0;
    for (int i = 0; i <= m; i++){
         if (binary_search(a, start, end, b[i])){
             return true;
         }
    }
    return false;
}
void swap2 (int index1, int index2, int a[]){
    int temp = a[index1];
    a[index1] = a[index2];
    a[index2] = temp;
}


// time: O(n), n is len of a
void even_first(int a[], int len){
    int odd_index = -1;
    for (int i = 0; i < len; i++){
        int reminder = a[i] % 2;
        if (reminder == 1 && odd_index == -1){
            odd_index = i;
        }
        if (odd_index != -1 && reminder == 0){
            swap2(odd_index,i,a);
            odd_index += 1;
        }
    }

}

// vowel_count(s) returns the number of vowels (a,e,i,o,u,A,E,I,O,U) in s
int vowel_count(const char *s){
    int count = 0;
    for (int i = 0; s[i]; i++){
        if ((s[i] == 'a') || (s[i] == 'e')|| (s[i] == 'i') || (s[i] == 'o') || (s[i] == 'u') ||
            (s[i] == 'A') || (s[i] == 'E') || (s[i] == 'I') || (s[i] == 'O') || (s[i] == 'U')){
            count += 1;
        }
    }
    return count;
}

// inflate(s) increments all digit characters in s (e.g., '3' => '4')
//   except for '9', which cannot get any bigger and is not changed
void inflate(char *s){
    for (int i = 0; s[i]; i++){
        if (s[i] => '0' && s[i] <= '8'){
            s[i] = s[i] + 1;
        }
    }
}

// char_match_count(s1, s2) counts how many characters of s1 appear in s2
// notes: Characters that appear more than once in s1 are counted once each.
//        It does not matter how any times a character appears in s2.
//        The null character is not counted.
int char_match_count(const char *s1, const char *s2){
    int count = 0;
    for (int i = 0; s1[i]; i++){
        for (int j = 0; s2[j]; j++){
            if (s1[i] == s2[j]){
                count += 1;
                break;
            }
        }
    }
    return count;
}

// a word search module

extern const int max_dimension; // 100

// word searches are only **lower case letters** 'a'...'z'

struct word_search {
    int width;
    int height;
    char grid[100 * 100 + 1];
};
// requires: width >= 1, height >= 1
//           grid is a string with strlen (width*height)
//           the char at row r, column c is found at grid[r * width + c]
//           (row 0, column 0 is in the upper-left corner)

// there are 8 valid DIRECTIONS:
extern const int num_directions; // 8

extern const int UP;
extern const int UP_RIGHT;
extern const int RIGHT;
extern const int DOWN_RIGHT;
extern const int DOWN;
extern const int DOWN_LEFT;
extern const int LEFT;
extern const int UP_LEFT;

////a.h
//static int x = 1;
/////////////////
//
//#include "a.h"
//extern int x;
// that are conveniently stored in an array for you:
extern const int DIRECTIONS[8];

extern const int NOT_FOUND;

// requires: all pointers are valid, all strings have strlen >= 1

// read_word_search(ws) reads a word search from input
//   and stores the result in *ws
// input format:
//   width [positive int]
//   height [positive int]
//   followed by height strings, each of length exactly width
// effects: reads input
//          modifies *ws
//          calls exit(1) if encounters invalid input
void read_word_search(struct word_search *ws){
    assert(ws != NULL);
    int width;
    int height;
    scanf("%d", &width);
    scanf("%d", &height);
    ws -> height = height;
    ws -> width =width;
    char c;
    while (scanf (" %c" , &c) == 1){
        assert(c <= 'z' && a <= 'a');
        for(int i = 0; i < width * height; i++){
            ws -> grid[i] = c;
        }
    }
}

void coordinate (int i, int *x, int *y, const struct word_search *ws){
    *x = i % ws ->width;
    *y = i / ws ->width;
}
// search(ws, word, start_row, start_col ) searches ws for the given word.
//   If word is found, it modifies *start_row and *start_col to
//     indicate the start of the word in ws, and returns a DIRECTION
//     to indicate which direction the word continues in
//   If word is not found, it returns NOT_FOUND
//   Note: if word occurs more than once, it does not matter
//     which location and/or direction is returned
// effects: may modify *start_row, *start_col

int search(const struct word_search *ws, const char *word,
           int *start_row, int *start_col){
    assert(ws != NULL);
    assert(word != NULL);
    assert(start_raw != NULL);
    assert(start_clo != NULL);
    for (int i = 0; i < ws -> width * ws ->height; i++){
        if (word[0] == ws -> grid [i]){
            int x = 0;
            int y = 0;
            coordinate (i, &x, &y, ws);
            //right
            int k = 1;
            for ( ; word[k] && (x + k < ws -> width); k++){
                if (word[k] != ws -> grid[i+k]){
                    break;
                }
            }
            if (!word[k]){
                *start_row = x;
                *start_col = y;
                return RIGHT;
            }
            // RIGHT_DOWN
            k = 1;
            for ( ; word[k] && (y + k < ws -> height) && (x + k < ws -> width); k++){
                if (word[k] != ws -> grid[i + k * ws -> width + k]){
                    break;
                }
            }
            if (!word[k]){
                *start_row = x;
                *start_col = y;
                return DOWN_RIGHT;
            }
            // DOWN
            k = 1;
            for ( ; word[k] && (y + k < ws -> height); k++){
                if (word[k] != ws -> grid[i + k * ws -> width]){
                    break;
                }
            }
            if (!word[k]){
                *start_row = x;
                *start_col = y;
                return DOWN;
            }
            // LEFT_DOWN
            k = 1;
            for ( ; word[k] && (y + k < ws -> height) && (x - k >= 0); k++){
                if (word[k] != ws -> grid[i + (k * ws -> width) - k]){
                    break;
                }
            }
            if (!word[k]){
                *start_row = x;
                *start_col = y;
                return DOWN_LEFT;
            }
            // LEFT
            k = 1;
            for ( ; word[k] && (x - k >= 0); k++){
                if (word[k] != ws -> grid[i - k]){
                    break;
                }
            }
            if (!word[k]){
                *start_row = x;
                *start_col = y;
                return LEFT;
            }
            //UP_LEFT
            k = 1;
            for ( ; word[k] && (y - k >= 0) && (x - k >= 0); k++){
                if (word[k] != ws -> grid[i - (k * ws -> width) - k]){
                    break;
                }
            }
            if (!word[k]){
                *start_row = x;
                *start_col = y;
                return UP_LEFT;
            }
            //UP
            k = 1;
            for ( ; word[k] && (y - k >= 0) ; k++){
                if (word[k] != ws -> grid[i - (k * ws -> width)]){
                    break;
                }
            }
            if (!word[k]){
                *start_row = x;
                *start_col = y;
                return UP;
            }
            //UP_RIGHT
            k = 1;
            for ( ; word[k] && (y - k >= 0) && (x + k < ws -> width); k++){
                if (word[k] != ws -> grid[i - (k * ws -> width) + k]){
                    break;
                }
            }
            if (!word[k]){
                *start_row = x;
                *start_col = y;
                return UP_RIGHT;
            }


        }
    }
    return NOT_FOUND;
}


// x_dir = 1 / 0 / -1
void print_upper(int x_dir, int y_dir, const struct word_search *ws,int x, int y) {
    int k = 0;
    for (int i = 0; i < ws -> height; i++){
        for(int j = 0; j < ws -> width; j++){
            //BOTTOM_RIGHT
            if ((x + (x_dir * k) == j) && (y + (y_dir * k) == i)){
                k++;
                printf("%c", ws -> grid[i*(ws -> width) + j] - 'a' +'A');
            }
            printf("%c", ws -> grid[i*(ws -> width) + j]);
        }
        printf("\n");
    }
}

// print_search(ws, word) searches ws for the given word.
//   If word is found, it prints the ws with the word in UPPERCASE
//   If word is not found, it prints "%s not found\n"
//   Note: if word occurs more than once, it does not matter
//     which location and/or direction is shown in uppercase
// effects: produces output
void print_search(const struct word_search *ws, const char *word){
    int x = 0;
    int y = 0;
    int dir = search(ws, word, &x, &y);
    if (dir == NOT_FOUND){
        printf("%s not found\n", word);
    }
    if (dir == DOWN_RIGHT) {
        print_upper(1, 1, ws, x , y);
    }

}

int main() {
//    l: print sequence_length as "length: %d\n"
//    a INT: print sequence_item_at as "item_at(%d): %d\n"
//    i INT1 INT2: calls sequence_insert_at(..., INT1, INT2)
//    r INT: calls sequence_remove_at(..., INT)
//    p: calls sequence_print
//    q: quit
    char c;
    int data[1000] = {0};
//    int array[3] = {0};
    struct sequence i = {0,1000, data};
    struct sequence *seq = &i;
    sequence_init(seq);
    int pos = 0;
    int val = 0;
    while (scanf("%c", &c) == 1){
        switch (c){
            case 'l':
                printf ("length: %d\n", sequence_length(seq));
            case 'a':
                scanf ("%d", &pos);
                sequence_item_at(seq, pos);
            case'i':
                scanf ("%d", &pos);
                scanf ("%d", &val);
                sequence_insert_at(seq, pos, val);
            case 'r':
                scanf("%d", &pos);
                sequence_remove_at(seq, pos);
            case 'p':
                sequence_print(seq);
            case 'q':
                break;
            default:
                printf("wrong input\n");
                break;
        }
    }
    return 0;
}
