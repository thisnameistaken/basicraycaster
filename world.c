#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "world.h"


void drawmap2D(int mapX, int mapY, int mapS, int map[]){
    int xo, yo;
    int i, j;
    for(i = 0; i < mapX; i++){
        for(j = 0; j < mapY; j++){

            if( map[i+j*mapY] ){
                glColor3f(1,1,1);
            }
            else{
                glColor3f(0,0,0);
            }
            
            xo = i * mapS;
            yo = j * mapS;

            glBegin(GL_QUADS);
            glVertex2i(xo +1, yo +1);
            glVertex2i(xo +1, yo + mapS -1);
            glVertex2i(xo+mapS -1, yo+mapS -1 );
            glVertex2i(xo+mapS-1 , yo +1);           
			glEnd();

        }
    }
};