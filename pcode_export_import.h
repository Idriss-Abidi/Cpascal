#ifndef pcode_export_import
#define pcode_export_import
// EXPORT
char *path = "C:\\Users\\ADMIN\\Desktop\\Cpascal\\test\\pcode.txt";

void fichier_pcode() //
{
    output_file = fopen(path, "w+");
    if (output_file == NULL)
    {
        perror("error opening file");
    }
    int i;
    for (i = 0; i <= pc; i++)
    {
        sauvegarder_instruction(pcode[i]);
    }
    fclose(output_file);
}

void sauvegarder_instruction(INSTRUCTION instruction)
{
    switch (instruction.mnemonic)
    {
    case ADD:
        fprintf(output_file, "%s \n", "ADD");
        break;
    case SUB:
        fprintf(output_file, "%s \n", "SUB");
        break;
    case MUL:
        fprintf(output_file, "%s \n", "MUL");
        break;
    case DIV:
        fprintf(output_file, "%s \n", "DIV");
        break;
    case EQL:
        fprintf(output_file, "%s \n", "EQL");
        break;
    case NEQ:
        fprintf(output_file, "%s \n", "NEQ");
        break;
    case GTR:
        fprintf(output_file, "%s \n", "GTR");
        break;
    case LSS:
        fprintf(output_file, "%s \n", "LSS");
        break;
    case GEQ:
        fprintf(output_file, "%s \n", "GEQ");
        break;
    case LEQ:
        fprintf(output_file, "%s \n", "LEQ");
        break;
    case PRN:
        fprintf(output_file, "%s \n", "PRN");
        break;
    case INN:
        fprintf(output_file, "%s \n", "INN");
        break;
    case INT:
        fprintf(output_file, "%s \t %d \n", "INT", (int)instruction.input);
        break;
    case LDI:
        if (instruction.type == INTEGER)
            fprintf(output_file, "%s \t %d \n", "LDI", (int)instruction.input);
        else
            fprintf(output_file, "%s \t %.2f \n", "LDI", instruction.input);
        break;
    case LDA:
        fprintf(output_file, "%s \t %d \n", "LDA", (int)instruction.input);
        break;
    case LDV:
        fprintf(output_file, "%s \n", "LDV");
        break;
    case STO:
        fprintf(output_file, "%s \n", "STO");
        break;
    case BRN:
        fprintf(output_file, "%s \t %d \n", "BRN", (int)instruction.input);
        break;
    case BZE:
        fprintf(output_file, "%s \t %d \n", "BZE", (int)instruction.input);
        break;
    case HLT:
        fprintf(output_file, "%s \n", "HLT");
        break;
    default:
        show_error(MNEMONIC_ERROR);
    }
}

// IMPORT
void charger_pcode()
{
    fichier = fopen(path, "r");
    if (fichier == NULL)
    {
        perror("error opening file");
        return;
    }
    pc = 0;
    char instruction[10];
    while (fscanf(fichier, "%s", instruction) != EOF)
    {
        if (pc >= MAXINSTRUCTIONS)
        {
            show_error(MAXINSTRUCTIONS_ERROR);
        }
        charger_instruction(instruction);
        pc++;
    }
    pc--;
    fclose(fichier);
}

void charger_instruction(char *instruction)
{
    int int_input;
    float float_input;
    char input_str[MAXID];
    if (strcmp(instruction, "ADD") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = ADD;
    }
    else if (strcmp(instruction, "SUB") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = SUB;
    }
    else if (strcmp(instruction, "MUL") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = MUL;
    }
    else if (strcmp(instruction, "DIV") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = DIV;
    }
    else if (strcmp(instruction, "EQL") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = EQL;
    }
    else if (strcmp(instruction, "NEQ") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = NEQ;
    }
    else if (strcmp(instruction, "GTR") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = GTR;
    }
    else if (strcmp(instruction, "LSS") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = LSS;
    }
    else if (strcmp(instruction, "GEQ") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = GEQ;
    }
    else if (strcmp(instruction, "LEQ") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = LEQ;
    }
    else if (strcmp(instruction, "PRN") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = PRN;
    }
    else if (strcmp(instruction, "INN") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = INN;
    }
    else if (strcmp(instruction, "INT") == 0)
    {
        pcode[pc].mnemonic = INT;
        fscanf(fichier, " \t %d \n", &int_input);
        pcode[pc].input = int_input;
    }
    else if (strcmp(instruction, "LDI") == 0)
    {
        pcode[pc].mnemonic = LDI;

        // Read the input as a string
        fscanf(fichier, " %s", input_str);

        // Check if the input is a float (contains '.')
        if (strchr(input_str, '.') != NULL)
        {
            // Input is a float
            float_input = atof(input_str);
            pcode[pc].input = float_input; // Store as double
            pcode[pc].type = FLOAT;
        }
        else
        {
            // Input is an integer
            int_input = atoi(input_str);
            pcode[pc].input = (double)int_input; // Store as double (cast from int)
            pcode[pc].type = INTEGER;
        }
    }
    else if (strcmp(instruction, "LDA") == 0)
    {
        pcode[pc].mnemonic = LDA;
        fscanf(fichier, " \t %d \n", &int_input);
        pcode[pc].input = int_input;
    }
    else if (strcmp(instruction, "LDV") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = LDV;
    }
    else if (strcmp(instruction, "STO") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = STO;
    }
    else if (strcmp(instruction, "BRN") == 0)
    {
        pcode[pc].mnemonic = BRN;
        fscanf(fichier, " \t %d \n", &int_input);
        pcode[pc].input = int_input;
    }
    else if (strcmp(instruction, "BZE") == 0)
    {
        pcode[pc].mnemonic = BZE;
        fscanf(fichier, " \t %d \n", &int_input);
        pcode[pc].input = int_input;
    }
    else if (strcmp(instruction, "HLT") == 0)
    {
        fscanf(fichier, " \n");
        pcode[pc].mnemonic = HLT;
    }
    else
    {
        // printf("TEST ETST %u %f", pcode[pc].mnemonic, pcode[pc].input);

        show_error(MNEMONIC_ERROR);
    }
}

#endif
