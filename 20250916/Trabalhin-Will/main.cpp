#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float scaleVal = 1.0f;
float angleDeg = 0.0f;
float transX = 0.0f, transY = 0.0f;

const float letterW = 0.6f;
const float letterH = 2.0f;
const float spacing = 0.15f;
const int nLetters = 6;

const float totalWidth = 6 * letterW + (6 - 1) * spacing;
const float halfTotalWidth = (6 * letterW + (6 - 1) * spacing) / 2.0f;
const float halfHeight = letterH / 2.0f;

const float worldLimit = 3.0f;

const float colorR = 0.0f, colorG = 1.0f, colorB = 0.0f;
const float bgR = 0.0f, bgG = 0.0f, bgB = 0.7f;

const float minScale = 0.2f;
const float maxScale = 5.0f;

void clampTranslation(void) {
    float halfWScaled = halfTotalWidth * scaleVal;
    float halfHScaled = halfHeight * scaleVal;

    float maxTx = worldLimit - halfWScaled;
    if (maxTx < 0.0f) maxTx = 0.0f;

    float maxTy = worldLimit - halfHScaled;
    if (maxTy < 0.0f) maxTy = 0.0f;

    if (transX > maxTx) transX = maxTx;
    if (transX < -maxTx) transX = -maxTx;

    if (transY > maxTy) transY = maxTy;
    if (transY < -maxTy) transY = -maxTy;
}

void drawM(void) {
    float w = letterW, h = letterH;
    float l = -w/2.0f, r = w/2.0f, t = h/2.0f, b = -h/2.0f;
    glBegin(GL_LINES);
        glVertex2f(l, b); glVertex2f(l, t);
        glVertex2f(l, t); glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 0.0f); glVertex2f(r, t);
        glVertex2f(r, t); glVertex2f(r, b);
    glEnd();
}

void drawA(void) {
    float w = letterW, h = letterH;
    float l = -w/2.0f, r = w/2.0f, t = h/2.0f, b = -h/2.0f;
    glBegin(GL_LINES);
        glVertex2f(l, b); glVertex2f(0.0f, t);
        glVertex2f(0.0f, t); glVertex2f(r, b);
        glVertex2f(l + w*0.15f, 0.0f); glVertex2f(r - w*0.15f, 0.0f);
    glEnd();
}

void drawR(void) {
    float w = letterW, h = letterH;
    float l = -w/2.0f, r = w/2.0f, t = h/2.0f, b = -h/2.0f;
    float midY = 0.0f;
    glBegin(GL_LINES);
        glVertex2f(l, b); glVertex2f(l, t);
        glVertex2f(l, t); glVertex2f(r - w*0.05f, t);
        glVertex2f(r - w*0.05f, t); glVertex2f(r - w*0.05f, midY + h*0.05f);
        glVertex2f(r - w*0.05f, midY + h*0.05f); glVertex2f(l + w*0.05f, midY);
        glVertex2f(l + w*0.05f, midY); glVertex2f(r, b);
    glEnd();
}

void drawC(void) {
    float w = letterW, h = letterH;
    float l = -w/2.0f, r = w/2.0f, t = h/2.0f, b = -h/2.0f;
    glBegin(GL_LINES);
        glVertex2f(r, t - h*0.1f); glVertex2f(l, t - h*0.1f);
        glVertex2f(l, t - h*0.1f); glVertex2f(l, b + h*0.1f);
        glVertex2f(l, b + h*0.1f); glVertex2f(r, b + h*0.1f);
    glEnd();
}

void drawO(void) {
    float w = letterW, h = letterH;
    float l = -w/2.0f, r = w/2.0f, t = h/2.0f, b = -h/2.0f;
    glBegin(GL_LINE_LOOP);
        glVertex2f(l, b); glVertex2f(l, t);
        glVertex2f(r, t); glVertex2f(r, b);
    glEnd();
}

void drawS(void) {
    float w = letterW, h = letterH;
    float l = -w/2.0f, r = w/2.0f, t = h/2.0f, b = -h/2.0f;
    float midY = 0.0f;
    glBegin(GL_LINES);
        glVertex2f(r, t); glVertex2f(l, t);
        glVertex2f(l, t); glVertex2f(l, midY);
        glVertex2f(l, midY); glVertex2f(r, midY);
        glVertex2f(r, midY); glVertex2f(r, b);
        glVertex2f(r, b); glVertex2f(l, b);
    glEnd();
}

void drawName(void) {
    glColor3f(colorR, colorG, colorB);
    glLineWidth(6.0f);

    float startX = -halfTotalWidth + letterW/2.0f;

    glPushMatrix();
        glTranslatef(startX + 0 * (letterW + spacing), 0.0f, 0.0f);
        drawM();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(startX + 1 * (letterW + spacing), 0.0f, 0.0f);
        drawA();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(startX + 2 * (letterW + spacing), 0.0f, 0.0f);
        drawR();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(startX + 3 * (letterW + spacing), 0.0f, 0.0f);
        drawC();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(startX + 4 * (letterW + spacing), 0.0f, 0.0f);
        drawO();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(startX + 5 * (letterW + spacing), 0.0f, 0.0f);
        drawS();
    glPopMatrix();
}

void displayCallback(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(transX, transY, 0.0f);
    glRotatef(angleDeg, 0.0f, 0.0f, 1.0f);
    glScalef(scaleVal, scaleVal, 1.0f);

    drawName();

    glFlush();
}

void reshapeCallback(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-worldLimit, worldLimit, -worldLimit, worldLimit);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();
}

void keyboardCallback(unsigned char key, int x, int y) {
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
            transX -= 0.15f;
            changed = 1;
            break;
        case 'd': case 'D':
            transX += 0.15f;
            changed = 1;
            break;
        case 'w': case 'W':
            transY += 0.15f;
            changed = 1;
            break;
        case 's': case 'S':
            transY -= 0.15f;
            changed = 1;
            break;
        case 27:
            scaleVal = 1.0f; angleDeg = 0.0f; transX = 0.0f; transY = 0.0f;
            changed = 1;
            break;
    }

    if (changed) {
        clampTranslation();
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("MARCOS - Transformacoes Afins (C puro)");

    glClearColor(bgR, bgG, bgB, 1.0f);

    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);

    printf("Controles:\n");
    printf("  + / - : aumenta/diminui escala\n");
    printf("  q / e : rotaciona\n");
    printf("  w/a/s/d : translada\n");
    printf("  ESC : reset\n");

    glutMainLoop();
    return 0;
}
