#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void cifrar_texto(char *texto, char *clave, char *resultado);
void descifrar_texto(char *texto, char *clave, char *resultado);
int calcular_desplazamiento(char k);
void limpiar_clave(char *clave);
char *obtener_parametro(char *args[], int argc, const char *opcion);

int main(int argc, char *argv[]) {
    char *texto = obtener_parametro(argv, argc, "--t");
    char *clave = obtener_parametro(argv, argc, "--c");
    char *texto_descifrado = obtener_parametro(argv, argc, "--d");
    char resultado[1000];

    if (texto != NULL && clave != NULL && texto_descifrado == NULL) {
        // Cifrar
        cifrar_texto(texto, clave, resultado);
    } else if (texto_descifrado != NULL && clave != NULL && texto == NULL) {
        // Descifrar
        descifrar_texto(texto_descifrado, clave, resultado);
    } else {
        printf("Error: Se necesitan argumentos válidos\n");
        return 1;
    }

    printf("Resultado: %s\n", resultado);
    return 0;
}

void cifrar_texto(char *texto, char *clave, char *resultado) {
    limpiar_clave(clave);  // Limpia la clave antes de usarla
    int longitudClave = strlen(clave);
    int claveIndex = 0;
    int i;

    for (i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];
        if (isalnum(c)) {
            int desplazamiento = calcular_desplazamiento(clave[claveIndex % longitudClave]);

            if (c >= 'a' && c <= 'z') {
                resultado[i] = (char) ((c - 'a' + desplazamiento) % 26 + 'a');
            } else if (c >= 'A' && c <= 'Z') {
                resultado[i] = (char) ((c - 'A' + desplazamiento) % 26 + 'A');
            } else if (c >= '0' && c <= '9') {
                resultado[i] = (char) ((c - '0' + desplazamiento) % 10 + '0');
            }

            claveIndex++;
        } else {
            resultado[i] = c;
        }
    }
    resultado[i] = '\0';  // Añade el carácter nulo al final
}

void descifrar_texto(char *texto, char *clave, char *resultado) {
    limpiar_clave(clave);  // Limpia la clave antes de usarla
    int longitudClave = strlen(clave);
    int claveIndex = 0;
    int i;

    for (i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];
        if (isalnum(c)) {
            int desplazamiento = calcular_desplazamiento(clave[claveIndex % longitudClave]);

            if (c >= 'a' && c <= 'z') {
                resultado[i] = (char) ((c - 'a' - desplazamiento + 26) % 26 + 'a');
            } else if (c >= 'A' && c <= 'Z') {
                resultado[i] = (char) ((c - 'A' - desplazamiento + 26) % 26 + 'A');
            } else if (c >= '0' && c <= '9') {
                resultado[i] = (char) ((c - '0' - desplazamiento + 10) % 10 + '0');
            }

            claveIndex++;
        } else {
            resultado[i] = c;
        }
    }
    resultado[i] = '\0';  // Añade el carácter nulo al final
}

int calcular_desplazamiento(char k) {
    if (k >= 'a' && k <= 'z') {
        return k - 'a';
    } else if (k >= 'A' && k <= 'Z') {
        return k - 'A';
    } else if (k >= '0' && k <= '9') {
        return k - '0';
    }
    return 0;
}

void limpiar_clave(char *clave) {
    int j = 0;
    for (int i = 0; clave[i] != '\0'; i++) {
        if (isalnum(clave[i])) {
            clave[j++] = clave[i];
        }
    }
    clave[j] = '\0';
}

char *obtener_parametro(char *args[], int argc, const char *opcion) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(args[i], opcion) == 0 && i + 1 < argc) {
            return args[i + 1];
        }
    }
    return NULL;
}
