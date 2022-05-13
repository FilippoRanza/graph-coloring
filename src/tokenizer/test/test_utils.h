char* make_modifiable_string(char* str) {

    int len = strlen(str);
    char* output = malloc(len + 1);
    if(output == NULL)
        return NULL;

    strcpy(output, str);
    return output;
}