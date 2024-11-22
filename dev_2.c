#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char *optarg ;
extern int optopt ;

void creation_matrice_aleatoire( int taille, int mat[taille][taille]){
    for(int i=0 ; i<taille ;i++)
        for(int j=0 ; j<taille ; j++)
            mat[i][j] = rand() % 100 ; //Remplir la matrice avec des valeurs comprises entre 0 et 99
}

//Fonction pour enregistrer la matrice dans un fichier texte::
void save_matrix_texte( int taille ,int mat[taille][taille], const char *filename){
    FILE* f = fopen(filename,"w");
    if(f == NULL){
        perror("Erreur d'ouverture du fichier texte .\n");
        return ;
    }
    for(int i=0 ; i<taille ; i++){
        for(int j=0 ; j<taille ; j++)
            fprintf(f,"%d",mat[i][j]);
        fprintf(f,"\n");
    }
    fclose(f);
}

//Fonction pour enregistrer la matrice dans un fichier binaire::
void save_matrix_binaire(int taille , int mat[taille][taille], const char *filename){
    FILE* f = fopen(filename,"wb");
    if(f == NULL){
        perror("Erreur d'ouverture du fichier binaire .\n");
        return ;
    }
    fwrite(&taille,sizeof(int),1,f);
    for(int i=0 ; i<taille ; i++)
        fwrite(mat[i],sizeof(int),taille,f);
    fclose(f);
}

//Fonction pour lire à partir d'un fichier binaire::
void lecture_matrix_binaire(const char *filename, int taille , int mat[taille][taille]){
    FILE* f = fopen(filename,"rb");
    if(!f){
        perror("Erreur d'ouverture du fichier binaire pour la lecture .\n");
        return ;
    }
    fread(&taille,sizeof(int),1,f); //lire la dimension de la matrice::
    printf("Matrice %dx%d (en binaire) :\n",taille,taille);

    for(int i=0 ; i<taille ; i++)
        fread(mat[i],sizeof(int),taille,f); //Lire chaque ligne de la matrice::
    
    fclose(f);
}

//Fonction pour lire la matrice à partir d'un fichier texte::
void lecture_matrix_text(const char *filename, int taille, int mat[taille][taille]){
    FILE* f = fopen(filename,"r");
    if(!f){
        perror("Erreur d'ouverture du fichier texte pour la lecture .\n");
        return;
    }

    for(int i=0 ; i<taille ; i++){
        for(int j=0 ; j<taille ; j++)
            fscanf(f,"%d",&mat[i][j]); //Lire chaque valeur de la matrice
    }
    //Fermeture du fichier texte après une lecture::
    fclose(f);
}

void afficher_matrice(int taille , int mat[taille][taille]){
    for(int i=0 ; i<taille ; i++){
        for(int j=0 ; j<taille ; j++)
            printf("%d\t",mat[i][j]);
        printf("\n");
    }
}

int main(int argc , char *argv[]){
    if( argc < 6){
        printf("Nombre arguments insuffisant sur la ligne de commande .\n");
        printf("Usage : nomfichier <arg2> <arg3> <arg4> <arg5> <arg6>  .\n ",argv[0]);
        return 0 ;
    }

    
    int taille=0; //La taille de la matrice::
    char *filename =NULL ; //nomDuFichier::
    int create=0 , affiche=0 , binary=1 , text=0 ;

    int opt  ;
    while( (opt = getopt(argc , argv ,"cad:bf:t")) != -1){
        switch(opt){
        case 'c':
            create = 1 ; break ; 
            
        case 'a':
            affiche = 1 ;
            break;
        case 'd':
             taille = atoi(optarg);
             break;
        case 'b':
            binary = 1 ; text = 0 ;
            break;
        case 'f':
            //Specifie le nom du fichier::
            filename = optarg ;
            break ;
        case 't':
            //Indique que le format du fichier est en mode texte::
            binary = 0 ; text = 1 ;
            break ;
        default:
            fprintf(stderr,"Usage :%s <-c | -a> -d taille -f filename <-b | -t>\n",argv[0]);
           exit(-1);
        }
    }

    if(taille <= 0 || filename == NULL){
        fprintf(stderr,"Taille et nom du fichier sont obligatoires .\n");
        exit(-1);
    }
    int mat[taille][taille] ;
    if(create){
        //creation d'une matrice aléatoire::
        creation_matrice_aleatoire(taille,mat);
        if(binary)
            save_matrix_binaire(taille,mat,filename);
        else
            save_matrix_binaire(taille,mat,filename);
        printf("Matrice créée et enregistrée dans le fichier '%s' .\n",filename);
    }

    if(affiche){
        if(binary)
            lecture_matrix_binaire(filename , taille , mat);
        else
            lecture_matrix_text(filename , taille , mat);
        printf("Matrice lue depuis le fichier '%s' :\n",filename);
        afficher_matrice(taille,mat);
    }

    return 0 ;
}