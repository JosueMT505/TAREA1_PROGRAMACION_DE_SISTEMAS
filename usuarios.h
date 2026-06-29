#ifndef USUARIOS_H
#define USUARIOS_H

#define MAX_STR 50

struct Usuario {
    char usuario[MAX_STR];
    char clave[MAX_STR];
    char nombre[MAX_STR];
};

int verificar_usuario();

#endif
