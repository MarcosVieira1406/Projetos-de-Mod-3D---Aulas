// Marcos Eduardo - Projeto modificado: desenha "MARCOS" e aplica transformações
// Compile: g++ marcos.cpp -o marcos -lGL -lGLU -lglut

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

// Estado de transformação
float scaleVal = 1.0f;
float angleDeg = 0.0f; // rotação em graus
float transX = 0.0f, transY = 0.0f;

// Parâmetros do layout das letras (em unidades do sistema de coordenadas do modelo)
const float letterW = 0.6f;   // largura de cada letra
const float letterH = 2.0f;   // altura de cada letra
const float spacing = 0.15f;  // espaço entre letras

// Número de letras em "MARCOS"
const int nLetters = 6;

// cálculo da largura total (sem escala)
const float totalWidth = nLetters * letterW + (nLetters - 1) * spacing; // largura total do nome
const float halfTotalWidth = totalWidth / 2.0f;
const float halfHeight = letterH / 2.0f;

// limites do "mundo" (mesma ortho usada)
const float worldLimit = 3.0f;

// cores aleatórias (usadas ao clicar)
float lastR = 0.0f, lastG = 1.0f, lastB = 0.0f;

// evita escala muito pequena que "apague" visualmente
const float minScale = 0.2f;
const float maxScale = 5.0f;

// Função utilitária para limitar translação para que o conjunto não saia da janela
void clampTranslation() {
    // com escala atual, metade da largura ocupada é:
    float halfWScaled = halfTotalWidth * scaleVal;
    float halfHScaled = halfHeight * scaleVal;

    float maxTx = max(0.0f, worldLimit - halfWScaled);
    float maxTy = max(0.0f, worldLimit - halfHScaled);

    transX = std::max(-maxTx, std::min(maxTx, transX));
    transY = std::max(-maxTy, std::min(maxTy, transY));
}

// --- funções que desenham letras centradas na origem de cada "caixa de letra" ---
// Cada letra ocupa um retângulo de largura letterW e altura letterH, centrado em (0,0).
// Usamos linhas grossas para formar as letras (pode-se trocar por polígonos).

void drawM() {
    float w = letterW, h = letterH;
    float left = -w/2, right = w/2, top = h/2, bottom = -h/2;
    glBegin(GL_LINES);
        glVertex2f(left, bottom); glVertex2f(left, top);   // perna esquerda
        glVertex2f(left, top); glVertex2f(0.0f, 0.0f);     // diagonal para o centro
        glVertex2f(0.0f, 0.0f); glVertex2f(right, top);    // diagonal para a outra perna
        glVertex2f(right, top); glVertex2f(right, bottom); // perna direita
    glEnd();
}

void drawA() {
    float w = letterW, h = letterH;
    float left = -w/2, right = w/2, top = h/2, bottom = -h/2;
    glBegin(GL_LINES);
        glVertex2f(left, bottom); glVertex2f(0.0f, top);   // perna esquerda -> topo
        glVertex2f(0.0f, top); glVertex2f(right, bottom);  // topo -> perna direita
        glVertex2f(left + w*0.15f, 0.0f); glVertex2f(right - w*0.15f, 0.0f); // barra do A
    glEnd();
}

void drawR() {
    float w = letterW, h = letterH;
    float left = -w/2, right = w/2, top = h/2, bottom = -h/2;
    float midY = 0.0f;
    glBegin(GL_LINES);
        glVertex2f(left, bottom); glVertex2f(left, top); // tronco
        glVertex2f(left, top); glVertex2f(right - w*0.05f, top); // topo horizontal leve
        glVertex2f(right - w*0.05f, top); glVertex2f(right - w*0.05f, midY + h*0.05f); // curva superior (linearizada)
        glVertex2f(right - w*0.05f, midY + h*0.05f); glVertex2f(left + w*0.05f, midY); // conectar ao tronco (parte interior)
        // perna inclinada do R
        glVertex2f(left + w*0.05f, midY); glVertex2f(right, bottom);
    glEnd();
}

void drawC() {
    float w = letterW, h = letterH;
    float left = -w/2, right = w/2, top = h/2, bottom = -h/2;
    glBegin(GL_LINES);
        glVertex2f(right, top - h*0.1f); glVertex2f(left, top - h*0.1f);
        glVertex2f(left, top - h*0.1f); glVertex2f(left, bottom + h*0.1f);
        glVertex2f(left, bottom + h*0.1f); glVertex2f(right, bottom + h*0.1f);
    glEnd();
}

void drawO() {
    float w = letterW, h = letterH;
    float left = -w/2, right = w/2, top = h/2, bottom = -h/2;
    // aproximamos um "O" por retângulo com cantos
    glBegin(GL_LINE_LOOP);
        glVertex2f(left, bottom);
        glVertex2f(left, top);
        glVertex2f(right, top);
        glVertex2f(right, bottom);
    glEnd();
}

void drawS() {
    float w = letterW, h = letterH;
    float left = -w/2, right = w/2, top = h/2, bottom = -h/2;
    float midY = 0.0f;
    glBegin(GL_LINES);
        glVertex2f(right, top); glVertex2f(left, top);
        glVertex2f(left, top); glVertex2f(left, midY);
        glVertex2f(left, midY); glVertex2f(right, midY);
        glVertex2f(right, midY); glVertex2f(right, bottom);
        glVertex2f(right, bottom); glVertex2f(left, bottom);
    glEnd();
}

// desenha o nome MARCOS centrado em x=0 (modelo)
void drawName() {
    // cor principal
    glColor3f(lastR, lastG, lastB);
    // configuramos largura de linha
    glLineWidth(6.0f);

    // começamos à esquerda (centro do primeiro bloco)
    float startX = -halfTotalWidth + letterW/2.0f;

    // letra M
    glPushMatrix();
        glTranslatef(startX + 0 * (letterW + spacing), 0.0f, 0.0f);
        drawM();
    glPopMatrix();

    // letra A
    glPushMatrix();
        glTranslatef(startX + 1 * (letterW + spacing), 0.0f, 0.0f);
        drawA();
    glPopMatrix();

    // letra R
    glPushMatrix();
        glTranslatef(startX + 2 * (letterW + spacing), 0.0f, 0.0f);
        drawR();
    glPopMatrix();

    // letra C
    glPushMatrix();
        glTranslatef(startX + 3 * (letterW + spacing), 0.0f, 0.0f);
        drawC();
    glPopMatrix();

    // letra O
    glPushMatrix();
        glTranslatef(startX + 4 * (letterW + spacing), 0.0f, 0.0f);
        drawO();
    glPopMatrix();

    // letra S
    glPushMatrix();
        glTranslatef(startX + 5 * (letterW + spacing), 0.0f, 0.0f);
        drawS();
    glPopMatrix();
}

// --- callbacks ---

void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT);

    // setup de projeção (área de enquadramento)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-worldLimit, worldLimit, -worldLimit, worldLimit);

    // aplicar transformações do modelo: translate -> rotate -> scale (são aplicadas em ordem reversa na pilha)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(transX, transY, 0.0f);
    glRotatef(angleDeg, 0.0f, 0.0f, 1.0f);
    glScalef(scaleVal, scaleVal, 1.0f);

    drawName();

    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    // mantemos ortho fixo em -3..3 para simples correspondência com worldLimit
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    bool changed = false;
    switch (key) {
        case '+':
            scaleVal *= 1.1f;
            if (scaleVal > maxScale) scaleVal = maxScale;
            changed = true;
            break;
        case '-':
            scaleVal /= 1.1f;
            if (scaleVal < minScale) scaleVal = minScale;
            changed = true;
            break;
        case 'q': // rotação anti-horária
        case 'Q':
            angleDeg += 5.0f;
            if (angleDeg >= 360.0f) angleDeg -= 360.0f;
            changed = true;
            break;
        case 'e': // rotação horária
        case 'E':
            angleDeg -= 5.0f;
            if (angleDeg <= -360.0f) angleDeg += 360.0f;
            changed = true;
            break;
        case 'a': // esquerda
        case 'A':
            transX -= 0.15f;
            changed = true;
            break;
        case 'd': // direita
        case 'D':
            transX += 0.15f;
            changed = true;
            break;
        case 'w': // cima
        case 'W':
            transY += 0.15f;
            changed = true;
            break;
        case 's': // baixo
        case 'S':
            transY -= 0.15f;
            changed = true;
            break;
        case 27: // ESC - reset
            scaleVal = 1.0f; angleDeg = 0.0f; transX = transY = 0.0f;
            changed = true;
            break;
    }

    if (changed) {
        // garante que, após transformar, o nome não saia da área visível
        clampTranslation();
        glutPostRedisplay();
    }
}

void mouseCallback(int button, int state, int mx, int my) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // altera cor do nome aleatoriamente
        lastR = (rand() % 10) / 10.0f;
        lastG = (rand() % 10) / 10.0f;
        lastB = (rand() % 10) / 10.0f;
        glutPostRedisplay();
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // limpa tela e reseta transformações
        scaleVal = 1.0f; angleDeg = 0.0f; transX = transY = 0.0f;
        lastR = 0; lastG = 1; lastB = 0;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    srand((unsigned)time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("MARCOS - Transformacoes Afins (Teclas)");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseCallback);

    // instruções no console
    printf("Controles:\n");
    printf("  + : aumenta escala\n");
    printf("  - : diminui escala (limitado para nao sumir)\n");
    printf("  q : rotaciona anti-horario\n");
    printf("  e : rotaciona horario\n");
    printf("  a : translacao esquerda\n");
    printf("  d : translacao direita\n");
    printf("  w : translacao cima\n");
    printf("  s : translacao baixo\n");
    printf("  ESC : reset (posicao/escala/rotacao)\n");
    printf("  Click esquerdo : muda cor do nome\n");
    printf("  Click direito : reseta e limpa\n");

    glutMainLoop();
    return 0;
}
