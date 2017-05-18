#include "niveaux.h"

void importer_niveaux()
{
    fixer_nombre_niveaux(); //Cherche dans le répertoire
    initialiser_tableaux_niveaux(); //Alloue la mémoire pour les niveaux

    int i;
    for(i=1; i<=nombre_niveau; i++)
    {
        char nom_fichier[11];
        sprintf(nom_fichier, "%d.lvl", i);
        importer_niveau(nom_fichier,i-1);
    }
}

void fixer_nombre_niveaux()
{
    DIR* rep = NULL;
    dirent* fichier = NULL;
    rep = opendir("./levels/");
    if (rep == NULL) 
        exit(1);  

    nombre_niveau = 0;

    while ((fichier = readdir(rep)) != NULL)
    {
        char nom_fichier[11];
        sprintf(nom_fichier, "%d.lvl", nombre_niveau+1);

        //Vérification du nom
        if(strcmp(fichier->d_name,nom_fichier)==0)
        {
            nombre_niveau++;
        }
    }

    printf("%d niveau(x) trouvé(s)\n",nombre_niveau);

    if (closedir(rep) == -1)
        exit(-1);
}

void initialiser_tableaux_niveaux()
{
    int i;

    if(nombre_niveau==0)
    {
        fprintf(stderr,"Erreur: 0 niveaux trouvés\n");
        exit(-1);
    }

    for(i=0; i<nombre_niveau; i++)
    {
        //Plateformes
        plateforme_niveau[i] = NULL;
        plateforme_niveau[i] = malloc(sizeof(plateforme)*NOMBRE_MAX_PLATEFORMES);
        if(plateforme_niveau[i]==NULL)
        {
            fprintf(stderr,"Problème d'allocation de mémoire (Plateformes)\n");
            exit(-1);
        }

        //Obstacles
        // obstacle_niveau[i] = NULL;
        // obstacle_niveau[i] = malloc(sizeof(obstacle)*NOMBRE_MAX_DECOR);
        // if(obstacle_niveau[i]==NULL)
        // {
        //     fprintf(stderr,"Problème d'allocation de mémoire (Obstacle)\n");
        //     exit(-1);
        // }
    }
    
}

void importer_niveau(char* nom_fichier, int numero_niveau)
{
    FILE* fichier = NULL;
    char chaine[500] = "";
    char path[20] = "./levels/";
    char etat = 'w'; 
    strcat(path,nom_fichier);
    int x,y,z;
    int num_plat = 0; //Itérateur sur les plateformes

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

                    if(etat=='d'||etat=='a'||etat=='p'||etat=='o')
                        etat = chaine[1];
                    if(etat=='p')
                        nombre_plateforme_niveau[numero_niveau] = chaine[13]-'0';
                    if(etat=='o')
                        nombre_obstacle_niveau[numero_niveau] = chaine[11]-'0';
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
                        sscanf(chaine, "(%d,%d,%d)",    &point_arrivee_niveau[numero_niveau].x,
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
                    case 'o': //Obstacles
                        printf("(Pas encore d'obstacle)");
                        break;
                    default:
                        fprintf(stderr,"Erreur d'état (chargement sauvegarde");
                        break;
                    }
                }
            }
        }

        fclose(fichier);
    }

}

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