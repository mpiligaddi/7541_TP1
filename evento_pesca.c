#include "evento_pesca.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RUTA 200
#define ERROR -1
#define FORMATO_LECTURA "%99[^;];%i;%i;%49[^\n]\n"
#define FORMATO_ESCRITURA "%s;%i;%i;%s\n"
#define VACIO 0
#define CANT_LINEAS 4
#define CORRECTA 0
#define INCORRECTA -1
#define MAX_ARCHIVO 100
#define MAX_EXTENSION 4
#define ARCHIVO "archivo"
#define EXTENSION "txt"

/*
*Recibe un puntero a pokemones y un archivo del arrecife, donde se hayan cargados todos los pokemones
*Devuelve la cantidad de lineas leidas del archivo que recibio como parametro
*/

int leer_archivo_arrecife(FILE* arch_arrecife, pokemon_t* pokemon) {

	return fscanf(arch_arrecife, FORMATO_LECTURA, (*pokemon).especie, &(*pokemon).velocidad, &(*pokemon).peso, (*pokemon).color);

}

/*
*Recibe un puntero a un vector de pokemones con todas sus estructuras validas, la cantidad de pokemones que hay en ese vector(que sera la necesaria para agrandar el vector) y un pokemon de tipo pokemon_t
*Devuelve un puntero del vector de pokemones agrandado una unidad (con un pokemon nuevo) o el puntero del vector con valor NULL (en caso de que falle realloc())  
*/

pokemon_t* agregar_pokemon(pokemon_t* pokemones, int cantidad,pokemon_t pokemon){

	pokemon_t* nuevo_pokemon = NULL;

	nuevo_pokemon = realloc(pokemones, (size_t)(cantidad)*sizeof(pokemon_t));

	if(nuevo_pokemon == NULL) { 
		return NULL;
	}
  
	pokemones = nuevo_pokemon;
	*(pokemones+(cantidad-1)) = pokemon; 

	return pokemones;
}

/*
*Recibe un puntero a un elemento del vector de pokemones del arrecife y un puntero a arrecife
*Elimina del vector de pokemones en el arrecife al elemento que cumple con alguna de las condiciones booleanas propias de pokemones.c y, de esta manera, reduce tambien el tope del vector pasado por referencia (ya que este va a ir variando). 
*/

void eliminar_elemento(pokemon_t* pokemon_buscado,arrecife_t* arrecife) {
	
	bool esta = false;
	int i=0;
	int pos=0;

	while((i < arrecife->cantidad_pokemon) && (esta == false)) {
		if((arrecife->pokemon+i) == pokemon_buscado) {
			pos=i;
			esta = true; 
		}
		i++;
	}
	if(esta == true) {
		for(int j = pos ; j<(arrecife->cantidad_pokemon)-1 ;j++) {
			(arrecife->pokemon)[j] = (arrecife->pokemon)[j+1];
		}
		(arrecife->cantidad_pokemon)--;
	}

} 

/*
*Recibe un puntero a arrecife. Previamente el elemento que debe eliminarse ya fue eliminado de mi vector de pokemones en el arrecife. Por lo tanto, tambien se redujo previamente la cantidad de elementos del mismo. 
*Reduce el tamanio de mi vector de pokemones que se hayan en el arrecife en una unidad.
*/

arrecife_t* achicar_arrecife(arrecife_t* arrecife) { 

	pokemon_t* nuevo_pokemon = NULL;

	nuevo_pokemon = realloc(arrecife->pokemon, sizeof(pokemon_t)*(size_t)(arrecife->cantidad_pokemon));

	if(nuevo_pokemon == NULL) {
		return NULL;
	}

	arrecife->pokemon = nuevo_pokemon;
	
	return arrecife;

}

/*
*Recibe la ruta de un archivo
*Chequea que su extension sea un txt y, en caso afirmativo, devuelve 0. Caso contrario, devuelve -1.
*/

int chequear_extension(const char* ruta_archivo) {

	char arch_arrecife[MAX_ARCHIVO] = ARCHIVO;
	char extension[MAX_EXTENSION] = EXTENSION;

	sscanf(ruta_archivo, "%[^.].%s", arch_arrecife, extension);

	if(strcmp(extension, "txt") == 0) {
		return CORRECTA;
	}
	return INCORRECTA;
}

arrecife_t* crear_arrecife(const char* ruta_archivo) {

	pokemon_t pokemon_actual;
	bool error = false;

	if(chequear_extension(ruta_archivo) == CORRECTA) { 

		FILE* arch_arrecife = fopen(ruta_archivo, "r");

		if(!arch_arrecife) {
			printf("No se pudo abrir el archivo de pokemones en el arrecife...\n");
			return NULL;
		}

		arrecife_t* arrecife = malloc(sizeof(arrecife_t));

		if(arrecife == NULL) {
			printf("Ocurrio un error inesperado!\n");
			fclose(arch_arrecife);
			return NULL;
		}

		arrecife->pokemon = NULL;
		arrecife->cantidad_pokemon = VACIO;

		int leidos = leer_archivo_arrecife(arch_arrecife, &pokemon_actual);
		
		while((leidos == CANT_LINEAS) && (error == false)) {
			(arrecife->cantidad_pokemon)++;
			arrecife->pokemon = agregar_pokemon(arrecife->pokemon,arrecife->cantidad_pokemon,pokemon_actual);
			if(arrecife->pokemon == NULL) {
				fclose(arch_arrecife);
				free(arrecife);
				error = true;
			}
			leidos = leer_archivo_arrecife(arch_arrecife, &pokemon_actual);
		}

		if(arrecife->cantidad_pokemon == VACIO) {
			printf("No se pudo comenzar a leer el archivo. Intentelo nuevamente.\n");
			fclose(arch_arrecife);
			free(arrecife->pokemon);
			free(arrecife);
			return NULL;
		}

		fclose(arch_arrecife);
		return arrecife;
	}

	printf("El archivo de pokemones en el arrecife debe tener una extension txt\n");
	return NULL;

}

acuario_t* crear_acuario() {

	acuario_t* acuario = malloc(sizeof(acuario_t));

	if(acuario == NULL) {
		return NULL;
	}

	acuario->pokemon = NULL;
	acuario->cantidad_pokemon = 0;

	return acuario; 
}

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion) {
	
	int contador_pokemons = 0;
	int j = 0;
	int i = 0;
	int variable_retorno = 0;
	bool error = false;

	for(int k = 0 ; k < arrecife->cantidad_pokemon ; k++) {
		if(seleccionar_pokemon(arrecife->pokemon+k) == true) {
			contador_pokemons++;
		}
	}

	if((contador_pokemons >= cant_seleccion) && (cant_seleccion != VACIO)) {
		while((j < cant_seleccion) && (i < arrecife->cantidad_pokemon) && (error != true)) { 
			if(seleccionar_pokemon(arrecife->pokemon+i) == true) {
				(acuario->cantidad_pokemon)++;
				acuario->pokemon = agregar_pokemon(acuario->pokemon,acuario->cantidad_pokemon,arrecife->pokemon[i]);
				if(acuario->pokemon == NULL) {
					free(acuario);
					variable_retorno = ERROR;
					error = true;
				}
				eliminar_elemento((arrecife->pokemon+i),arrecife); 
				arrecife = achicar_arrecife(arrecife); 
				if(arrecife == NULL) {
					error = true;
				}
				j++;
			}
			else { 
				i++;
			}
		}
	}
	else if((contador_pokemons < cant_seleccion) && (cant_seleccion != VACIO)) {
		variable_retorno = ERROR;
	}
	return variable_retorno;
}

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)) {
	for(int i = 0; i < arrecife->cantidad_pokemon ; i++) {
		mostrar_pokemon((arrecife->pokemon)+i);
	}
}

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo) {

	FILE* arch_acuario = fopen(nombre_archivo, "w");

	if(!arch_acuario) {
		printf("No se pudo abrir el archivo de pokemones en el acuario...\n");
		return ERROR;
	}

	for(int i = 0 ; i < acuario->cantidad_pokemon ; i++) { 
		fprintf(arch_acuario,FORMATO_ESCRITURA,acuario->pokemon[i].especie, acuario->pokemon[i].velocidad, acuario->pokemon[i].peso, acuario->pokemon[i].color);
	}

	fclose(arch_acuario);

	return 0;

}

void liberar_acuario(acuario_t* acuario) {
	if(acuario->cantidad_pokemon != 0) {
		free(acuario->pokemon);
	}
	free(acuario);
}

void liberar_arrecife(arrecife_t* arrecife) {
	if(arrecife->cantidad_pokemon != 0) {
		free(arrecife->pokemon);
	}
	free(arrecife);
}
