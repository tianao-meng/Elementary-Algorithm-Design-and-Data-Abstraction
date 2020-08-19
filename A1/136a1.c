#include <stdio.h>
#include<assert.h>
int is_leap_year(int year){
    assert(year >= 1582 );
    if ((((year % 4) == 0) && ((year % 100)!=0))
        || ((year % 400) == 0)){
        return 1;
    }
    return 0;

}

int away_div(int num , int denom){
    int remainder = num % denom;
    if (remainder == 0) {
        return num / denom;
    } else {
        return (num / denom)+1;
    }
}
// (num % denom ==0) ? (num / denom) :((num / denom)+1);

int num_pizzas(int num_people, int slices_per_pizza, int slices_each ){
    assert(slices_per_pizza >= 1);
    int total_slices = num_people * slices_each;
    return away_div(total_slices, slices_per_pizza);
}

int hst_calculation (int amount){
    int reminder = (amount * 13) % 100;
    if (reminder >= 50) {
        return (amount * 0.13) + 1;
    } else {
        return amount * 0.13;
    }
}

int price_check(int price, int qty, int unit_size, int ref_price, int ref_qty, int ref_unit_size){
    int amount = price/(unit_size * qty);
    int remainder_amount = price - (amount * unit_size * qty);
    int ref_amount = ref_price / (ref_qty * ref_unit_size);
    int reminder_ref_amount = ref_price - ref_amount * ref_qty * ref_unit_size;
    return (amount < ref_amount || (amount = ref_amount && reminder_amount <= reminder_ref_amount));
}

int min_tiles(int tw, int th, int rw, int rh){
    int ans1 = away_div(rw, tw) * away_div(rh, th);
    int ans2 = away_div(rw, th) * away_div(rh, tw);
    return (ans1 <= ans2) ? ans1 : ans2;
}

void print_text(){
    printf("Hello, World! Welcome to CS %d!\n\n", 136);
    printf("These are some facts obtained from\n");
    printf("https://www.allaboutbirds.org\n");
    printf("about the 'Branta Canadensis'\n");
    printf("(known to his friends as \"Mr. Goose\").\n");
    printf("Their length ranges from %d to %dcm,\n", 76, 110);
    printf("which is approximately %d%% of their\n", 60);
    printf("large wingspan. They can weigh up to %dkg.\n",9);
    printf("They mate for life with very low \"divorce rates\"\n");
    printf("and mate \"assortatively\", meaning larger birds\n");
    printf("choose larger mates and the same for smaller ones.\n");
    printf("We hope you've enjoyed these fun geese facts on A1.\n");
    printf("Don't forget to put a newline (\\n) after each line.\n");
}

int price = 0;
int cans = 0;
int sales = 0;
int money_inserted = 0;
void money_print(int amount){
    int reminder = amount % 100;
    int integer = amount / 100;
    printf("$%d.%02d\n", integer, reminder);
}
void reset_machine(){
    price = 1;
    cans = 0;
    sales = 0;
    money_inserted = 0;
    printf("reset: %d,cans: %d, sales: %d, money_inserted: %d\n",price,cans,sales,money_inserted);
}
void display_status(){
    printf("display status: %d,cans: %d, sales: %d, money_inserted: %d\n",price,cans,sales,money_inserted);
}
void insert_money(amount){
    if (amount < 0){
        printf("Error: No balance\n");
    } else {
        money_inserted+=amount;
    }
}
void dispense(){
    if (cans > 1 && money_inserted > price){
        cans -= 1;
        money_inserted -= price;
        sales += 1;
    }
    if (money_inserted < price){
        printf("Error: please insert $%d\n", price);
    }
    if (cans == 0){
        printf("Error: not enough cans\n");
    }
}
void get_change(){
    int change = money_inserted - price;
    money_inserted = 0;
    if (change < 0){
        printf("the balance has been zero");
    } else {
        printf("user balance %d, change %d\n", 0,change);
    }
}
void set_price(int amount){
    if (amount < 0) {
        printf("Error: price is negative");
    } else {
        price = amount;
        printf("price %d\n",amount);
    }
}
void add_inventory(int qty){
    if (qty < 0){
        printf("Error: number of cans is negative");
    } else {
        cans += qty;
        printf("cans %d\n",cans);
        //printf("cans %d\n",cans +=qty);
    }
}

// global const
const int INT_MIN = -2147483648;
const int INT_MAX = 2147483647;
const int READ_INT_FAIL = -2147483648;

int read_int() {
    int num;
    if (scanf("%d", &num) != 1) return READ_INT_FAIL;
    return num;
}
void original_reverse(){
    int read = read_int();
    if (read == READ_INT_FAIL){
        return;
    }
    printf ("%d ",read);

    original_reverse();
    printf ("%d ",read);
}
void bigger_read(int max){
    int num = read_int();
    if (num == READ_INT_FAIL){
        return;
    }
    if (num > max){
        printf(" %d",num);
        max=num;
    }
    bigger_read(max);

}

void statistcs (int count, int sum, int mean, int min, int max){
    int num = read_int();
    if (num == READ_INT_FAIL){
        printf ("count: %d, sum: %d, mean: %d, min: %d, max: %d\n",count, sum, mean, min, max);
        return;
    }
    count+=1;
    sum+=num;
    mean = sum/count;
    if (num < min){
        min = num;
    }
    if (num > max){
        max = num;
    }
    statistcs(count, sum, mean, min, max);

}
void reverse_digit(int read){
    int reminder = read % 10;
    int num = read / 10;
    if (num == 0){
        printf("%d",reminder);
        return;
    }

    printf("%d",reminder);
    reverse_digit(num);
}
void reverse_order_digit(){
    int read = read_int();
    if (read == READ_INT_FAIL){
        return;
    }
    reverse_order_digit();
    reverse_digit(read);

    printf ("\n");

}
int reverse_min(){
    int num = read_int();
    if (num == READ_INT_FAIL){
        return INT_MAX ;
    }
    int a=reverse_min();
    if (num<a){
        printf("%d ",num);
        return num;

    }

    return a;
}




int main() {
    //printf("%d\n", is_leap_year(2000));
/*    printf("%d\n", away_div(5,2));
    printf("%d\n", num_pizzas(3, 3, 10));*/
    //print_text();
    //money_print(-1);
/*    reset_machine();
    display_status();
    add_inventory(10);
    insert_money(10);
    dispense();
    get_change();
    set_price(2);
    add_inventory(10);*/


    //original_reverse();
    //bigger_read(INT_MIN);
    //statistcs(0,0,0,INT_MAX,INT_MIN);
    //reverse_order_digit();
    reverse_min();
    return 0;
}
