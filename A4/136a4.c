#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

double poly_with_root_sqrt2(double x) {
    return x * x - 2;
}
double bisection(double (*f)(double), double lo, double hi, double tolerance) {
    double mid = (lo + hi) / 2;
    double mid_ans = f(mid);
    double lo_ans = f(lo);
    double hi_ans = f(hi);
    if (mid_ans < 0){
        if (-mid_ans < tolerance){
            return mid;
        }
    } else {
        if (mid_ans < tolerance){
            return mid;
        }
    }

    if ((mid_ans * lo_ans) < 0){
        bisection(f, lo, mid, tolerance);
    }

    if ((mid_ans * hi_ans) < 0){
        bisection(f, mid, hi, tolerance);
    }
}
const int READ_INT_FAIL = INT_MIN;
const char READ_CHAR_FAIL = 0;


int read_int(void) {
    int i = 0;
    if (scanf("%d", &i) == 1){
        return i;
    } else {
        return READ_INT_FAIL;
    }
}
//'0' = ascii(0);
//    = 0; "000" NULL
char read_char(bool ignore_ws) {
    char c = ' ';
    if (ignore_ws){
        if (scanf(" %c", &c) != 1 ){
            return READ_CHAR_FAIL;
        } else {
            scanf(" %c", &c);
            return c;
        }
    } else {
        if (scanf("%c", &c) != 1 ){
            return READ_CHAR_FAIL;
        } else {
            scanf("%c", &c);
            return c;
        }
    }
}


struct coke_machine {
    // add your fields
    int price;
    int cans;
    int sales;
    int money_inserted;
};

void money_print(int amount){
    int a = amount / 100;
    int b = amount % 100;
    printf("$%d.%d",a,b);
};

void reset_machine(struct coke_machine *machine){
    machine -> price = 1;
    machine -> cans = 0;
    machine -> sales = 0;
    machine -> money_inserted = 0;
};

void display_status(const struct coke_machine *machine){
    printf("current state: price %d, cans %d, sales %d, money_inserted %d",
            machine -> price, machine -> cans, machine -> sales, machine -> money_inserted);
};

void dispense(struct coke_machine *machine){
    if ((machine -> cans <= 0) && (machine -> money_inserted >= machine ->price)){
        printf("not enough cans");
    } else if ((machine -> money_inserted) < (machine -> price)){
        int more = machine -> price - machine -> money_inserted;
        printf("need %d more dolors", more);
    } else {
        machine -> money_inserted -= machine -> price;
        machine -> sales += 1;
        machine -> cans -= 1;
    }

};

void insert_money(struct coke_machine *machine, int amount){
    if (amount < 0){
        printf("error");
    } else {
        machine -> money_inserted += amount;
    }
};

void get_change(struct coke_machine *machine){
    if (machine -> money_inserted == 0){
        printf("error");
    } else {
        printf("get money %d", machine -> money_inserted);
        machine -> money_inserted = 0;
    }
};

void set_price(struct coke_machine *machine, int amount){
    if (amount <= 0){
        printf("error");
    } else {
        machine -> price = amount;
    }

};

void add_inventory(struct coke_machine *machine, int qty){
    if (qty <= 0){
        printf("error");
    } else {
        machine -> cans += qty;
    }
};

int u = 1;
int l = 2;
int r = 3;
int d = 4;

struct robot {
    int x;
    int y;
    int max_u;
    int max_l;
    int max_r;
    int max_d;
};

// robot_init(r) initializes the robot *r to be at the origin (0,0)
//   with no history
// effects: modifies *r
void robot_init(struct robot *r){
    r -> x =0;
    r -> y =0;
    r -> max_u =0;
    r -> max_l =0;
    r -> max_r =0;
    r -> max_d =0;
};

// robot_move(r, direction, distance) moves the robot *r
//   in direction by distance
// requires: distance > 0
// effects:  modifies *r
void robot_move(struct robot *r, int direction, int distance){
    assert(distance > 0);
    if (direction == 1){
        r -> y += distance;
        if (r -> y > r -> max_u){
            r -> max_u = r -> y;
        }
    } else if (direction == 2){
        r -> x -= distance;
        if (r -> x < r -> max_l){
            r -> max_l = r -> x;
        }
    } else if (direction == 3){
        r -> x += distance;
        if (r -> x > r -> max_r){
            r -> max_r = r -> x;
        }
    } else {
        r -> y -= distance;
        if (r -> y < r -> max_d){
            r -> max_d = r -> y;
        }
    }

};

// robot_pos(r, x, y) modifies *x and *y to store the
//   current x-y position of robot r
// effects: modifies *x and *y
void robot_pos(const struct robot *r, int *x, int *y){
    int current_x = r -> x;
    int current_y = r -> y;
    *x = current_x;
    *y = current_y;
};

// robot_max(r, direction) determines the maximum distance from
//   the origin (0,0) that the robot r has travelled in direction
int robot_max(const struct robot *r, int direction){
    if (direction == 1){
        if (r -> y > 0){
            return r -> y;
        } else {
            return 0;
        }
    } else if (direction == 2){
        if (r -> x < 0){
            return -(r->x);
        } else {
            return 0;
        }

    } else if (direction == 3){
        if (r -> x > 0){
            return (r -> x);
        } else {
            return 0;
        }

    } else {
        if (r -> y < 0){
            return -(r -> y);
        } else {
            return 0;
        }
    }
};



int main() {
//    int x = 3;
//    int y = 3;
//    robot_pos(NULL, &x, &y);
//    printf("Hello, World!\n");
//    bisection(poly_with_root_sqrt2, 1, 1, 1);
    struct robot ro = {0,0,0,0,0,0};
    struct robot *r = &ro;
    int x = 0;
    int y = 0;
    char c;
    int b;
    while(scanf(" %c", &c) == 1) {
        switch(c){
            case 'i':
                robot_init(r);
                break;
            case 'q':
                return 0;
            case 'p':
                robot_pos(r, &x, &y);
                printf("(%d,%d)\n", x, y);
                break;
            case 'b':
                printf("(%d,%d)-(%d,%d)\n", r -> max_l, r -> max_d, r -> max_r, r -> max_u);
                break;
            case 'u':
                scanf("%d", &b);
                robot_move(r, 1, b);
                break;
            case 'l':
                scanf("%d", &b);
                robot_move(r, 2, b);
                break;
            case 'r':
                scanf("%d", &b);
                robot_move(r, 3, b);
                break;
            case 'd':
                scanf("%d", &b);
                robot_move(r, 4, b);
                break;
            default:
                return 1;

        }
    }
    return 0;
}
