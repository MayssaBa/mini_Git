#ifndef WORKFILE_H
#define WORKFILE_H


typedef struct {
    char* name;
    char* hash;
    int mode;
}WorkFile;


WorkFile* createWorkFile(char* name);
char* wfts(WorkFile* wf);
WorkFile* stwf(char* ch);



#endif