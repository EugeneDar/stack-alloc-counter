#include <stdio.h>
#include <string.h>

int foo () {
    int a = 0;
    int b = 1;
    int c = 2;
    int res = c - b - a;
    return res;
}

int main(int argc, const char** argv) {
    int num;

    scanf("%d", &num);

    while (num > 0) {
        printf("Call foo\n");
        num -= foo();
    }

    return 0;
}
