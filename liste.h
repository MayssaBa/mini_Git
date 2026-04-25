#ifndef LIST_H
#define LIST_H


typedef struct cell {
    char* data;
    struct cell* next;
} Cell;
typedef Cell* list;


list* initList();
Cell* buildCell(char *ch);
void insertFirst(list *l,Cell *c);
Cell* listGet(list *l,int i);
Cell* searchList(list* l,char* str);
char *ctos(Cell *c);
char *ltos(list *L);
list* stol(char *s);
void ltof(list *L, char *path);
list* ftol(char *path);


#endif