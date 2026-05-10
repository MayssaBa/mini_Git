#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "file.h"
#include <dirent.h>




int hashFile(char *source, char *dest)
{
    char cmd[500];
    sprintf(cmd, "sha256sum %s > %s",source,dest);
    return system(cmd);
}

char* sha256file(char* file){
    static char template[]="/tmp/myfileXXXXXX";
    char fname [1000];
    strcpy(fname , template);
    int fd=mkstemp(fname); //pour creer un fich temp=>nhoto fih rl hash n'affichiwha puis supp
    if (fd==-1)
        return NULL;
    char cmd[500];
    snprintf(cmd, sizeof(cmd),"sha256sum %s > %s",file,fname);
    close(fd); //rq: mkstemp: cree et ouvre le fich temp=> il faut le close
    system(cmd);
    FILE* f=fopen(fname,"r");
    if(!f)
        return NULL;
    char* hash=malloc(65); //c'est car on va le retourner=>donc un pointeur qui alloc pour 64 caracteres +/0: rq: dans main il faut le free!!!
    fscanf(f,"%64s",hash);
    fclose(f);
    remove(fname);

    return hash;

}

list* listdir(char* root_dir){
    DIR *dp=opendir(root_dir);
    struct dirent *ep;
    if (dp!=NULL)
    {
        list* l=initList();
        Cell *p=NULL;
        while((ep=readdir(dp))!= NULL)
        {   
            if (strcmp(ep->d_name, ".")==0 || strcmp(ep->d_name, "..")==0)
                continue;

            Cell *c=buildCell(ep->d_name);
            if(*l==NULL){
                *l=c;
                p=c;
            }
            else{
                p->next=c;
                p=p->next;

            }
        }
        closedir(dp);
        return l;
    }
    return NULL;
    
}

int file_exists(char *file){
    if(file==NULL){
        return 0;
    }
    list* listFich=listdir(".");
    if(listFich==NULL){
        return 0;
    }
    int res=searchList(listFich, file);
    free(listFich);

    return res;
}

void cp(char *to, char *from){
    if (!file_exists(from)) {
        printf("Le fichier source n'existe pas\n");
        return;
    }
    FILE* f=fopen(from,"r"); //rq: r ==>read => pour lire le fich src
    FILE* fto=fopen(to,"w"); //rq: w ==>write => pour ecrire dans le fich dest
    
    if(f==NULL || fto==NULL) {
            printf("Erreur lors de l'ouverture des fichiers.\n");
            return;
    }
    char buffer[1024]; // besh t7ot bel ligne bel ligne
    while(fgets(buffer,sizeof(buffer),f)!=NULL) { // fgets: ta9ra from bel ligne w t7ot fel buffer
        fputs(buffer, fto); //thez mel buffer w ecrit fel to (destination)=> el copying
    }
    fclose(f);
    fclose(fto);
}


char *hashToPath(char *hash)
{
    if (hash==NULL)
        return NULL;

    int len=strlen(hash);
    if(len<3)
        return strdup(hash);

    char *path=(char*)malloc(len+2); 

    path[0]=hash[0];
    path[1]=hash[1];
    path[2]='/';
    strcpy(path+3,hash+2);
    
    return path;
}


void blobFile(char* file){
    if(file_exists(file)==0){
        printf("Le fichier %s n'existe pas pour creer un instantané!!\n",file);
        return;
    }

    char* hash=sha256file(file);
    if(!hash){
        printf("Erreur lors de la lecture du hash\n");
        return;
    }
    ;
    char* path=hashToPath(hash); //mesh yrajaa: xy/hedyujdkld...... =>besh nsajlou fih el copie

    int len=strlen("mkdir -p ")+strlen(path)+1; //tehseb long taa cmd besh taamlelha malloc besh tekteb fiha el commande w tnjm testaamel variable (path)****
    char *cmd=malloc(len);
    sprintf(cmd,"mkdir -p %.*s",2,path); //pour creer le folder xy/ => prendre les 2 premieres caracteres**
    system(cmd);
    free(cmd);

    FILE *f=fopen(path,"w"); //pour creer le file taht el folder xy/
    if(f) {
        fclose(f);
    }

    cp(path,file);
    printf("Snapshot file créé successfully: %s\n",path);
    free(path);
}






