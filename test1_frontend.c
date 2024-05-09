#include <stdio.h>

int global_var = 100; // Global variable

mifuncion() {
    int local_var = 50; // Local variable
    int i;
    int c = 123;

    // Variation using 'if'
    if (global_var > local_var) {
        puts("Global variable is greater than local variable");
    } else {
        puts("Local variable is greater than global variable");
    }

    // Variation using 'for'
    for (i = 0; i < 3; i = i + 1) {
        printf("%d\n", i + 1);
    }


    // Variation using 'while'
    while (c > 120) {
        c = c - 1;
        printf("%d\n", c);
    }

    puts("Prueba");
    return c + 1;
}

main() {
    int c;

    // Variation using 'printf'
    printf("%s", "Entering mifuncion...\n");

    c = mifuncion();
    
    printf("%s", "Exiting mifuncion...\n");

    // Variation using 'puts'
    puts("Back in main");

    // Variation using local variable in 'printf'
    printf("%d\n", c);

    // Variation using global variable in 'printf'
    printf("%d\n", global_var);

    printf("%d %s %d\n", c, " ", mifuncion());

    //return 0;
}


//@ (main)

