#include "niveaux.h"

/*Importe les niveaux contenu dans le dossier ./level/*/
void importer_niveaux()
{
    fixer_nombre_niveaux(); //Cherche dans le répertoire

    if(num_niveau<0||num_niveau>=nombre_niveau)
    {
        fprintf(stderr,"Niveau choisi incorrect\n");
        exit(-1);
    }

    initialiser_tableaux_niveaux(); //Alloue la mémoire pour les niveaux

    int i;
    for(i=1; i<=nombre_niveau; i++)
    {
        char nom_fichier[11];
        sprintf(nom_fichier, "%d.lvl", i);
        importer_niveau(nom_fichier,i-1);
    }
}

/*Compte le nombre de niveaux dans le dossier*/
void fixer_nombre_niveaux()
{
    DIR* rep = NULL;
    dirent* fichier = NULL;
    rep = opendir("./levels/");
    if (rep == NULL) 
        exit(1);  

    nombre_niveau = -2;

    //On compte le nombre de fichiers
    while ((fichier = readdir(rep)) != NULL)
    {
        nombre_niveau++;
    }

    printf("%d niveau(x) trouvé(s)\n",nombre_niveau);

    if (closedir(rep) == -1)
        exit(-1);
}

/*Alloue la mémoire aux tableaux qui contiendront tous les niveaux*/
void initialiser_tableaux_niveaux()
{
    if(nombre_niveau==0)
    {
        fprintf(stderr,"Erreur: 0 niveaux trouvés\n");
        exit(-1);
    }

    point_depart_niveau = (point*) malloc(sizeof(point)*(nombre_niveau+1));
    point_arrivee_niveau = (point*) malloc(sizeof(point)*(nombre_niveau+1));
    nombre_plateforme_niveau = (int*) malloc(sizeof(int)*(nombre_niveau+1));
    nombre_saut_niveau = (int*) malloc(sizeof(int)*(nombre_niveau+1));
    obstacle_niveau = (couple_points**) malloc(sizeof(couple_points*)*(nombre_niveau+1));
    orientation_arrive_niveau = (char*) malloc(sizeof(char)*(nombre_niveau+1));
    nombre_obstacle_niveau = (int*) malloc(sizeof(int)*(nombre_niveau+1));    
    saut_niveau = (plateforme**) malloc(sizeof(plateforme*)*50);
    plateforme_niveau = (plateforme**) malloc(sizeof(plateforme*)*50);
}

/*Importe les donnés d'un fichier niveau, avec son nom de fichier*/
void importer_niveau(char* nom_fichier, int numero_niveau)
{
    FILE* fichier = NULL;
    char chaine[500] = "";
    char path[20] = "./levels/";
    char etat = 'w'; 
    strcat(path,nom_fichier);
    int j,x,y,z;
    int num_plat = 0; //Itérateur sur les plateformes
    int num_plat_saut = 0; //Itérateur sur les plateformes de saut
    int num_obstacle = 0; //Itérateur sur les objets obstacles

    fichier = fopen(path, "r");

    if(fichier == NULL)
    {
        fprintf(stderr,"Impossible d'ouvrir le fichier de sauvegarde : %s\n",nom_fichier);
    }
    else
    {
        while(fgets(chaine, 500, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            // \n => Ligne ignoré
            if(strcmp(chaine,"\n")!=0)
            {
                // Changement d'état
                if(chaine[0]=='#') 
                {
                    etat = chaine[1];

                    if(etat=='d'||etat=='a'||etat=='p'||etat=='o'||etat=='s')
                        etat = chaine[1];
                    if(etat=='p') //Plateforme normale
                    {
                        if(strlen(chaine)<13)
                        {
                            fprintf(stderr,"Problème dans le fichier du niveau %d\n",numero_niveau);
                            exit(-1);
                        }

                        nombre_plateforme_niveau[numero_niveau] = (chaine[13]-'0')*10+chaine[14]-'0';
                        
                        //Allocation de la mémoire pour le tableau de plateforme de ce niveau

                        plateforme_niveau[numero_niveau] = (plateforme*) malloc(sizeof(plateforme)*nombre_plateforme_niveau[numero_niveau]);
                        
                        for(j=0; j<nombre_plateforme_niveau[numero_niveau]; j++)
                        {
                            plateforme p;
                            p.p1 = nouveau_point(0,0,0);  p.p2 = nouveau_point(0,0,0);  p.p3 = nouveau_point(0,0,0);  p.p4 = nouveau_point(0,0,0);
                            plateforme_niveau[numero_niveau][j] = p;
                        }
                        if(plateforme_niveau[numero_niveau]==NULL)
                        {
                            fprintf(stderr,"Problème d'allocation de mémoire (Plateformes)\n");
                            exit(-1);
                        }
                    }
                    if(etat=='s') //Plateforme de saut
                    {
                        if(strlen(chaine)<7)
                        {
                            fprintf(stderr,"Problème dans le fichier du niveau %d\n",numero_niveau);
                            exit(-1);
                        }

                        nombre_saut_niveau[numero_niveau] = (chaine[7]-'0')*10+chaine[8]-'0';

                        //Allocation de la mémoire pour le tableau de sauts de ce niveau

                        saut_niveau[numero_niveau] = (plateforme*) malloc(sizeof(plateforme)*nombre_saut_niveau[numero_niveau]);

                        for(j=0; j<nombre_saut_niveau[numero_niveau]; j++)
                        {
                            plateforme p;
                            p.p1 = nouveau_point(0,0,0);  p.p2 = nouveau_point(0,0,0);  p.p3 = nouveau_point(0,0,0);  p.p4 = nouveau_point(0,0,0);
                            saut_niveau[numero_niveau][j] = p;
                        }
                        if(saut_niveau[numero_niveau]==NULL)
                        {
                            fprintf(stderr,"Problème d'allocation de mémoire (Sauts)\n");
                            exit(-1);
                        }
                    }
                    if(etat=='o') //Objet obstacle
                    {
                        if(strlen(chaine)<11)
                        {
                            fprintf(stderr,"Problème dans le fichier du niveau %d\n",numero_niveau);
                            exit(-1);
                        }
                        
                        nombre_obstacle_niveau[numero_niveau] = (chaine[11]-'0')*10+chaine[12]-'0';

                        //Allocation de la mémoire pour le tableau d'obstacle de ce niveau

                        obstacle_niveau[numero_niveau] = NULL;
                        obstacle_niveau[numero_niveau] = (couple_points*) malloc(sizeof(couple_points)*nombre_obstacle_niveau[numero_niveau]);
                        for(j=0; j<nombre_obstacle_niveau[numero_niveau]; j++)
                        {
                            couple_points couple;
                            couple.p1 = nouveau_point(0,0,0);
                            couple.p2 = nouveau_point(0,0,0);
                            obstacle_niveau[numero_niveau][j] = couple;
                        }
                        if(obstacle_niveau[numero_niveau]==NULL)
                        {
                            fprintf(stderr,"Problème d'allocation de mémoire (Obstacles)\n");
                            exit(-1);
                        }
                    }
                }
                else    //On lit des données
                {
                   // Données
                    switch(etat)
                    {
                    case 'd': //Coordonnées de départ
                        sscanf(chaine, "(%d,%d,%d)", &x, &y, &z);
                        point_depart_niveau[numero_niveau] = nouveau_point(x,y,z);

                        break;
                    case 'a': //Coordonnées de l'arrivée
                        sscanf(chaine, "%c (%d,%d,%d)", &orientation_arrive_niveau[numero_niveau],
                                                        &point_arrivee_niveau[numero_niveau].x,
                                                        &point_arrivee_niveau[numero_niveau].y,
                                                        &point_arrivee_niveau[numero_niveau].z);
                        break;
                    case 'p': //Plateformes
                        
                        sscanf(chaine, "(%d,%d,%d)(%d,%d,%d)(%d,%d,%d)(%d,%d,%d)",
                                                        &plateforme_niveau[numero_niveau][num_plat].p1.x,
                                                        &plateforme_niveau[numero_niveau][num_plat].p1.y,
                                                        &plateforme_niveau[numero_niveau][num_plat].p1.z,
                                                        &plateforme_niveau[numero_niveau][num_plat].p2.x,
                                                        &plateforme_niveau[numero_niveau][num_plat].p2.y,
                                                        &plateforme_niveau[numero_niveau][num_plat].p2.z,
                                                        &plateforme_niveau[numero_niveau][num_plat].p3.x,
                                                        &plateforme_niveau[numero_niveau][num_plat].p3.y,
                                                        &plateforme_niveau[numero_niveau][num_plat].p3.z,
                                                        &plateforme_niveau[numero_niveau][num_plat].p4.x,
                                                        &plateforme_niveau[numero_niveau][num_plat].p4.y,
                                                        &plateforme_niveau[numero_niveau][num_plat].p4.z);
                        num_plat++;
                        break;
                    case 's': //Plateformes de saut
                        sscanf(chaine, "(%d,%d,%d)(%d,%d,%d)(%d,%d,%d)(%d,%d,%d)",
                                                        &saut_niveau[numero_niveau][num_plat_saut].p1.x,
                                                        &saut_niveau[numero_niveau][num_plat_saut].p1.y,
                                                        &saut_niveau[numero_niveau][num_plat_saut].p1.z,
                                                        &saut_niveau[numero_niveau][num_plat_saut].p2.x,
                                                        &saut_niveau[numero_niveau][num_plat_saut].p2.y,
                                                        &saut_niveau[numero_niveau][num_plat_saut].p2.z,
                                                        &saut_niveau[numero_niveau][num_plat_saut].p3.x,
                                                        &saut_niveau[numero_niveau][num_plat_saut].p3.y,
                                                        &saut_niveau[numero_niveau][num_plat_saut].p3.z,
                                                        &saut_niveau[numero_niveau][num_plat_saut].p4.x,
                                                        &saut_niveau[numero_niveau][num_plat_saut].p4.y,
                                                        &saut_niveau[numero_niveau][num_plat_saut].p4.z);
                        num_plat_saut++;
                        break;
                    case 'o': //Obstacles
                        sscanf(chaine, "(%d,%d,%d)(%d,%d,%d)",
                                                        &obstacle_niveau[numero_niveau][num_obstacle].p1.x,
                                                        &obstacle_niveau[numero_niveau][num_obstacle].p1.y,
                                                        &obstacle_niveau[numero_niveau][num_obstacle].p1.z,
                                                        &obstacle_niveau[numero_niveau][num_obstacle].p2.x,
                                                        &obstacle_niveau[numero_niveau][num_obstacle].p2.y,
                                                        &obstacle_niveau[numero_niveau][num_obstacle].p2.z);
                        num_obstacle++;
                        break;
                    default:
                        fprintf(stderr,"Erreur d'état (chargement sauvegarde)\n");
                        break;
                    }
                }
            }
        }

        fclose(fichier);
    }

}

/*Affiche quelques données des niveaux stockés (manque obstacle + sauts)*/
void afficher_niveaux()
{
    int i,j;
    for(i=0; i<nombre_niveau; i++)
    {
        printf("Niveau %d/%d\n",i+1,nombre_niveau);

        printf("\tPoint de départ: (%d,%d,%d)\n",point_depart_niveau[i].x,point_depart_niveau[i].y,point_depart_niveau[i].z);
        printf("\tPoint objectif: (%d,%d,%d)\n",point_arrivee_niveau[i].x,point_arrivee_niveau[i].y,point_arrivee_niveau[i].z);

        for(j=0; j<nombre_plateforme_niveau[i]; j++)
        {
            int x1 = plateforme_niveau[i][j].p1.x;
            int y1 = plateforme_niveau[i][j].p1.y;
            int z1 = plateforme_niveau[i][j].p1.z;

            int x2 = plateforme_niveau[i][j].p2.x;
            int y2 = plateforme_niveau[i][j].p2.y;
            int z2 = plateforme_niveau[i][j].p2.z;

            int x3 = plateforme_niveau[i][j].p3.x;
            int y3 = plateforme_niveau[i][j].p3.y;
            int z3 = plateforme_niveau[i][j].p3.z;

            int x4 = plateforme_niveau[i][j].p4.x;
            int y4 = plateforme_niveau[i][j].p4.y;
            int z4 = plateforme_niveau[i][j].p4.z;

            printf("\tPlateforme[Niveau %d][Num %d] : (%d,%d,%d)(%d,%d,%d)(%d,%d,%d)(%d,%d,%d)\n",i,j,x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);
        }
        printf("\n");
    }
}