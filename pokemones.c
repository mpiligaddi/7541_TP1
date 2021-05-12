#include "evento_pesca.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define CUATRO_LETRAS 4
#define COLOR_FAVORITO "amarillo"
#define LETRA_ESPECIAL "o"
#define COLOR_ESPECIAL "dorado"
#define VACIO 0
#define MIN_LETRAS_ESPECIALES 2
#define VELOCIDAD_MIN 20
#define VELOCIDAD_MAX 40
#define MAX_COMANDO 20
#define CANT_SELECCION 2
#define MAX_NOMBRE 20
#define ARCH_ACUARIO "acuario.txt"
#define LINEA_COMANDO "comando"
#define FONDO_AMARILLO "\e[103m"
#define FONDO_CYAN "\e[46m"
#define FONDO_VIOLETA "\e[45m"
#define FONDO_MAGENTA "\e[105m"
#define FONDO_VERDE "\e[42m"
#define FONDO_GRIS "\e[107m"
#define NORMAL "\e[0m"
#define VERDE "\e[32;1m"
#define NEGRO "\e[30m"
#define FONDO_AZUL "\e[44m"
#define FONDO_ROJO "\e[101m"
#define TITULO_ESPECIE "ESPECIE"
#define TITULO_COLOR "COLOR"
#define TITULO_PESO "PESO"
#define TITULO_VELOCIDAD "VELOCIDAD"
#define MAX_TRASLADOS 5
#define MAX_OPCIONES 5
#define MODO_UNO 1
#define MODO_DOS 2
#define MODO_TRES 3
#define MODO_CUATRO 4
#define ACCESO_PERMITIDO 'S'

/*
*Recibe un puntero a pokemones de tipo pokemon_t
*Condicion para saber si el pokemon va a ser trasladado al arrecife o no. 
*Devuelve true en caso de que su color sea COLOR_FAVORITO o false si no
*/

bool tiene_mejor_color(pokemon_t* pokemon) {

	if(strcmp(pokemon->color, COLOR_FAVORITO) == 0) {
		return true;
	}
	return false;
	
}

/*
*Recibe un puntero a pokemones de tipo pokemon_t
*Condicion para saber si el pokemon va a ser trasladado al arrecife o no. 
*Devuelve true en caso de que tenga cuatro letras en su especie o false si no
*/

bool tiene_cuatro_letras(pokemon_t* pokemon) {

	if(strlen(pokemon->especie) == CUATRO_LETRAS) {
		return true;
	}
	return false;

}

/*
*Recibe un puntero a pokemones de tipo pokemon_t
*Condicion para saber si el pokemon va a ser trasladado al arrecife o no. 
*Devuelve true en caso de que tenga velocidad divisible por dos o false si no
*/

bool tiene_velocidad_par(pokemon_t* pokemon) {

	if((pokemon->velocidad)%2 == VACIO) {
		return true;
	}
	return false;

}

/*
*Recibe un puntero a pokemones de tipo pokemon_t
*Condicion para saber si el pokemon va a ser trasladado al arrecife o no. 
*Devuelve true en caso de que su ultima letra de especie sea la "o" y su color sea dorado o false si no
*/

bool es_edicion_limitada(pokemon_t* pokemon) {

	size_t cantidad_letras = strlen(pokemon->especie);
	if((strcmp((pokemon->especie+cantidad_letras-1), LETRA_ESPECIAL) == 0) && (strcmp(pokemon->color, COLOR_ESPECIAL)) == 0 ) {
		return true;
	}
	return false;

}

/*
*Recibe un puntero a pokemones de tipo pokemon_t
*Condicion para saber si el pokemon va a ser trasladado al arrecife o no. 
*Devuelve true en caso de que su velocidad se encuentre entre MIN y MAX o false si no
*/

bool tiene_velocidad_promedio(pokemon_t* pokemon) {

	if((pokemon->velocidad > VELOCIDAD_MIN) && (pokemon->velocidad < VELOCIDAD_MAX)) {
		return true;
	}
	return false;

}

/*
*Recibe un puntero a pokemones de tipo pokemon_t
*La funcion se encarga de listar, mostrando por pantalla con colores, a los pokemones que se encuentran en el arrecife.
*/

void mostrar_modo_color(pokemon_t* pokemon) {

	printf(FONDO_CYAN NEGRO "||%-12s"FONDO_VERDE"||%-12i||%-12i"FONDO_CYAN"||%-12s||" NORMAL "\n",pokemon->especie,pokemon->velocidad,pokemon->peso,pokemon->color);

}

/*
*Recibe un puntero a pokemones de tipo pokemon_t
*La funcion se encarga de listar, mostrando por pantalla y por columnas, a los pokemones que se encuentran en el arrecife.
*/

void mostrar_modo_columnas(pokemon_t* pokemon) {

	printf(FONDO_GRIS NEGRO"||%-12s||%-12i||%-12i||%-12s||" NORMAL "\n",pokemon->especie,pokemon->velocidad,pokemon->peso,pokemon->color);

}

/*
*Recibe un puntero a pokemones de tipo pokemon_t
*La funcion se encarga de listar, mostrando por pantalla con senialador a color, a los pokemones que se encuentran en el arrecife.
*/

void mostrar_modo_navidad(pokemon_t* pokemon) {

	printf(FONDO_ROJO VERDE"❇❇" VERDE"%-14s%-14i%-14i%-12s" VERDE "❇❇" NORMAL "\n",pokemon->especie,pokemon->velocidad,pokemon->peso,pokemon->color);

}

/*
*Recibe un puntero a pokemones de tipo pokemon_t
*La funcion se encarga de listar, mostrando por pantalla con dibujos, a los pokemones que se encuentran en el arrecife.
*/

void mostrar_modo_estrellas(pokemon_t* pokemon) {

	printf(FONDO_GRIS NEGRO "☆★%-12s☆★%-12i☆★%-12i☆★%-12s☆★" NORMAL "\n",pokemon->especie,pokemon->velocidad,pokemon->peso,pokemon->color);

}

/*
*Recibe un puntero a pokemones de tipo pokemon_t
*La funcion se encarga de listar, mostrando por pantalla con espaciado, a los pokemones que se encuentran en el arrecife.
*/

void mostrar_modo_bokita(pokemon_t* pokemon) {

	printf(FONDO_AZUL NEGRO "=========================================================="NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"||%-12s||%-12i||%-12i||%-12s||"NORMAL "\n",pokemon->especie,pokemon->velocidad,pokemon->peso,pokemon->color);
	printf(FONDO_AZUL NEGRO "=========================================================="NORMAL "\n");

}

/*
*Determina e imprime el formato de lectura que presenta el usuario
*/

void determinar_modo(int numero_traslado) {

	if(numero_traslado == MODO_UNO) {
		printf(FONDO_AMARILLO NEGRO "=============== USTED ESTA EN MODO COLUMNAS =============="NORMAL "\n");
	}
	else if(numero_traslado == MODO_DOS) {
		printf(FONDO_AMARILLO NEGRO"================ USTED ESTA EN MODO NAVIDAD  ============="NORMAL "\n");
	}
	else if(numero_traslado == MODO_TRES) {
		printf(FONDO_AMARILLO NEGRO"================ USTED ESTA EN MODO ESTRELLAS ============"NORMAL "\n");
	}
	else if(numero_traslado == MODO_CUATRO) {
		printf(FONDO_AMARILLO NEGRO"================ USTED ESTA EN MODO BOKITA  =============="NORMAL "\n");
	}
	else {
		printf(FONDO_AMARILLO NEGRO"================ USTED ESTA EN MODO COLORES =============="NORMAL "\n");
	}

}

/*
*Imprime por pantalla la portada
*/

void imprimir_portada(int numero_traslado) {

	printf("\n");
	determinar_modo(numero_traslado);
	printf(FONDO_MAGENTA NEGRO "=========================================================="NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"=================== TRASLADO NUMERO %i ===================="NORMAL "\n",numero_traslado);
	printf(FONDO_AMARILLO NEGRO"================POKEMONES EN EL ARRECIFE ================="NORMAL "\n");
	printf(FONDO_MAGENTA NEGRO "==========================================================" NORMAL "\n");
	printf(FONDO_MAGENTA NEGRO "||%-12s||%-12s||%-12s||%-12s||" NORMAL "\n" NORMAL,TITULO_ESPECIE,TITULO_VELOCIDAD,TITULO_PESO,TITULO_COLOR);
	printf(FONDO_MAGENTA NEGRO "==========================================================" NORMAL "\n");

}

/*
*Imprime por pantalla un aviso de finalizacion del programa, en caso de filtrarse los pokemones.
*/

void imprimir_aviso() {

	printf("\n");
	printf(FONDO_AMARILLO NEGRO "====================== AVISO ========================"NORMAL "\n");
	printf(FONDO_VIOLETA NEGRO "====================================================="NORMAL "\n");
	printf(FONDO_GRIS NEGRO "Los pokemones ya han sido seleccionados y trasladados" NORMAL "\n");
	printf(FONDO_GRIS NEGRO "exitosamente del arrecife al acuario de Misty.       " NORMAL "\n");
	printf(FONDO_GRIS NEGRO"¡Solo queda que demuestren sus amplias habilidades!  " NORMAL "\n");
	printf(FONDO_GRIS NEGRO"Aquellos pokemones seleccionados ya se encuentran en " NORMAL "\n");
	printf(FONDO_GRIS NEGRO "un archivo de texto llamado acuario.txt :)           " NORMAL "\n");
	printf(FONDO_VIOLETA NEGRO "====================================================="NORMAL "\n");
	printf("\n");

}

/*
*Imprime por pantalla el inicio del programa
*/

void imprimir_inicio() {

	printf(" 	,---.   .---.  ,-. .-.,---.           .---.  .-. .-.""\n");
	printf(" 	| .-.. / .-. ) | |/ / | .-'  |·..   /| / .-. ) |  .||""\n");
	printf(" 	| |-' )| | |(_)| | /  | `-.  |(. . / ||   | |(_)|   |""\n");
	printf(" 	| |--' | | | | | |    | .-'  (_) ..  ||   | || | |  |""\n");
	printf(" 	| |    | `-' / | |)   |  `--.|    /  | `-' / | | |) |""\n");
	printf(" 	/(      )---'  |((_)- '/( __.'| |..| | )---' / ( (_ )""\n");
	printf("	(__)    (_)     (_)    (__)    '-'  '-'(_)   (__)  ""\n");
	printf("\n");

	printf(FONDO_AMARILLO NEGRO"		⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⣠⣤⣶⣶ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⢰⣿⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣀⣀⣾⣿⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⡏⠉⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⠀⠀⠀⠈⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠉⠁⠀⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠙⠿⠿⠿⠻⠿⠿⠟⠿⠛⠉⠀⠀⠀⠀⠀⣸⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣴⣿⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⢰⣹⡆⠀⠀⠀⠀⠀⠀⣭⣷⠀⠀⠀⠸⣿⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠈⠉⠀⠀⠤⠄⠀⠀⠀⠉⠁⠀⠀⠀⠀⢿⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⢾⣿⣷⠀⠀⠀⠀⡠⠤⢄⠀⠀⠀⠠⣿⣿⣷⠀⢸⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⡀⠉⠀⠀⠀⠀⠀⢄⠀⢀⠀⠀⠀⠀⠉⠉⠁⠀⠀⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿ "NORMAL "\n");
	printf("\n");

	printf(FONDO_VIOLETA NEGRO "	====================================================="NORMAL "\n");
	printf(FONDO_GRIS NEGRO "	Bienvenido a la simulacion de ¡Gran Pesca Pokemon!		"NORMAL "\n");
	printf(FONDO_GRIS NEGRO "		Presione cualquier tecla para continuar :)		"NORMAL "\n");
	printf(FONDO_VIOLETA NEGRO "	====================================================="NORMAL "\n");

	char letra;
	scanf(" %c", &letra);

}

/*
*Imprime por pantalla la portada principal propia de la lista (completa) de pokemones en el arrecife
*/

void imprimir_portada_principal() {

	printf("\n");
	printf(FONDO_MAGENTA NEGRO "=========================================================="NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"=================== SIN TRASLADOS AUN ===================="NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"==============POKEMONES TOTALES EN EL ARRECIFE ==========="NORMAL "\n");
	printf(FONDO_MAGENTA NEGRO "==========================================================" NORMAL "\n");
	printf(FONDO_MAGENTA NEGRO "||%-12s||%-12s||%-12s||%-12s||" NORMAL "\n" NORMAL,TITULO_ESPECIE,TITULO_VELOCIDAD,TITULO_PESO,TITULO_COLOR);
	printf(FONDO_MAGENTA NEGRO "==========================================================" NORMAL "\n");

}

/*
*Devuelve la respuesta determinada por el usuario. True si quiere filtrar los pokemones o false si no.
*/

bool preguntar_acceso() {

	bool acceso_permitido = false;

	printf("\n");
	printf(FONDO_VIOLETA NEGRO "	====================================================="NORMAL "\n");
	printf(FONDO_GRIS NEGRO "Presione la tecla 'S' para filtrar los pokemones o cualquier otra para salir:)"NORMAL "\n");
	printf(FONDO_VIOLETA NEGRO "	====================================================="NORMAL "\n");

	char letra;
	scanf(" %c", &letra);

	if(letra == ACCESO_PERMITIDO) {
		acceso_permitido = true;
	}
	return acceso_permitido;

}

/*
*Imprime por pantalla un aviso de finalizacion del programa, en caso de no querer filtrar los pokemones
*/

void imprimir_primer_aviso() {
	printf("Se selecciono la opcion de no filtrar los pokemones!\n");
	printf("Se quedaran felizmente en el arrecife...\n");
}


int main(int argc , char *argv[]) {
	
	arrecife_t* arrecife = NULL;
	acuario_t* acuario = NULL;
	char comando[MAX_COMANDO] = LINEA_COMANDO;
	strcpy(comando, argv[1]);

	arrecife = crear_arrecife(comando);
	acuario = crear_acuario();

	void (*mostrar_pokemones[MAX_OPCIONES])(pokemon_t*) = {mostrar_modo_columnas, mostrar_modo_navidad, mostrar_modo_estrellas, mostrar_modo_bokita, mostrar_modo_color};
	bool (*filtrar_pokemones[MAX_OPCIONES])(pokemon_t*) = {tiene_mejor_color, tiene_cuatro_letras, tiene_velocidad_par, es_edicion_limitada,tiene_velocidad_promedio};

	if((arrecife != NULL) && (acuario != NULL)) { 
		imprimir_inicio();
		imprimir_portada_principal();
		censar_arrecife(arrecife, mostrar_pokemones[0]); 

		if(preguntar_acceso() == false) {
			imprimir_primer_aviso();
		}
		else {
			for(int i = 0; i < MAX_TRASLADOS; i++) {
				imprimir_portada(i+1);
				trasladar_pokemon(arrecife,acuario,filtrar_pokemones[i],CANT_SELECCION); 
				censar_arrecife(arrecife, mostrar_pokemones[i]); 
			}
			guardar_datos_acuario(acuario, ARCH_ACUARIO);
			imprimir_aviso();
		}
	}

	if(arrecife != NULL) {
		liberar_arrecife(arrecife);
	}

	if(acuario != NULL) {
		liberar_acuario(acuario);
	}

	return 0;
}