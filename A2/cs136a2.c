#include <stdio.h>
#include <assert.h>
void draw_triangle(int size) {
    assert(size >= 1);
    const int width = size * 2 + 1;
    for (int y = 0; y < width; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x <= y) {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}
void draw_border(int size){
    assert(size >= 1);
    const int width =size * 2 +1;
    for (int y = 0; y < width; ++y){
        for (int x = 0; x < width; ++x){
            if (x == 0 || y ==0 || x == width-1 || y == width-1 ){
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }

}
void draw_x(int size){
    assert(size >= 1);
    const int width =size * 2 +1;
    for (int y = 0; y < width; ++y){
        for (int x = 0; x < width; ++x){
            if (x+y == width - 1 || x == y){
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }

}
void draw_checker(int size){
    assert(size >= 1);
    const int width =size * 2 +1;
    for (int y = 0; y < width; ++y){
        for (int x = 0; x < width; ++x){
            if (((x + y) % 2) == 0 ){
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }

}
void draw_diamond(int size){
    assert(size >= 1);
    const int width =size * 2 +1;
    for (int y = 0; y < width; ++y){
        for (int x = 0; x < width; ++x){
            if ( (y + size) == x || (y - size) == x ||
                (width - 1 - y) + size == x || (width - 1 - y) - size == x )  {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

const int INT_MIN = -2147483648;
const int INT_MAX = 2147483647;
const int READ_INT_FAIL = -2147483648;
int read_int() {
    int num;
    if (scanf("%d", &num) != 1) return READ_INT_FAIL;
    return num;
}

void bigger_read (int max){
    int num = read_int();
    while (num != READ_INT_FAIL){

        if (num > max){
            printf("%d ",num);
            max = num;
        }
        num = read_int();

    }

}
void statistics (){
    int count = 0;
    int sum = 0;
    int mean = 0;
    int min =INT_MAX;
    int max =INT_MIN;
    int num = read_int();
    while (num != READ_INT_FAIL){
        count += 1;
        sum += num;
        if (num < min){
            min = num;
        }
        if (num > max){
            max = num;
        }
        num = read_int();

    }
    mean = sum / count;
    printf("count: %d, sum: %d, mean: %d, min: %d, max: %d", count, sum, mean, min, max);
}
void difference(){
    int num = read_int();
    int previous = 0;
    int diff = 0;
    while (num != READ_INT_FAIL){
        diff = num - previous;
        printf("%d\n", diff);
        previous = num;
        num = read_int();
    }
}
void encode(){
    int num =read_int();
    int previous = num;
    int count = 0;
    while (num != READ_INT_FAIL){
        if (num == previous){
            count+=1;
        }
        if (num != previous){
            printf("%d %d\n", count, previous);
            count = 1;
            previous = num;
        }
        num = read_int();
    }
    printf("%d %d\n", count, previous);
}
// 1 1 1 1 3 3 1 -2147483648
void safe_to_add(int a, int b){
    if ((a >= 0 && b <= 0) || (a <= 0 && b >= 0)){
        int sum = a +b;
        printf("%d",sum);
        return;
    }
    if (a > 0){
        if (((a/2) + (b/2)) < INT_MAX/2){
            int sum = a +b;
            printf("%d",sum);
            return;
        }
        if ((a/2) + (b/2) == INT_MAX/2){
            int reminder_a = a % 2;
            int reminder_b = b % 2;
            if ((reminder_a + reminder_b) <= 1){
                int sum = a +b;
                printf("%d",sum);
                return;
            } else {
                printf("overflow");
                return;
            }
        } else {
            printf("overflow");
            return;
        }
    } else {
        if (((a/2) + (b/2)) > INT_MIN/2){
            int sum = a +b;
            printf("%d",sum);
            return;
        }
        if (((a/2) + (b/2)) == INT_MIN/2){
            int reminder_a = a % 2;
            int reminder_b = b % 2;
            if ((reminder_a + reminder_b)==0){
                int sum = a +b;
                printf("%d",sum);
                return;
            }else {
                printf("overflow");
                return;
            }
        }
    }
}

void mean(int a, int b, int c){
    printf("%d",a/3 + b/3 + c/3 + (a%3 + b%3 + c%3) / 3);
}

void cryptography(){
    int key;
    char c;
    scanf("%d", &key);
    assert((0 <= key) && (key <=94));
    scanf("%c", &c );
    assert(c == '\n');
    while (scanf("%c", &c) == 1){
        if (c == '\n'){
            printf("\n");
        } else {
            printf("%c", (c + key - ' ') % 95 + ' ');
        }
    }
}

double find_sqrt(double n, double tol){
    double x = 1;
    while ((((x * x) -n) > tol) || ((n - (x * x)) > tol)){
        double x_next = (x + (n / x)) / 2;
        x = x_next;
    }
    printf("%f",x);
    return x;

}
int main() {
    //draw_triangle(3);
    //draw_x(3);
    //draw_checker(2);
    //draw_diamond(3);
    //bigger_read(INT_MIN);
    //statistics ();
    //difference();
    //encode();
    //-1073741824
    //-1073741823
    //safe_to_add(1073741824,1073741824);
    //mean(-1,0,2);
    //cryptography();
    find_sqrt(4.00,0.01);
    return 0;
}
