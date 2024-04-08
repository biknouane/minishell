#include <stdio.h>

typedef enum {
    NORMAL,
    IN_SINGLE_QUOTE,
    IN_DOUBLE_QUOTE
} State;

void parseString(const char *str) {
    State state = NORMAL;

    for (int i = 0; str[i] != '\0'; i++) {
        switch (state) {
            case NORMAL:
                if (str[i] == '\'') {
                    state = IN_SINGLE_QUOTE;
                    printf("Entering single quote mode\n");
                } else if (str[i] == '"') {
                    state = IN_DOUBLE_QUOTE;
                    printf("Entering double quote mode\n");
                } else if (str[i] != ' ') {
                    printf("%c", str[i]);
                }
                break;

            case IN_SINGLE_QUOTE:
                if (str[i] == '\'') {
                    state = NORMAL;
                    printf("Leaving single quote mode\n");
                } else {
                    printf("%c", str[i]);
                }
                break;

            case IN_DOUBLE_QUOTE:
                if (str[i] == '"') {
                    state = NORMAL;
                    printf("Leaving double quote mode\n");
                } else {
                    printf("%c", str[i]);
                }
                break;
        }
    }

    printf("\n");
}

int main() {
    const char *str = "ls -la > file.txt | echo \"hello ' wold\"";
    parseString(str);
    return 0;
}
