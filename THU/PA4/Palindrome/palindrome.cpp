#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long ll;

const int MAXLEN = 17000002;

char str[MAXLEN], man[(MAXLEN<<1)|1];
int mlen;
int radius[(MAXLEN<<1)|1];
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))

#define NOTNL(x) ((x)!='\n'&&(x)!='\r')

void makeManacher() {
    // memset(man, 0, sizeof(man));
    char *pm = man;
    *(pm++) = '$'; *(pm++) = '#';
    for (char *ps = str; *ps && NOTNL(*ps); ps++) {
        *(pm++) = *ps;
        *(pm++) = '#';
    }
    mlen = pm - man;
}

int Manacher() {
    // memset(radius, 0, sizeof(radius));
    int right_edge = 0, center = 0;
    int ans_start, max_len = 0;
    for (int i = 1; man[i]; i++) {
        radius[i] = right_edge > i ? min(radius[2 * center - i], right_edge - i) : 1;
        while (i + radius[i] < mlen && i - radius[i] > 0) {
            if (man[i - radius[i]] == man[i + radius[i]])
                radius[i]++;
            else break;
        }
        if (i + radius[i] > right_edge) {
            right_edge = i + radius[i];
            center = i;
        }
        if (radius[i] - 1 > max_len) {
            max_len = radius[i] - 1;
        }
    }
    return max_len;
}


int main()
{
    fgets(str, MAXLEN, stdin);
    makeManacher();
    int mp = Manacher();
    // printf("%d\n", mp);
    ll sum = 0;
    for (int i = 0; man[i]; i++) {
        if (man[i] == '#') 
            sum += (radius[i] >> 1);
        else sum += (radius[i] & 1) ? ((radius[i] + 1) >> 1) : ((radius[i]) >> 1);
    }
    printf("%lld\n", sum);
    return 0;
}