#include "jeu.h"

/*Initialise les paramètre nécessaires à OpenGL*/
void initGL()
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    glutInitWindowPosition(50,50);
    glutCreateWindow("La boule magique");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_CUBE_MAP_ARB); 

    glGenTextures(3, tex_sol);
    glGenTextures(6, tex_skybox);
    glGenTextures(2, tex_portail);

    glBindTexture(GL_TEXTURE_2D, tex_sol[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    //INFO: Les chargements de textures sont faits dans LancementJeu()
}

/*Gère les arguments de l'appel du programme*/
void gestion_arguments(int argc, char** argv)
{
    int i;
    num_niveau = 0;
    if(argc>0)
    {
        for(i=0; i<argc; i++)
        {
            //Gestion de l'argument de debug pour ne pas afficher de texture
            if(strcmp(argv[i],"-notexture")==0 || strcmp(argv[i],"-notex")==0)
            {
                no_texture=1;
            }
            //Gestion du niveau spécifié en argument
            if(strcmp(argv[i],"-lvl")==0 && i+1<argc)
            {
                num_niveau=atoi(argv[++i])-1;
            }
        }
    }
    else // Cas normal: Texture et niveau 1
    {
        no_texture=0;
        num_niveau=0;
    }
}

/*Initialise les vecteurs au début du jeu*/
void majVecteurs()
{
    //Rayon de la boule
    brayon = 2;
    // FAIT DANS definir_niveau()
    // //Coordonnées du centre de la boule
    // bx = 0;
    // by = 50;
    // bz = 0;
    //Vecteur de vitesse de la boule
    vx = 0;
    vy = 0;
    vz = 0;
    //Vecteur d'accélération de la boule
    ax = 0;
    ay = 0;
    az = 0;
    //Vecteur de gravité de la boule
    gx = 0;
    gy = -0.001;
    gz = 0;
    //Position de l'observateur
    ox = bx;
    oy = by + brayon*5;
    oz = bz;
    //Frottement
    fx = 0;
    fz = 0;
    //Direction avant de s'arrêter, on initialise pour partir direction x
    dx = 1;
    dz = 0;
}

/*Lance le jeu*/
void lancement()
{
    //Menu
    glutDisplayFunc(AffichageMenu);
    glutIdleFunc(Animer);
    glutKeyboardFunc(GererClavierMenu); //<= Lancera lancementJeu
    glutMainLoop();
}

/*Appeler via le menu pour lancer le jeu*/
void lancementJeu()
{
    majVecteurs();
    gestionMenu();
    nb_plateformes = 0;
    nb_objets = 0;
    nb_sauts = 0;
    definir_decor(LARGEUR_ELEMENT_DECOR);

    init_texture();
    definir_niveau();

    glutDisplayFunc(Affichage);
    glutIdleFunc(Animer);
    glutKeyboardFunc(GererClavier);
    glutSpecialFunc(GestionSpecial);

    glutMainLoop();
}

/*Permet d'appliquer des textures aux objets*/
void init_texture()
{
    if(!no_texture)
    {
        chargementTexture(&tex_sol[0], "img/test.png");
        chargementTexture(&tex_sol[1], "img/test3.png");
        chargementTexture(&tex_portail[0], "img/portail.png");
        chargementTexture(&tex_skybox[0],"img/testLF.png");
        chargementTexture(&tex_skybox[1],"img/testRT.png");
        chargementTexture(&tex_skybox[2],"img/testDN.png");
        chargementTexture(&tex_skybox[3],"img/testUP.png");
        chargementTexture(&tex_skybox[4],"img/testFT.png");
        chargementTexture(&tex_skybox[5],"img/testBK.png");
    }
}


void niveau_superieur()
{
    if (num_niveau == nombre_niveau)
    {
        printf("Jeu termine ! \n");
        exit(0);
    }
    else 
    {
        num_niveau ++;
        
        int i;
        plateforme p;
        p.p1 = nouveau_point(1000,1000,1000);  p.p2 = nouveau_point(1000,1000,1000);  p.p3 = nouveau_point(1000,1000,1000);  p.p4 = nouveau_point(1000,1000,1000);
        objet o;
        o.p1 = nouveau_point(1000,1000,1000);  o.p2 = nouveau_point(1000,1000,1000);
        for (i=0; i<nb_plateformes;i++)
        {
            tab_plateformes[i] = p;
        }
        nb_plateformes=0;
        for (i=0; i<nb_objets;i++)
        {
            tab_objets[i]=o;
        }
        nb_objets=0;
        for (i=0; i<nb_sauts;i++)
        {
            tab_sauts[i]=p;
        }
        nb_sauts=0;

        definir_niveau();
        vx=0; vy=0; vz=0;
    }
}


/*Definit les niveaux du jeu*/
void definir_niveau()
{
    int i;

    // On ajoute chaque plateforme
    for(i=0; i<nombre_plateforme_niveau[num_niveau]; i++)
    {
        ajouter_plateforme_charge(plateforme_niveau[num_niveau][i]);
    }

    // On ajoute chaque plateforme de saut
    for(i=0; i<nombre_saut_niveau[num_niveau]; i++)
    {
        ajouter_saut_charge(saut_niveau[num_niveau][i]);
    }

    //On fixe le point de départ
    bx = point_depart_niveau[num_niveau].x;
    by = point_depart_niveau[num_niveau].y;
    bz = point_depart_niveau[num_niveau].z;

    //On fixe le point de départ
    start = nouveau_point(bx, by, bz);
    //On fixe le point d'arrivée
    goal = nouveau_point(   point_arrivee_niveau[num_niveau].x,
                            point_arrivee_niveau[num_niveau].y,
                            point_arrivee_niveau[num_niveau].z);
    goal_orientation = orientation_arrive_niveau[num_niveau];
    ajouter_pilier_portail(goal,goal_orientation);    

    //On fixe les obstacles/objets
    for(i=0; i<nombre_obstacle_niveau[num_niveau]; i++)
    {
        ajouter_objet(obstacle_niveau[num_niveau][i].p1,obstacle_niveau[num_niveau][i].p2);
    }

    if (num_niveau == 1)
    {
        plateforme p = tab_plateformes[0];
        for (i=2; i<NOMBRE_MAX_OBJETS; i++)
        {
            generer_objet_sur_plateforme(p);
        }
    }

}

//Fonction Affichage pour flutDisplayFunc
void Affichage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPushMatrix() ;
    glLoadIdentity();
    //afficher_vecteurs();

    glFrustum(-1,1,-1,1,1,1000);

    // char vx_string[50];
    // sprintf(vx_string, "%f", vx);
    // afficherText(10,0,0,1,1,vx_string);

    maj_position_boule();

    verification_limites();
    
    ax=0; ay=0; az=0;

    //maj caméra
    // float positionCameraX = bx-vx*400;//((bx-vx*400)>7)?bx-vx-7:((bx-vx*400)<-7)?bx-vx+7:bx-vx*400;
    // float positionCameraY = by+brayon*4;
    // float positionCameraZ = bz-vz*400;//((bz-vz*400)>7)?bz-vz-7:((bz-vz*400)<-7)?bz-vz+7:bz-vz*400;

    //Mise a jour de la caméra
    maj_observateur();
    gluLookAt(ox, oy, oz, bx, by+brayon, bz+0.0000001, 0, 1, 0);

    // point p=nouveau_point(0,0,0);
    // portail(p, 'z');
    collision_boule_objet();
    //Affichage Boule
    dessiner_boule(brayon,bx,by,bz);
    portail(goal,goal_orientation);
    afficher_plateformes();
    afficher_objets();
    afficher_decor();
    afficher_cubemap();

    glutSwapBuffers();
}

/*Vérifie si on est encore dans les limites du monde*/
void verification_limites()
{
    if(bx>LIMITE_MAP || bx<-LIMITE_MAP || bz>LIMITE_MAP || bz<-LIMITE_MAP || by<-100)
    {
        ax=0; ay=0; az=0;
        vx=0; vy=0; vz=0;
        bx=start.x; by=start.y;  bz=start.z;
    }
}

void Animer()
{
    glutPostRedisplay();
}
