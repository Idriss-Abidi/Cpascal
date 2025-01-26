#ifndef syntax
#define syntax
void generer1(MNEMONIC mnemonic)
{
    if (pc == MAXINSTRUCTIONS)
    {
        show_error(MAXINSTRUCTIONS_ERROR);
    }
    pc++;
    pcode[pc].mnemonic = mnemonic;
}

void generer2(MNEMONIC mnemonic, float input)
{
    if (pc == MAXINSTRUCTIONS)
    {
        show_error(MAXINSTRUCTIONS_ERROR);
    }
    pc++;
    pcode[pc].mnemonic = mnemonic;
    pcode[pc].input = input;
    // printf("%f<==\n", pcode[pc].input);
}

void generer2_LDI(MNEMONIC mnemonic, float input, TYPE type)
{
    if (pc == MAXINSTRUCTIONS)
    {
        show_error(MAXINSTRUCTIONS_ERROR);
    }
    pc++;
    pcode[pc].mnemonic = mnemonic;
    pcode[pc].type = type;
    pcode[pc].input = input;
    // printf("%f<==\n", pcode[pc].input);
}

void test_symbol(TOKEN_CODE token_code, ERROR_CODE error_code)
{
    if (token_courant.code == token_code)
    {
        Lire_Token();
    }
    else
    {
        show_error(error_code);
    }
}

void PROGRAM()
{
    test_symbol(PROGRAM_TOKEN, PROGRAM_ERROR);
    test_symbol(ID_TOKEN, ID_ERROR);
    Ajouter_Program(token_precedent.name);
    test_symbol(SC_TOKEN, SC_ERROR);
    BLOCK();
    test_symbol(PT_TOKEN, PT_ERROR);
    test_symbol(EOF_TOKEN, EOF_ERROR);
    generer1(HLT);
}

void BLOCK()
{
    CONSTS();
    VARS();
    pcode[0].mnemonic = INT;
    pcode[0].input = offset;
    INSTS();
}

void CONSTS()
{
    switch (token_courant.code)
    {
    case CONST_TOKEN:
        Lire_Token();
        test_symbol(ID_TOKEN, ID_ERROR);
        Ajouter_Sym(token_precedent.name, TCONSTANT, 1);
        generer2(LDA, Adresse_Sym(token_precedent.name));
        test_symbol(EQUAL_TOKEN, EQUAL_ERROR);
        // test_symbol(NUMBER_TOKEN, NUMBER_ERROR);
        if (token_courant.code == INTEGER_TOKEN)
        {
            test_symbol(INTEGER_TOKEN, INTEGER_ERROR);
            generer2_LDI(LDI, token_precedent.value, 0);
        }
        else
        {
            test_symbol(FLOAT_TOKEN, FLOAT_ERROR);
            generer2_LDI(LDI, token_precedent.value, 1);
        }
        // printf("==>%f\n", previous_token.value);
        // generate_two_LDI(LDI, previous_token.value, 0);
        generer1(STO);
        test_symbol(SC_TOKEN, SC_ERROR);
        while (token_courant.code == ID_TOKEN)
        {
            Lire_Token();
            Ajouter_Sym(token_precedent.name, TCONSTANT, 1);
            generer2(LDA, Adresse_Sym(token_precedent.name));
            test_symbol(EQUAL_TOKEN, EQUAL_ERROR);
            // test_symbol(NUMBER_TOKEN, NUMBER_ERROR);
            if (token_courant.code == INTEGER_TOKEN)
            {
                test_symbol(INTEGER_TOKEN, INTEGER_ERROR);
                generer2_LDI(LDI, token_precedent.value, 0);
            }
            else
            {
                test_symbol(FLOAT_TOKEN, FLOAT_ERROR);
                generer2_LDI(LDI, token_precedent.value, 1);
            }
            generer1(STO);
            test_symbol(SC_TOKEN, SC_ERROR);
        }
        break;
    case VAR_TOKEN:
        break;
    case BEGIN_TOKEN:
        break;
    default:
        show_error(SYNTAX_ERROR);
    }
}

void VARS()
{
    char tokenNom[MAXID];
    switch (token_courant.code)
    {
    case VAR_TOKEN:
        Lire_Token();
        test_symbol(ID_TOKEN, ID_ERROR);
        strcpy(tokenNom, token_precedent.name);
        test_symbol(TP_TOKEN, TP_ERROR);
        if (token_courant.code == ARRAY_TOKEN)
        {

            Lire_Token();
            test_symbol(LB_TOKEN, LB_ERROR);

            test_symbol(INTEGER_TOKEN, INTEGER_ERROR);

            int size = token_precedent.value;
            test_symbol(RB_TOKEN, RB_ERROR);
            test_symbol(OF_TOKEN, OF_ERROR);
            if (token_courant.code == INTEGER_TOKEN)
            {
                for (int i = 0; i < size; i++)
                {
                    char tokenNomIndex[MAXID];
                    if (i == 0)
                        sprintf(tokenNomIndex, "%s", tokenNom); // Format the string with an integer
                    else
                        sprintf(tokenNomIndex, "%s+%d", tokenNom, i); // Format the string with an integer
                    // printf("=>%s", tokenNomIndex);
                    Ajouter_Sym(tokenNomIndex, TVARIABLE, 0);
                }
            }
            else if (token_courant.code == FLOAT_TOKEN)
            {
                for (int i = 0; i < size; i++)
                {
                    char tokenNomIndex[MAXID];
                    if (i == 0)
                        sprintf(tokenNomIndex, "%s", tokenNom); // Format the string with an integer
                    else
                        sprintf(tokenNomIndex, "%s+%d", tokenNom, i); // Format the string with an integer

                    Ajouter_Sym(tokenNomIndex, TVARIABLE, 1);
                }
            }
            else
                show_error(SYNTAX_ERROR);
            Lire_Token();
        }
        else if (token_courant.code == INTEGER_TOKEN)
        {
            test_symbol(INTEGER_TOKEN, INTEGER_ERROR);
            Ajouter_Sym(tokenNom, TVARIABLE, 0);
        }
        else
        {
            test_symbol(FLOAT_TOKEN, FLOAT_ERROR);
            Ajouter_Sym(tokenNom, TVARIABLE, 1);
        }

        while (token_courant.code == CO_TOKEN)
        {
            Lire_Token();
            test_symbol(ID_TOKEN, ID_ERROR);
            strcpy(tokenNom, token_precedent.name);
            test_symbol(TP_TOKEN, TP_ERROR);
            if (token_courant.code == ARRAY_TOKEN)
            {

                Lire_Token();
                test_symbol(LB_TOKEN, LB_ERROR);

                test_symbol(INTEGER_TOKEN, INTEGER_ERROR);

                int size = token_precedent.value;
                test_symbol(RB_TOKEN, RB_ERROR);
                test_symbol(OF_TOKEN, OF_ERROR);
                if (token_courant.code == INTEGER_TOKEN)
                {
                    for (int i = 0; i < size; i++)
                    {
                        char tokenNomIndex[MAXID];
                        if (i == 0)
                            sprintf(tokenNomIndex, "%s", tokenNom); // Format the string with an integer
                        else
                            sprintf(tokenNomIndex, "%s+%d", tokenNom, i); // Format the string with an integer
                        // printf("=>%s", tokenNomIndex);
                        Ajouter_Sym(tokenNomIndex, TVARIABLE, 0);
                    }
                }
                else if (token_courant.code == FLOAT_TOKEN)
                {
                    for (int i = 0; i < size; i++)
                    {
                        char tokenNomIndex[MAXID];
                        if (i == 0)
                            sprintf(tokenNomIndex, "%s", tokenNom); // Format the string with an integer
                        else
                            sprintf(tokenNomIndex, "%s+%d", tokenNom, i); // Format the string with an integer

                        Ajouter_Sym(tokenNomIndex, TVARIABLE, 1);
                    }
                }
                else
                    show_error(SYNTAX_ERROR);
                Lire_Token();
            }
            else if (token_courant.code == INTEGER_TOKEN)
            {
                test_symbol(INTEGER_TOKEN, INTEGER_ERROR);
                Ajouter_Sym(tokenNom, TVARIABLE, 0);
            }
            else
            {
                test_symbol(FLOAT_TOKEN, FLOAT_ERROR);
                Ajouter_Sym(tokenNom, TVARIABLE, 1);
            }
            // add_symbol(previous_token.name, TVARIABLE);
        }
        test_symbol(SC_TOKEN, SC_ERROR);
        break;
    case BEGIN_TOKEN:
        break;
    default:
        show_error(SYNTAX_ERROR);
    }
}

void INSTS()
{
    test_symbol(BEGIN_TOKEN, BEGIN_ERROR);
    INST();
    while (token_courant.code == SC_TOKEN)
    {
        Lire_Token();
        INST();
    }
    test_symbol(END_TOKEN, END_ERROR);
}

void INST()
{
    switch (token_courant.code)
    {
    case BEGIN_TOKEN:
        INSTS();
        break;
    case ID_TOKEN:
        AFFEC();
        break;
    case IF_TOKEN:
        SI();
        break;
    case WHILE_TOKEN:
        TANTQUE();
        break;
    case WRITE_TOKEN:
        ECRIRE();
        break;
    case READ_TOKEN:
        LIRE();
        break;
    case REPEAT_TOKEN:
        REPETER();
        break;
    case FOR_TOKEN:
        POUR();
        break;
    case CASE_TOKEN:
        CAS();
        break;
    case SC_TOKEN:
        break;
    case END_TOKEN:
        break;
    case ELSE_TOKEN:
        break;
    case UNTIL_TOKEN:
        break;
    case INTEGER_TOKEN:
        break;
    case FLOAT_TOKEN:
        break;
    case NUMBER_TOKEN:
        break;
    default:
        show_error(SYNTAX_ERROR);
    }
}

void AFFEC()
{
    // int mnemonic;
    valider_affectation(token_courant.name);
    int index = trouver_symbole(token_courant.name);
    // TYPE Ltype = sym_table[index].type;
    test_symbol(ID_TOKEN, ID_ERROR);
    generer2(LDA, Adresse_Sym(token_precedent.name));
    test_symbol(ASG_TOKEN, ASG_ERROR);
    EXPR();
    generer1(STO);
}

void SI()
{
    int bze_index, brn_index;
    test_symbol(IF_TOKEN, IF_ERROR);
    COND();
    generer1(BZE);
    bze_index = pc;
    test_symbol(THEN_TOKEN, THEN_ERROR);
    INST();
    generer2(BRN, pc + 2);
    brn_index = pc;
    pcode[bze_index].input = pc + 1;
    switch (token_courant.code)
    {
    case ELSE_TOKEN:
        Lire_Token();
        INST();
        pcode[brn_index].input = pc + 1;
        break;
    case SC_TOKEN:
        break;
    case END_TOKEN:
        break;
    case UNTIL_TOKEN:
        break;
    case NUMBER_TOKEN:
        break;
    default:
        show_error(SYNTAX_ERROR);
    }
}

void TANTQUE()
{
    int while_index = pc + 1, bze_index;
    test_symbol(WHILE_TOKEN, WHILE_ERROR);
    COND();
    generer1(BZE);
    bze_index = pc;
    test_symbol(DO_TOKEN, DO_ERROR);
    INST();
    generer2(BRN, while_index);
    pcode[bze_index].input = pc + 1;
}

void ECRIRE()
{
    test_symbol(WRITE_TOKEN, WRITE_ERROR);
    test_symbol(LP_TOKEN, LP_ERROR);
    EXPR();
    generer1(PRN);
    while (token_courant.code == CO_TOKEN)
    {
        Lire_Token();
        EXPR();
        generer1(PRN);
    }
    test_symbol(RP_TOKEN, RP_ERROR);
}

void LIRE()
{
    test_symbol(READ_TOKEN, READ_ERROR);
    test_symbol(LP_TOKEN, LP_ERROR);
    test_symbol(ID_TOKEN, ID_ERROR);
    valider_affectation(token_precedent.name);
    generer2(LDA, Adresse_Sym(token_precedent.name));
    generer1(INN);
    while (token_courant.code == CO_TOKEN)
    {
        Lire_Token();
        test_symbol(ID_TOKEN, ID_ERROR);
        valider_affectation(token_precedent.name);
        generer2(LDA, Adresse_Sym(token_precedent.name));
        generer1(INN);
    }
    test_symbol(RP_TOKEN, RP_ERROR);
}

void COND()
{
    int mnemonic;
    EXPR();
    mnemonic = COMP();
    EXPR();
    generer1(mnemonic);
}

int COMP()
{
    switch (token_courant.code)
    {
    case EQUAL_TOKEN:
        Lire_Token();
        return EQL;
    case DIFF_TOKEN:
        Lire_Token();
        return NEQ;
    case LS_TOKEN:
        Lire_Token();
        return LSS;
    case GT_TOKEN:
        Lire_Token();
        return GTR;
    case LE_TOKEN:
        Lire_Token();
        return LEQ;
    case GE_TOKEN:
        Lire_Token();
        return GEQ;
    default:
        show_error(SYNTAX_ERROR);
    }
}

void EXPR()
{

    int mnemonic;
    TERM();
    while (token_courant.code == ADD_TOKEN || token_courant.code == SUB_TOKEN)
    {
        mnemonic = ADDSUB();
        TERM();
        generer1(mnemonic);
    }
}

int ADDSUB()
{
    switch (token_courant.code)
    {
    case ADD_TOKEN:
        Lire_Token();
        return ADD;
    case SUB_TOKEN:
        Lire_Token();
        return SUB;
    default:
        show_error(SYNTAX_ERROR);
    }
}

void TERM()
{
    int mnemonic;
    FACTOR();
    while (token_courant.code == MUL_TOKEN || token_courant.code == DIV_TOKEN)
    {
        mnemonic = MULTDIV();
        FACTOR();
        generer1(mnemonic);
    }
}

int MULTDIV()
{
    switch (token_courant.code)
    {
    case MUL_TOKEN:
        Lire_Token();
        return MUL;
    case DIV_TOKEN:
        Lire_Token();
        return DIV;
    default:
        show_error(SYNTAX_ERROR);
    }
}

void FACTOR()
{
    switch (token_courant.code)
    {
    case ID_TOKEN:
        valider_operation(token_courant.name);

        generer2(LDA, Adresse_Sym(token_courant.name));
        generer1(LDV);
        Lire_Token();
        break;
    case INTEGER_TOKEN:
        generer2_LDI(LDI, token_courant.value, 0);
        Lire_Token();
        break;
    case FLOAT_TOKEN:
        generer2_LDI(LDI, token_courant.value, 1);
        Lire_Token();
        break;
    case NUMBER_TOKEN:
        generer2(LDI, token_courant.value);
        Lire_Token();
        break;
    case LP_TOKEN:
        Lire_Token();
        EXPR();
        test_symbol(RP_TOKEN, RP_ERROR);
        break;
    default:
        show_error(SYNTAX_ERROR);
    }
}

void REPETER()
{
    int repeatIndex = pc + 1;
    test_symbol(REPEAT_TOKEN, REPEAT_ERROR);
    INST();
    test_symbol(UNTIL_TOKEN, UNTIL_ERROR);
    COND();
    generer2(BZE, repeatIndex);
}

void POUR()
{
    int type, address, for_index, bze_index;
    test_symbol(FOR_TOKEN, FOR_ERROR);
    test_symbol(ID_TOKEN, ID_ERROR);
    valider_affectation(token_precedent.name);
    address = Adresse_Sym(token_precedent.name);
    generer2(LDA, address);
    test_symbol(ASG_TOKEN, ASG_ERROR);
    if (token_courant.code == INTEGER_TOKEN)
        test_symbol(INTEGER_TOKEN, INTEGER_ERROR);
    else if (token_courant.code == FLOAT_TOKEN)
        test_symbol(FLOAT_TOKEN, FLOAT_ERROR);
    else
        test_symbol(ID_TOKEN, ID_ERROR);
    generer2_LDI(LDI, token_precedent.value, 0);
    generer1(STO);
    switch (token_courant.code)
    {
    case TO_TOKEN:
        type = TO_TOKEN;
        Lire_Token();
        break;
    case DOWNTO_TOKEN:
        type = DOWNTO_TOKEN;
        Lire_Token();
        break;
    default:
        show_error(SYNTAX_ERROR);
    }
    if (token_courant.code == INTEGER_TOKEN)
        test_symbol(INTEGER_TOKEN, INTEGER_ERROR);
    else
        test_symbol(FLOAT_TOKEN, FLOAT_ERROR);
    for_index = pc + 1;
    generer2(LDA, address);
    generer1(LDV);
    generer2_LDI(LDI, token_precedent.value, 0);
    // generer1(LEQ);
    if (type == TO_TOKEN)
        generer1(LEQ);
    else
        generer1(GEQ);
    generer1(BZE);
    bze_index = pc;
    test_symbol(DO_TOKEN, DO_ERROR);
    INST();
    generer2(LDA, address);
    generer2(LDA, address);
    generer1(LDV);
    generer2_LDI(LDI, 1, 0);
    if (type == TO_TOKEN)
        generer1(ADD);
    else
        generer1(SUB);
    generer1(STO);
    generer2(BRN, for_index);
    pcode[bze_index].input = pc + 1;
}

void CAS()
{
    int i, bze_index, address;
    test_symbol(CASE_TOKEN, CASE_ERROR);
    test_symbol(ID_TOKEN, ID_ERROR);
    address = Adresse_Sym(token_precedent.name);
    generer2(LDA, address);
    generer1(LDV);
    valider_operation(token_precedent.name);
    test_symbol(OF_TOKEN, OF_ERROR);
    if (token_courant.code == INTEGER_TOKEN)
    {
        test_symbol(INTEGER_TOKEN, INTEGER_ERROR);
        generer2_LDI(LDI, token_precedent.value, 0);
    }
    else
    {
        test_symbol(FLOAT_TOKEN, FLOAT_ERROR);
        generer2_LDI(LDI, token_precedent.value, 1);
    }
    generer1(EQL);
    generer1(BZE);
    bze_index = pc;
    test_symbol(TP_TOKEN, TP_ERROR);
    INST();
    generer1(BRN);
    case_brn[case_brn_size++] = pc;
    pcode[bze_index].input = pc + 1;
    while (token_courant.code == INTEGER_TOKEN || token_courant.code == FLOAT_TOKEN)
    {
        generer2(LDA, address);
        generer1(LDV);
        // generate_two(LDI, current_token.value);
        if (token_courant.code == INTEGER_TOKEN)
        {
            generer2_LDI(LDI, token_courant.value, 0);
        }
        else
        {
            generer2_LDI(LDI, token_courant.value, 1);
        }
        generer1(EQL);
        generer1(BZE);
        bze_index = pc;
        Lire_Token();
        test_symbol(TP_TOKEN, TP_ERROR);
        INST();
        generer1(BRN);
        case_brn[case_brn_size++] = pc;
        pcode[bze_index].input = pc + 1;
    }
    switch (token_courant.code)
    {
    case ELSE_TOKEN:
        Lire_Token();
        INST();
        break;
    case END_TOKEN:
        break;
    default:
        show_error(SYNTAX_ERROR);
    }
    for (i = 0; i < case_brn_size; i++)
    {
        pcode[case_brn[i]].input = pc + 1;
    };
    test_symbol(END_TOKEN, END_ERROR);
}

#endif
