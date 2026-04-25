#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "worktree.h"
#include "file.h"

WorkFile* createWorkFile(char* name){
    WorkFile* wf=(WorkFile*)malloc(sizeof(WorkFile));
    wf->name=name;
    wf->hash=NULL;
    wf->mode=0;
    return wf;
}
char* wfts(WorkFile* wf){
    if (wf==NULL){return NULL;}
    char tab[4];
    sprintf(tab,"%d",wf->mode);//car mode est int!!
    int lenHash;

    if(wf->hash==NULL){
        lenHash=4; //le cas ou NULL car srtlen ne marche pas avec NULL!!
    }else{
        lenHash=strlen(wf->hash);
    }

    int lng=strlen(wf->name)+lenHash+strlen(tab)+3+1;//3=> nbre de \t et 1=>\0
    char *ch=malloc(lng);
    ch[0] = '\0'; //pour initialiser la chaine: tnjmsh taamel concat maa ch ferghaa!!

    strcat(ch,wf->name);
    strcat(ch,"\t");
    if(wf->hash==NULL){
        strcat(ch,"NULL");
    }else{
        strcat(ch,wf->hash);
    }
    
    strcat(ch,"\t");
    strcat(ch,tab);

    return ch;

 }

WorkFile* stwf(char* ch){
    if(ch==NULL){return NULL;}
    
    char* cop=strdup(ch); // copie modifiable=>tnjmsh tmodifie ala ch toul=>ch read only!!
    char* splt=strtok(cop,"\t");//mesh t9os (split) ch selon el sep=\t

    WorkFile* wf=(WorkFile*)malloc(sizeof(WorkFile));

    wf->name=strdup(splt);//fe kol mara taamel copie mel part eli t9asmt 5ater baad taamel free w houa pointeur el splt ythi3!!
    splt=strtok(NULL,"\t");
    wf->hash=strdup(splt);
    splt=strtok(NULL,"\t");
    wf->mode=strtol(splt,NULL,10); //t7awel mel string lel int(long)=>NULL=>yaani moush mesh ne5o win ye9ef a fin et 10=>base decimale

    free(cop); 
    return wf;
}


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
    wt->tab[wt->n++].name=name;
    wt->tab[wt->n].hash=hash;
    wt->tab[wt->n].mode=mode;
    return 1;

}
// char* wtts(WorkTree* wt) {

// }





