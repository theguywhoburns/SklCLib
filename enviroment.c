#include <stdlib.h>

#include <util/enviroment.h>


char *arg2cmd(int argc, char** argv) {
    char *buf=NULL;
    int n = 0;
    int k, i;
    for (i=0; i <argc;++i) {
        int k=strlen(argv[i]);
        buf=( char *)realloc(buf,n+k+4);
        char *p=buf+n;
        char endq=0;
        // this is a poor mans quoting, which is good enough for anything that's not ridiculous
        if (strchr(argv[i], ' ')) {
            if (!strchr(argv[i], '\'')) {
                *p++='\'';
                endq='\'';
            } else {
                *p++='\"';
                endq='\"';
            }
        }
        memcpy(p, argv[i], k);
        p+=k;
        if (i < (argc-1)) *p++=' ';
        if (endq) *p++=endq;
        *p='\0';
        n = p-buf;
    }
    return buf;
}

bool Enviroment_Init(_Enviroment* env, int* argc, char*** argv) {
    if(env == NULL) return false;

    string* cmd = malloc(sizeof(string));
    cmd->data = arg2cmd(*argc, *argv);
    cmd->len = StringLength(cmd->str_data);
    env->CommandLine = cmd;

    string* cur_dir = malloc(sizeof(string));
    *cur_dir = StringCreateEx(*argv[0], StringLength(*argv[0]), false);
    env->CurrentDirectory = cur_dir; 

    return true;
}

void Enviroment_Shutdown(_Enviroment* env) {

}