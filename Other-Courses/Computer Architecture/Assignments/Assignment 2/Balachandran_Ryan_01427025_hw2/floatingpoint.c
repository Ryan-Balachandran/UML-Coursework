/*----------------------------------------------------*/
/*--------------------ASSIGNMENT 2--------------------*/
/*----------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

typedef union float_32
{
     float floating_value_in_32_bits;
     int arg_32;

     struct  sign_exp_mantissa
     {
         unsigned  mantissa:23;
         unsigned  exponent:8;
         unsigned      sign:1;
     } f_bits;

     struct single_bits
     {
          unsigned  b0 :1;    // Mantissa
          unsigned  b1 :1;    // Mantissa
          unsigned  b2 :1;    // Mantissa
          unsigned  b3 :1;    // Mantissa

          unsigned  b4 :1;    // Mantissa
          unsigned  b5 :1;    // Mantissa
          unsigned  b6 :1;    // Mantissa
          unsigned  b7 :1;    // Mantissa

          unsigned  b8 :1;    // Mantissa
          unsigned  b9 :1;    // Mantissa
          unsigned  b10:1;    // Mantissa
          unsigned  b11:1;    // Mantissa

          unsigned  b12:1;    // Mantissa
          unsigned  b13:1;    // Mantissa
          unsigned  b14:1;    // Mantissa
          unsigned  b15:1;    // Mantissa

          unsigned  b16:1;    // Mantissa
          unsigned  b17:1;    // Mantissa
          unsigned  b18:1;    // Mantissa
          unsigned  b19:1;    // Mantissa

          unsigned  b20:1;    // Mantissa
          unsigned  b21:1;    // Mantissa
          unsigned  b22:1;    // Mantissa

          unsigned  b23:1;    // Exponent
          unsigned  b24:1;    // Exponent
          unsigned  b25:1;    // Exponent
          unsigned  b26:1;    // Exponent
          unsigned  b27:1;    // Exponent
          unsigned  b28:1;    // Exponent
          unsigned  b29:1;    // Exponent
          unsigned  b30:1;    // Exponent

          unsigned  b31:1;    // Sign
     } bit;

} FLOAT_UN;


// A function to print out bits from a 32 bit container
// provided by the union FLOAT_UN above, and using
// a text string as a label for the bit string
// as passed in the second argument

int print_bits(FLOAT_UN float_32, char* text)
{
     char bit_string[43];
     int i;

     for(i = 0; i < 42; i++)
     {
          bit_string[i] = ' ';
     }

     bit_string[42] = '\0';

     // SIGN BIT
     bit_string[0] = float_32.bit.b31?'1':'0';

     // EXPONENT
     bit_string[2] = float_32.bit.b30?'1':'0';
     bit_string[3] = float_32.bit.b29?'1':'0';
     bit_string[4] = float_32.bit.b28?'1':'0';
     bit_string[5] = float_32.bit.b27?'1':'0';

     bit_string[7] = float_32.bit.b26?'1':'0';
     bit_string[8] = float_32.bit.b25?'1':'0';
     bit_string[9] = float_32.bit.b24?'1':'0';
     bit_string[10] = float_32.bit.b23?'1':'0';

     // MANTISSA
     bit_string[12] = float_32.bit.b22?'1':'0';
     bit_string[13] = float_32.bit.b21?'1':'0';
     bit_string[14] = float_32.bit.b20?'1':'0';

     bit_string[16] = float_32.bit.b19?'1':'0';
     bit_string[17] = float_32.bit.b18?'1':'0';
     bit_string[18] = float_32.bit.b17?'1':'0';
     bit_string[19] = float_32.bit.b16?'1':'0';

     bit_string[21] = float_32.bit.b15?'1':'0';
     bit_string[22] = float_32.bit.b14?'1':'0';
     bit_string[23] = float_32.bit.b13?'1':'0';
     bit_string[24] = float_32.bit.b12?'1':'0';

     bit_string[26] = float_32.bit.b11?'1':'0';
     bit_string[27] = float_32.bit.b10?'1':'0';
     bit_string[28] = float_32.bit.b9?'1':'0';
     bit_string[29] = float_32.bit.b8?'1':'0';

     bit_string[31] = float_32.bit.b7?'1':'0';
     bit_string[32] = float_32.bit.b6?'1':'0';
     bit_string[33] = float_32.bit.b5?'1':'0';
     bit_string[34] = float_32.bit.b4?'1':'0';

     bit_string[36] = float_32.bit.b3?'1':'0';
     bit_string[37] = float_32.bit.b2?'1':'0';
     bit_string[38] = float_32.bit.b1?'1':'0';
     bit_string[39] = float_32.bit.b0?'1':'0';

     printf("%s%c | ", text, bit_string[0]);

     for(int exp = 2; exp <= 10; exp++)
     {
          printf("%c", bit_string[exp]);
     }

     printf(" | ");

     for(int mant = 12; mant <= 39; mant++)
     {
          printf("%c", bit_string[mant]);
     }

     printf("\n");
     return 0;
}


int main(int argc, char * argv[])
{
     FLOAT_UN float_32_s1, float_32_s2, float_32_rslt;

     /* local helper variables */
     float the_hardware_Result;
     float result;
     int mant_s1, mant_s2, mant_res, exp_s1, exp_s2, exp_rslt;
     //int i, j, k;

     /* Request two floating point numbers */
     printf("************************************************************************************\n");
     printf("This program will emulate the addition of two IEEE 754 floating point numbers.\n");
     printf("Please enter two positive floating point values each with: \n");
     printf("- no more than 6 significan digits\n");
     printf("- a value between + 10**37 and 10**-37\n\n");

     printf("Enter float 1: ");
     scanf("%g", &float_32_s1.floating_value_in_32_bits);

     printf("Enter float 2: ");
     scanf("%g", &float_32_s2.floating_value_in_32_bits);

     print_bits(float_32_s1, "\nOriginal pattern of Float 1: ");
     print_bits(float_32_s2, "Original pattern of Float 2: ");



     /* GENERATE FLOATINGPOINT HARDWARE RESULT */
     the_hardware_Result = float_32_s1.floating_value_in_32_bits + float_32_s2.floating_value_in_32_bits;



     /* GET THE MANTISSA AND EXPONENT COMPONENTS INTO THE HELPER VARIABLES*/
     mant_s1 = float_32_s1.f_bits.mantissa;
     mant_s2 = float_32_s2.f_bits.mantissa;
     exp_s1  = float_32_s1.f_bits.exponent;
     exp_s2  = float_32_s2.f_bits.exponent;

     printf("\nExponent of float 1 as int: %u\n", exp_s1);
     printf("Exponent of float 2 as int: %u\n", exp_s2);

     if(exp_s1 > exp_s2)
     {
          printf("Floating point 1 is larger\n");
          exp_rslt = exp_s1 - exp_s2;

          if(exp_rslt == 0)
          {
               printf("Shift count = %u\n", exp_rslt);
          }
          else
          {
               exp_s2 = exp_s1;

               printf("Shift count = %u\n", exp_rslt);

               exp_rslt -= 1;
               mant_s2 >>= 1;
               mant_s2 |= 0b10000000000000000000000;
               mant_s2 >>= exp_rslt;
          }
     }
     else
     {
          printf("Floating point 2 is larger\n");
          exp_rslt = exp_s2 - exp_s1;

          if(exp_rslt == 0)
          {
               printf("Shift count = %u\n", exp_rslt);
          }
          else
          {
               exp_s1 = exp_s2;

               printf("Shift count = %u\n", exp_rslt);

               exp_rslt -= 1;
               mant_s1 >>= 1;
               mant_s1 |= 0b10000000000000000000000;
               mant_s1 >>= exp_rslt;
          }
     }

     float_32_s1.f_bits.exponent = exp_s1;
     float_32_s2.f_bits.exponent = exp_s2;

     print_bits(float_32_s1, "\nExponent of Float 1 after alignment: ");
     print_bits(float_32_s2, "Exponent of Float 2 after alignment: ");
     float_32_rslt.f_bits.exponent = exp_s1;


     /* CHECK FOR NORMALIZATION AND SLAM IN THE HIDDEN BIT IF NORMALIZED*/
     float_32_s1.f_bits.mantissa = mant_s1;
     float_32_s2.f_bits.mantissa = mant_s2;

     print_bits(float_32_s1, "\nMantissa of Float 1: ");
     print_bits(float_32_s2, "Mantissa of Float 2: ");


     /* ADD THE MANTISSA'S OF THE TWO FLOATING POINTS TOGETHER */

     printf("\n\n");
     print_bits(float_32_s1, "     ");
     print_bits(float_32_s2, "    +");
     printf("    ----------------------------------------------\n");

     // EDIT binary addition                                          <<----------------------------
     //mant_res = mant_s1 | mant_s2;
     float_32_rslt.f_bits.mantissa = mant_s1 | mant_s2;

     //float_32_rslt.f_bits.mantissa = mant_res;
     print_bits(float_32_rslt, "     ");


     result = float_32_rslt.floating_value_in_32_bits;

     printf("\n");
     print_bits(float_32_rslt, "\nBit pattern of result: ");
     printf("EMULATED FLOATING RESULT FROM PRINTF ==>>> %-g \n", result);
     printf("HARDWARE FLOATING RESULT FROM PRINTF ==>>> %-g \n", the_hardware_Result);
     printf("************************************************************************************\n");
}
