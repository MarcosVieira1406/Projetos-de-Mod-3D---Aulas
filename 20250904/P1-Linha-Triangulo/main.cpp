//Autor: Marcos Eduardo - Projeto: Linha e triangulo 04/09/2025

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>

float r,g,b,x,y;
bool check = true;

GLfloat escala = 1;

void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON)

    {
        check=true;
        x = mousex;
        y = 480-mousey;
        r = (rand()%10)/10.0;
        g = (rand()%10)/10.0;
        b = (rand()%10)/10.0;
    }
    else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        check = false;
    }
    glutPostRedisplay();
}

static void desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(r,g,b);
    glPointSize(50);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    if(check)
    {
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
    }
    glFlush();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //define a area de enquadramento do sistema/cena
    gluOrtho2D(-3, 3, -3, 3);

    glScalef(escala, escala, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLineWidth(10);
    glBegin(GL_LINES);
        glVertex2f(-2.0f, 0.0f);
        glVertex2f(2.0f, 0.0f);
        glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0, 1, 0);
        glVertex2f(-2.0f, -2.0f);
        glVertex2f(2.0f, -2.0f);
        glColor3f(1, 0, 0);
        glVertex2f(0.0f, 2.0f);
    glEnd();

        glFlush();
}

void listeningKey (unsigned char tecla, GLint x, GLint y){
    switch(tecla){
        case '+': escala += 0.1f; break;
        case '-':
            escala -= 0.1f;
            if(escala < 0.1f) escala = 0.1f;
            break;
    }
    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(300,100);
    glutCreateWindow("Ola GLUT");
    glutKeyboardFunc(listeningKey);
    glutDisplayFunc(desenha);
    glClear(GL_COLOR_BUFFER_BIT);
    glutMouseFunc(mouse);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glClearColor(0, 0, 1, 0);
    glutMainLoop();
    return EXIT_SUCCESS;
}
