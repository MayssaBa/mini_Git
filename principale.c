#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "file.h"
#include "worktree.h"


void main(){
    // int x=hashFile("fich.txt","hashFich.txt");
    // if(x==0){
    //     printf("hashage avec succee: %d\n",x);
    // }else{
    //     printf("prob hashage %d\n",x);
    // }
    // char* hash=sha256file("fich.txt");
    // printf("%s\n",hash);
    // free(hash);
    
    // list*l=initList();
    // insertFirst(l,buildCell("f1"));
    // insertFirst(l,buildCell("f2"));
    // insertFirst(l,buildCell("f3"));

    // char* ch=ltos(l);
    // printf("%s\n",ch);

    // Cell* c=listGet(l,1);
    // printf("Elmt 1: %s\n",ctos(c));
    
    // Cell* s=searchList(l,"f4");
    // if(s==NULL){
    //     printf("NULL\n");}
    // else{
    //     printf("%s\n",ctos(s));
    // }

    // list* l1=stol("f4|f5|f6|f7");
    // ltof(l1,"testLTOF.txt");
    // list* l2=ftol("testLTOF.txt");
    // char* l2ch=ltos(l2);
    // printf("%s\n",l2ch);

    
    // list *l3=listdir(".");
    // printf("afterrrr");
    // if (l3!= NULL)
    // {
    //     char *ch3= ltos(l3);
    //     printf("listdir reslt:\n %s\n",ch3);
    //     free(s);
    // }else{printf("null!!!");}

    // int exist=file_exists("nnnn");
    // printf("exist?: %d\n",exist);

    // cp("copie_testLTOF.txt","testLTOF.txt");
    // cp("copie_testLTOF.txt","nnnnn.txt"); //tester le cas de fich dest moush mawjoud!

    // char* hash2=sha256file("fich.txt");
    // char* hashPath=hashToPath(hash2);
    // if(hashPath){
    //     printf("hashtopath: %s\n",hashPath);}
    // else{
    //     printf("hash est NULL (hashtopath)\n");}
    // free(hash2);

    // blobFile("fich.txt");
    


    //chap2************************:
    WorkFile* wf=createWorkFile("fich.txt");
    if(wf){printf("WF crée avec succee!\n");}
    char* chwf=wfts(wf);
    printf("%s\n",chwf);

    WorkFile* wf2=stwf("file.txt\thashshshshs\t111");
    // if(wf2){printf("WF crée avec succee!\n");}else{printf("errrr");}
    char* chwf2=wfts(wf2);
    printf("%s\n",chwf2);

    WorkTree* wt=initWorkTree();
    if(wt){printf("WTree cree avec succee\n");}else{printf("erreur de wtree!!\n");}

    //rq: il ne faut pas worktree null!!!!!!!!
    int exist_WT=inWorkTree(wt,"f1.txt");
    if(wt->n==0){printf("workTree NULL\n");}
    else{
        if(exist_WT==-1){
            printf("le file n'existe pas");
        }
        else{printf("le file existe a l'index %d\n",exist_WT);}
    }

    int app=appendWorkTree(wt,"f1.txt","shshshsh1",222);
    if(app==1){printf("Ajout avec succee en Wtree\n");}
    else{printf("erreur d'ajout / exist deja ou Wtree pleine\n");}

    






    






    


}















