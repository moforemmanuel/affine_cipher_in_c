#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define g_alphabets "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

typedef struct
{
    /* data */
    int a, b;
} twoInts;


char* encrypt(int a, int b, char* plain_text);
char* decrypt(int a, int b, char* cipher_text);

char* get_text();
twoInts get_input();

char* get_plain_text();
char* get_cipher_text();

int letter_to_index(char letter);
char index_to_letter(int index);

int mod26(int n);
int gcd(int a, int b);
int modInverse(int a, int m);

void driver();

int main() {
    while (1) {
        driver();
        int decision;
        printf("Would u like to perform another operation?\n1)Yes\n2)No\nDecision: ");
        scanf("%d", &decision);
        
        if (decision != 1){
            printf("... Goodbye ...\n");
            exit(EXIT_SUCCESS);
        }
    }
        
    
}


void driver() {
    
    twoInts input = get_input();
    int choice;
    printf("\nWhat operation would you like to perform?\n");
    printf("1)Encrypt\n2)Decrypt\n3)Exit\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\ny = λx + b (mod 26)\n");
        printf("\nEnter Plain text: ");
        char* plain_text = get_plain_text();
        char* cipher_text = encrypt(input.a, input.b, plain_text);
        printf("\nPlain Text: %s\nCipher Text: %s\n\n", plain_text, cipher_text);
        free(plain_text);
        free(cipher_text);
    } 

    else if (choice == 2) {
        printf("\nx = (λ^-1)(y - b)(mod 26)\n");
        printf("\nEnter Cipher text: ");
        char* cipher_text = get_cipher_text();
        char* plain_text = decrypt(input.a, input.b, cipher_text);
        printf("\nCipher Text: %s\nPlain Text: %s\n\n", cipher_text, plain_text);
        free(cipher_text);
        free(plain_text);
    }

    else if (choice == 3) {
        printf("\n... Goodbye ...\n");
        exit(EXIT_SUCCESS);
    }

    else {
        printf("\nInvalid choice\n");
    }
    
    
  
}

char* get_text() {
    // char* s = calloc(1, sizeof(char));
    // char t;
    // int len;

    // while (scanf("%c", &t) == 1) {
    //     if (t == '\n') break;
    //     else if(!isalpha(t)) continue;
    //     len = strlen(s);
    //     s = realloc(s, len+1);
    //     *(s + len) = t;
        
    // }
    // *(s + len + 1) = '\0';

    char s[100];
    fgets(s,100,stdin);
    puts(s);
    return s;
}

char* get_plain_text(){
    // get_text();
    char* text = get_text();
    // char* plain_text = malloc(strlen(text));
    // for (int i = 0; i < strlen(text); i++){
    //     *(plain_text + i) = tolower(*(text + i));
    // }
    // free(text);
    return text;

}
char* get_cipher_text(){
    // get_text();
    char* text = get_text();
    char* cipher_text = malloc(strlen(text));
    for (int i = 0; i < strlen(text); i++){
        *(cipher_text + i) = toupper(*(text + i));
    }
    free(text);
    return cipher_text;
}


twoInts get_input(){
    twoInts input;
    printf("\nPlease enter λ (1 <= λ <= 25): \n");
    scanf("%d", &input.a); 
    if (input.a == 0) {
        printf("Quiting ...\n");
        exit(EXIT_SUCCESS);
    }
    printf("Please enter K (any value): \n");
    scanf("%d", &input.b);

    if (input.a > 25 || input.a < 1){
        printf("\nλ must be between 1 and 25\n");
        exit(EXIT_FAILURE);
    }

    else if (gcd(input.a, input.b) != 1) {
        printf("\nλ and K must be co-prime\n");
        exit(EXIT_FAILURE); 
    }

    else if (gcd(input.a, 26) != 1){
        printf("\nλ and 26 must be co-prime\n");
        exit(EXIT_FAILURE);
    }
    
    return input;
}

int mod26(int n) {
    return (n % 26 + 26) % 26;
}

int gcd(int a, int b) {
    int i, gcd;
    for (i = 1; i <= a && i <= b; ++i) {
        if (a % i == 0 && b % i == 0) {
            gcd = i;
        }
    }

    return gcd;
}

int modInverse(int a, int m)
{
    int m0 = m;
    int y = 0, x = 1;
 
    if (m == 1)
        return 0;
 
    while (a > 1) {
        // q is quotient
        int q = a / m;
        int t = m;
 
        // m is remainder now, process same as
        // Euclid's algo
        m = a % m, a = t;
        t = y;
 
        // Update y and x
        y = x - q * y;
        x = t;
    }
 
    // Make x positive
    if (x < 0)
        x += m0;
 
    return x;
}

int letter_to_index(char letter){
    char *ptr = strchr(g_alphabets, letter);
    if (ptr == NULL) return -1;
    return (int)(ptr - g_alphabets);
}

char index_to_letter(int index){
    return g_alphabets[index];
}

char* encrypt(int a, int b, char* plain_text) {
    char* cipher_text = malloc(strlen(plain_text));

    for(int i = 0; i < strlen(plain_text); i++) {
        char plain_letter = toupper(plain_text[i]);
        int x = letter_to_index(plain_letter); //plain index
        int cipher_index = mod26((a*x) + b);
        char cipher_letter = index_to_letter(cipher_index);
        *(cipher_text + i) = cipher_letter;
    }

    *(cipher_text + strlen(plain_text)) = '\0';

    return cipher_text;
    
}

char* decrypt(int a, int b, char* cipher_text) {
    //x = inv(a)*(y - b) mod 26
    printf("cipher len: %d\n", strlen(cipher_text));
    char* plain_text = malloc(strlen(cipher_text) + 1);
    printf("plain len: %d\n", strlen(plain_text));


    for(int i = 0; i < strlen(cipher_text); i++) {
        char cipher_letter = cipher_text[i];
        int y = letter_to_index(cipher_letter);
        int a_inv = modInverse(a, 26);
        int plain_index = mod26(a_inv*(y - b));
        char plain_letter = index_to_letter(plain_index);
        // *(plain_text + i) = tolower(plain_letter);
        plain_text[i] = tolower(plain_letter);

    }
    printf("plain len after: %d\n", strlen(plain_text));

    // *(plain_text + strlen(cipher_text)) = '\0';
    plain_text[strlen(cipher_text) + 1] = '\0';
    printf("plain len after null: %d\n", strlen(plain_text));

    return plain_text;
    
}