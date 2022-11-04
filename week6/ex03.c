#include <stdio.h>

void findAnswer(char ans, int *a, int *b) {
    int l = *a;
    int r = *b;
    int mid = (l + r) / 2;
    if (ans == 'N') {
        *b = mid;
    } else if (ans == 'Y') {
        *a = mid + 1;
    }
}
int main() {
    int a,b,n;
    scanf("%d %d %d", &a, &b, &n);
    getchar();
    for (int i = 0; i < n; i++) {
        char ans;
        scanf("%c", &ans);
        findAnswer(ans, &a, &b);
    }
    printf("%d", a);
    return 0;
}