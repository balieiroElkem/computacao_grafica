#include <gl/glut.h>
#include <gl/glu.h>
#include <stdio.h>
#include <cmath>

// Variáveis para controle do tanque
float angleX = 0.0f, angleY = 0.0f;
float turretAngleY = 0.0f; // Rotação da torre
float posX = 0.0f, posY = 0.0f, posZ = 0.0f; // Posição do tanque
float lastMouseX, lastMouseY;
bool mouseDown = false;

// Função para desenhar um cilindro
void drawCylinder(GLfloat radius, GLfloat height) {
    GLUquadric *quadric = gluNewQuadric();
    gluCylinder(quadric, radius, radius, height, 32, 32);
    gluDeleteQuadric(quadric);
}

// Função para desenhar o tanque
void drawTank() {
    // Corpo do tanque
    glPushMatrix();
    glColor3f(1.0f, 0.8f, 0.9f);
    glScalef(1.0f, 0.5f, 1.2f); 
    glutSolidCube(1.0f);
    glPopMatrix();

    // Torre do tanque
    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.7f);
    glTranslatef(0.0f, 0.3f, 0.0f);
    glRotatef(turretAngleY, 0.0f, 1.0f, 0.0f); // Rotação da torre
    glScalef(0.5f, 0.3f, 0.5f); 
    glutSolidCube(1.0f);
    glPopMatrix();

    // Canhão do tanque
    glPushMatrix();
    glColor4f(0.576f, 0.133f, 0.722f, 0.8f);
    glTranslatef(0.0f, 0.3f, 0.3f);
    glRotatef(-90, 1.0f, 0.0f, 0.0f); 
    drawCylinder(0.05f, 1.0f);
    glPopMatrix();

    // Esteiras do tanque - Esquerda
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(-0.6f, -0.25f, 0.0f);
    glScalef(0.1f, 0.2f, 1.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Esteiras do tanque - Direita
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(0.6f, -0.25f, 0.0f);
    glScalef(0.1f, 0.2f, 1.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Rodas do tanque - Esquerda
    for (int i = -1; i <= 2; i++) {
        glPushMatrix();
        glColor3f(0.6f, 0.6f, 0.6f);
        glTranslatef(-0.7f, -0.3f, -0.14 + i * 0.4f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        drawCylinder(0.15f, 0.1f);
        glPopMatrix();
    }

    // Rodas do tanque - Direita
    for (int i = -1; i <= 2; i++) {
        glPushMatrix();
        glColor3f(0.6f, 0.6f, 0.6f);
        glTranslatef(0.6f, -0.3f, -0.14 + i * 0.4f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        drawCylinder(0.15f, 0.1f);
        glPopMatrix();
    }
}

// Função de exibição
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -7.0f);  // Posição da câmera
    glTranslatef(posX, posY, posZ);   // Posição do tanque
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);  // Inclinação do tanque
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);  // Rotação do tanque

    drawTank();

    glutSwapBuffers();
}

// Função chamada quando uma tecla é pressionada
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Move o tanque para frente
            posZ += 0.1f * cos(angleY * M_PI / 180.0f);
            posX += 0.1f * sin(angleY * M_PI / 180.0f);
            break;
        case 's': // Move o tanque para trás
            posZ -= 0.1f * cos(angleY * M_PI / 180.0f);
            posX -= 0.1f * sin(angleY * M_PI / 180.0f);
            break;
        case 'a': // Rotaciona o tanque para a esquerda
            angleY -= 5.0f;
            break;
        case 'd': // Rotaciona o tanque para a direita
            angleY += 5.0f;
            break;
        case 27: // Esc para sair
            exit(0);
    }
    glutPostRedisplay();
}

// Função chamada quando uma tecla especial é pressionada (setas do teclado)
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: // Rotaciona a torre para a esquerda
            turretAngleY -= 5.0f;
            break;
        case GLUT_KEY_RIGHT: // Rotaciona a torre para a direita
            turretAngleY += 5.0f;
            break;
    }
    glutPostRedisplay();
}

// Função para lidar com movimento do mouse
void mouseMotion(int x, int y) {
    if (mouseDown) {
        angleY += (x - lastMouseX) * 0.3f;
        angleX += (y - lastMouseY) * 0.3f;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

// Função para lidar com clique do mouse
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseDown = true;
        lastMouseX = x;
        lastMouseY = y;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mouseDown = false;
    }
}

// Função de inicialização
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tank 3D");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);        // Define a função para teclas normais
    glutSpecialFunc(specialKeys);      // Define a função para teclas especiais (setas)
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutMainLoop();

    return 0;
}
