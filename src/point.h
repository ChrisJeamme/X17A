#ifndef POINT_H
    #define POINT_H

    typedef struct
    {
        int x;
        int y;
        int z;
    }Point;


    typedef struct
    {
        float x;
        float y;
        float z;
    }Pointf;

    typedef struct
    {
        Point pointA;
        Point pointB;
        int xmin;
        int xmax;
        int ymin;
        int ymax;
    }Cote;

#endif
