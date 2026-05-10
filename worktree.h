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
WorkTree *stwt(char *s);
int wttf(WorkTree *wt, char *file);
WorkTree *ftwt(char *file);
char* blobWorkTree(WorkTree* wt);
int getChmod(const char *path);
void setMode(int mode, char* path);
char* saveWorkTree(WorkTree* wt, char* path);



#endif