#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "usuarios.h"
#include "productos.h"

// NOMBRE: JOSUE MARTINEZ

int main() {
    verificar_usuario();

    int totalProductos = 0;
    struct Producto *productos = cargarProductos(&totalProductos);

    int capDetalles = 5;
    int totalDetalles = 0;
    struct DetalleVenta *detalles = malloc(capDetalles * sizeof(struct DetalleVenta));

    char opcion[5];
    do {
        char cod[MAX_STR];
        int cant;
        printf("\nCódigo producto: ");
        scanf("%s", cod);
        printf("Cantidad: ");
        scanf("%d", &cant);

        int enc = -1;
        for (int i = 0; i < totalProductos; i++) {
            if (strcmp(productos[i].codigo, cod) == 0) {
                enc = i;
                break;
            }
        }

        if (enc == -1) {
            printf("No existe el producto.\n");
        } else if (productos[enc].cantidad < cant) {
            printf("Inventario insuficiente (Disponible: %d).\n", productos[enc].cantidad);
        } else {
            if (totalDetalles >= capDetalles) {
                capDetalles *= 2;
                detalles = realloc(detalles, capDetalles * sizeof(struct DetalleVenta));
            }
            strcpy(detalles[totalDetalles].codigo, productos[enc].codigo);
            strcpy(detalles[totalDetalles].nombre, productos[enc].nombre);
            detalles[totalDetalles].cantidad_a_vender = cant;
            detalles[totalDetalles].costo = productos[enc].costo;
            detalles[totalDetalles].precio_venta = productos[enc].precio_venta;
            totalDetalles++;
            
            productos[enc].cantidad -= cant; 
        }

        printf("¿Registrar otro? (si/no): ");
        scanf("%s", opcion);
    } while (strcmp(opcion, "no") != 0);

    if (totalDetalles > 0) {
        int numFactura = obtenerUltimoNumFactura() + 1;
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);


        printf("\n>>> COMPROBANTE DIGITAL DE COMPRA <<<");
        printf("\nID Venta: #%d", numFactura);
        printf("\nFecha: %04d/%02d/%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        printf("\n------------------------------------------------");
        printf("\n%-20s %-8s %-10s %-8s", "DETALLE", "CANT.", "P.UNIT", "TOTAL");
        printf("\n------------------------------------------------");
        
        float granTotal = 0;
        for (int i = 0; i < totalDetalles; i++) {
            float totalProd = detalles[i].cantidad_a_vender * detalles[i].precio_venta;
            granTotal += totalProd;
            printf("\n%-20s %-8d $%-9.2f $%-8.2f", 
                   detalles[i].nombre, detalles[i].cantidad_a_vender, detalles[i].precio_venta, totalProd);
        }
        
        printf("\n------------------------------------------------");
        printf("\nVALOR TOTAL A PAGAR:                  $%.2f", granTotal);
        printf("\n------------------------------------------------\n\n");

        char conf[5];
        printf("¿Procesar transaccion? (si/no): ");
        scanf("%s", conf);

        if (strcmp(conf, "si") == 0) {
            guardarProductos(productos, totalProductos);
            registrarVenta(detalles, totalDetalles, numFactura);
            printf("Transacción exitosa. Inventario actualizado.\n");
        } else {
            printf("Transacción cancelada.\n");
        }
    }

    free(productos);
    free(detalles);
    return 0;
}
