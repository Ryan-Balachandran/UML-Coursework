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

    struct sign_exp_mantissa
    {
        unsigned mantissa:23;
        unsigned exponent:8;
        unsigned     sign:1;
    } f_bits;

    struct single_bits
    {
        // MANTISSA
        unsigned b0 :1;    unsigned b1 :1;    unsigned b2 :1;    unsigned b3 :1;
        unsigned b4 :1;    unsigned b5 :1;    unsigned b6 :1;    unsigned b7 :1;
        unsigned b8 :1;    unsigned b9 :1;    unsigned b10:1;    unsigned b11:1;
        unsigned b12:1;    unsigned b13:1;    unsigned b14:1;    unsigned b15:1;
        unsigned b16:1;    unsigned b17:1;    unsigned b18:1;    unsigned b19:1;
        unsigned b20:1;    unsigned b21:1;    unsigned b22:1;

        // EXPONENT
        unsigned b23:1;    unsigned b24:1;    unsigned b25:1;    unsigned b26:1;
        unsigned b27:1;    unsigned b28:1;    unsigned b29:1;    unsigned b30:1;

        // SIGN
        unsigned b31:1;
    } bit;
} FLOAT_UN;

void initial_print(FLOAT_UN float_32)
{
    char bit_string[43];

    for(int i = 0; i < 42; i++)
    {
        bit_string[i] = ' ';
    }

    bit_string[42] = '\0';

    // SIGN BIT
    bit_string[0] = float_32.bit.b31?'1':'0';

    // EXPONENT
    bit_string[2] = float_32.bit.b30?'1':'0';   bit_string[3] = float_32.bit.b29?'1':'0';
    bit_string[4] = float_32.bit.b28?'1':'0';   bit_string[5] = float_32.bit.b27?'1':'0';

    bit_string[7] = float_32.bit.b26?'1':'0';   bit_string[8] = float_32.bit.b25?'1':'0';
    bit_string[9] = float_32.bit.b24?'1':'0';   bit_string[10] = float_32.bit.b23?'1':'0';

    // MANTISSA
    bit_string[12] = float_32.bit.b22?'1':'0';
    bit_string[13] = float_32.bit.b21?'1':'0';
    bit_string[14] = float_32.bit.b20?'1':'0';

    bit_string[16] = float_32.bit.b19?'1':'0';  bit_string[17] = float_32.bit.b18?'1':'0';
    bit_string[18] = float_32.bit.b17?'1':'0';  bit_string[19] = float_32.bit.b16?'1':'0';

    bit_string[21] = float_32.bit.b15?'1':'0';  bit_string[22] = float_32.bit.b14?'1':'0';
    bit_string[23] = float_32.bit.b13?'1':'0';  bit_string[24] = float_32.bit.b12?'1':'0';

    bit_string[26] = float_32.bit.b11?'1':'0';  bit_string[27] = float_32.bit.b10?'1':'0';
    bit_string[28] = float_32.bit.b9?'1':'0';   bit_string[29] = float_32.bit.b8?'1':'0';

    bit_string[31] = float_32.bit.b7?'1':'0';   bit_string[32] = float_32.bit.b6?'1':'0';
    bit_string[33] = float_32.bit.b5?'1':'0';   bit_string[34] = float_32.bit.b4?'1':'0';

    bit_string[36] = float_32.bit.b3?'1':'0';   bit_string[37] = float_32.bit.b2?'1':'0';
    bit_string[38] = float_32.bit.b1?'1':'0';   bit_string[39] = float_32.bit.b0?'1':'0';

    printf("***************************************************************************");
    printf("\nThe floating value for %g is broken out as: \n", float_32.floating_value_in_32_bits);
    printf("\n  Element: hex          or: binary\n");
    printf("--------------------------------------------------------------------------");


    printf("\n Mantissa: 0x%-10x or:    |           | %s", float_32.f_bits.mantissa, "");
    for(int m = 12; m < 42; m++)
    {
        printf("%c", bit_string[m]);
    }

    printf("\n Exponent: 0x%-10x or:    | %s", float_32.f_bits.exponent, "");
    for(int ex = 2; ex < 11; ex++)
    {
        printf("%c", bit_string[ex]);
    }
    printf(" |");

    printf("\n     Sign: %-12x or:  %x", float_32.f_bits.sign, float_32.f_bits.sign);
    printf(" |           | \n");


    // SIGN | EXPONENT | MANTISSA
    printf("in base10: %-12.6g or:  ", float_32.floating_value_in_32_bits);

    printf("%-c", bit_string[0]);   // SIGN
    printf(" | ");

    for(int ex = 2; ex < 11; ex++)  // EXPONENT
    {
        printf("%c", bit_string[ex]);
    }

    printf(" | ");

    for(int m = 12; m < 42; m++)    // MANTISSA
    {
        printf("%c", bit_string[m]);
    }
}

void print_bits(FLOAT_UN float_32, char* text)
{
    char bit_string[43];

    for(int i = 0; i < 42; i++)
    {
        bit_string[i] = ' ';
    }

    bit_string[42] = '\0';

    // SIGN BIT
    bit_string[0] = float_32.bit.b31?'1':'0';

    // EXPONENT
    bit_string[2] = float_32.bit.b30?'1':'0';   bit_string[3] = float_32.bit.b29?'1':'0';
    bit_string[4] = float_32.bit.b28?'1':'0';   bit_string[5] = float_32.bit.b27?'1':'0';

    bit_string[7] = float_32.bit.b26?'1':'0';   bit_string[8] = float_32.bit.b25?'1':'0';
    bit_string[9] = float_32.bit.b24?'1':'0';   bit_string[10] = float_32.bit.b23?'1':'0';

    // MANTISSA
    bit_string[12] = float_32.bit.b22?'1':'0';
    bit_string[13] = float_32.bit.b21?'1':'0';
    bit_string[14] = float_32.bit.b20?'1':'0';

    bit_string[16] = float_32.bit.b19?'1':'0';  bit_string[17] = float_32.bit.b18?'1':'0';
    bit_string[18] = float_32.bit.b17?'1':'0';  bit_string[19] = float_32.bit.b16?'1':'0';

    bit_string[21] = float_32.bit.b15?'1':'0';  bit_string[22] = float_32.bit.b14?'1':'0';
    bit_string[23] = float_32.bit.b13?'1':'0';  bit_string[24] = float_32.bit.b12?'1':'0';

    bit_string[26] = float_32.bit.b11?'1':'0';  bit_string[27] = float_32.bit.b10?'1':'0';
    bit_string[28] = float_32.bit.b9?'1':'0';   bit_string[29] = float_32.bit.b8?'1':'0';

    bit_string[31] = float_32.bit.b7?'1':'0';   bit_string[32] = float_32.bit.b6?'1':'0';
    bit_string[33] = float_32.bit.b5?'1':'0';   bit_string[34] = float_32.bit.b4?'1':'0';

    bit_string[36] = float_32.bit.b3?'1':'0';   bit_string[37] = float_32.bit.b2?'1':'0';
    bit_string[38] = float_32.bit.b1?'1':'0';   bit_string[39] = float_32.bit.b0?'1':'0';

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
}

int main()
{
    FLOAT_UN float_1, float_2, emulated_32, hardware_32;

    /* LOCAL HELPER VARIABLES */
    int mant_1, mant_2, mant_result, shift_rslt;
    int exp_1, exp_2;

    /* REQUEST TWO FLOATING POINT NUMBERS */
    printf("\n\n************************************************************************************\n");
    printf("This program will emulate the addition of two IEEE 754 floating point numbers.\n");
    printf("Please enter two positive floating point values each with: \n");
    printf("- no more than 6 significan digits\n");
    printf("- a value between + 10**37 and 10**-37\n\n");

    printf("Enter float 1: ");
    scanf("%g", &float_1.floating_value_in_32_bits);

    printf("Enter float 2: ");
    scanf("%g", &float_2.floating_value_in_32_bits);

    printf("\n");

    initial_print(float_1);
    print_bits(float_1, "\n\nOriginal pattern of Float 1: ");
    printf("\n***************************************************************************\n\n");


    initial_print(float_2);
    print_bits(float_2, "\n\nOriginal pattern of Float 2: ");
    printf("\n***************************************************************************\n");


    /* GET THE MANTISSA AND EXPONENT COMPONENTS INTO THE HELPER VARIABLES */
    printf("\nCOPY EXPONENT AND MANTISSA INTO THEIR LOCAL HELPER INT VARIABLES\n");
    mant_1 = float_1.f_bits.mantissa;
    mant_2 = float_2.f_bits.mantissa;

    exp_1 = float_1.f_bits.exponent;
    exp_2 = float_2.f_bits.exponent;

    printf("\nExponent of float 1 as int: %u\n", exp_1);
    printf("Exponent of float 2 as int: %u\n", exp_2);

    printf("\nMantissa of float 1 as int: %u\n", mant_1);
    printf("Mantissa of float 2 as int: %u\n", mant_2);

    /* CHECK FOR NORMALIZATION IN BOTH MANTISSA */
    /* ADD HIDDEN BIT IF NECESSARY */
    if(exp_1)
    {
        mant_1 |= (1<<23);
    }

    if(exp_2)
    {
        mant_2 |= (1<<23);
    }

    printf("\nMantissa of float 1 as int (after normalization): %u\n", mant_1);
    printf("Mantissa of float 2 as int (after normalization): %u\n", mant_2);

    /* IF THE EXPONENTS ARE DIFFERENT, SHIFT TO MATCH */
    shift_rslt = exp_1 - exp_2;
    printf("Shift result: %d", shift_rslt);
    if(shift_rslt < 0)
    {
        shift_rslt = -(shift_rslt);     // Change the sign
        mant_1 >>= (shift_rslt > 24 ? 24 : shift_rslt);
        emulated_32.f_bits.exponent = exp_2;
    }
    else
    {
        mant_2 >>= (shift_rslt > 24 ? 24 : shift_rslt);
        emulated_32.f_bits.exponent = exp_1;
    }

    /* ADD THE MANTISSA'S OF THE TWO FLOATING POINTS TOGETHER */
    printf("\n\n");
    print_bits(float_1, "     ");
    print_bits(float_2, "   + ");
    printf("    ----------------------------------------------\n");

    /* ADD THE MANTISSAS */
    mant_result = mant_1 + mant_2;

    /* CHECK FOR OVERFLOW */
    if(mant_result & (1 << 24))
    {
        mant_result >>= 1;
        emulated_32.f_bits.exponent++;
        emulated_32.f_bits.mantissa = (mant_result & ~(1 << 23));
    }
    else
    {
        emulated_32.f_bits.mantissa = (mant_result & ~(1 << 23));
    }

    /* CHECK FOR INFINITY */
    if(emulated_32.f_bits.exponent == 0xff)
    {
        emulated_32.f_bits.mantissa = 0;
    }

    /* CHECK SIGN BIT */
    emulated_32.f_bits.sign = 0;

    /* COMPUTE HARDWARE RESULT */
    hardware_32.floating_value_in_32_bits = float_1.floating_value_in_32_bits + float_2.floating_value_in_32_bits;

    print_bits(emulated_32, "     ");

    printf("\n\nEMULATED FLOATING POINT RESULT ==>>> %f ", emulated_32.floating_value_in_32_bits);
    printf("\nHARDWARE FLOATING POINT RESULT ==>>> %f ", hardware_32.floating_value_in_32_bits);

    printf("\n\n************************************************************************************\n");
    return 0;
}
