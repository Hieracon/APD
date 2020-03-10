#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
    unsigned char inputs;
    unsigned char x2, x1, x0;
    unsigned char outs;
    unsigned char temp;

    while(1){
        cin>>inputs;

        inputs = inputs & 0b0000111;

        x0 = inputs & 1 << 0;

        x1 = inputs >> 1 & 1 << 0;

        x2 = inputs >> 2 & 1 << 0;

        outs = 0;

        // f0
        temp = x2 ^ x1 ^ x0;

        if(temp & 1 << 0){
            outs = outs | 1 << 0;
        }

        if(inputs < 3){
            outs = outs | 1 << 1;
        }

        temp = (~x2 & x1) | (x2 & x0);
        if(temp & 1 << 0){
            outs = outs | 1 << 2;
        }

        if((inputs == 2) || (inputs == 3) || (inputs == 5) || (inputs == 7)){
            outs = outs | 1 << 2;
        }

        outs +='0';
        cout << outs << endl;
    }

    return 0;
}
