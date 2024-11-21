#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char *optarg ;
extern int optopt ;

void creation_matrice_aleatoire(int **mat , int taille){
    for(int i=0 ; i<taille ;i++)
        for(int j=0 ; j<taille ; j++)
            mat[i][j] = rand()%100 ; //Remplir la matrice avec des valeurs comprises entre 0 et 99
}

//Fonction pour enregistrer la matrice dans un fichier texte::
void save_matrix_texte(int **mat , int taille , char *filename){
    FILE* f = fopen(filename,"w");
    if(f == NULL){
        perror("Erreur d'ouverture du fichier texte .\n");
        return ;
    }
    for(int i=0 ; i<taille ; i++){
        fro(int j=0 ; j<taille ; j++)
            fprintf(f,"%d",mat[i][j]);
        fprintf(f,"\n");
    }
    fclose(f);
}

//Fonction pour enregistrer la matrice dans un fichier binaire::
void save_matrix_binaire(int **mat , int taille , char *filename){
    FILE* f = fopen(filename,"wb");
    if(f == NULL){
        perror("Erreur d'ouverture du fichier binaire .\n");
        return ;
    }
    for(int i=0 ; i<taille ; i++)
        fwrite(mat[i],sizeof(int),taille,f);
    fclose(f);
}

//Fonction pour lire à partir d'un fichier binaire::
void lecture_matrix_text(char *filename){
    FILE* f = fopen(filename,"rb");
    if(!f){
        perror("Erreur d'ouverture du fichier binaire pour la lecture .\n");
        return ;
    }
    int taille ;
    fread(&taille,sizeof(int),1,f); //lire la dimension de la matrice::
    printf("Matrice %dx%d (en texte) :\n",taille,taille);

    int **mat = malloc(taille * sizeof(int*));
    if(mat){
        for(int i=0 ; i<taille ;i++)
            mat[i] = malloc(taille * sizeof(int));
    }

    for(int i=0 ; i<taille ; i++)
        fread(mat[i],sizeof(int),taille,f); //Lire chaque ligne de la matrice::

    for(int i=0 ; i<taille ; i++){
        for(int j=0 ; j<taille ; j++)
            printf("%d\t",mat[i][j]);
    }
    printf("\n");

    for(int i=0 ; i<taille ; i++)
        if(mat[i])
            free(mat[i]);
    
    fclose(f);
}

//Fonction pour lire la matrice à partir d'un fichier texte::
void lecture_matrix_text(char *filename){
    FILE* f = fopen(filename,"r");
    if(!f){
        perror("Erreur d'ouverture du fichier texte pour la lecture .\n");
        return;
    }

    int taille;
    fscanf(f,"%d",&taille); //Lire la dimension de la matrice
    printf("Matrice %dx%d (en texte) :\n",taille,taille);

    int **mat = malloc(taille * sizeof(int*));
    if(mat){
        for(int i=0 ; i<taille ;i++)
            mat[i] = malloc(taille * sizeof(int));
    }

    for(int i=0 ; i<taille ; i++){
        for(int j=0 ; j<taille ; j++)
            fscanf(f,"%d",&mat[i][j]); //Lire chaque valeur de la matrice
    }

    for(int i=0 ; i<taille ; i++){
        for(int j=0 ; j<taille ; j++)
            printf("%d\t",mat[i][j]);
    }
    printf("\n");

    //Fermeture du fichier texte après une lecture::
    fclose(f);
}

int main(int argc , char *argv[]){
    if( argc < 7){
        printf("Nombre arguments insuffisant sur la ligne de commande .\n");
        printf("Usage : nomfichier <arg2> <arg3> <arg4> <arg5> <arg6> <arg7> .\n ",argv[0]);
        return 0 ;
    }

    int opt ;
    while( (opt = getopt(argc , argv ,"")))


}