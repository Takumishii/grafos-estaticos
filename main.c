#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _NodoL {
  int vertice;
  struct _NodoL *siguiente;
};

struct _NodoG {
  int coloracion;
  char colorsito[10];
  struct _NodoL *adyacentes;
};

struct _NodoG *agregarNodo();
void agregarArista(struct _NodoG *grafo[], int vertice1, int vertice2);
void configurarGrafo(struct _NodoG *grafo[]);
void colorearGrafo(struct _NodoG *grafo[], int n);
void mostrar(struct _NodoG *grafo[], int n);

int main() {
  int n = 10;
  struct _NodoG *grafo[n];
  for (int i = 0; i < n; i++) {
    grafo[i] = agregarNodo();
  }

  configurarGrafo(grafo);

  colorearGrafo(grafo, n);

  mostrar(grafo, n);

  for (int i = 0; i < n; i++) {
    struct _NodoL *actual = grafo[i]->adyacentes;
    while (actual != NULL) {
      struct _NodoL *temp = actual;
      actual = actual->siguiente;
      free(temp);
    }
    free(grafo[i]);
  }

  return 0;
}

struct _NodoG *agregarNodo() {
  struct _NodoG *nuevoNodo = (struct _NodoG *)malloc(sizeof(struct _NodoG));
  nuevoNodo->coloracion = -1;
  nuevoNodo->adyacentes = NULL;
  return nuevoNodo;
}

void agregarArista(struct _NodoG *grafo[], int vertice1, int vertice2) {
  struct _NodoL *nuevoNodo1 = (struct _NodoL *)malloc(sizeof(struct _NodoL));
  nuevoNodo1->vertice = vertice2;
  nuevoNodo1->siguiente = grafo[vertice1]->adyacentes;
  grafo[vertice1]->adyacentes = nuevoNodo1;

  struct _NodoL *nuevoNodo2 = (struct _NodoL *)malloc(sizeof(struct _NodoL));
  nuevoNodo2->vertice = vertice1;
  nuevoNodo2->siguiente = grafo[vertice2]->adyacentes;
  grafo[vertice2]->adyacentes = nuevoNodo2;
}

void configurarGrafo(struct _NodoG *grafo[]) {
  // pentagono
  for (int i = 0; i < 5; i++) {
    agregarArista(grafo, i, (i + 1) % 5);
  }

  // estrella
  for (int i = 0; i < 5; i++) {
    agregarArista(grafo, 5 + i, 5 + ((i + 2) % 5));
  }

  // conectar
  for (int i = 0; i < 5; i++) {
    agregarArista(grafo, i, i + 5);
  }
}
// solucion del problema
void colorearGrafo(struct _NodoG *grafo[], int n) {
  const char *colores[] = {"", "azul", "rojo", "verde"};
  int num_colores = 3;
  int colores_usados[n];

  for (int i = 0; i < n; i++) {
    colores_usados[i] = 0;
  }

  grafo[0]->coloracion = 1;
  strcpy(grafo[0]->colorsito, colores[1]);

  for (int i = 1; i < n; i++) {
    struct _NodoL *actual = grafo[i]->adyacentes;
    while (actual != NULL) {
      if (grafo[actual->vertice]->coloracion != -1) {
        colores_usados[grafo[actual->vertice]->coloracion] = 1;
      }
      actual = actual->siguiente;
    }

    int color;
    for (color = 1; color <= num_colores; color++) {
      if (colores_usados[color] == 0) {
        break;
      }
    }

    grafo[i]->coloracion = color;
    strcpy(grafo[i]->colorsito, colores[color]);

    actual = grafo[i]->adyacentes;
    while (actual != NULL) {
      if (grafo[actual->vertice]->coloracion != -1) {
        colores_usados[grafo[actual->vertice]->coloracion] = 0;
      }
      actual = actual->siguiente;
    }
  }
}

void mostrar(struct _NodoG *grafo[], int n) {
  for (int i = 0; i < n; i++) {
    const char *grupo = (i < 5) ? "Pentágono" : "Estrella";
    printf("Vértice %d (%s): Color %d (%s)\n", i, grupo, grafo[i]->coloracion,
           grafo[i]->colorsito);
    printf("  Conectado a: ");
    struct _NodoL *actual = grafo[i]->adyacentes;
    while (actual != NULL) {
      printf("%d (%s) ", actual->vertice, grafo[actual->vertice]->colorsito);
      actual = actual->siguiente;
    }
    printf("\n");
  }
}
