#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>

// A Pool ADT that provides dynamic, resizable character arrays.

struct pool {
    int len;  // active len
    int maxlen;
    char *addr;
    int * my_heap;

};

// NOTE: All of the following functions REQUIRE:
//       pointers to a pool (e.g., p) are valid (i.e., not NULL)
//       and all sizes (e.g., size) greater than zero

// TIME: n is the number of "active" allocations, which is the number
//       of successful allocs that have not been freed

// SEE ASSIGNMENT TEXT for the behaviour rules of pool_alloc and pool_realloc

// pool_create() creates a new pool of size characters
// effects: allocates memory (caller must call pool_destroy)
// time:    O(1)
struct pool *pool_create(int size){
    assert(size > 0);
    struct pool * new = (struct pool *) malloc(sizeof(struct pool));
    new -> len = 0;
    new -> maxlen = size;
    new -> addr = (char *) malloc (new -> maxlen * sizeof(char));
    int * my_heap = (int *) malloc (new -> maxlen * sizeof(int));
    new -> my_heap = my_heap;
    return new;


}

// pool_destroy(p) destroys the pool p if there are no active allocations
//   returns true if successful or false if there are active allocations
// effects:  the memory at p is invalid (freed) if successful
// time:     O(1)
bool pool_destroy(struct pool *p){
    assert (p != NULL);
    if (p -> len  == 0){
        free(p -> addr);
        free(p -> my_heap);
        free (p);
        return true;
    } else {
        return false;
    }
}

// pool_alloc(p, size) returns a pointer to an uninitialized char array
//   of size from within pool p, or NULL if no block of size is available
// effects: modifies p if successful
// time: O(n)
char *pool_alloc(struct pool *p, int size){
    assert(p != NULL);
    assert(size > 0);
    if (p -> len + size  > p -> maxlen){
        return NULL;
    }
    int count = 0;
    for(int i = 0; i < p -> len;){
        if (p -> my_heap[i] == 0){
            count = 1;
            for(int j = 1; j < size; j++ ){
                if (p -> my_heap [i + j] != 0){
                    break;
                }
                count ++;
            }
        }
        if (count == size){
            p -> my_heap[i] = size;
            for (int k = 1; k < size; k++){
                p ->my_heap [i + k] = -1;
                p -> len ++;
                return p -> addr + i;
            }

        }
        i = i + count;
        count = 1;
    }
    return NULL;



}

//3-1-1003-1-1
//111111111
//00000000000000
// pool_free(p, addr) makes the active allocation at addr available in the pool.
//   returns true if successful (addr corresponds to an active allocation
//   from a previous call to pool_alloc or pool_realloc) or false otherwise
// effects: modifies p if successful
// time: O(n)
bool pool_free(struct pool *p, char *addr){
    assert(p != NULL);
    assert(addr != NULL);
    int pos = addr - p -> addr;
    if (p -> my_heap[pos] <= 0){
        return false;
    } else {
        int size = p -> my_heap [pos];
        for (int i = 0; i < size; i++){
            p -> my_heap [pos + i] = 0;
            p -> len -= 1;
        }
    }


}

// pool_realloc(p, addr, size) changes the size of the active allocation at
//   addr and returns the new address for the allocation.
//   returns NULL if addr does not correspond to an active allocation
//   or the pool can not be resized (in which case the original allocation
//   does not change)
// effects: modifies p if successful
// time:    O(n) + O(k) where k is min(size, m) and
//          m is the size of the original allocation
char *pool_realloc(struct pool *p, char *addr, int size){
    assert(p != NULL);
    assert(addr != NULL);
    assert(size > 0);

    int pos = addr - p -> addr;
    int ori_len = p -> my_heap [pos];
    int more_len = size - ori_len;
    if (p -> my_heap[pos] == -1 || p -> my_heap[pos] == 0){
        return NULL;
    }
    if (more_len <= 0){
        p -> my_heap[pos] = size;
        for (int i = 1; i < ori_len; i++){
            if(i < size){
                p -> my_heap[pos + i] = -1;
            } else {
                p -> my_heap[pos + i] = 0;
            }
        }
        return p -> addr + pos;
    }
    int count = 0;
    if (more_len > 0){
        for (int i = 0; i < more_len; i++){
            if (p -> my_heap[pos + ori_len + i] != 0){
                pool_free(p, addr);
                break;
            }
            p -> my_heap[pos + ori_len + i] = -1;
            p -> len+=1;
            p -> my_heap[pos] ++;
            count++;
            if (count == more_len){
                return p -> addr + pos;
            }
        }
        char * ans = pool_alloc(p,size);
        if(ans){
            return ans;
        } else {
            p -> my_heap[pos] = ori_len;
            for(int i = 1; i < ori_len; i++){
                p -> my_heap[pos + i] = -1;
                return p -> addr + pos;
            }
        }


    }



}

// pool_print_active(p) prints out a description of the active allocations
//   in pool p using the following format:
//   "active: index1 [size1], index2 [size2], ..., indexN [sizeN]\n" or
//   "active: none\n" if there are no active allocations
//   where the index of an allocation is relative to the start of the pool
// effects: displays a message
// time: O(n)
void pool_print_active(const struct pool *p){
    assert(p != NULL);
    if (p -> len == 0){
        printf ("active: none\n");
    }
    int found = 0;
    for (int i = 0; i < p -> maxlen; i++){
        if (p -> my_heap[i] != 0 && p -> my_heap[i] != -1 && found == 0){
            printf("active: %d [%d]",i, p -> my_heap[i]);
            found = 1;
        }
        if (p -> my_heap[i] != 0 && p -> my_heap[i] != -1 && found != 0){
            printf(", %d [%d]",i, p -> my_heap[i]);
        }
    }
    printf("\n");
}

// pool_print_available(p) prints out a description of the available
//   contiguous blocks of memory still available in pool p:
//   "available: index1 [size1], index2 [size2], ..., indexM [sizeM]\n" or
//   "available: none\n" if all of the pool has been allocated
// NOTE: It is impossible for two blocks of available memory to be adjacent.
//       If two blocks are adjacent, they should be merged to be a single,
//       larger block. In other words: index_K+1 > index_K + size_K
// effects: displays a message
// time:    O(n)
void pool_print_available(const struct pool *p){
    assert(p != NULL);
    if (p -> len == p -> maxlen){
        printf ("active: none\n");
    }
    int found = 0;
    int count = 1;
    for(int i = 0; i < p -> maxlen;){
        if (p -> my_heap[i] == 0 && found == 0) {
            found = 1;
            for (int j = 1; j + i < p->maxlen; j++) {
                if (p->my_heap[i + j] == 0) {
                    count++;
                } else {
                    printf("available: %d [%d]", i, count);
                    count = 1;
                    i = i + j;
                    break;
                }
            }
            continue;
        }
        if (p -> my_heap[i] == 0){
            for (int j= 1; j + i <p -> maxlen; j++){
                if (p -> my_heap[i + j] == 0){
                    count ++;
                } else{
                    printf(", %d [%d]", i, count);
                    count = 1;
                    i = i + j;
                    break;
                }
            }
        }
    }
    if (p -> my_heap[p -> maxlen - 1] == 0){
        printf(", %d [%d]", p -> maxlen - count, count);
    }
    printf("\n");
}

// pool_print_active(p) prints out a description of the active a






// This is a Dictionary ADT that can store *ANY* kind of data
// with both keys and values as void pointers (void *)

// It also allows you to select the k-th key (via dict_select)
// and find the number of keys in O(1) (via dict_size)

// The running times given as O(h) correspond to the height of the
// underlying BST, which is hidden from the client.
// In the worst case, O(h) is O(n) and in the best case is O(logn)
// typedef: Dictionary ==> (struct dictionary *)
typedef struct dictionary *Dictionary;

// function typedefs:

// DictKeyCompare(key_a, key_b) uses the same convention as strcmp
//   to compare two keys
typedef int (*DictKeyCompare) (void *key_a, void *key_b);

// FreeFunction(obj) frees all memory associated with obj
typedef void (*FreeFunction) (void *obj);

// PrintKeyVal(key, val) prints out the key and value for dict_print
typedef void (*PrintKeyVal) (void *key, void *val);


struct bstnode {
    void *item;                // key
    void *value;               // additional value (augmentation)
    struct bstnode *left;
    struct bstnode *right;
    int size;                  // *** new augmentation (see notes)
};

struct dictionary {
    struct bstnode *root;
    // function pointers
    DictKeyCompare key_compare;
    FreeFunction free_key;
    FreeFunction free_val;
    PrintKeyVal print_keyval;
};





// dict_create(cmp_function, free_key_function, free_val_function,
//             print_function) creates a new dictionary
//   (see above function typedefs for parameter descriptions)
// effects: allocates memory (client must call dict_destroy)
Dictionary dict_create(DictKeyCompare cmp_function,
                       FreeFunction free_key_function,
                       FreeFunction free_val_function,
                       PrintKeyVal print_function){
    Dictionary dic = (Dictionary) malloc(sizeof(struct dictionary));
    dic -> key_compare = cmp_function;
    dic -> free_key = free_key_function;
    dic -> free_val = free_val_function;
    dic -> print_keyval = print_function;
    dic -> root = NULL;
    return dic;
}

// dict_insert(key, val, d) inserts key/val pair into d
//   if key already exists then it frees both the old key and old value
// effects: modifies d, may free old key/value
// time:    O(h)
void search (void *key, void *val, struct bstnode * node, Dictionary d){
    if(d ->key_compare(key, node -> item) == 0){
        d -> free_key (node -> item);
        d -> free_key (node -> value);
        node -> item = key;
        node -> value = val;
        return;
    }
    if(d ->key_compare(key, node -> item) == -1){
        if (node -> left == NULL){
            struct bstnode *new = (struct bstnode *)malloc(sizeof(struct bstnode));
            new -> value = val;
            new -> item = key;
            new -> right = NULL;
            new -> left = NULL;
            new -> size = 1;
            node -> left = new;
            return;
        }
        search(key, val, node -> left, d);
        node -> size = node -> left -> size + node -> left -> size + 1;
    } else {
        if(node -> right == NULL){
            struct bstnode *new = (struct bstnode *)malloc(sizeof(struct bstnode));
            new -> value = val;
            new -> item = key;
            new -> right = NULL;
            new -> left = NULL;
            new -> size = 1;
            node -> right = new;
            return;

        }
        search(key, val, node -> right, d);
        node -> size = node -> left -> size + node -> left -> size + 1;
    }


}

//       5
//        6
void dict_insert(void *key, void *val, Dictionary d){
    struct bstnode *node = d -> root;
    search(key, val, node, d);


}

// dict_lookup(key, d) finds the value corresponding to the key in d
//   or returns NULL if key does not exist
// time:    O(h)

void *look (void *key, struct bstnode* node, Dictionary d){
    if(d ->key_compare(key, node -> item) == 0){
        return node -> value;
    }
    if(d ->key_compare(key, node -> item) == -1){
        if (node -> left == NULL){
            return NULL;
        }
        return look(key, node -> left, d);
    } else {
        if(node -> right == NULL){
            return NULL;
        }
        return look(key, node -> right, d);
    }


}
void *dict_lookup(void *key, Dictionary d){
    struct bstnode *node = d -> root;
    look(key, node, d);
}

// dict_remove(key, d) removes (and frees) the key and value in d
// notes:   does nothing if key does not exist in d
// effects: modifies d, frees key/value
// time:    O(h)

//struct bstnode {
//    void *item;                // key
//    void *value;               // additional value (augmentation)
//    struct bstnode *left;
//    struct bstnode *right;
//    int size;                  // *** new augmentation (see notes)
//};
//
//struct dictionary {
//    struct bstnode *root;
//    // function pointers
//    DictKeyCompare key_compare;
//    FreeFunction free_key;
//    FreeFunction free_val;
//    PrintKeyVal print_keyval;
//};
struct bstnode *node_remove(void* key, struct bstnode *node){
    if(node == NULL){
        return NULL;
    }
    if(key < node -> item){
        node -> left = node_remove(key, node -> left);
    } else if (key > node -> item){
        node -> right = node_remove(key, node -> right);
    } else{
        if(node -> left == NULL){
            struct bstnode * new = node -> right;
            free(node);
            return new;
        } else if (node -> right == NULL){
            struct bstnode * new = node -> left;
            free(node);
            return new;
        } else {
            struct bstnode * next = node -> right;
            struct bstnode * parent_of_next = NULL;
            while(next -> left){
                parent_of_next = next;
                next = next -> left;
            }
            node -> item = next -> item;
            node -> value = next -> value;
            if(parent_of_next){
                parent_of_next -> left = next -> right;
            } else {
                node -> right = next -> right;
            }
            free(next);
        }
        return node;

    }

}
void dict_remove(void *key, Dictionary d){
    struct bstnode *node_moved = node_remove(key, d -> root);
}

const int PREORDER = -1;
const int INORDER = 0;
const int POSTORDER = 1;

// dict_print(order, d) prints the dictionary in the given order
// notes:    reveals the underlying BST structure
//           prints nothing if d is empty
// requires: order is one of (PREORDER, INORDER, POSTORDER)
// effects:  displays output
// time:     O(n)
void preorder_print(struct bstnode * node, Dictionary d){

    d -> print_keyval(node -> item, node -> value);

    if (node -> left ){
        preorder_print(node->left, d);
    }

    if(node->right) {
        preorder_print(node->right, d);
    }

}
void in_print(struct bstnode * node, Dictionary d){

    if (node -> left ){
        in_print(node->left, d);
    }

    d -> print_keyval(node -> item, node -> value);


    if(node->right) {
        in_print(node->right, d);
    }

}
void post_print(struct bstnode * node, Dictionary d){

    if (node -> left ){
        post_print(node->left, d);
    }

    if(node->right) {
        post_print(node->right, d);
    }

    d -> print_keyval(node -> item, node -> value);




}
void dict_print(int order, Dictionary d){
    struct bstnode * node = d -> root;
    if(order == PREORDER){
        preorder_print(node, d);
    }
    if(order == INORDER){
        in_print(node, d);
    }
    if(order == POSTORDER){
        post_print(node, d);
    }
}

// dict_select(k, d) finds the k-th key in d
// requires: 0 <= k < dict_size(d)
// time:     O(h)
//0 1 2 3 4 5 6 7 8 9
void *choose(int k, struct bstnode * node){
    if (node -> left -> size + 1 == k + 1){
        return node -> value;
    }
    if (node -> left -> size + 1 < k + 1){
        return choose(k - node -> left -> size - 1, node -> right) ;
    }
    if (node -> left -> size + 1 > k + 1){
        return choose(k, node -> left) ;
    }

}
void *dict_select(int k, Dictionary d){
    struct bstnode * node = d -> root;
    void * val = choose(k, node);
    return val;
}

// dict_size(d) returns the number of keys in d
// time: O(1)
int dict_size(Dictionary d){
    if (d -> root == NULL){
        return 0;
    }
    return d -> root -> size;
}

// dict_destroy(d) frees all memory for d
// effects: d is no longer valid, all keys and values are freed
// time:    O(n)

//struct bstnode {
//    void *item;                // key
//    void *value;               // additional value (augmentation)
//    struct bstnode *left;
//    struct bstnode *right;
//    int size;                  // *** new augmentation (see notes)
//};
//
//struct dictionary {
//    struct bstnode *root;
//    // function pointers
//    DictKeyCompare key_compare;
//    FreeFunction free_key;
//    FreeFunction free_val;
//    PrintKeyVal print_keyval;
//};
void destory(struct bstnode * node, Dictionary d){
    if (node) {
        destory(node -> left, d);
        destory(node -> right, d);

        d -> free_key(node -> item);
        d -> free_val(node -> value);
        free(node);
    }
}
void dict_destroy(Dictionary d){
    struct bstnode * node = d -> root;
    destory(node,d);
    free(d);
}

// IMPORTANT! You cannot modify these structures or constants:


#include <stdbool.h>

// SEASHELL_READONLY

// A Module for a minheap data structure

struct minheap {
    int len;
    int maxlen;
    int *data;
};


// minheap_create() creates a new empty minheap
// effects: allocates memory (client must call minheap_destroy)
struct minheap *minheap_create(void){
    struct minheap * heap = (struct minheap *) malloc(sizeof (struct minheap));
    heap -> len = 0;
    heap -> maxlen = 1;
    heap -> data = NULL;
}

// minheap_is_empty(h) determines if heap h is empty
// time: O(1)
bool minheap_is_empty(const struct minheap *h){
    if (h -> len == 0){
        return true;
    }
    return false;
}

// minheap_insert(i, h) adds i to heap h
// effects: h is modified
// time:    O(logn), n is the size of the heap
void swap (int *arr, int new, int root){
    int temp = 0;
    temp = arr[new];
    arr[new] = arr[root];
    arr[root] = temp;
}
int get_parent(int index){
    return (index - 1) / 2;
}
int get_left (int index){
    return 2 * index + 1;
}
int get_right (int index){
    return 2 * index + 2;
}
void minheap_insert(int i, struct minheap *h){
    int maxlen;
    if (h -> len == h -> maxlen){
        maxlen = h -> maxlen * 2 + 1;
        h -> data = realloc(h -> data, maxlen);
        h -> maxlen = maxlen;
    }
    h -> data[h -> len] = i;
    int index = h -> len;
    while (index >= 0){
        int parent_index = get_parent(index);
        if (h -> data[index] < h -> data[parent_index]){
            swap(h -> data, index, parent_index);
            index = parent_index;
        } else {
            break;
        }


    }
    h -> len += 1;
}

// minheap_top(h) returns the top of the heap
// requires: h is not empty
// time:     O(1)
int minheap_top(const struct minheap *h){
    assert (h != NULL);
    if (h -> len == 0){
        return INT_MAX;
    }
    return h -> data[0];
}


// minheap_remove(h) removes and returns the top of the heap
// requires: h is not empty
// effects:  h is modified
// time:     O(logn), n is the size of the heap




void swap_o(int *arr, int out_of_space, int child) {  // out_of_space is the index
    int temp = arr[out_of_space];
    arr[out_of_space] = arr[child];
    arr[child] = temp;
}



int minheap_remove(struct minheap *h) {
    assert(h != NULL);
    int out_of_space = h->data[h->len - 1];
    // there! out_of_space is the value itself!!
    h->data[0] = out_of_space;
    h->len -= 1;

    int index = 0;
    while (index < h->len) {
        int left = get_left(index);
        int right = get_right(index);
        if (h->data[index] > h->data[left] || h->data[index] > h->data[right]) {
            if (h->data[left] <= h->data[right]) { // left is smaller
                swap_o(h->data, index, left);
                index = left;
            } else if (h->data[left] > h->data[right]) { // right
                swap_o(h->data, index, right);
                index = right;
            }
        } else break;
    }
    return h->data[h->len + 1];
}

// minheap_destroy(h) frees all memory for h
// effects: h is no longer valid
// time:    O(1)
//struct minheap {
//    int len;
//    int maxlen;
//    int *data;
//};
void minheap_destroy(struct minheap *h){
    free(h -> data);
    free(h);
}


// heapsort(a, len) sorts a in ascending order
// requires: a is a valid array, len > 0
// effects:  modifies a
// time:     O(nlogn)
void heapsort(int a[], int len){
    assert(a != NULL);
    assert(len > 0);
    struct minheap* res = (struct minheap*)malloc(sizeof(struct minheap));
    res -> len = len;
    res -> maxlen = len;
    res -> data = (int*)malloc(len * sizeof(int));;
    for (int i = 0; i < res -> len; i++){
        minheap_insert(a[i], res);
    }
    int ans = 0;
    for (int i = 0; i < res -> len; i++){
        ans = minheap_remove(res);
        a[i] = ans;
    }
    minheap_destroy(res);

}

int main() {
    printf("Hello, World!\n");
    return 0;
}
