#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float scaleVal = 1.0f;
float angleDeg = 0.0f;
float transX = 0.0f, transY = 0.0f;

const float minScale = 0.2f;
const float maxScale = 5.0f;

const float nameWidth = 0.7f;
const float nameHeight = 0.2f;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(transX, transY, 0.0f);
    glRotatef(angleDeg, 0.0f, 0.0f, 1.0f);
    glScalef(scaleVal, scaleVal, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);

        glVertex2f(0.0f, -0.1f); glVertex2f(0.0f, 0.1f);
        glVertex2f(0.0f, 0.1f);  glVertex2f(0.05f, 0.0f);
        glVertex2f(0.05f, 0.0f); glVertex2f(0.1f, 0.1f);
        glVertex2f(0.1f, 0.1f);  glVertex2f(0.1f, -0.1f);

        glVertex2f(0.15f, -0.1f); glVertex2f(0.2f, 0.1f);
        glVertex2f(0.2f, 0.1f);   glVertex2f(0.25f, -0.1f);
        glVertex2f(0.17f, 0.0f);  glVertex2f(0.23f, 0.0f);

        glVertex2f(0.3f, -0.1f);  glVertex2f(0.3f, 0.1f);
        glVertex2f(0.3f, 0.1f);   glVertex2f(0.35f, 0.1f);
        glVertex2f(0.35f, 0.1f);  glVertex2f(0.35f, 0.0f);
        glVertex2f(0.35f, 0.0f);  glVertex2f(0.3f, 0.0f);
        glVertex2f(0.3f, 0.0f);   glVertex2f(0.36f, -0.1f);

        glVertex2f(0.45f, 0.1f);  glVertex2f(0.4f, 0.1f);
        glVertex2f(0.4f, 0.1f);   glVertex2f(0.4f, -0.1f);
        glVertex2f(0.4f, -0.1f);  glVertex2f(0.45f, -0.1f);

        glVertex2f(0.5f, -0.1f);  glVertex2f(0.5f, 0.1f);
        glVertex2f(0.5f, 0.1f);   glVertex2f(0.6f, 0.1f);
        glVertex2f(0.6f, 0.1f);   glVertex2f(0.6f, -0.1f);
        glVertex2f(0.6f, -0.1f);  glVertex2f(0.5f, -0.1f);

        glVertex2f(0.65f, 0.1f);  glVertex2f(0.7f, 0.1f);
        glVertex2f(0.65f, 0.1f);  glVertex2f(0.65f, 0.0f);
        glVertex2f(0.65f, 0.0f);  glVertex2f(0.7f, 0.0f);
        glVertex2f(0.7f, 0.0f);   glVertex2f(0.7f, -0.1f);
        glVertex2f(0.65f, -0.1f); glVertex2f(0.7f, -0.1f);
    glEnd();

    glFlush();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-0.2, 0.9, -0.25, 0.25);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    int changed = 0;
    switch (key) {
        case '+':
            scaleVal *= 1.1f;
            if (scaleVal > maxScale) scaleVal = maxScale;
            changed = 1;
            break;
        case '-':
            scaleVal /= 1.1f;
            if (scaleVal < minScale) scaleVal = minScale;
            changed = 1;
            break;
        case 'q': case 'Q':
            angleDeg += 5.0f;
            if (angleDeg >= 360.0f) angleDeg -= 360.0f;
            changed = 1;
            break;
        case 'e': case 'E':
            angleDeg -= 5.0f;
            if (angleDeg <= -360.0f) angleDeg += 360.0f;
            changed = 1;
            break;
        case 'a': case 'A':
            transX -= 0.05f;
            changed = 1;
            break;
        case 'd': case 'D':
            transX += 0.05f;
            changed = 1;
            break;
        case 'w': case 'W':
            transY += 0.05f;
            changed = 1;
            break;
        case 's': case 'S':
            transY -= 0.05f;
            changed = 1;
            break;
        case 27:
            scaleVal = 1.0f; angleDeg = 0.0f; transX = 0.0f; transY = 0.0f;
            changed = 1;
            break;
    }

    float halfVisibleWidth = (0.9f + 0.2f) / 2.0f;
    float halfVisibleHeight = (0.25f + 0.25f) / 2.0f;
    float halfNameWidth = (nameWidth * scaleVal) / 2.0f;
    float halfNameHeight = (nameHeight * scaleVal) / 2.0f;

    if (transX > halfVisibleWidth - halfNameWidth) transX = halfVisibleWidth - halfNameWidth;
    if (transX < -halfVisibleWidth + halfNameWidth) transX = -halfVisibleWidth + halfNameWidth;
    if (transY > halfVisibleHeight - halfNameHeight) transY = halfVisibleHeight - halfNameHeight;
    if (transY < -halfVisibleHeight + halfNameHeight) transY = -halfVisibleHeight + halfNameHeight;

    if (changed) glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("MARCOS");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    printf("Controles:\n");
    printf("  + / - : aumenta/diminui escala\n");
    printf("  q / e : rotaciona\n");
    printf("  w/a/s/d : translada\n");
    printf("  ESC : reset\n");

    glutMainLoop();
    return 0;
}
