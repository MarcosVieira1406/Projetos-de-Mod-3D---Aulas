//Autor: Marcos Eduardo - Projeto: Linha e triangulo 04/09/2025


#include <GL/glut.h>
#include <stdlib.h>

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //define a area de enquadramento do sistema
    gluOrtho2D(-3, 3, -3, 3);
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

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("GLUT Shapes");
    glClearColor(0, 1, 0, 0);
    glutDisplayFunc(display);
    glutMainLoop();
    return EXIT_SUCCESS;
}
