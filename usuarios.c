#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"

int verificar_usuario() {
    char usuario[MAX_STR];
    char clave[MAX_STR];
    int intentos = 0;

    while (intentos < 3) {
        printf("Usuario: ");
        scanf("%s", usuario);
        printf("Clave: ");
        scanf("%s", clave);

        FILE *f = fopen("vendedores.txt", "r");
        if (!f) {
            printf("Error al abrir vendedores.txt\n");
            exit(1);
        }

        struct Usuario u;
        int loginCorrecto = 0;
        char linea[200];

        while (fgets(linea, sizeof(linea), f)) {
            linea[strcspn(linea, "\n")] = 0;
            char *token = strtok(linea, ",");
            if (token) strcpy(u.usuario, token);
            token = strtok(NULL, ",");
            if (token) strcpy(u.clave, token);
            token = strtok(NULL, ",");
            if (token) strcpy(u.nombre, token);

            if (strcmp(usuario, u.usuario) == 0 && strcmp(clave, u.clave) == 0) {
                loginCorrecto = 1;
                printf("Bienvenido/a, %s!\n", u.nombre);
                break;
            }
        }
        fclose(f);

        if (loginCorrecto) {
            return 1;
        } else {
            intentos++;
            printf("Datos erróneos. Intentos restantes: %d\n", 3 - intentos);
        }
    }

    printf("Se superó el límite de intentos. Cerrando sistema.\n");
    exit(0);
}
