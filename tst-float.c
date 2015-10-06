/*
 * Simple program to test FP unit VM context switch. Launch 4 or more 
 * per vCPU and pCPU, and crunch fp addition, and compre to predefined 
 * outcome. Context switch between Guests and host, hopefully will catch
 * a bad saved/restor resulting in bad outcome.
 *
 * Compile:
 *	<aarch64-linux-gnu-gcc|arm-linux-gnueabi-gcc> \
 *		-o tst-float tst-float.c
 * 
 * Usage:
 * - sleep 1ms between adding
 * ./tst-float 1& 
 *
 * Author: Mario Smarduch. Samsung - Research Silicon Valey.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float trunc_float(float f, int n)
{
        f = (int) (f * pow(10,5));
        f /= pow(10,5);
        return f;
}

int main(int argc, char **argv)
{
        volatile float f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10;
        /* Prepared truncted result */
        float result = 3.402530; 
        int t_o;
        float temp = 0.0;
    
        if(argc != 2) {
                t_o = 10;
                goto crunch;
        } 

        t_o = atoi(argv[1]);
        if(t_o == 0)
                t_o = 10;
crunch:

        for(;;) {
                temp = 0.0;
                f0 = 1.01324;
                f1 = f2 = f3 = f4 = f5 = f6 = f7 = f8 = f9 = f10 = 0;
                f0 += 0.2123;
                f1 += f0 + 0.2133;
                f2 += f1 + 0.2143;
                f3 += f2 + 0.2153;
                f4 += f3 + 0.2163;
                f5 += f4 + 0.2173;
                f6 += f5 + 0.2183;
                f7 += f6 + 0.2193;
                f8 += f7 + 0.2203;
                f9 += f8 + 0.2213;
                f10 += f9 + 0.2213;
                /* truncate to compare */
                temp = trunc_float(f10,5);

		if(temp != result) {
                        fprintf(stderr, "FP test failed\n");
                        exit(-1);
                }

                poll(0, 0, t_o);
        }
}
