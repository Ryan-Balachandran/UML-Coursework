/* This is the Mic-1 linker */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>       // Added this in to remove "implicit declaration" warning

#define HEADERS     1
#define NO_HEADERS  0

typedef struct nament
{
    char   name[26];        // Name of label
    int    addr;            // line number of label
    struct nament *next;    // next name in symbol table
} SYMTABENTRY;

void add_symbol(char *symbol, int line_number);
void generate_code(int);
void print_first_pass(int);
void append_table(void);
void dump_table(void);
int get_sym_val(char *);

SYMTABENTRY *symtab = NULL;
FILE  *p1, *p2;
char  cstr_12[13];

int main(int argc, char *argv[])
{
    int  i, start, pc_offset = 0, pc = 0;
    int  linum = 0, object_file = 0, dump_tab = 0;
    int  line_number, new_pc;
    char instruction[18];
    char symbol[26];

    // if -s is included on masm command, set up to
    // dump the symbol table after the binary code
    if(argc > 1 && (strcmp(argv[1], "-s") == 0))
    {
        dump_tab = linum = 1;
    }
    else if(argc > 1 && (strcmp(argv[1], "-o") == 0))
    {
        object_file = 1;
    }

    // Execute options if they exist
    if((dump_tab == 1) | (object_file == 1))
    {
        start = 2;
    }
    else
    {
        start = 1;
    }

    // Create new file and remove name
    p1 = fopen("/tmp/passone", "w+");
    unlink("/tmp/passone");

    for(i = start; i < argc; ++i)
    {
        // Check that we can open the file
        if((p2 = fopen(argv[i], "r")) == NULL)
        {
            printf("ERROR: cannot open file %s\n", argv[i]);
            exit(2);
        }

        while(fscanf(p2, "%d %s", &pc, instruction) != EOF)
        {
            // check for end of program
            if(pc == 4096) break;

            new_pc = pc + pc_offset;
            symbol[0] = '\0';

            // line not cooked yet
            if(instruction[0] == 'U')
            {
                fscanf(p2, "%s", symbol);
            }

            fprintf(p1, "  %d  %s  %s\n", new_pc, instruction, symbol);
        }

        while(fscanf(p2, "%s %d", symbol, &line_number) != EOF)
        {
            add_symbol(symbol, line_number + pc_offset);
        }

        pc_offset = new_pc + 1;
        fclose(p2);
    }

    // if this option was on do it
    if(object_file)
    {
        print_first_pass(NO_HEADERS);
        printf("4096 x\n");
        append_table();
        return 0;
    }

    if(linum)
    {
        print_first_pass(HEADERS);
    }

    generate_code(linum);

    return 0;
}

void print_first_pass(int headers)
{
    char inbuf[81];

    if(headers == HEADERS)
    {
        printf("\n  FIRST PASS \n");
        rewind(p1);

        while(fgets(inbuf, 80, p1) != NULL)
        {
            printf("   %s", inbuf);
        }

        printf("\n  SECOND PASS \n");
    }
    else
    {
        rewind(p1);

        while(fgets(inbuf, 80, p1) != NULL)
        {
            printf("   %s", inbuf);
        }
    }
}

// rewind the temporary file and complete each unresolved
// instruction ... send binary to stdout
void generate_code(int linum)
{
    char linbuf[10];
    char instruction[18];
    int  line_number;
    int  pc, mask, sym_val, i, j, old_pc, diff;
    char symbol[26];

    line_number = old_pc = 0;
    rewind(p1);

    //sprintf(linbuf, "%5d:  ", line_number);

    while(fscanf(p1, "%d %s", &pc, instruction) != EOF)
    {
        if((diff = pc - old_pc) > 1)
        {
            for(j = 1; j < diff; j++)
            {
                //sprintf(linbuf, "%5d:  ", line_number++);
                //printf("%s1111111111111111\n", (linum ? linbuf: "\0"));
                printf("1111111111111111 \n");
            }
        }

        //sprintf(linbuf, "%5d:  ", line_number++);
        old_pc = pc;

        if(instruction[0] == 'U')
        {
            fscanf(p1, "%s", symbol);
            sym_val = get_sym_val(symbol);

            if(sym_val == -1)
            {
                //fprintf(stderr, "No symbol in symbol table: %s\n", symbol);
                printf("Error no symbol: %s\n", symbol);
                exit(3);
            }

            // contains end of instructions
            for(i = 0; i < 12; i++)
            {
                cstr_12[i] = '0';
            }

            cstr_12[12] = '\0';  // global string array
            mask = 2048;

            for(i = 0; i < 12; i++)
            {
                if(sym_val & mask)
                {
                    cstr_12[i] = '1';
                }

                mask >>= 1;
            }

            for(i = 0; i < 12; i++)
            {
                instruction[i + 5] = cstr_12[i];
            }

            //printf("%s%s\n", (linum ? linbuf: "\0"), &instruction[1]);
            printf("%s\n", &instruction[1]);
        }
        else
        {
            // instruction
            //printf("%s%s\n", (linum ? linbuf: "\0"), instruction);
            printf("%s\n", instruction);
        }
    }

    //fclose(p1);
    return;
}

// add to symbol table
void add_symbol(char *symbol, int line_number)
{
    SYMTABENTRY *newSymbol;

    newSymbol = (SYMTABENTRY *)malloc(sizeof(SYMTABENTRY));

    // Have symtab point to the newest symbol
    if(symtab == NULL)
    {
        symtab = newSymbol;
        newSymbol -> next = NULL;
    }
    else
    {
        newSymbol -> next = symtab;
        symtab = newSymbol;
    }

    strcpy(newSymbol -> name, symbol);
    newSymbol -> addr = line_number;

    return;
}

// Traverse list to print every node
void append_table()
{
    while(symtab != NULL)
    {
        printf("%s \t\t\t%d\n", symtab -> name, symtab -> addr);
        symtab = symtab -> next;
    }

    return;
}

// Return address of symbol to resolve code
// Traverse list looking for symbol
int get_sym_val(char *symbol)
{
    int cmp;
    SYMTABENTRY *list = symtab;

    while(list != NULL)
    {
        cmp = strcmp(list -> name, symbol);

        if(cmp == 0)
        {
            return list -> addr;
        }
        else
        {
            list = list -> next;
        }
    }

    return -1;
}
