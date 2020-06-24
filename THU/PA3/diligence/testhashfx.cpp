#include <stdio.h>

typedef unsigned int uint;
typedef unsigned long long ull;
#define NHASH  10005
#define MULT  131
uint hash(const char *str)
{
    ull h=0;
    const char *p;
    for(p=str; *p!='\0'; p++)
            h = MULT*h + *p;
    return h % NHASH;
}
char word[9];
void rdstr(char *to) {
    char c = getchar();
    while (c < 'a' || c > 'z') c = getchar();
    while (c >= 'a' && c <= 'z') *(to++) = c, c = getchar();
    *to = 0;
}
int main(){
    while (1) {
        rdstr(word);
        printf("%lld\n", hash(word));
    }

    return 0;
}