#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
struct point {
    int x;
    int y;
};

struct rectangle {
    struct point top_left;
    struct point bottom_right;
};
bool point_equal(struct point a, struct point b) {
    return(a.x == b.x && a.y == b.y);
}

bool valid_rectangle(struct rectangle r) {
    int top_left_x = r.top_left.x;
    int top_left_y = r.top_left.y;
    int bottom_right_x = r.bottom_right.x;
    int bottom_right_y=r.bottom_right.y;
    return ((top_left_x < bottom_right_x) && (top_left_y > bottom_right_y));
}

bool rectangle_equal(struct rectangle a, struct rectangle b) {
    int a_top_left_x = a.top_left.x;
    int a_top_left_y = a.top_left.y;
    int a_bottom_right_x = a.bottom_right.x;
    int a_bottom_right_y = a.bottom_right.y;
    int b_top_left_x = b.top_left.x;
    int b_top_left_y = b.top_left.y;
    int b_bottom_right_x = b.bottom_right.x;
    int b_bottom_right_y = b.bottom_right.y;
    return ((a_top_left_x == b_top_left_x) && (a_top_left_y == b_top_left_y) &&
            (a_bottom_right_x == b_bottom_right_x) && (a_bottom_right_y == b_bottom_right_y));

}

int rectangle_area(struct rectangle r) {
    int top_left_x = r.top_left.x;
    int top_left_y = r.top_left.y;
    int bottom_right_x = r.bottom_right.x;
    int bottom_right_y=r.bottom_right.y;
    return((bottom_right_x - top_left_x) * (top_left_y - bottom_right_y)) ;
}

bool rectangle_inside(struct rectangle r, struct point p) {
    int top_left_x = r.top_left.x;
    int top_left_y = r.top_left.y;
    int bottom_right_x = r.bottom_right.x;
    int bottom_right_y=r.bottom_right.y;
    return ((top_left_x  <= p.x) && (p.x <= bottom_right_x) && (bottom_right_y <= p.y) && (p.y <= top_left_y));
}

struct rectangle rectangle_rotate(struct rectangle r) {
    int top_left_x = r.top_left.x;
    int top_left_y = r.top_left.y;
    int bottom_right_x = r.bottom_right.x;
    int bottom_right_y = r.bottom_right.y;
    int top_left_x_new = top_left_y;
    int top_left_y_new = - top_left_x;
    int bottom_right_x_new = bottom_right_y;
    int bottom_right_y_new = - bottom_right_x;
    const struct point top_left_new = {top_left_x_new , top_left_y_new};
    const struct point bottom_right_new = {bottom_right_x_new , bottom_right_y_new};
    const struct rectangle rectangle_new = {top_left_new , bottom_right_new};
    return rectangle_new;
}

// requires: 0 <= whole
//           0 <= num < denom
//           2 <= denom
struct imperial {
    int whole;
    int num;
    int denom;
};

bool imperial_valid(struct imperial imp) {
    return ((imp.whole >= 0) && (0 <= imp.num) && (imp.num < imp.denom) && (2 <= imp.denom));
}

//int x = 0;
//if ((0 < x) < 1) {
//    print;
//}
int gcd(int a, int b){
    while (a != b) {
        if (a > b){
            a = a - b;
        } else {
            b = b - a;
        }
    }
    return a;
}


int imperial_cmp(struct imperial a, struct imperial b) {
    assert(imperial_valid(a) == true && imperial_valid(b) == true);
    if (a.whole > b.whole){
        return 1;
    } else if (a.whole < b.whole){
        return -1;
    } else {
        int lcm = abs(a.denom * b.denom) / gcd(a.denom , b.denom);
        int x = lcm / a.denom;
        int y = lcm / b.denom;
        if ((x * a.num ) > (y * b.num)){
            return 1;
        } else if ((x * a.num ) < (y * b.num)){
            return -1;
        } else {
            return 0;
        }
    }
}

struct imperial imperial_mult(struct imperial imp, int k) {
    assert(imperial_valid(imp) == true);
    int num = imp.whole * imp.denom + imp.num;
    int num_new = num * k;
    int whole_new = num_new / imp.denom;
    int nom_num = num % imp.denom;
    const struct imperial imperial_new = {whole_new , nom_num , imp.denom};
    return imperial_new;
}

struct imperial imperial_add(struct imperial a, struct imperial b) {
    assert(imperial_valid(a) == true && imperial_valid(b) == true);
    int lcm = abs(a.denom * b.denom) / gcd(a.denom , b.denom);
    int x = lcm / a.denom;
    int y = lcm / b.denom;
    int a_num = x * a.num;
    int b_num = y * b.num;
    int new_num = (a_num + b_num) % lcm;
    int new_whole = (a.whole + b.whole) + (a.num + b.num) / lcm;
    const struct imperial add = {new_whole , new_num , lcm};
    return add;
}



struct imperial imperial_sub(struct imperial a, struct imperial b) {
    assert (imperial_cmp(a, b) == -1);
    assert(imperial_valid(a) == true && imperial_valid(b) == true);
    int lcm = abs(a.denom * b.denom) / gcd(a.denom, b.denom);
    int x = lcm / a.denom;
    int y = lcm / b.denom;
    int a_num = x * a.num;
    int b_num = y * b.num;
    int total_sub = abs(a_num - b_num);
    int new_num = total_sub % lcm;
    int new_whole = 0;
    if ((a_num - b_num) < 0) {
        new_whole = (a.whole - b.whole) - total_sub / lcm;
    } else {
        new_whole = (a.whole - b.whole) - (a.num - b.num) / lcm;
    }
    const struct imperial subtract = {new_whole, new_num, lcm};

    return subtract;
}

const int IS_EMPTY = 1;
const int PUSH = 2;
const int POP = 3;
const int TOP = 4;
const int QUIT = 5;
void fatal_error() {
    printf("FATAL ERROR\n");
    exit(0);
}
void stack_io(int value){

    while(1){
        int cmd = read_symbol(); 
        switch (cmd) {
            case IS_EMPTY:
                if (value == READ_INT_FAIL){
                    printf("is_empty: true\n");
                } else {
                    printf("is_empty: false\n");
                }
                break;
            case PUSH:
                int next = read_int();
                stack_io(next);
            case POP:
                if (value != READ_INT_FAIL){
                    printf("pop: %d\n", value);
                    return;
                } else {
                    printf("pop: error: stack is empty\n");
                }
            case TOP:
                if (value != READ_INT_FAIL){
                    printf("top: %d\n", value);
                } else {
                    printf("top: error: stack is empty\n");
                }
            case QUIT:
                if (value == READ_INT_FAIL){
                    return;
                } else {
                    printf("quit: error: stack is not empty\n");
                }
            default:
                fatal_error();

        }

    }

    // this starts the stack


    //is_empty        displays status of the stack (empty or not)

    //push int        pushes int on to the stack

    //pop             pops the stack (**)

    //top             displays the top of the stack (**)

    //quit            exits the program [**]

}

int main() {
    printf("Hello, World!\n");
    // this just ensures the symbols have been initialized correctly
    assert(IS_EMPTY == lookup_symbol("is_empty"));
    assert(PUSH == lookup_symbol("push"));
    assert(POP == lookup_symbol("pop"));
    assert(TOP == lookup_symbol("top"));
    assert(QUIT == lookup_symbol("quit"));
    stack_io(READ_INT_FAIL);
    return 0;
}
