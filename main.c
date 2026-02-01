#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int64_t i64;
typedef uint64_t u64;

#define BY 100000000000 // 100 000 000 000+ here. For some reason a lesser number breaks everything.

typedef struct {
    u64 node;
    u64 next_val;
    char* sum;
} b16; // b for bytes - always thought that using bits for size is pretty pointless

int u64_to_string(u64 num, char* str) {
    int i = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return 1;
    }

    while (num > 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }

    for (int j = 0; j < i / 2; j++) {
        char tmp = str[j];
        str[j] = str[i - 1 - j];
        str[i - 1 - j] = tmp;
    }

    str[i] = '\0';
    return i;
}

void b16_add(b16* b) {
    if (!b) return;

    char str_int[30];
    char str_frac[30];

    u64 temp_int = b->node / BY + b->next_val / BY;
    u64 temp_frac = b->node % BY + b->next_val % BY;

    u64_to_string(temp_int, str_int);
    u64_to_string(temp_frac, str_frac);

    b->sum = malloc(strlen(str_int) + strlen(str_frac)+1);
    if (*str_int == '0') {
       sprintf(b->sum, "%s", str_frac); 
       return;
    }
    sprintf(b->sum, "%s%s", str_int, str_frac);
}

int main() {
    b16 myb16 = {
       .node     = 9223372036854775807,
       .next_val = 9223372036854775806,
       .sum = NULL
    };

    b16_add(&myb16);

    printf("%s\n", myb16.sum);

    free(myb16.sum);
    return 0;
}

