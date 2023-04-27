#include <stdio.h>


int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("%s: файл не был введен\n", argv[0]);
    } else {
        FILE* f;
        f = fopen(argv[1], "r");
        if (f) {
            printf("%s: %s файл был открыт\n", argv[0], argv[1]);
            char str[64];
            while (fgets(str, sizeof(str), f)) {
                printf("%s", str);
            }
            fclose(f);
        } else {
            printf("%s: %s файл не был открыт\n", argv[0], argv[1]);
        }
    }

    
    return 0;
}
