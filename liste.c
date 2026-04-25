#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"


list* initList(){
    list *l=(list*)malloc(sizeof(list));
    *l=NULL;
    return l;
}
Cell* buildCell(char *ch){
    Cell *c=(Cell*)malloc(sizeof(Cell));
    c->data=strdup(ch); // hetha besh baad fel stol matfas5sh el ch fel free; t7ot copie
    c->next=NULL;
    return c;
}
void insertFirst(list *l,Cell *c){
    c->next=*l;
    *l=c;
}
char *ctos(Cell *c)
{
    if(c==NULL)
        return NULL;
    return c->data;
}

char* ltos(list* L) //L est un pointeur sur le pointeur liste qui pointe sur cell
{
    if(L==NULL || *L==NULL) //L est l’adresse d’un pointeur de liste (Cell)* /////// *L est la valeur stockée dans L=>adr de premier elt
        return NULL;
    int total=0;
    Cell *p=*L;
    while (p!=NULL)
    {
        total+=strlen(p->data)+1;
        p=p->next;
    }
    char* result=(char*)malloc(sizeof(char)*(total+1));
    result[0]='\0';
    p=*L;
    while(p!=NULL)
    {
        strcat(result,ctos(p));
        if(p->next != NULL)
            strcat(result, "|");
        p=p->next;
    }
    return result;
}


Cell* listGet(list *l,int i){
    int j=0;
    Cell *p=*l;
    while(j<i && p!=NULL){
        p=p->next;
        j++;
    }
    return p;
}
Cell* searchList(list* l,char* str){
    if (l==NULL || *l==NULL) {
        return NULL;
    }
    Cell *p=*l;
    while(p!=NULL){
        if(strcmp(p->data,str)==0){
            return p;
        }
        p=p->next;
    }
    return NULL;
}

list* stol(char *s)
{
    if (s==NULL)
        return NULL;

    list *L=initList();
    char *copy=strdup(s);
    char *token=strtok(copy, "|"); // y9assam el chaine hasb el sep: exple: "f4\0f5\0f6" 

    Cell *p=NULL;

    while (token!=NULL)
    {
        Cell *c=buildCell(token);

        if (*L==NULL)
        {
            *L=c;
            p=c;
        }
        else
        {
            p->next=c;
            p=c;
        }

        token = strtok(NULL, "|");//token=f4 alouel puis a chaque fois t9adem hata twali NULL : fin chaine
    }

    free(copy);
    return L;
}

void ltof(list *L, char *path)
{
    if (L == NULL || *L == NULL)
        return;

    FILE *f = fopen(path, "w");
    if (f == NULL)
        return;

    Cell *p = *L;

    while (p != NULL)
    {
        fprintf(f, "%s", p->data);
        if (p->next != NULL)
            fprintf(f, "|");
        p = p->next;
    }

    fclose(f);
}

list* ftol(char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
        return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buffer = (char *)malloc(size + 1);
    fread(buffer, 1, size, f);
    buffer[size] = '\0';

    fclose(f);

    list *L = stol(buffer);
    free(buffer);

    return L;
}








