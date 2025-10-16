#include <windows.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

// Quadrado
GLfloat squareX = 100.0f;
GLfloat squareY = 150.0f;
GLsizei rsize = 50;

// Vetor de translacao do quadrado
GLfloat xstep = 3.0f;
GLfloat ystep = 3.0f;

// Círculo
GLfloat circleX = 320.0f;
GLfloat circleY = 240.0f;
GLfloat circleRadius = 30.0f;
GLfloat circleSpeed = 5.0f;

GLfloat windowWidth;
GLfloat windowHeight;

bool colidindo = false;

// Função para desenhar um círculo
void DesenhaCirculo(GLfloat x, GLfloat y, GLfloat radius)
{
    float ang, dx, dy;
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 360; i++)
    {
        ang = (i * 3.14159f) / 180.0f;
        dx = x + (cos(ang) * radius);
        dy = y + (sin(ang) * radius);
        glVertex2f(dx, dy);
    }
    glEnd();
}

// Função para verificar colisão entre círculo e retângulo
bool VerificaColisao()
{
    // Encontra o ponto mais próximo do círculo no retângulo
    GLfloat closestX = fmax(squareX, fmin(circleX, squareX + rsize));
    GLfloat closestY = fmax(squareY, fmin(circleY, squareY + rsize));

    // Calcula a distância entre o círculo e este ponto mais próximo
    GLfloat distanceX = circleX - closestX;
    GLfloat distanceY = circleY - closestY;

    // Se a distância for menor que o raio do círculo, há colisão
    GLfloat distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
    return distanceSquared < (circleRadius * circleRadius);
}

void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o quadrado
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2i(squareX, squareY+rsize);
        glVertex2i(squareX, squareY);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2i(squareX+rsize, squareY);
        glVertex2i(squareX+rsize, squareY+rsize);
    glEnd();

    // Desenha o círculo (verde)
    glLineWidth(3);
    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    DesenhaCirculo(circleX, circleY, circleRadius);

    glutSwapBuffers();
}

void Timer(int value)
{
    // Muda a direção quando chega na borda esquerda ou direita
    if(squareX > windowWidth-rsize || squareX < 0)
        xstep = -xstep;

    // Muda a direção quando chega na borda superior ou inferior
    if(squareY > windowHeight-rsize || squareY < 0)
        ystep = -ystep;

    // Verificação de bordas. Se a window for menor e o quadrado sair do volume de visualização
    if(squareX > windowWidth-rsize)
        squareX = windowWidth-rsize-1;

    if(squareY > windowHeight-rsize)
        squareY = windowHeight-rsize-1;

    squareX += xstep;
    squareY += ystep;

    // Verifica colisão
    colidindo = VerificaColisao();
    if(colidindo)
    {
        printf("COLISAO DETECTADA!\n");
    }

    glutPostRedisplay();
    glutTimerFunc(5, Timer, 0);
}

// Função para controlar o círculo com as setas do teclado
void TeclasEspeciais(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            circleY += circleSpeed;
            if(circleY + circleRadius > windowHeight)
                circleY = windowHeight - circleRadius;
            break;
        case GLUT_KEY_DOWN:
            circleY -= circleSpeed;
            if(circleY - circleRadius < 0)
                circleY = circleRadius;
            break;
        case GLUT_KEY_LEFT:
            circleX -= circleSpeed;
            if(circleX - circleRadius < 0)
                circleX = circleRadius;
            break;
        case GLUT_KEY_RIGHT:
            circleX += circleSpeed;
            if(circleX + circleRadius > windowWidth)
                circleX = windowWidth - circleRadius;
            break;
    }

    glutPostRedisplay();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    printf("\n w: %d      h: %d ", w, h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    windowWidth = w;
    windowHeight = h;
    gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(300, 250);
    glutCreateWindow("Animacao com Colisao");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutSpecialFunc(TeclasEspeciais);
    glutTimerFunc(5, Timer, 0);
    glutMainLoop();

    return 0;
}
