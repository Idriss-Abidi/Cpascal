#include "lexical.h"             // Section : Declararations et analyse lexicale
#include "syntax.h"              // Section : Analyse syntaxique et les fonctions de generation de pcode
#include "semantic.h"            // Section : Analyse semantique
#include "pcode_export_import.h" // L'exportation et l'importation de pcode generé => CHANGER PATH DANS CE FICHIER!!

void interpret_pcode()
{
    pc = 0;
    while (pcode[pc].mnemonic != HLT)
        interpret_instruction(pcode[pc]);
}

void interpret_instruction(INSTRUCTION instruction)
{
    int x, y, address;
    float fx, fy;
    switch (instruction.mnemonic)
    {
    case ADD:
    {
        fy = pile[sp--];
        fx = pile[sp];
        pile[sp] = fx + fy;
        pc++;
        break;
    }
    case SUB:
    {
        fy = pile[sp--];
        fx = pile[sp];
        pile[sp] = fx - fy;
        pc++;
        break;
    }
    case MUL:
    {
        fy = pile[sp--];
        fx = pile[sp];
        pile[sp] = fx * fy;
        pc++;
        break;
    }
    case DIV:
    {
        fy = pile[sp--];
        fx = pile[sp];
        pile[sp] = fx / fy;
        pc++;
        break;
    }
    case EQL:
    {
        fy = pile[sp--];
        fx = pile[sp];
        pile[sp] = (fx == fy) ? 1 : 0;
        pc++;
        break;
    }
    case NEQ:
    {
        fy = pile[sp--];
        fx = pile[sp];
        pile[sp] = (fx != fy) ? 1 : 0;
        pc++;
        break;
    }
    case GTR:
    {
        fy = pile[sp--];
        fx = pile[sp];
        pile[sp] = (fx > fy) ? 1 : 0;
        pc++;
        break;
    }
    case LSS:
    {
        fy = pile[sp--];
        fx = pile[sp];
        pile[sp] = (fx < fy) ? 1 : 0;
        pc++;
        break;
    }
    case GEQ:
    {
        fy = pile[sp--];
        fx = pile[sp];
        pile[sp] = (fx >= fy) ? 1 : 0;
        pc++;
        break;
    }
    case LEQ:
    {
        fy = pile[sp--];
        fx = pile[sp];
        pile[sp] = (fx <= fy) ? 1 : 0;
        pc++;
        break;
    }
    case PRN:
    {

        float number = pile[sp--]; // Pile stock les nombres comme des doubles

        // Print le nombre selon son type
        if (number == (int)number)
        {
            // integer
            printf("%d\n", (int)number);
        }
        else
        {
            // float
            printf("%.2f\n", number);
        }
        pc++;
        break;
    }
    case INN:
    {
        address = (int)pile[sp--];
        scanf("%f", &pile[address]);
        pc++;
        break;
    }
    case INT:
    {
        sp += (int)instruction.input;
        pc++;
        break;
    }
    case LDI:
    {
        if (instruction.type == INTEGER)
            pile[++sp] = (int)instruction.input;
        else
            pile[++sp] = instruction.input;
        // stack[++sp] = instruction.input;
        pc++;
        break;
    }
    case LDA:
    {
        pile[++sp] = (int)instruction.input;
        pc++;
        break;
    }
    case LDV:
    {
        address = (int)pile[sp];
        pile[sp] = pile[address];
        pc++;
        break;
    }
    case STO:
    {
        fy = pile[sp--];
        fx = pile[sp--];
        TYPE Ltype = sym_table[(int)fx + 1].typeNum;
        // printf("Ltype: %d\n", Ltype);
        if (Ltype == INTEGER)
            pile[(int)fx] = (int)fy;
        else
            pile[(int)fx] = fy;
        pc++;
        break;
    }
    case BRN:
    {
        pc = (int)instruction.input;
        break;
    }
    case BZE:
    {
        if (pile[sp] == 0)
            pc = (int)instruction.input;
        else
            pc++;
        break;
    }
    case HLT:
    {
        exit(0);
    }
    default:
    {
        show_error(MNEMONIC_ERROR);
    }
    }
}

// #include "importer.h" //ok#include <stdlib.h> // For exit()

void show_error(ERROR_CODE error_code)
{
    printf("\nLine %d # %s", compteur_ligne, erreurs[error_code]);
    exit(EXIT_FAILURE);
}
void pascalSimulator()
{
    Sym_Suivant();
    Lire_Token();
    PROGRAM();
}

void genererPCODE()
{
    fichier_pcode();
    charger_pcode();
    interpret_pcode();
}
int main(int argc, char *argv[])
{

    // FICHIE DE CODE TEST
    // CHANGER PATH
    const char *file = "C:\\Users\\ADMIN\\Desktop\\Cpascal\\test\\test3.p";

    // 3: INT | FLOAT OPERATIONS

    // 2: IF ELSE
    // 9: CASE

    // 5: FOR INTO/DOWNTO
    // 1 : FOR IMBRIQUE
    // 6: WHILE
    // 8: REPEAT

    /// 7: TABLEAU

    fichier = fopen(file, "r");
    if (fichier == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", file);
        exit(EXIT_FAILURE);
    }
    pascalSimulator();

    fclose(fichier);

    fichier = NULL;
    genererPCODE();

    return 0;
}