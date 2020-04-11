#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "world.h"
#include <math.h>
#include "ray.h"
#include "pi.h"

float px, py, pdx, pdy, pa;// playerpos, delta, and angle
/*
int mapX1 = 8;
int mapY1 = 8;
int mapS1 = 64;
int mapPower1 = 6;
int map1[]= {
    1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,1,1,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,1,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1

};

*/

int mapX1 = 16;
int mapY1 = 16;
int mapS1 = 256;
int mapPower1 = 8;
int map1[]= {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,1,0,0,0,0,0,0,0,0,1,1,0,1,
    1,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,
    1,0,0,2,0,0,0,0,1,1,0,0,0,0,0,1,
    1,0,0,0,0,1,1,0,0,0,0,0,0,1,0,1,
    1,0,0,0,0,1,1,0,0,0,1,0,0,1,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

};
int mapplayerx1 = 300;
int mapplayery1 = 300;

void drawplayer(){
	glColor3f(0,0,1);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(px,py);
	glEnd();
	
	glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px,py);
    glVertex2i(px +pdx*5, py+pdy*5);
    glEnd();
	
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);

    //drawmap2D(mapX1, mapY1, mapS1, map1);
    drawrays(mapX1, mapY1, mapPower1, mapS1, map1, pa, px, py);
	//drawplayer();
    //drawgun();
	
	glutSwapBuffers();
	
}

void init(){
	glClearColor(.3,.3,.3,0);
	gluOrtho2D(0,1024,512,0);
	px = 300;
	py = 300;
    pdx = cos(pa) *5;
    pdy = sin(pa) * 5;

}

void keypressed(unsigned char key, int x, int y){
    int loc = (int)(px +mapY1*py);
    if(key == 'k'){
        pa -= .1;
        if(pa<0){
            pa += 2 * PI; 
        }
        pdx = cos(pa) *5;
        pdy = sin(pa) * 5;
    }
    if(key == 'l' ){
        pa += .1;
        if(pa > 2*PI){
            pa -= 2 * PI; 
        }
        pdx = cos(pa) *5;
        pdy = sin(pa) * 5;
    }
    
    if(key == 'a' ){
        /*if(map1[loc] != 0){
            px -= 1;
            py -= 1;
        }
        else{
            px -= 2*pdy;
            py -= 2*pdx;
        }*/
        px -= 2*pdy;
        py -= 2*pdx;
        
    }
    if(key == 'd' ){
        /*if(map1[loc] != 0){
            px -= 1;
            py -= 1;
        }
        else{
            px += 2*pdy;
            py += 2*pdx;
        }*/
        px += 2*pdy;
        py += 2*pdx;
        
    }
    if(key == 's' ){
        /*if(map1[loc] != 0){
            px -= 1;
            py -= 1;
        }

        else{
            px -= 2*pdx;
            py -= 2*pdy;
        }*/
        px -= 2*pdx;
        py -= 2*pdy;
    }
    if(key == 'w'){
        /*if(map1[loc] != 0){
            px -= 1;
            py -= 1;
        }
        else{
        px += 2*pdx;
        py += 2*pdy;
        }*/
        px += 2*pdx;
        py += 2*pdy;
    }

    glutPostRedisplay();
}



int main(int argc, char** argv){
	
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1280,720);
	glutCreateWindow("bruh bruh bruh moment");
	init();
	glutDisplayFunc(display);
    glutKeyboardFunc(keypressed);
	glutMainLoop();
	
	return 0;
	
}
