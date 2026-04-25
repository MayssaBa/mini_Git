#ifndef FILE_H
#define FILE_H

#include "liste.h"



int hashFile(char *source,char *dest);
char* sha256file(char* file);
list* listdir(char* root_dir);
int file_exists(char *file);
void cp(char *to,char *from);
char *hashToPath(char *hash);
void blobFile(char* file);

#endif