#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "productos.h"

struct Producto* cargarProductos(int *total) {
    FILE *f = fopen("producto.txt", "r");
    if (!f) {
        *total = 0;
        return NULL;
    }

    int capacidad = 10;
    *total = 0;
    struct Producto *productos = malloc(capacidad * sizeof(struct Producto));

    char linea[200];
    while (fgets(linea, sizeof(linea), f)) {
        if (*total >= capacidad) {
            capacidad *= 2;
            productos = realloc(productos, capacidad * sizeof(struct Producto));
        }

        linea[strcspn(linea, "\n")] = 0;
        char *token = strtok(linea, ",");
        if (token) strcpy(productos[*total].codigo, token);
        token = strtok(NULL, ",");
        if (token) strcpy(productos[*total].nombre, token);
        token = strtok(NULL, ",");
        if (token) productos[*total].cantidad = atoi(token);
        token = strtok(NULL, ",");
        if (token) productos[*total].costo = atof(token);
        token = strtok(NULL, ",");
        if (token) productos[*total].precio_venta = atof(token);

        (*total)++;
    }
    fclose(f);
    return productos;
}

void guardarProductos(struct Producto *productos, int total) {
    FILE *f = fopen("producto.txt", "w");
    if (!f) return;
    for (int i = 0; i < total; i++) {
        fprintf(f, "%s,%s,%d,%.2f,%.2f\n", productos[i].codigo, productos[i].nombre, productos[i].cantidad, productos[i].costo, productos[i].precio_venta);
    }
    fclose(f);
}

int obtenerUltimoNumFactura() {
    FILE *f = fopen("ventas.txt", "r");
    if (!f) return 0;

    int ultimoNum = 0;
    char linea[300];
    while (fgets(linea, sizeof(linea), f)) {
        char *token = strtok(linea, ",");
        if (token) {
            ultimoNum = atoi(token);
        }
    }
    fclose(f);
    return ultimoNum;
}

void registrarVenta(struct DetalleVenta *detalles, int totalDetalles, int numFactura) {
    FILE *f = fopen("ventas.txt", "a");
    if (!f) return;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char fecha[12];
    sprintf(fecha, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    for (int i = 0; i < totalDetalles; i++) {
        fprintf(f, "%d,%s,%s,%d,%.2f,%.2f,%s\n", 
                numFactura, detalles[i].codigo, detalles[i].nombre, 
                detalles[i].cantidad_a_vender, detalles[i].costo, 
                detalles[i].precio_venta, fecha);
    }
    fclose(f);
}
