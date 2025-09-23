#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

struct Ponto {
    float x, y;
};

Ponto primeiroPonto;
bool temPrimeiroPonto = false;
int contadorCliques = 0;

void mouse(int button, int state, int mousex, int mousey) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        contadorCliques++;
        float x = mousex;
        float y = 480 - mousey;

        if(contadorCliques == 1) {
            primeiroPonto.x = x;
            primeiroPonto.y = y;
            temPrimeiroPonto = true;
        }
        else if(contadorCliques == 2 && temPrimeiroPonto) {
            glColor3f(1, 0, 0);
            glLineWidth(3);
            glBegin(GL_LINES);
                glVertex2f(primeiroPonto.x, primeiroPonto.y);
                glVertex2f(x, y);
            glEnd();
            glFlush();
            primeiroPonto.x = x;
            primeiroPonto.y = y;
        }
        else if(contadorCliques >= 3) {
            glClear(GL_COLOR_BUFFER_BIT);
            glFlush();
            contadorCliques = 1;
            primeiroPonto.x = x;
            primeiroPonto.y = y;
            temPrimeiroPonto = true;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Linhas por Cliques");

    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 640, 0, 480);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
