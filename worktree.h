#ifndef WORKTREE_H
#define WORKTREE_H

#define SIZE 30



typedef struct {
    char* name;
    char* hash;
    int mode;
}WorkFile;

typedef struct {
    WorkFile* tab;
    int size;
    int n;
}WorkTree;

WorkFile* createWorkFile(char* name);
char* wfts(WorkFile* wf);
WorkFile* stwf(char* ch);
WorkTree* initWorkTree();
int inWorkTree(WorkTree* wt, char* name);
int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode);
char* wtts(WorkTree* wt) ;


#endif