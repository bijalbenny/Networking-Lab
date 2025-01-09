#include <unistd.h>

int main() {
    char *args[] = {"./sample", NULL};
    execv(args[0], args);
}


/*
sea2@sjcet-OptiPlex-SFF-7010:~/Bijal$ gcc sample.c -o sample
csea2@sjcet-OptiPlex-SFF-7010:~/Bijal$ gcc exec.c -o exec
csea2@sjcet-OptiPlex-SFF-7010:~/Bijal$ ./exec*/
