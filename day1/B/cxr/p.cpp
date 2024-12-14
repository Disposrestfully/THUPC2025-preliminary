#include<bits/stdc++.h>
using namespace std;
int main(){
    int cas=0;
    while (1){
        system("./gen > 1.in");
        system("./std < 1.in > 1.ans");
        system("./bf2 < 1.in > 1.out");
        if (system("diff -B 1.out 1.ans")) return 0;
        printf("AC %d\n",++cas);
    }
    return 0;
}