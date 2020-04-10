#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "ray.h"

int maxint(int a, int b){
    if (a> b){
        return a;
    }
    return b;
}

float minfloat(float a, float b){
    if(a< b){
        return a;
    }
    return b;
}

float dist(float ax, float ay, float bx, float by, float ang){
    return (sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)));
}

void drawrays(int mapX, int mapY, int MAPPOWER, int MAPSIZE, int mapin[],  float pa, float px, float py){
    int mx, my, mp, dof, r, dof_max, xtimesy, distfin;
    float rx, ry, ra, xo,yo;

    dof_max = maxint(mapX, mapY); 
    ra = pa - DR*40; 
    if(ra <0){
        ra+=2*PI;
    }
    if(ra > 2*PI){
        ra-=2*PI;
    }

    for(r = 0; r<80; r++){ // main for loop to draw a ray
        //----------------
        //horizontal check
        //----------------
        float disH = 100000; 
        float hx = px; 
        float hy = py;
        dof = 0;
        float itan = -1/tan(ra);
        if(ra>PI){//looking up
            ry = (((int)py>>MAPPOWER)<<MAPPOWER)-.0001;
            rx = (py-ry) * itan +px;
            yo = -MAPSIZE;
            xo = -yo * itan;
        }
        if(ra<PI){//looking down
            ry = (((int)py>>MAPPOWER)<<MAPPOWER)+MAPSIZE;
            rx = (py-ry) * itan +px;
            yo = MAPSIZE;
            xo = -yo * itan;
        }
        if(ra == 0 || ra == PI){//striaght left or right
            rx = px;
            ry = py;
            dof = 8;
        }
        while(dof < 8){
            mx = (int)rx >>MAPPOWER;
            my = (int)ry >>MAPPOWER;
            mp = my * mapX +mx;
            if(mp > 0 && mp < mapX*mapY && mapin[mp] == 1){
                hx = rx;
                hy = ry;
                disH=dist(px,py,hx,hy,ra);
                dof = 8; //wall inside map
            }
            else{
                rx += xo;
                ry += yo; // next 
                dof += 1;
            }
        }
        /*glColor3f(0,1,0);
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(px,py); //draw ray from player pos to end of ray pos for horizontal check
        glVertex2i(rx,ry);
        glEnd();*/



        //----------------
        //Vertical   check
        //----------------
        float disV = 100000; 
        float vx = px; 
        float vy = py;
        dof = 0;
        float ntan = -1 * tan(ra);
        if(ra>PI2 && ra<PI3){//looking left
            rx = (((int)px>>MAPPOWER)<<MAPPOWER)-.0001;
            ry = (px-rx) * ntan +py;
            xo = -MAPSIZE;
            yo = -xo * ntan;
        }
        if(ra<PI2 || ra > PI3){//looking right
            rx = (((int)px>>MAPPOWER)<<MAPPOWER) +MAPSIZE;
            ry = (px-rx) * ntan +py;
            xo = MAPSIZE;
            yo = -xo * ntan;
        }
        if(ra == 0 || ra == PI){//striaght up or down
            rx = px;
            ry = py;
            dof = 8;
        }
        while(dof < 8){
            mx = (int)rx >>MAPPOWER;
            my = (int)ry >>MAPPOWER;
            mp = my * mapX +mx;
            if(mp > 0 && mp < mapX*mapY && mapin[mp] == 1){
                vx = rx;
                vy = ry;
                disV=dist(px,py,vx,vy,ra);
                dof = 8; //wall in map
            }
            else{
                rx += xo;
                ry += yo; // next 
                dof += 1;
            }
        }
        if(disH < disV){
            rx = hx;
            ry = hy;
            distfin = disH;
            glColor3f(.9,0,0);
        }
        else{
            rx = vx;
            ry = vy;
            distfin = disV;
            glColor3f(.6,0,0);
        }
        //glColor3f(1,0,0);
        /*glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(px,py); //draw ray from player pos to end of ray pos
        glVertex2i(rx,ry);
        glEnd();*/

        //-------------------
        //start draw 3d walls
        //-------------------
        float anglefix = pa-ra;
        if(anglefix <0){
            anglefix+=2*PI;
        }
        if(anglefix > 2*PI){
            anglefix-=2*PI;
        }
        distfin = distfin *cos(anglefix);//*cos(anglefix);
        float lineH = MAPSIZE*500/distfin;
        if(lineH > 500){
            lineH = 500;
        }
        float lineO = 250 - lineH/2;
        
        glLineWidth(200); //walls made of 8 with lines
        glBegin(GL_LINES);
        glVertex2i(r*5 +256, lineO);
        glVertex2i(r*5 +256, lineH+lineO);
        glEnd();
        //-----------------
        //end draw 3d walls
        //-----------------

        ra += DR; 
        if(ra <0){
            ra+=2*PI;
        }
        if(ra > 2*PI){
            ra-=2*PI;
        }

    }
}