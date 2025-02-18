#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <cmath>

#define M_PI 3.1416f

struct PolarData
{
    unsigned long int* numbers;
    unsigned long count;
    float* vertices;
};

namespace
{
float zoom = 1.0f;
float offsetX = 0.0f, offsetY = 0.0f, offsetZ = 0.0f;
PolarData* polarData = nullptr;
int screenWidth, screenHeight;
float camTheta = 1.0f;       // Ángulo horizontal (radianes)
float camPhi = 1.0f;  // Ángulo vertical (radianes)
float camDistance = 50.0f;   // Distancia desde el objetivo
float panX = 0.0f, panY = 0.0f; // Desplazamiento del objetivo
int lastMouseX, lastMouseY;  // Última posición del mouse
bool rotating = false;       // Bandera para rotación
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            rotating = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else
        {
            rotating = false;
        }
    }
}

void motion(int x, int y)
{
    if (rotating)
    {
        // Calcular diferencia de movimiento
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;
        lastMouseX = x;
        lastMouseY = y;

        // Actualizar ángulos
        camTheta += deltaX * 0.01f;
        camPhi += deltaY * 0.01f;

        // Limitar ángulo vertical para evitar inversiones
        //camPhi = std::max(0.1f, std::min((float)M_PI - 0.1f, camPhi));

        glutPostRedisplay();
    }
}

PolarData* LoadPolarData()
{
    PolarData* data = new PolarData();
    FILE* f = fopen("10M.bin", "rb");
    if (f)
    {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        rewind(f);

        data->count = size / sizeof(unsigned long int);
        data->numbers = new unsigned long int[data->count];
        size_t read = fread(data->numbers, sizeof(unsigned long int), data->count, f);
        // Verificar si la lectura fue exitosa
        if (read != data->count)
        {
            std::cerr << "Error leyendo los datos." << std::endl;
            delete[] data->numbers;
            delete data;
            return nullptr;
        }
        // Verificar el cierre del archivo
        if (fclose(f) != 0)
        {
            std::cerr << "Error al cerrar el archivo." << std::endl;
            delete[] data->numbers;
            delete data;
            return nullptr;
        }
        data->vertices = new float[data->count * 3];
        int aux = 0;
        for (unsigned long i = 0; i < data->count; i++)//por cada ciclo del bucle el vector almacena 3 valores (las coordenadas).
        {
            double p,theta,fi;
            p = theta = fi = data->numbers[i];
            data->vertices[aux]     = static_cast<float>(p * sin(fi) * cos(theta));
            data->vertices[aux + 1] = static_cast<float>(p * sin(fi) * sin(theta));
            data->vertices[aux + 2] = static_cast<float>(p * cos(fi));
            aux = aux + 3;
        }

        return data;
    }
    delete data;
    return nullptr;
}

void Cleanup()
{
    if (polarData)
    {
        delete[] polarData->numbers;
        delete[] polarData->vertices;
        delete polarData;
        polarData = nullptr; // Add this line
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Calcular posición de la cámara (coordenadas esféricas)
    float eyeX = camDistance * sin(camPhi) * cos(camTheta) + panX;
    float eyeY = camDistance * cos(camPhi) + panY;
    float eyeZ = camDistance * sin(camPhi) * sin(camTheta);

    // Configurar vista

    gluLookAt(eyeX, eyeY, eyeZ,   // Posición cámara
              panX, panY, 0.0f,   // Punto de enfoque
              0.0f, 1.0f, 0.0f);  // Vector "up"

    glPushMatrix();
    glScalef(zoom, zoom, zoom);
    glTranslatef(offsetX, offsetY, offsetZ);
    // Dibujar puntos (sin transformaciones adicionales)
    glColor3f(0, 1, 0);
    glPointSize(0.0f);
    glBegin(GL_POINTS);
    for (unsigned long i = 0; i < polarData->count * 3; i += 3)
    {
        glVertex3f(polarData->vertices[i],
                   polarData->vertices[i + 1],
                   polarData->vertices[i + 2]);
    }

    glEnd();

    glutSwapBuffers();
}

// Función para manejar teclas
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '+': // Aumentar zoom
        zoom *= 1.2f;
        break;
    case '-': // Reducir zoom
        zoom /= 1.2f;
        break;
    case 'w': // Mover hacia arriba
        offsetY += 10.1f / zoom;
        break;
    case 's': // Mover hacia abajo
        offsetY -= 10.1f / zoom;
        break;
    case 'a': // Mover hacia la izquierda
        offsetX -= 10.1f / zoom;
        break;
    case 'd': // Mover hacia la derecha
        offsetX += 10.1f / zoom;
        break;
    // Añadir en teclado:
    case 'q':
        offsetZ += 10.1f / zoom;
        break;  // Mover hacia adelante
    case 'e':
        offsetZ -= 10.1f / zoom;
        break;  // Mover hacia atrás
    case 27: // Esc para salir
        exit(0);
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("Visualizador 3D");
    glEnable(GL_DEPTH_TEST);

    // Configurar proyección 3D
    screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, (double)screenWidth / screenHeight, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    polarData = LoadPolarData();
    if (!polarData)
        return 1;

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);
    atexit(Cleanup);

    glutMainLoop();
    return 0;
}
