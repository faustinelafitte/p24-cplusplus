#include <iostream>
void swap(int*x, int*y){
    int t=(*x);
    *x=*y;
    *y=t;
}
int main(){
    int a=84;
    int b=-72;
    swap(a,b);
    return 0;
}