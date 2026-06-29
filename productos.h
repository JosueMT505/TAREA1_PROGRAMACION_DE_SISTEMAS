#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#define MAX_STR 50

struct Producto {
    char codigo[MAX_STR];
    char nombre[MAX_STR];
    int cantidad;
    float costo;
    float precio_venta;
};

struct DetalleVenta {
    char codigo[MAX_STR];
    char nombre[MAX_STR];
    int cantidad_a_vender;
    float costo;
    float precio_venta;
};

struct Producto* cargarProductos(int *total);
void guardarProductos(struct Producto *productos, int total);
int obtenerUltimoNumFactura();
void registrarVenta(struct DetalleVenta *detalles, int totalDetalles, int numFactura);

#endif
