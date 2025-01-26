#ifndef semantic
#define semantic

void semantic_erreur(ERROR_CODE error_code, char *id)
{
    printf("\n Erreur Semantique : ligne %d - %s / %s", compteur_ligne, erreurs[error_code], id);
    exit(1);
}

int trouver_symbole(char *id)
{
    int i;
    for (i = 0; i < sym_table_size; i++)
    {
        if (strcmp(sym_table[i].name, id) == 0)
        {
            return i;
        }
    }
    return -1;
}

int Adresse_Sym(char *id)
{
    int index = trouver_symbole(id);
    return sym_table[index].address;
}

void Ajouter_Sym(char *id, SYM_TYPE sym_type, TYPE type)
{
    if (sym_table_size < 20)
    {
        switch (sym_type)
        {
        case TPROGRAM:
            Ajouter_Program(id);
            break;
        case TCONSTANT:
            Ajouter_constante(id);
            break;
        case TVARIABLE:
            AJouter_variable(id, type);
        }
    }
    else
    {
        show_error(MAXSYMBOLES_ERROR);
    }
}

void Ajouter_Program(char *id)
{
    sym_table[sym_table_size].type = TPROGRAM;
    strcpy(sym_table[sym_table_size].name, id);
    sym_table_size++;
}

void Ajouter_constante(char *id)
{
    if (trouver_symbole(id) == -1)
    {
        sym_table[sym_table_size].type = TCONSTANT;
        strcpy(sym_table[sym_table_size].name, id);
        sym_table[sym_table_size].address = offset++;
        sym_table[sym_table_size].typeNum = 1;
        sym_table_size++;
    }
    else
    {
        semantic_erreur(MULTIPLE_ERROR, id);
    }
}

void AJouter_variable(char *id, TYPE type)
{
    if (trouver_symbole(id) == -1)
    {
        sym_table[sym_table_size].type = TVARIABLE;
        strcpy(sym_table[sym_table_size].name, id);
        sym_table[sym_table_size].address = offset++;
        sym_table[sym_table_size].typeNum = type;
        sym_table_size++;
    }
    else
    {
        semantic_erreur(MULTIPLE_ERROR, id);
    }
}

void valider_affectation(char *id)
{
    int index = trouver_symbole(id);
    if (index != -1)
    {
        // SYM_TYPE sym_type = sym_table[index].type;
        switch (sym_table[index].type)
        {
        case TVARIABLE:
            break;
        case TCONSTANT:
            semantic_erreur(TCONSTANT_ERROR, id);
            break;
        case TPROGRAM:
            semantic_erreur(TPROGRAM_ERROR, id);
        }
    }
    else
    {
        semantic_erreur(UNDECLARED_ERROR, id);
    }
}

void valider_operation(char *id)
{
    int index = trouver_symbole(id);
    if (index != -1)
    {
        SYM_TYPE sym_type = sym_table[index].type;
        if (sym_type == TPROGRAM)
        {
            semantic_erreur(TPROGRAM_ERROR, id);
        }
    }
    else
    {
        semantic_erreur(UNDECLARED_ERROR, id);
    }
}

#endif
