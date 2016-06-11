#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage()
{
    fprintf(stderr, "./main <filename>\n");
    exit(-1);
}

void parse(char * text)
{
    char * filename = "foo.c";
    FILE * fp = fopen(filename, "w");
    if(fp == NULL)
    {
        fprintf(stderr, "Couldn't open file needed for writing.\n");
    }

    fprintf(fp, "#include <stdlib.h>\n int main() { char array[2048] = {0}; char * ptr = array; ");

    int i;
    for(i = 0; i < strlen(text); i++)
    {
        switch(text[i])
        {
            case '.':
                fprintf(fp, "putchar(*ptr);");
                break;

            case ',':
                fprintf(fp, "*ptr = getchar();");
                break;

            case '+':
                fprintf(fp, "++*ptr;");
                break;

            case '-':
                fprintf(fp, "--*ptr;");
                break;

            case '[':
                fprintf(fp, "while(*ptr) {");
                break;

            case ']':
                fprintf(fp, "}");
                break;

            case '>':
                fprintf(fp, "++ptr;");
                break;

            case '<':
                fprintf(fp, "--ptr;");
                break;

            default:
                fprintf(stdout, "Ignoring token; %c\n", text[i]);
                break;
        }
    }

    fprintf(fp, "}");
    fclose(fp);
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        usage();
    }

    char * filename = argv[1];
    FILE * fp = fopen(filename, "r");

    if(fp == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", filename);
    }

    /* Get file size */
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    char * buffer = (char *)malloc(sizeof(char) * fileSize);
    if(buffer == NULL)
    {
        fprintf(stderr, "Could not allocate the needed memory; %li bytes\n", fileSize);
    }

    size_t result = fread(buffer, 1, fileSize, fp);
    if(result != fileSize)
    {
        fprintf(stderr, "Something went wrong when reading the file.\n");
    }

    parse(buffer);
    fclose(fp);
    free(buffer);
    return 0;
}
