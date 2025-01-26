#ifndef lexical
#define lexical

#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

#include <string.h>

#define MAXID 20
#define MAXNUMBER 10
#define MAXSYMBOLES 40
#define MAXINSTRUCTIONS 400
#define MAXMEMORY 400
#define MAXCASE 15

// enums
typedef enum
{
    INTEGER_TOKEN,
    FLOAT_TOKEN,
    PROGRAM_TOKEN,
    BEGIN_TOKEN,
    END_TOKEN,
    CONST_TOKEN,
    VAR_TOKEN,
    IF_TOKEN,
    FUNC_TOKEN, // Fonction
    PROC_TOKEN, // Procedure
    THEN_TOKEN,
    ELSE_TOKEN,
    WHILE_TOKEN,
    DO_TOKEN,
    REPEAT_TOKEN,
    UNTIL_TOKEN,
    FOR_TOKEN,
    TO_TOKEN,
    DOWNTO_TOKEN,
    CASE_TOKEN,
    OF_TOKEN,
    WRITE_TOKEN,
    READ_TOKEN,
    SC_TOKEN,
    PT_TOKEN,
    TP_TOKEN,
    CO_TOKEN,
    LP_TOKEN,
    RP_TOKEN,
    LE_TOKEN,
    GE_TOKEN,
    LS_TOKEN,
    GT_TOKEN,
    ASG_TOKEN,
    EQUAL_TOKEN,
    DIFF_TOKEN,
    ADD_TOKEN,
    SUB_TOKEN,
    MUL_TOKEN,
    DIV_TOKEN,
    NUMBER_TOKEN,
    ARRAY_TOKEN,
    LB_TOKEN,
    RB_TOKEN,
    ID_TOKEN,
    EOF_TOKEN,
    RETURN_TOKEN
} TOKEN_CODE;

// error codes

typedef enum
{
    UNRECOGNISED_ERROR,
    MAXID_ERROR,
    MAXNUMBER_ERROR,
    PROGRAM_ERROR,
    BEGIN_ERROR,
    END_ERROR,
    IF_ERROR,
    THEN_ERROR,
    WHILE_ERROR,
    DO_ERROR,
    REPEAT_ERROR,
    UNTIL_ERROR,
    FOR_ERROR,
    CASE_ERROR,
    OF_ERROR,
    WRITE_ERROR,
    READ_ERROR,
    SC_ERROR,
    PT_ERROR,
    TP_ERROR,
    LP_ERROR,
    RP_ERROR,
    ASG_ERROR,
    EQUAL_ERROR,
    NUMBER_ERROR,
    INTEGER_ERROR,
    FLOAT_ERROR,
    ARRAY_ERROR,
    LB_ERROR,
    RB_ERROR,
    ID_ERROR,
    EOF_ERROR,
    COMMENT_ERROR,
    SYNTAX_ERROR,
    MULTIPLE_ERROR,
    UNDECLARED_ERROR,
    TPROGRAM_ERROR,
    TCONSTANT_ERROR,
    MAXSYMBOLES_ERROR,
    MAXINSTRUCTIONS_ERROR,
    MNEMONIC_ERROR,
    FUNC_ERR,
    PROC_ERR,
    ARGUMENT_ERR,
    RETURN_ERR
} ERROR_CODE;

// types of symbols

typedef enum
{
    TPROGRAM,
    TCONSTANT,
    TVARIABLE,
} SYM_TYPE;

// mnemonics

typedef enum
{
    ADD,
    SUB,
    MUL,
    DIV,
    EQL,
    NEQ,
    GTR,
    LSS,
    GEQ,
    LEQ,
    PRN,
    INN,
    INT,
    LDI,
    LDA,
    LDV,
    STO,
    BRN,
    BZE,
    HLT
} MNEMONIC;

// type
typedef enum
{
    INTEGER,
    FLOAT,
} TYPE;

// structures

// token

typedef struct
{
    TOKEN_CODE code;
    char name[MAXID];
    float value;
    TYPE type;
} TOKEN;

// symbols table entry

typedef struct
{
    char name[MAXID];
    SYM_TYPE type;
    int address;
    TYPE typeNum;
} SYM_ENTRY;

// instruction

typedef struct
{
    MNEMONIC mnemonic;
    float input;
    TYPE type;
} INSTRUCTION;

// function prototypes

char Sym_Suivant();
void Lire_Mot();
void Lire_Nombre();
void Lire_SP();
void Lire_Token();
void ignorer(); // ignore les espaces, tabulation, retour à la ligne
void ignorer_commentaire(int divToken);

void test_symbol(TOKEN_CODE token_code, ERROR_CODE error_code);
void PROGRAM();
void BLOCK();
void CONSTS();
void VARS();
void INSTS();
void INST();
void AFFEC();
void SI();
void TANTQUE();
void ECRIRE();
void LIRE();
void COND();
int COMP();
void EXPR();
int ADDSUB();
void TERM();
int MULTDIV();
void FACTOR();
void REPETER();
void POUR();
void CAS();
void FONCTION_SANS_ARGUMENTS();
void FONCTION_AVEC_ARGUMENTS();
void PROCEDURE_SANS_ARGUMENTS();
void PROCEDURE_AVEC_ARGUMENTS();
void FUNCTION();
void RETURN();

// semantic
void semantic_erreur(ERROR_CODE error_code, char *id);
int trouver_symbole(char *id);
int Adresse_Sym(char *id);
void Ajouter_Sym(char *id, SYM_TYPE sym_type, TYPE type);
void Ajouter_Program(char *id);
void Ajouter_constante(char *id);
void AJouter_variable(char *id, TYPE type);
void valider_affectation(char *id);
void valider_operation(char *id);

void generer1(MNEMONIC mnemonic);
void generer2(MNEMONIC mnemonic, float input);

void interpret_pcode();
void interpret_instruction(INSTRUCTION instruction);

void fichier_pcode();
void sauvegarder_instruction(INSTRUCTION instruction);

void charger_pcode();
void charger_instruction(char *instruction);

void show_error(ERROR_CODE error_code);
int start();

FILE *fichier;
FILE *output_file;

TOKEN token_courant;
TOKEN token_precedent;

char Car_Courant;

SYM_ENTRY sym_table[MAXSYMBOLES];
INSTRUCTION pcode[MAXINSTRUCTIONS];
int case_brn[MAXCASE];
float pile[MAXMEMORY];

int compteur_ligne = 1;
int sym_table_size = 0;
int case_brn_size = 0;
int offset = 0;
int pc = 0; // program counter
int sp = 0; // stack pointer

// error messages

const char *erreurs[] = {
    "LEXICAL ERROR: unrecognized character",
    "LEXICAL ERROR: maximum identifier length exceeded",
    "LEXICAL ERROR: maximum number length exceeded",
    "SYNTAX ERROR: PROGRAM expected",
    "SYNTAX ERROR: BEGIN expected",
    "SYNTAX ERROR: END expected",
    "SYNTAX ERROR: IF expected",
    "SYNTAX ERROR: THEN expected",
    "SYNTAX ERROR: WHILE expected",
    "SYNTAX ERROR: DO expected",
    "SYNTAX ERROR: REPEAT expected",
    "SYNTAX ERROR: UNTIL expected",
    "SYNTAX ERROR: FOR expected",
    "SYNTAX ERROR: CASE expected",
    "SYNTAX ERROR: OF expected",
    "SYNTAX ERROR: WRITE expected",
    "SYNTAX ERROR: READ expected",
    "SYNTAX ERROR: SC expected",
    "SYNTAX ERROR: PT expected",
    "SYNTAX ERROR: TP expected",
    "SYNTAX ERROR: LP expected",
    "SYNTAX ERROR: RP expected",
    "SYNTAX ERROR: ASG expected",
    "SYNTAX ERROR: EQUAL expected",
    "SYNTAX ERROR: NUMBER expected",
    "SYNTAX ERROR: INTEGER expected",
    "SYNTAX ERROR: FLOAT expected",
    "SYNTAX ERROR: ARRAY expected",
    "SYNTAX ERROR: LB_TOKEN expected",
    "SYNTAX ERROR: RB_TOKEN expected",
    "SYNTAX ERROR: ID expected",
    "SYNTAX ERROR: EOF expected",
    "SYNTAX ERROR: end of comment } expected",
    "SYNTAX ERROR: incorrect syntax",
    "SEMANTIC ERROR: identifier already declared",
    "SEMANTIC ERROR: undeclared identifier",
    "SEMANTIC ERROR: program identifier cannot be used",
    "SEMANTIC ERROR: constant cannot be assigned",
    "GENERATOR ERROR: maximum symboles size reached",
    "GENERATOR ERROR: maximum instruction size reached",
    "GENERATOR ERROR: unrecognized mnemonic",
    "FUNCTION ERROR: function token expected",
    "PROCEDURE ERROR: procedure token expected",
    "ARGUMENT ERROR: Erreur d'argument de fonction ou procedure ",
    "RETURN ERROR: return token expected"};

char Sym_Suivant()
{
    Car_Courant = fgetc(fichier);
}

void Lire_Mot()
{
    char mot[MAXID];

    int i = 0;
    mot[i++] = Car_Courant;
    Sym_Suivant();
    while (isalnum(Car_Courant) || Car_Courant == '_')
    {
        if (i < MAXID - 1)
        {
            mot[i++] = Car_Courant;
            Sym_Suivant();
        }
        else
        {
            show_error(MAXID_ERROR);
        }
    }

    // 2. Check for array index syntax: identifier[...]
    if (Car_Courant == '[')
    {
        // Temporarily null-terminate the base identifier
        char base[MAXID];
        strncpy(base, mot, i);
        base[i] = '\0';

        // 3. Skip processing if the base is "ARRAY"
        if (stricmp(base, "ARRAY") != 0)
        {
            // Read the '['
            Sym_Suivant();

            // 4. Read the index (digits inside the brackets)
            char index_str[MAXID];
            int index_len = 0;
            while (isdigit(Car_Courant))
            {
                if (index_len < MAXID - 1)
                {
                    index_str[index_len++] = Car_Courant;
                    Sym_Suivant();
                }
                else
                {
                    show_error(MAXID_ERROR);
                }
            }
            index_str[index_len] = '\0';

            // 5. Check for closing ']'
            if (Car_Courant != ']')
            {
                show_error(SYNTAX_ERROR);
            }
            Sym_Suivant(); // Consume ']'

            // 6. Convert index to integer and format the token name
            int index = atoi(index_str);
            if (index == 0)
            {
                // Case 1: Index is 0 → "tab"
                strcpy(mot, base);
                i = strlen(base);
            }
            else
            {
                // Case 2: Index ≠ 0 → "tab+5"
                snprintf(mot, MAXID, "%s+%d", base, index);
                i = strlen(mot);
            }
        }
    }

    mot[i] = '\0';
    strcpy(token_courant.name, mot);
    if (stricmp(mot, "program") == 0)
    {
        token_courant.code = PROGRAM_TOKEN;
    }
    else if (stricmp(mot, "begin") == 0)
    {
        token_courant.code = BEGIN_TOKEN;
    }
    else if (stricmp(mot, "end") == 0)
    {
        token_courant.code = END_TOKEN;
    }
    else if (stricmp(mot, "const") == 0)
    {
        token_courant.code = CONST_TOKEN;
    }
    else if (stricmp(mot, "var") == 0)
    {
        token_courant.code = VAR_TOKEN;
    }
    else if (stricmp(mot, "integer") == 0)
    {
        token_courant.code = INTEGER_TOKEN;
    }
    else if (stricmp(mot, "float") == 0)
    {
        token_courant.code = FLOAT_TOKEN;
    }
    else if (stricmp(mot, "array") == 0)
    {
        token_courant.code = ARRAY_TOKEN;
    }
    else if (stricmp(mot, "write") == 0)
    {
        token_courant.code = WRITE_TOKEN;
    }
    else if (stricmp(mot, "read") == 0)
    {
        token_courant.code = READ_TOKEN;
    }
    else if (stricmp(mot, "if") == 0)
    {
        token_courant.code = IF_TOKEN;
    }
    else if (stricmp(mot, "then") == 0)
    {
        token_courant.code = THEN_TOKEN;
    }
    else if (stricmp(mot, "else") == 0)
    {
        token_courant.code = ELSE_TOKEN;
    }
    else if (stricmp(mot, "while") == 0)
    {
        token_courant.code = WHILE_TOKEN;
    }
    else if (stricmp(mot, "do") == 0)
    {
        token_courant.code = DO_TOKEN;
    }
    else if (stricmp(mot, "repeat") == 0)
    {
        token_courant.code = REPEAT_TOKEN;
    }
    else if (stricmp(mot, "until") == 0)
    {
        token_courant.code = UNTIL_TOKEN;
    }
    else if (stricmp(mot, "for") == 0)
    {
        token_courant.code = FOR_TOKEN;
    }
    else if (stricmp(mot, "into") == 0)
    {
        token_courant.code = TO_TOKEN;
    }
    else if (stricmp(mot, "downto") == 0)
    {
        token_courant.code = DOWNTO_TOKEN;
    }
    else if (stricmp(mot, "case") == 0)
    {
        token_courant.code = CASE_TOKEN;
    }
    else if (stricmp(mot, "of") == 0)
    {
        token_courant.code = OF_TOKEN;
    }
    else if (stricmp(mot, "function") == 0)
    {
        token_courant.code = FUNC_TOKEN;
    }
    else if (stricmp(mot, "procedure") == 0)
    {
        token_courant.code = PROC_TOKEN;
    }
    else if (stricmp(mot, "return") == 0)
    {
        token_courant.code = RETURN_TOKEN;
    }

    else
    {
        token_courant.code = ID_TOKEN;
    }
}

void Lire_Nombre()
{
    char nombre[MAXNUMBER];
    int i = 0;
    int est_reel = 0;

    nombre[i++] = Car_Courant;
    Sym_Suivant();
    while (isdigit(Car_Courant))
    {
        if (i < MAXNUMBER - 1)
        {
            nombre[i++] = Car_Courant;
            Sym_Suivant();
        }
        else
        {
            show_error(MAXNUMBER_ERROR);
        }
    }
    // Vérifie le point pour l'écriture décimal
    if (Car_Courant == '.')
    {
        est_reel = 1;
        nombre[i++] = Car_Courant;
        Sym_Suivant();
        // Lire la partie fractionnel
        while (isdigit(Car_Courant))
        {
            if (i < MAXNUMBER - 1)
            {
                nombre[i++] = Car_Courant;
                Sym_Suivant();
            }
            else
            {
                show_error(MAXNUMBER_ERROR);
            }
        }
    }
    nombre[i] = '\0';
    strcpy(token_courant.name, nombre);
    if (est_reel)
        token_courant.value = atof(nombre);
    else
        token_courant.value = atoi(nombre);
    token_courant.code = est_reel ? FLOAT_TOKEN : INTEGER_TOKEN;
    token_courant.type = est_reel ? FLOAT : INTEGER;
}

void Lire_SP()
{
    switch (Car_Courant)
    {
    case ';':
        token_courant.code = SC_TOKEN;
        Sym_Suivant();
        break;
    case '.':
        token_courant.code = PT_TOKEN;
        Sym_Suivant();
        break;
    case ',':
        token_courant.code = CO_TOKEN;
        Sym_Suivant();
        break;
    case '(':
        token_courant.code = LP_TOKEN;
        Sym_Suivant();
        break;
    case ')':
        token_courant.code = RP_TOKEN;
        Sym_Suivant();
        break;
    case '<':
        Sym_Suivant();
        if (Car_Courant == '=')
        {
            token_courant.code = LE_TOKEN;
            Sym_Suivant();
        }
        else if (Car_Courant == '>')
        {
            token_courant.code = DIFF_TOKEN;
            Sym_Suivant();
        }
        else
        {
            token_courant.code = LS_TOKEN;
        }
        break;
    case '>':
        Sym_Suivant();
        if (Car_Courant == '=')
        {
            token_courant.code = GE_TOKEN;
            Sym_Suivant();
        }
        else
        {
            token_courant.code = GT_TOKEN;
        }
        break;
    case ':':
        Sym_Suivant();
        if (Car_Courant == '=')
        {
            Sym_Suivant();
            token_courant.code = ASG_TOKEN;
        }
        else
        {
            token_courant.code = TP_TOKEN;
        }
        break;
    case '=':
        token_courant.code = EQUAL_TOKEN;
        Sym_Suivant();
        break;
    case '+':
        token_courant.code = ADD_TOKEN;
        Sym_Suivant();
        break;
    case '-':
        token_courant.code = SUB_TOKEN;
        Sym_Suivant();
        break;
    case '*':
        token_courant.code = MUL_TOKEN;
        Sym_Suivant();
        break;
    case '/':
        token_courant.code = DIV_TOKEN;
        Sym_Suivant();
        break;
    case '[':
        token_courant.code = LB_TOKEN;
        Sym_Suivant();
        break;
    case ']':
        token_courant.code = RB_TOKEN;
        Sym_Suivant();
        break;
    case EOF:
        token_courant.code = EOF_TOKEN;
        Sym_Suivant();
        break;
    default:
        show_error(UNRECOGNISED_ERROR);
    }
}

void Lire_Token()
{
    token_precedent = token_courant;
    ignorer();
    if (isalpha(Car_Courant))
    {
        Lire_Mot();
    }
    else if (isdigit(Car_Courant))
    {
        Lire_Nombre();
    }
    else
    {
        Lire_SP();
    }
}
void ignorer()
{
    int divToken = 0;
    while (Car_Courant == ' ' || Car_Courant == '\n' || Car_Courant == '\t' ||
           Car_Courant == '{' || Car_Courant == '/')
    {

        // Handle newlines
        if (Car_Courant == '\n')
        {
            compteur_ligne++;
        }

        // Handle whitespace
        if (Car_Courant == ' ' || Car_Courant == '\n' || Car_Courant == '\t')
        {
            Sym_Suivant();
        }
        else
        {
            // Handle comments
            if (Car_Courant == '{')
            {
                // Block comment
                Sym_Suivant();
                while (Car_Courant != '}' && Car_Courant != EOF)
                {
                    if (Car_Courant == '\n')
                        compteur_ligne++;
                    Sym_Suivant();
                }

                if (Car_Courant == '}')
                {
                    Sym_Suivant();
                }
                else
                {
                    show_error(COMMENT_ERROR);
                }
            }
            else if (Car_Courant == '/')
            {
                // Potential line comment
                Sym_Suivant();
                if (Car_Courant == '/')
                {
                    // Line comment
                    while (Car_Courant != '\n' && Car_Courant != EOF)
                    {
                        Sym_Suivant();
                    }
                    if (Car_Courant == '\n')
                    {
                        compteur_ligne++;
                        Sym_Suivant();
                    }
                }
                else
                {
                    // Not a comment - backtrack
                    ungetc(Car_Courant, fichier);
                    Car_Courant = '/';
                    divToken = 1;
                }
            }

            // Break loop if we found standalone '/'
            if (divToken == 1)
                break;
        }
    }
}
#endif
