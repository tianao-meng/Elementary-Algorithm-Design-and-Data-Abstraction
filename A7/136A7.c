#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

// mirror_mirror(s) returns a *new* string that contains
//   contents of s, followed by the contents of s reversed
// requires: s is not NULL
// effects:  allocates memory (caller must free)
// time:     O(n)
char *mirror_mirror(const char *s) {
    assert(s != NULL);
    int len = 0;
    for (int i = 0; s[i]; i++){
        len++;
    }
    //printf("%d", len);
    char * total = (char *) malloc((2*len+1) * sizeof(char));
    // malloc returns a "void pointer"
    // (char *) -> casting
    for(int i = 0; s[i]; i++){
        total[i] = s[i];
    }
    char * reverse = (char *) malloc((len+1) * sizeof(char));
    for(int i = len - 1;i >= 0; i-- ){
        reverse[len-i-1] = s[i];
    }
    //reverse[len] = 0;
    //printf("%s", reverse);
    strcat(total, reverse);
    total[2*len+1] = 0;
    printf("%s", total);
    free(reverse);
    return total;
}

// new , s
//strcpy(str1, str2);


// a USER ADT that simply stores a username and password

struct user {
    char * username;
    char * password;
};

// is_valid_username(username) determines if username only contains
//   lower case letters and has a length of at least 3
// time: O(n)
bool is_valid_username(const char *username){
    // assert(username != NULL);
    int len = 0;
    for ( int i = 0; username[i]; i++){
        len ++;
    }
    if (len < 3){
        return false;
    }
    int count = 0;
    for (int i = 0; i < len && username[i] >= 'a') && (username[i] <= 'z' ; i++){
        count += 1;
    }
    if (count = len){
        return false;
    }
    return true;
}

// is_valid_password(password) determines if password contains only printable
//   ascii characters with no whitespace and has a length of at least 6
// time: O(n)
bool is_valid_password(const char *password){
    int len = 0;
    for ( int i = 0; password[i]; i++){
        len ++;
    }
    if (len < 6){
        return false;
    }
    for (int i = 0; i < len; i++){
        if ((password[i] <= ' ') || (password[i] > '~')){
            return false;
        }
    }
    return true;
}

// user_create(username, password) creates a new user with the given
//   username and password. If username/password are invalid, returns NULL
// note:    makes an internal "copy" of username and password
// effects: may allocate memory (client must call user_destroy if non-NULL)
// time:    O(n + m), where n,m are the length of username,password
struct user *user_create(const char *username, const char *password){
    struct user * client = (struct user *) malloc(sizeof(struct user));
    if(!is_valid_username(username) || !(is_valid_password(password))){
        return NULL;
    }
    client -> password = password;
    client -> username = username;
    return client;
}

// get_username(user) returns the username from u
// requires: u is a valid user created by user_create;
const char *get_username(const struct user *u){
    assert(u != NULL);
    return u -> username;
}

// is_correct_password(u, password) determines if the password for u
//   is identical
// requires: u is a valid user created by user_create;
// time:     O(n)
bool is_correct_password(const struct user *u, const char *password) {
    assert(u != NULL);
    return(strcmp(u->password, password) == 0);
}
// user_destroy(u) destroys u and frees all memory for u
// requires: u is a valid user created by user_create;
// effects:  frees memory for u
void user_destroy(struct user *u){
    assert(u != NULL);
    free(u);
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    /* create temp arrays */
    int L[n1], R[n2];
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

struct set{
    int * arr;
    int maxlen;
    int len;
};

// NOTE: All of the following functions REQUIRE:
//       pointers to a set (e.g., s) are valid (not NULL)

// set_create() returns a new empty set
// effects: allocates memory (caller must call set_destroy)
// time: O(1)
struct set *set_create(void){
    struct set * client = (struct set *) malloc(sizeof(struct set));
    client -> maxlen = 128;
    client -> len = 0;
    client -> arr = (int *) malloc(sizeof(int) * client -> maxlen);
    return client;
}

// set_destroy(s) frees all dynamically allocated memory
// effects: the memory at s is invalid (freed)
// time: O(1)
void set_destroy(struct set *s){
    assert(s != NULL);
    free(s -> arr);
    free(s);
}

// memory leak

// set_size(s) returns the number of elements in s
// time: O(1)
int set_size(const struct set *s){
    assert(s != NULL);
    return s -> len;
}

// set_member(s, i) determines if i is in set s
// time: O(logn)
bool set_member(const struct set *s, int i){
    assert(s != NULL);

    int start = 0;
    int end = set_size(s) - 1;
    while(start >= end) {
        int mid = (start + end) /2 ;
        if (i < s -> arr [mid]) {
            end = mid - 1;
        } else if (i > s -> arr [mid]) {
            start = mid + 1;
        } else {
            return true;
        }
    }
    return false;
}

// set_add(s, i) adds i to the set s, if it does not already contain i
// effects: s may be modified
// time: O(n) where n is set_size(s)

void set_add(struct set *s, int i){
    assert(s != NULL);

    if (set_member(s, i)){
        return;
    } else {
        int temp = 0;
        int position = -1;
        
        if (s -> len >= s -> maxlen) {
            s -> maxlen = s -> maxlen * 2;
            s ->arr= realloc(s -> arr, sizeof(int)* s->maxlen);
        }

        for (int j = 0; j < s -> len; j++){
            if (s -> arr[j] > i){
                temp = s -> arr[j + 1];
                s -> arr[j] = i;
                position = j;
                break;
            }
        }
        for (int j = position + 1; j < s -> len; j++ ){
            s -> arr[j] = temp;
            if(j == s -> len - 1){
                break;
            }
            temp = s -> arr[j + 1];
        }
    }
    s -> len += 1;
}


// set_remove(s, i) removes i from s. If i is not in s, s isn't changed
// effects: s may be modified
// time: O(n) where n is set_size(s)
void set_remove(struct set *s, int i){
    assert(s != NULL);
    if (!set_member(s, i)){
        return;
    } else {
        int len = set_size(s);
        for (int k = 0; k < len; k++){
            if (s -> arr[k] == i){
                int first = k;
                for (int j = first; j < len; j++){
                    s -> arr[j] = s -> arr[j+1];
                }
                s ->len = len - 1;
                break;
            }
        }

    }

}

// set_union(s1, s2) returns a new set that is the union of s1 and s2
// effects: allocates memory for the new set (caller must call set_destroy)
// time: O(n) where n is set_size(s1) + set_size(s2)

struct set *set_union(const struct set *s1, const struct set *s2){
    assert(s1 != NULL);
    assert(s2 != NULL);
    int maxlen = s1 -> maxlen + s2 -> maxlen;
    struct set * s = (struct set *) malloc(sizeof(struct set));
    s -> maxlen =maxlen;
    s -> arr = (int *) malloc(sizeof(int) * s -> maxlen);
    int len_s1 = set_size(s1);
    int len_s2 = set_size(s2);
    for (int i = 0; i < len_s1; i++){
        s -> arr [i] = s1 -> arr[i];
    }
    int count = 0;
    for (int i = 0; i < len_s2; i++){
        set_add( s,s2 -> arr[i]);
        count += 1;
    }
    s -> maxlen = maxlen;
    s -> len = len_s1 + count;
    return s;

}

// set_intersect(s1, s2) returns a new set that is the intersection of s1 and s2
// effects: allocates memory for the new set (caller must call set_destroy)
// time: O(n) where n is set_size(s1) + set_size(s2)
struct set *set_intersect(const struct set *s1, const struct set *s2){
    assert(s1 != NULL);
    assert(s2 != NULL);
    int len1 = s1 -> len;
    int len2 = s2 -> len;
    int maxlen = -1;
    if (len1 < len2){
        maxlen = len1;
    } else {
        maxlen = len2;
    }
    struct set * s =(struct set *) malloc(sizeof(struct set));
    s -> maxlen = maxlen;
    s -> arr = (int *) malloc(sizeof(int) * s -> maxlen);
    int idx1 = 0;
    int idx2 = 0;
    // i is the index of intersect set
    int len = 0;
    for (int i = 0;i < s -> maxlen; ) {
        if ((idx1 == len1) || (idx2 == len2)){
            break;
        }
        if (s1->arr[idx1] < s2 -> arr[idx2]) {
            idx1++;
        } else if ( s1->arr[idx1] > s2 -> arr[idx2]){
            idx2++;
        } else {
            s -> arr[i] = s1 -> arr[idx1];
            i++;
            idx1++;
            idx2++;
            len++;
        }
    }
    s -> len = len;
    return s;
}
// array_to_set(a, len) returns a new set that is all the unique elements of a
// requires: len > 0
// effects: allocates memory for the new set (caller must call set_destroy)
// time: O(nlogn)
struct set *array_to_set(const int a[], int len){
    assert(len > 0);
    struct set * new = (struct set *) malloc(sizeof(struct set));

    new -> maxlen = 2 * len;

    int new_a[len];
    int * result = (int *) malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++ ){
        new_a[i] = a[i];
    }

    Merge_sort(new_a);

    int result_len = 0;
    int res_idx = 0;
    new -> arr = result;
    for(int i = 0; i < len; i++){

//        result[i] = new_a[i];
//        result_len++;
        if (!set_member(new,new_a[i])){
            result[res_idx] = new_a[i];
            res_idx++;
            result_len++;
        }
    }
    new -> arr = result;
    new -> len = result_len;
}
// set_to_array(s) returns a new array that is the elements of s
// in ascending order, or NULL if s is empty
// effects: may allocate memory for a new array (caller must call free)
// time: O(n)
int *set_to_array(const struct set *s){
    assert(s != NULL);
    int result_len = s -> len;
    int * result = (int *) malloc(sizeof(int) * result_len);
    for (int i = 0; i < s -> len; i++){
        result[i] = s -> arr[i];
    }
    if (result_len == 0){
        result = NULL;
    }
    Merge_sort(result);
    return result;

}

// set_print(s) prints the ele// set_print(s) prints the elements of set s to the screen in ascending order.
//   using the format: "[element_smallest,element_next,...,element_largest]\n"
//   or "[empty]\n"
// effects: prints out a message
// time: O(n)
void set_print(const struct set *s){
    assert(s != NULL);
    for (int i = 0; i < s -> len; i++){
        if (i == 0){
            printf("[%d,", s -> arr[i]);
        } else if (i == s -> len - 1){
            printf("%d]", s -> arr[i]);
        } else {
            printf("%d,", s -> arr[i]);
        }
    }
}

// phonetic[0] = stop
char * a[2] = {
    [0] = "a",
    [1] = "b"
}
const char *phonetic[127] = {
        ['\0'] = "Stop",
        ['1'] = "One",
        ['2'] = "Two",
        ['3'] = "Three",
        ['4'] = "Four",
        ['5'] = "Five",
        ['6'] = "Six",
        ['7'] = "Seven",
        ['8'] = "Eight",
        ['9'] = "Niner",
        ['0'] = "Zero",
        ['.'] = "Point",
        ['A'] = "Alpha",
        ['B'] = "Bravo",
        ['C'] = "Charlie",
        ['D'] = "Delta",
        ['E'] = "Echo",
        ['F'] = "Foxtrot",
        ['G'] = "Golf",
        ['H'] = "Hotel",
        ['I'] = "India",
        ['J'] = "Juliet",
        ['K'] = "Kilo",
        ['L'] = "Lima",
        ['M'] = "Mike",
        ['N'] = "November",
        ['O'] = "Oscar",
        ['P'] = "Papa",
        ['Q'] = "Quebec",
        ['R'] = "Romeo",
        ['S'] = "Sierra",
        ['T'] = "Tango",
        ['U'] = "Uniform",
        ['V'] = "Victor",
        ['W'] = "Whiskey",
        ['X'] = "X-ray",
        ['Y'] = "Yankee",
        ['Z'] = "Zulu",
        ['a'] = "Alpha",
        ['b'] = "Bravo",
        ['c'] = "Charlie",
        ['d'] = "Delta",
        ['e'] = "Echo",
        ['f'] = "Foxtrot",
        ['g'] = "Golf",
        ['h'] = "Hotel",
        ['i'] = "India",
        ['j'] = "Juliet",
        ['k'] = "Kilo",
        ['l'] = "Lima",
        ['m'] = "Mike",
        ['n'] = "November",
        ['o'] = "Oscar",
        ['p'] = "Papa",
        ['q'] = "Quebec",
        ['r'] = "Romeo",
        ['s'] = "Sierra",
        ['t'] = "Tango",
        ['u'] = "Uniform",
        ['v'] = "Victor",
        ['w'] = "Whiskey",
        ['x'] = "X-ray",
        ['y'] = "Yankee",
        ['z'] = "Zulu"
};
// speak_io(s) displays the string s using
//   the phonetic alphabet (as described in the assignment)
// requires: alphabet[0] is not NULL
// effects:  displays a message
// time:     O(???)
void speak_io(const char *s, const char *alphabet[]){
    assert(alphabet [0] != NULL);
    for (int i = 0; s[i]; i++){
        if (s[i] == 0){
             printf("%s\n",alphabet[num]);
        }
        int num = s[i];
        printf("%s ",alphabet[num]);
    }
}

"abc"
a=apple;
b=bob;
c=candy;
// speak_str(s) returns a new string that contains
//   s using the phonetic alphabet
// requires: alphabet[0] is not NULL
// effects:  allocates memory (client must free)
// time:     O(???)
char *speak_str(const char *s, const char *alphabet[]) {
    assert(alphabet[0] != NULL);
    int len_s = 0;
    for (int i = 0; s[i]; i++) {
        len_s++;
    }
    int st_len = 0;
    for (int i = 0; s[i]; i++) {
        int num = s[i];
        const char *res = alphabet[num];
        for (int j = 0; res[j]; j++) {
            st_len++;
        }
    }
    int total_len = st_len;
    char *ans = (char *) malloc(total_len * (sizeof(char)));
    int ans_idx = 0;
    for (int i = 0; s[i]; i++) {
        int num = s[i];
        const char *res = alphabet[num];
        for (int j = 0; res[j]; j++) {
            ans[ans_idx] = res[j];
            ans_idx++;
        }
    }
    return ans;
}

int main() {
    char *s = mirror_mirror("The Mandalorian");
    //char *s = mirror_mirror("The Mandalorian");
    //assert(!strcmp(s, "The MandaloriannairoladnaM ehT"));
    free(s);
    return 0;
}
