#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage()
{
    fprintf(stderr, "./main <filename>\n");
    exit(-1);
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        usage();
    }

    char * readFilename = argv[1];
    FILE * readFp = fopen(readFilename, "r");

    if(readFp == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", readFilename);
    }

    char * writeFilename = "foo.c";
    FILE * writeFp = fopen(writeFilename, "w");
    if(writeFp == NULL)
    {
        fprintf(stderr, "Couldn't open file needed for writing.\n");
    }

    fprintf(writeFp, "#include <stdlib.h>\n int main() { char array[2048] = {0}; char * ptr = array; ");

    char c;
    while((c = fgetc(readFp)) != EOF)
    {
        switch(c)
        {
            case '.':
                fprintf(writeFp, "putchar(*ptr);");
                break;

            case ',':
                fprintf(writeFp, "*ptr = getchar();");
                break;

            case '+':
                fprintf(writeFp, "++*ptr;");
                break;

            case '-':
                fprintf(writeFp, "--*ptr;");
                break;

            case '[':
                fprintf(writeFp, "while(*ptr) {");
                break;

            case ']':
                fprintf(writeFp, "}");
                break;

            case '>':
                fprintf(writeFp, "++ptr;");
                break;

            case '<':
                fprintf(writeFp, "--ptr;");
                break;

            default:
                fprintf(stdout, "Ignoring token; %c\n", c);
                break;
        }
    }

    fprintf(writeFp, "}");
    fclose(writeFp);
    fclose(readFp);
    return 0;
}
