#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "worktree.h"
#include "workfile.h"
#include "file.h"
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <libgen.h> 




WorkTree* initWorkTree(){
    WorkTree* wt=(WorkTree*)malloc(sizeof(WorkTree));
    wt->tab=(WorkFile*)malloc(SIZE*sizeof(WorkFile));
    wt->size=SIZE;
    wt->n=0;
    return wt;
}
int inWorkTree(WorkTree* wt, char* name){
    int i=0;
    while(i!=wt->n){
        if(strcmp(wt->tab[i].name,name)==0){
            return i;
        }else{
            i++;
        }
    }
    return -1;
}

int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode) {
    if(inWorkTree(wt,name)!=-1){return 0;}
    if(wt->n==SIZE){return 0;}
    
    wt->tab[wt->n].name=name;
    wt->tab[wt->n].hash=hash;
    wt->tab[wt->n].mode=mode;
    wt->n++;
    return 1;

}


char *wtts(WorkTree *wt)
{
    if (wt==NULL || wt->n==0)
        return NULL;
    int total=0;
    for (int i=0; i< wt->n; i++)
    {
        char* chWf=wfts(&(wt->tab[i]));
        total+=strlen(chWf)+1;
        free(chWf);
    }
    char* res=malloc(total+1);
    res[0]='\0';
    for (int i=0; i < wt->n; i++)
    {
        char *chWf=wfts(&(wt->tab[i]));
        strcat(res, chWf);
        strcat(res, "\n");
        free(chWf);
    }

    return res;
}

WorkTree *stwt(char *s)
{
    if(s==NULL)
        return NULL;

    WorkTree* wt=initWorkTree();
    char* copy=strdup(s);
    char* saveptr; //besh thot fih win you9ef fe kol mara (strtok tetfkr wahdha donc tnjmsh testaamelha martin 5ater tthaya3 el pointeur louel)
    char* line=strtok_r(copy,"\n",&saveptr);
    while(line!=NULL)
    {
        WorkFile *wf=stwf(line);
        appendWorkTree(wt, wf->name, wf->hash, wf->mode);
        line=strtok_r(NULL,"\n",&saveptr);
    }
    free(copy);
    return wt;
}

int wttf(WorkTree *wt, char *file)
{
    if (wt==NULL)
        return 0;
    FILE *f=fopen(file, "w");
    if (f==NULL)
        return 0;
    char *chWt=wtts(wt);
    if(chWt!=NULL)
    {
        fprintf(f, "%s", chWt);
        free(chWt);
    }
    fclose(f);
    return 1;
}

WorkTree* ftwt(char *file)
{
    FILE *f=fopen(file, "r");
    if (f==NULL)
        return NULL;

    char line[256];
    char *txt=malloc(1);
    txt[0]='\0';
    while(fgets(line,sizeof(line),f)){
        txt=realloc(txt,strlen(txt)+strlen(line)+1);
        strcat(txt,line);
    }
    fclose(f);

    WorkTree *wt=stwt(txt);
    free(txt);

    return wt;
}

char* blobWorkTree(WorkTree* wt){
    if(wt==NULL){return NULL;}
    static char fname[]="/tmp/myfileXXXXXX";
    int fd=mkstemp(fname);
    // printf("%d file tmp!!!!! %s\n",fd,fname);
    if (fd==-1)
        return NULL;
    
    close(fd);
    int x=wttf(wt,fname);
    // printf("%d wttf te5demmmm\n",x);
    if(x==0){
        return NULL;
    }
    char* hashtmp=sha256file(fname);
    if(hashtmp==NULL)
        return NULL;
    char* path=hashToPath(hashtmp);
    if(path==NULL){
        free(hashtmp);
        return NULL;
    }
    char *patht=malloc(strlen(path) + 3);
    sprintf(patht, "%s.t", path);
    int len=strlen("mkdir -p ")+strlen(patht)+1; //tehseb long taa cmd besh taamlelha malloc besh tekteb fiha el commande w tnjm testaamel variable (path)****
    char *cmd=malloc(len);
    sprintf(cmd,"mkdir -p %.*s",2,patht); //pour creer le folder xy/ => prendre les 2 premieres caracteres**
    system(cmd);
    free(cmd);

    cp(patht,fname);

    remove(fname);
    free(patht);

    return hashtmp;

}

int getChmod(const char *path){
    struct stat ret;
    if (stat(path, &ret)==-1) {
        return -1;
    }
    return
        (ret.st_mode & S_IRUSR)|(ret.st_mode & S_IWUSR)|(ret.st_mode & S_IXUSR)|/*owner*/
        (ret.st_mode & S_IRGRP)|(ret.st_mode & S_IWGRP)|(ret.st_mode & S_IXGRP)|/*group*/
        (ret.st_mode & S_IROTH)|(ret.st_mode & S_IWOTH)|(ret.st_mode & S_IXOTH);/*other*/
}
void setMode(int mode, char* path){
    char buff [100];
    sprintf(buff, "chmod %d %s", mode, path);
    system(buff);
}

char *saveWorkTree(WorkTree *wt, char *path)
{
    if(path==NULL || wt==NULL){return NULL;}

    for(int i=0;i<wt->n;i++){
        WorkFile* wf=&(wt->tab[i]);
        // printf("Recherche fichier: %s/%s\n", path, wf->name);

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath),"%s/%s",path, wf->name);

        if(listdir(fullpath)!=NULL){
            list* lwt=listdir(fullpath);
            WorkTree* newWt=initWorkTree();
            Cell *c=*lwt;
            while(c!=NULL){
                appendWorkTree(newWt,c->data,NULL,0);
                c=c->next;
            }
            char* hashWT=saveWorkTree(newWt,fullpath);
            wf->hash=hashWT;
            wf->mode=getChmod(fullpath);
        }else{
            blobFile(fullpath);
            wf->hash=strdup(sha256file(fullpath));
            wf->mode=getChmod(fullpath);
        }

    }
    return blobWorkTree(wt);
}







