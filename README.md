# Visualizador 3D de Números Primos con OpenGL

![OpenGL](https://img.shields.io/badge/OpenGL-1.0+-green)
![GLUT](https://img.shields.io/badge/GLUT-3.7+-blue)
![OpenGL Visualization](https://img.shields.io/badge/OpenGL-3D%20Visualization-blue)
![Screenshot 2025-02-15 105414copi](https://github.com/user-attachments/assets/291fe06e-7eee-4d03-8603-11290bb1b150)
Visualizador interactivo 3D que representa los primeros 10 millones de números primos mediante coordenadas esféricas, utilizando OpenGL y GLUT.
## 🚀 Características Principales
- **Visualización 3D inmersiva** de números primos como puntos en espacio esférico
- **Controles interactivos**:
  - 🖱️ Rotación orbital con arrastre del botón derecho
  - 🔍 Zoom con teclas `+`/`-`
  - 🎮 Desplazamiento en ejes X/Y/Z (`WASD`, `Q/E`)
- **Optimización de memoria** para manejar grandes conjuntos de datos
- **Cámara dinámica** con proyección en perspectiva
## ⚙️ Requisitos e Instalación
### Dependencias:
- OpenGL
- GLUT
- Compilador C++ (g++/MinGW)

## 🕹️ Controles
| Tecla  | 	Acción |
| --- | ---: |
| W/A/S/D	 |  Movimiento en X/Y |
|Q/E	 |  Movimiento en Z|
|+/-	 |  Zoom|
|ESC 	|   Salir|
|Click Derecho	 |  Movimiento orbital|

## 🔄 Conversión a Coordenadas 3D
Transformación esférica aplicada:
```c
p = theta = fi = numero_primo;
x = p * sin(fi) * cos(theta);
y = p * sin(fi) * sin(theta);
z = p * cos(fi);
```
## 🛠️ Compilación y Ejecución
### Compilacion:
```bash
g++ main.cpp -o visualizador -lglut32 -lopengl32 -lglu32
```
### Ejecucion:
```bash
./visualizador
```
## ⛓️ Dependencias y Ejecución directa
### 🐧 Linux:
```bash
sudo apt update
sudo apt install freeglut3 freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
```
### 🪟 Windows:
Para este proyecto trabaje con `Code::Blocks` como IDE, hay un instalador con compilador que ya trae instalado el openGL 1.0v.

[Code::Blocks](https://github.com/sebolla-gif/Samurai-Game-V1.0/tree/main/CodeBlocks%2017.12%20y%20Allegro%204.2).

Ademas de esto se debe instalar el `GLUT`, que se encuentra desponible en:

[GLUT](https://github.com/sebolla-gif/Coordenadas-Polares-OpenGL/tree/main/glut-3.7.6-bin).

[Setup GLUT in Codeblocks IDE on Windows](https://www.youtube.com/watch?v=oc6lW2gpfPs).

### Ejecución directa en Windows:

En la carpeta `bin` hay un ejecutable de programa en formato `.exe`, la carpeta tambien contiene los archivos binarios con los nuemros primos.
El ejecutable necesita contener en la raiz del programa el archivo `10M.bin` y el `.dll` de la carpeta [GLUT](https://github.com/sebolla-gif/Coordenadas-Polares-OpenGL/tree/main/glut-3.7.6-bin).

* En caso de querer usar otro archivo binario, tanto en windows como en linux, se debe modificar la ruta del archivo en la funcion `LoadPolarData()`.

Ejemplo:
```c
PolarData* LoadPolarData()
{
    PolarData* data = new PolarData();
    FILE* f = fopen("C:\\Program Files (x86)\\CodeBlocks\\MinGW\\bin\\10M.bin", "rb");
```
## Mejoras futuras
- Implementar VBOs para mejorar el rendimiento del renderizado. (Para esto se debe trabajar con versiones mas actuales de OpenGL)
- Añadir soporte para múltiples archivos de datos. (Ej .txt)
- Desarrollar una interfaz gráfica para la selección de archivos. (QT)
  
En el futuro, se planea integrar los proyectos [NumerosPrimos](https://github.com/sebolla-gif/NumerosPrimos), [Coordenadas-Polares-OpenGL](https://github.com/sebolla-gif/Coordenadas-Polares-OpenGL) y este mismo, con el objetivo de desarrollar una interfaz que sirva tanto para calcular como para graficar los números.

## Licencia

MIT License © 2025 Sebastián Vaccaro

