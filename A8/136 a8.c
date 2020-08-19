#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
//#include <stdbool.h>
// slurp() reads in all input until EOF and returns a new string
//   with the contents (or NULL if EOF is encountered immediately)
// effects: may allocate memory (caller must free)
//          read inputs
// time:    O(n) [amortized]

char *slurp(void){
    int maxlen = 1;
    int len = 0;
    char c;
    if (scanf("%c", &c) != 1){
        return NULL;
    }
    char * ans = (char *)malloc(maxlen * sizeof(char));
    ans[0] = c;
    len +=1;
    while (scanf("%c", &c) == 1){
        ans[len] = c;
        len += 1;
        if (len == maxlen){
            s->maxlen *= 2;
            ans= realloc(ans, sizeof(int)* maxlen);
        }
    }
    ans[len] = 0;
    return ans;
}

// this is a module that deals with arrays of strings

// all string parameters must be valid strings

// a "word" is simply a sequence of non-whitespace characters
// and may includes characters that are not letters


// split(s, num_strings) returns an array of strings, corresponding
//   to the words in s in the order that they appear in s.
// notes: modifies s by replacing all whitespace chars with '\0'
//        each string in the array "points" to an address within s
//        *num_strings is modified to contain the length
//        returns NULL if s is empty or only contains whitespace
// effects: modifies s, *num_strings
//          allocates memory for the array (not for each string)
//          client must free the returned value
// time:    O(n), n is the length of s

char **split(char *s, int *num_strings){
    int len_s = 0;
    int len_str = 0;
    for (int i = 0; s[i];i++){
        if (s[i] == ' '){
            len_str+=1;
            s[i] = '\0';
        }
        len_s+=1;
    }
    len_str += 1;
    *num_strings = len_str;
    if (len_str == 0) {
        return NULL;
    }
    char ** ans = (char **) malloc(len_str * sizeof(char*));
    ans[0] = s;
    int idx_ans = 1;
  //  for (int j = 1; j < len_str; j++){
    for (int i = 0; ;i++) {
        if (idx_ans >= len_str) break;
        if (s[i] == '\0') {
            ans[idx_ans] = s + i + 1;
            idx_ans++;

        }
    }
    return ans;

}


 void merge(char ** aos,  char ** left, int llen,  char ** right, int rlen){
     int left_pos = 0;
     int right_pos = 0;
     int i = 0;
     for (; i < llen + rlen; i++){
         if (strcmp(left[left_pos] , right[right_pos]) == -1
             || strcmp(left[left_pos] , right[right_pos]) == 0){
             aos[i] = left[left_pos];
             left_pos++;
             if (left_pos == mid_index){
                 break;
             }
         }
         if (strcmp(left[left_pos] , right[right_pos]) == 1){
             aos[i] = right[right_pos];
             right_pos++;
             if (right_pos == len - llen){
                 break;
             }
         }
     }
     for (; i < (l + len); i++){
         if (left_pos <= llen){
             aos[i] = left[left_pos];
             left_pos++;
         }
         if (right_pos <= rlen){
             aos[i] = right[right_pos];
             right_pos++;
         }

     }

}

void seperate(char **aos, int l, int r) {
    int len = r - l;
    int llen = (r - l)/2;
    int rlen = len - llen;
    
    char ** left = (char**)malloc(llen * sizeof(char*));
    char ** right = (char**)malloc(rlen * sizeof(char*));
    
    for (int i = 0; i < llen; i++){
        left[i] = aos[l + i];
    }
    for (int i = 0; i < rlen; i++){
        right[i] = aos [l + llen + i];
    }
    int mid= (l + r) / 2;
    
    seperate(left,l,mid);
    seperate(right,mid + 1,r);
    merge(aos, left, llen, right, rlen);
    free(left);
    free(right);

}
// merge_sort(aos, len) sorts the array of strings aos in
//   lexicographical order
// effects: modifies a
// time:    O(m*n*logn), n is len, m is len of largest string
//todo : free
void merge_sort(char **aos, int len){
    seperate(aos, 0, len - 1);
}


// word_freq(s) prints all of the unique words is s along with the
//   number of times each word occurs using "%s [%d]\n"
// notes: words are printed in descending order of the number of times
//          they occur (ties broken by lexicographical order)
//        prints nothing if s is empty or only contains whitespace
// time:  O(???) n is the number of words, m is len of largest word
//        [at most m*n^2 -- justify your time in  in your aos.c]
// todo : free
void swap (char ** a, int index_a, int index_b, int len){
    char * temp;
    temp = a[index_b];
    a[index_b] = a[index_a];
    a[index_a] = temp;
}
void swap_int(int * a, int index_a, int index_b, int len){
    int temp;
    temp = a[index_b];
    a[index_b] = a[index_a];
    a[index_a] = temp;
}
void word_freq(const char *s){
    int num_str = 0;
    int len_s = 0;
    for (int i = 0; s[i];i++){
        len_s+=1;
    }
    char *s_copy = (char*) malloc(sizeof(char) * len_s);
    strcpy(s_copy,s);
    char ** ans = split(s_copy, &num_str);

    merge_sort(ans, num_str);

    int *num = (int*) malloc(sizeof(int) * num_str);
    char ** res = (char**) malloc(sizeof(char*) * num_str);
    int previous = 0;
    int count = 1;
    int num_index = 0;
    for(int i = 1;i < num_str;i++){
        if(strcmp(ans[previous], ans[i]) == 0){
            count++;
        } else {
            num[num_index] = count;
            res[num_index] = ans[previous];
            previous = i;
            count = 1;
            num_index += 1;
        }
    }
    num[num_index] = count;
    res[num_index] = ans[previous];

    int min= INT_MAX;
    int min_index = 0;
    //int *arr = (int*) malloc(sizeof(int) * num_str);
    for (int j = 0; j <= num_index; j++) {
        for (int i = j; i <= num_index; i++) {
            if (num[i] < min) {
                min = num[i];
                min_index = i;
                }
            }
        swap(res, j, min_index, num_str);
        swap_int(num, j, min_index, num_str);
        min = INT_MAX;
     }
    for (int i = 0;i <= num_index; i++){
        printf("%s [%d]\n", res[i], num[i]);
    }
}



#include <stdbool.h>

// the symbol_table ADT assigns int IDs to strings, so they can
// be referenced as an integers instead of by strings

// To facilitate CS136 testing:
//   * INVALID_SYMBOL should be defined as -1
//   * valid symbols should be assigned the IDs 1, 2, 3, etc. (in order)
//   * so all IDs from 1 ... symbol_count() should be valid symbol IDs

// all symbol table parameters must be valid symbol tables

// for times, n is the string length, m is symbol_count()

struct symbol_table {
    int maxlen;
    int len;
    char ** str;
};

// is_valid_symbol_string(s) determines if the string in s is a valid
//   symbol according to the following naming rules:
//   * length is at least one
//   * only contain letters, underscores and numbers
//   * starts with a letter
// time: O(n)
bool is_valid_symbol(const char *s){

    int len = 0;

    for (int i = 0; s[i]; i++){
        len += 1;
        if (!(('a' <= s[i] && s[i] <= 'z' ) || ('A' <= s[i] && s[i] <= 'Z' )
              || (s[i] == '_') || ('0' <= s[i] && s[i] <= '9'))){
            return false;
        }
    }

    if (!(('a' <= s[0] && s[0] <= 'z' ) || ('A' <= s[0] && s[0] <= 'Z' ) )){
        return false;
    }

    if (len < 1){
        return false;
    }
    return true;

}

// symbol_table_create() creates an empty symbol table
// effects: allocates memory (must call symbol_table_destroy)
struct symbol_table *symbol_table_create(void){
    struct symbol_table * symbolTable = (struct symbol_table*) malloc (sizeof(struct symbol_table));
    symbolTable -> len = 0;
    symbolTable -> maxlen = 1;
    symbolTable -> str = (char**) malloc (sizeof(char*) * symbolTable -> maxlen);
    return symbolTable;
}

// symbol_table_destroy(st) destroys the symbol table st
// effects: st is no longer valid
// time:    O(m)
void symbol_table_destroy(struct symbol_table *st){
    free (st -> str);
    free (st);
}

// the constant INVALID_SYMBOL is returned by symbol_lookup & symbol_read when:
// * the string (parameter or from input) is not a valid symbol
// * the end of the input (e.g., EOF) is encountered in symbol_read

//when i include other's header file, others defined this variable,
// i use this variable,  i need to use extern, in this environment.
// tell my compiler that i must use this variable before compile headerfile .
extern const int INVALID_SYMBOL;

// symbol_count(st) returns the number of symbol IDs that have been
//   generated
int symbol_count(const struct symbol_table *st){
    return st -> len;
}

// symbol_read(st) returns the ID for the next symbol from input
//   (which may be a new or existing ID) or INVALID_SYMBOL
// effects: reads from input
//          modifies st (if returns a "new" symbol)
// time:    O(n*m)
int symbol_read(struct symbol_table *st){
    char ** ans = st -> str;
    int len = st -> len;
    int symbol_max = 1;
    char * symbol = (char*) malloc(sizeof(char) * symbol_max);
    int str_len = 0;

    while (scanf("%c", symbol) == 1){
        str_len += 1;
        if (str_len == symbol_max){
            symbol_max *= symbol_max;
            realloc(symbol, symbol_max);
        }
    }
        
    if(! is_valid_symbol(symbol)){
        return INVALID_SYMBOL;
    }

    for (int i = 0; i < st -> len; i++){
        if (strcmp(ans[i], symbol) == 0) {
            return i + 2;
        }
    }
    if (len == st -> maxlen){
        ans = realloc(st -> str , 2 * st -> maxlen);
        st -> maxlen = 2 * st -> maxlen;
    }
    ans[len] = symbol;
    st -> len += 1;
    return len + 1;
    
}

// symbol_lookup(st, symbol_string) returns the ID for symbol_string
//   (which may be a new or existing ID) or INVALID_SYMBOL
// effects: modifies st (if returns a "new" symbol)
// time:    O(n*m)
int symbol_lookup(struct symbol_table *st, const char *symbol_string){
    char ** ans = st -> str;
    int len = st -> len;

    if(! is_valid_symbol(symbol_string)){
        return INVALID_SYMBOL;
    }

    for (int i = 0; i < len; i++){
        if (strcmp(ans[i], symbol_string) == 0){
            return i + 1;
        }

    }
    if (len == st -> maxlen){
        ans = realloc(st -> str , 2 * st -> maxlen);
        st -> maxlen = 2 * st -> maxlen;
    }
    ans[len] = symbol_string;
    st -> len += 1;
    return len ;

}

// symbol_print(st, symbol_id) prints the symbol corresponding to symbol_id
//   using "%s" (no newline)
// requires: symbol_id is a valid ID: 0 < symbol_id <= symbol_count()
// effects: displays a message
// time:    O(n)
void symbol_print(const struct symbol_table *st, int symbol_id){
    int index = symbol_id - 1;
    printf("%s", st -> str[index]);
}


#include <stdlib.h>
#include <stdbool.h>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// provided from the notes for your convenience
struct llnode {
    int item;
    struct llnode *next;
};
// 1 -> 2....
// wrapper
struct llist {
    struct llnode *front;
};

struct llist *list_create(void) {
    struct llist *lst = malloc(sizeof(struct llist));
    lst->front = NULL;
    return lst;
}

void add_front(const int i, struct llist *lst) {

    struct llnode *node = malloc(sizeof(struct llnode));
    
    if(lst -> front == NULL){
        lst -> front = node;
    }
    node->item = i;
    node->next = lst->front;
    lst->front = node;
}

int length(const struct llist *lst) {
    int length = 0;
    
    struct llnode *node = lst -> front;
    while (node) {
        ++length;
        node = node->next;
    }
    return length;
}

void list_destroy(struct llist *lst) {
    struct llnode *curnode = lst -> front;
    while (curnode) {
        struct llnode *nextnode = curnode->next;
        free(curnode);
        curnode = nextnode;
    }
    free(lst);
}


// print_list(lst) pretty prints lst
//   using the format: "[first->second->...->last]\n"
//   or "[empty]\n"
// effects: prints out a message
// time : O(n)
void print_list(const struct llist *lst){
    struct llnode *node = lst -> front;
    int len = 0;
    while (node){
        len += 1;
        node = node -> next;
    }

    node = lst -> front;
    if (len == 0){
        printf("[empty]\n");
    } else {
        // todo: try without for loop
        for (int i = 1; i <= len;i++){
            if (i == 1){
                printf("[%d ->", node -> item);
                node = node -> next;
            } else if (i == len){
                printf("%d]", node -> item);
            } else {
                printf("%d ->", node -> item);
                node = node -> next;
            }
        }
    }


}

// array_to_list(a, len) generates a new linked list from array a
//   the first item of the list is a[0]... and the last is a[len-1]
// requires: len > 0
// effects: allocates memory (caller must call list_destroy)
// time: O(n)
struct llist *array_to_llist(const int a[], int len){
    assert(a != NULL && len > 0);
    struct llist * list = list_create();
//    struct llnode *node = malloc(sizeof(struct llnode));
//    list -> front = node;
//    for (int i = 0; i < len; i++){
//        node -> item = a[0];
//        struct llnode *nnode = malloc(sizeof(struct llnode));
//        node -> next =nnode;
//        node = nnode;
//    }
    for (int i = len - 1; i >= 0; i--){
        add_front(a[i],list);
    }
    return list;

}

// list_to_array(lst) generates a new array from lst
//   a[0] is the first item of the list, etc.
//   returns NULL if lst is empty
// effects: allocates memory (caller must free)
// time: O(n)
int *llist_to_array(const struct llist *lst){
    int len = length(lst);
    if (len == 0){
        return NULL;
    }
    int * arr = (int *)malloc(len * sizeof(int));
    struct llnode * node = lst ->front;
    int count = 0;
    while (node != NULL){
        arr[count] = node -> item;
        node = node -> next;
        count++;
    }
    return arr;
}

// map(f, lst) modifies each item of lst to be f(item)
// effects: modifies lst
void map(int (*f)(int), struct llist *lst){
    struct llnode * node = lst ->front;
    int item;
    while (node != NULL){
        item = node -> item;
        node -> item = f(item);
        node = node -> next;
    }
}

// filter(f, lst) removes each item of lst where f(item) is false
// effects: modifies lst
void filter(bool (*f)(int), struct llist *lst){
    struct llnode * first_correct = lst ->front;

    while (first_correct != NULL){
        if (f(first_correct -> item) == true){
            break;
        }
        struct llnode * temp = first_correct -> next;
        free(first_correct);
        first_correct = temp;
    }
    if (first_correct == NULL){
        return;
    }

    struct llnode * node = first_correct -> next;
    while (node != NULL){
        if (f(node -> item) == true){
            first_correct = node;
        } else {
            struct llnode * temp = node -> next;
            free (node);
            node = temp;
            first_correct -> next = node;
            continue;
        }

        node = node -> next;
    }


}



// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
struct llnode {
    int item;
    struct llnode *next;
};

struct sequence{
    struct llnode *front;
    int len;
};
// A module for an int sequence ADT

struct sequence;

// NOTE: All of the following functions REQUIRE:
//       pointers to a sequence (e.g., seq) are valid (not NULL)

// sequence_create() returns a pointer to a new (empty) sequence
// effects: allocates memory (caller must call sequence_destroy)
// time: O(1)
struct sequence *sequence_create(void){
    struct sequence *sq = ((struct sequence *)malloc(sizeof(struct sequence)));
    sq -> front = NULL;
    sq -> len = 0;
    return sq;
}

// sequence_destroy(seq) frees all dynamically allocated memory
// effects: the memory at seq is invalid (freed)
// time:    O(n)
void sequence_destroy(struct sequence *seq){
    assert(seq != NULL);
    struct llnode * node = seq -> front;

    while (node){
        struct llnode * remove = node;
        node = node -> next;
        free(remove);
    }
    free(seq);
}
// NULL -> next =====> exception


// sequence_length(seq) returns the number of items in seq
// time: O(1)
int sequence_length(const struct sequence *seq){
    assert(seq != NULL);
    return seq -> len;
}

// sequence_item_at(seq, pos) returns the item in seq at the given pos
// requires: 0 <= pos < sequence_length(seq)
// time:     O(n)
int sequence_item_at(const struct sequence *seq, int pos){
    assert(seq != NULL);
    int len = sequence_length(seq);
    assert(pos >= 0 && pos < len);

    struct llnode * node = seq -> front;

    int count = 0;
    while (node){
        if (count == pos){
            return node -> item;
        }
        node = node -> next;
        count++;

    }
}

// sequence_insert_at(seq, pos, val) inserts a new item with value val
//   at position pos in seq
//   (changing the position of items at position >= pos)
// requires: and 0 <= pos <= sequence_length(seq)
// effects:  modifies seq
// time:     O(n)
void sequence_insert_at(struct sequence *seq, int pos, int val){
    assert(seq != NULL);
    int len = sequence_length(seq);
    assert(pos >= 0 && pos < len);

    struct llnode * node = seq -> front;
    int count = 0;
    struct llnode *new = (struct llnode *)malloc(sizeof(struct llnode));

    if (pos == 0){
        new -> item = val;
        new -> next = seq -> front;
        seq -> front = new;
        seq -> len += 1;
        return;
    }
    struct llnode * last = node;
    while (node){
        last = node;
        node = node -> next;
        count++;
        if (count == pos){
            new -> item = val;
            new -> next = node;
            last -> next = new;
        }
    }
//    if (pos == len){
//        last -> next = new;
//        new -> item = val;
//        new -> next = NULL;
//    }
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
    int len = sequence_length(seq);
    assert(pos >= 0 && pos < len);

    struct llnode * node = seq -> front;
    int count = 0;
    int ans = 0;

    while (node){
        if (pos == 0){
            struct llnode * next = node -> next;
            ans = node -> item;
            free(node);
            seq -> front = next;
            break;
        }
        struct llnode * last = node;
        node = node -> next;
        count++;
        if (count == pos){
            last -> next = node -> next;
            ans = node -> item;
            free(node);
        }
    }
    seq -> len -= 1;

    return ans;
}

// sequence_print(seq) prints out the items in seq
//   using the format: "[item_0,item_1,...,item_last]\n"
//   or "[empty]\n"
// effects: prints out a message
// time:    O(n)
void sequence_print(const struct sequence *seq){
    assert(seq != NULL);

    int len = sequence_length(seq);
    if (len == 0){
        printf("[empty]\n");
        return;
    }

    struct llnode * node = seq -> front;
    printf("[");
    while(node -> next){
        printf("%d,", node -> item);
        node = node -> next;
    }
    printf("%d]", node -> item);

//    int count = 0;
//    while (node){
//        if (count == 0){
//            count ++;
//            printf("[%d,", node -> item);
//            node = node -> next;
//            continue;
//        }
//        if(count > 0 && count < len){
//            printf("%d,",node ->item);
//            count++;
//            node = node -> next;
//        }
//
//        if (count == len){
//            printf("%d]\n",node -> item);
//            node = node -> next;
//        }
//
//
//    }

}




//char *mirror_mirror(const char *s) {
//    assert(s != NULL);
//    int len = 0;
//    for (int i = 0; s[i]; i++){
//        len++;
//    }
//    //printf("%d", len);
//    char * total = (char *) malloc((2*len+1) * sizeof(char));
//    // malloc returns a "void pointer"
//    // (char *) -> casting
////    for(int i = 0; s[i]; i++){
////        total[i] = s[i];
////    }
////    total[len] = 0;
//    char * reverse = (char *) malloc((len+1) * sizeof(char));
//    for(int i = len - 1;i >= 0; i-- ){
//        reverse[len-i-1] = s[i];
//    }
//    reverse[len] = 0;
//    strcpy(total, s);
//    //printf("%s", reverse);
//    strcat(total, reverse);
//    total[2*len+1] = 0;
//    printf("%s", total);
//    free(reverse);
//    return total;
//}
//
//// new , s
////strcpy(str1, str2);
//int add (int a, int b){
//    int c = a + b;
//    return c;
//}
//
int main() {
//    //const int d = add(1,2);
//    int arr[10] = {0};
//    int result_len = 10;
//    int * result = (int *) malloc(sizeof(int) * result_len);
//    for (int i = 0; i < 10; i++){
//        result [i] = arr[i];
//        printf("%d\n",result [i]);
//        printf("%d\n",arr[i]);
//    }



//    char * a = "sb";
//    int *b =a;
//    printf("%p\n",&a);
//    printf("%p\n",a);
//    printf("%p\n",&b);
//    printf("%p",b);
    //char *s = mirror_mirror("The Mandalorian");
    //char *s = mirror_mirror("The Mandalorian");
    //assert(!strcmp(s, "The MandaloriannairoladnaM ehT"));
    //free(s);
//    char c[20]= {'b','o','b','a','b'};
//    char b[3]={'e','f'};
//    //strcat(c, b);
//    printf("%s",c);
//    int count =0;
//    for (int i = 0;c[i];i++){
//        count += 1;
//    }
//    printf("%d",count);
    return 0;

}
