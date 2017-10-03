#include <stdio.h>
#include "generador.h"

void escribir_cabecera_compatibilidad(FILE *pasm){
	return;
}

void escribir_subseccion_data(FILE *fpasm){
	fprintf(fpasm, "segment.data\n");
	fprintf(fpasm, "\tmsg_div_cero db \"FATAL ERROR. DIVISION POR CERO\", 0\n");
	return;
}

void escribir_cabecera_bss(FILE *fpasm){
	fprintf(fpasm, "segment .bss\n");
	fprintf(fpasm, "\t__esp resd 1\n");
	return;
}

void declarar_variable(FILE* fpasm, char * nombre,  int tipo,  int tamano){
	
	if(tipo == ENTERO)
		fprintf(fpasm, "\t_%s resd %d\n", nombre, tamano);
	else
		fprintf(fpasm, "\t_%s resb %d\n", nombre, tamano);

	return;
}

void escribir_segmento_codigo(FILE *pasm){
	fprintf(fpasm, "segment .text\n");
	fprintf(fpasm, "\tglobal main\n");
	fprintf(fpasm, "\textern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean\n");
	fprintf(fpasm, "\textern print_endofline, print_blank, print_string\n");
	fprintf(fpasm, "\textern alfa_malloc, alfa_free, ld_float\n");

	return;
}

void escribir_inicio_main(FILE *pasm){
	fprintf(fpasm, "; ------------------------\n");
	fprintf(fpasm, "; PROCEDIMIENTO PRINCIPAL\n");
	fprintf(fpasm, "; ------------------------\n");

	fprintf(fpasm, "main: \n");
	fprintf(fpasm, "; GUARDA DE PUNTERO DE PILA\n");
	fprintf(fpasm, "\tmov dword [__esp] , esp\n");
	return;
}

void escribir_fin(FILE *fpasm){
	/*FALTARIA LA SALIDA DE MANERA CONTROLADA*/
	fprintf(fpasm, "; RESTAURACION DE PUNTERO DE PILA\n");
	fprintf(fpasm, "\tmov dword esp, [__esp]\n");
	fprintf(fpasm, "\tret\n");
	fprintf(fpasm, "div_por_cero:\n");
	fprintf(fpasm, "\tpush dword msg_div_cero\n");
	fprintf(fpasm, "\tcall print_string\n"):
	fprintf(fpasm, "\tmov dword esp, [__esp]\n");
	fprintf(fpasm, "\tret\n");
	return;
}

void escribir_operando(FILE* fpasm, char* nombre, int es_var){
	if(es_var==0){ /* VALOR EXPLICITO */
		fprintf(fpasm, "\tpush dword %s\n", nombre);
	} else if(es_var==1){
		fprintf(fpsm, "\t push dword [_%s]\n", nombre);
	} else {
		fprintf(stderr, "ERROR: VALOR DE ES_VAR INCORRECTO EN LA FUNCION ESCRIBIR_OPERANDO (VALORES VALIDOS 0 Y 1)\n");
		exit(1);
	}
	return;
}

void asignar(FILE* fpasm, char* nombre, int es_referencia){

	fprintf(fpasm, "\tpop dword eax\n");
	if(es_referencia == 0){ /*VALOR EXPLICITO */
		fprintf(fpasm, "\tmov [_%s], eax\n", nombre);
	} else if (es_referencia == 1){
		fprintf(fpasm, "\tmov ebx, [eax]\n");
		fprintf(fpasm, "\tmov [_%s], ebx\n", nombre);
	} else {
		fprintf(stderr, "ERROR: VALOR DE ES_REFERENCIA INCORRECTO EN LA FUNCION ASIGNAR (VALORES VALIDOS 0 Y 1)\n");
		exit(1):
	}
	return;
}

void sumar(FILE* fpasm, int es_referencia_1, int es_referencia_2){
	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_referencia1 != 0 || es_referencia1 !=1 || es_referencia2 !=0 || es_referencia2 !=1){
		fprintf(stderr, "ERROR: VALOR DE ES_REFERENCIA INCORRECTO EN LA FUNCION SUMAR (VALORES VALIDOS 0 Y 1)\n");
		exit(1):	
	}

	if(es_referencia1 == 1){ /* ES UNA REFERENCIA*/
		fprintf(fpasm, "\tmov ecx, [eax]\n");
		fprintf(fpasm, "\tmov eax, ecx\n");
	}

	if(es_referencia2 == 1){ /* ES UNA REFERENCIA */
		fprintf(fpasm, "\tmov ecx, [ebx]\n");
		fprintf(fpasm, "\tmov ebx, ecx\n");
	}

	fprintf(fpasm, "\tadd eax, ebx\n");
	fprintf(fpasm, "\tpush dword eax\n");

	return;
}

void restar(FILE* fpasm, int es_referencia_1, int es_referencia_2){
	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_referencia1 != 0 || es_referencia1 !=1 || es_referencia2 !=0 || es_referencia2 !=1){
		fprintf(stderr, "ERROR: VALOR DE ES_REFERENCIA INCORRECTO EN LA FUNCION RESTAR(VALORES VALIDOS 0 Y 1)\n");
		exit(1):	
	}

	if(es_referencia1 == 1){ /* ES UNA REFERENCIA*/
		fprintf(fpasm, "\tmov ecx, [eax]\n");
		fprintf(fpasm, "\tmov eax, ecx\n");
	}

	if(es_referencia2 == 1){ /* ES UNA REFERENCIA */
		fprintf(fpasm, "\tmov ecx, [ebx]\n");
		fprintf(fpasm, "\tmov ebx, ecx\n");
	}

	fprintf(fpasm, "\tsub eax, ebx\n");
	fprintf(fpasm, "\tpush dword eax\n");

	return;
}

void multiplicar(FILE* fpasm, int es_referencia_1, int es_referencia_2){
	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_referencia1 != 0 || es_referencia1 !=1 || es_referencia2 !=0 || es_referencia2 !=1){
		fprintf(stderr, "ERROR: VALOR DE ES_REFERENCIA INCORRECTO EN LA FUNCION MULTIPLICAR(VALORES VALIDOS 0 Y 1)\n");
		exit(1):	
	}

	if(es_referencia1 == 1){ /* ES UNA REFERENCIA*/
		fprintf(fpasm, "\tmov ecx, [eax]\n");
		fprintf(fpasm, "\tmov eax, ecx\n");
	}

	if(es_referencia2 == 1){ /* ES UNA REFERENCIA */
		fprintf(fpasm, "\tmov ecx, [ebx]\n");
		fprintf(fpasm, "\tmov ebx, ecx\n");
	}

	fprintf(fpasm, "\timul ebx\n");
	fprintf(fpasm, "\tpush dword eax\n");
	return;
}

void dividir(FILE* fpasm, int es_referencia_1, int es_referencia_2){
	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_referencia1 != 0 || es_referencia1 !=1 || es_referencia2 !=0 || es_referencia2 !=1){
		fprintf(stderr, "ERROR: VALOR DE ES_REFERENCIA INCORRECTO EN LA FUNCION DIVIDIR(VALORES VALIDOS 0 Y 1)\n");
		exit(1):	
	}

	if(es_referencia1 == 1){ /* ES UNA REFERENCIA*/
		fprintf(fpasm, "\tmov ecx, [eax]\n");
		fprintf(fpasm, "\tmov eax, ecx\n");
	}

	if(es_referencia2 == 1){ /* ES UNA REFERENCIA */
		fprintf(fpasm, "\tmov ecx, [ebx]\n");
		fprintf(fpasm, "\tmov ebx, ecx\n");
	}

	fprintf(fpasm, "\tcdq\n");
	fprintf(fpasm, "\tcmp ebx, 0\n");
	fprintf(fpasm, "\tje div_por_cero\n");
	fprintf(fpasm, "\tidiv ebx\n");

	fprintf(fpasm, "\tpush dword eax\n");
}

void o(FILE* fpasm, int es_referencia_1, int es_referencia_2){
	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_referencia1 != 0 || es_referencia1 !=1 || es_referencia2 !=0 || es_referencia2 !=1){
		fprintf(stderr, "ERROR: VALOR DE ES_REFERENCIA INCORRECTO EN LA FUNCION OR(VALORES VALIDOS 0 Y 1)\n");
		exit(1):	
	}

	if(es_referencia1 == 1){ /* ES UNA REFERENCIA*/
		fprintf(fpasm, "\tmov ecx, [eax]\n");
		fprintf(fpasm, "\tmov eax, ecx\n");
	}

	if(es_referencia2 == 1){ /* ES UNA REFERENCIA */
		fprintf(fpasm, "\tmov ecx, [ebx]\n");
		fprintf(fpasm, "\tmov ebx, ecx\n");
	}

	fprintf(fpasm, "\tor eax, ebx\n");
	fprintf(fpasm, "\tpush dword eax\n");

	return;
}

void y(FILE* fpasm, int es_referencia_1, int es_referencia_2){

	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_referencia1 != 0 || es_referencia1 !=1 || es_referencia2 !=0 || es_referencia2 !=1){
		fprintf(stderr, "ERROR: VALOR DE ES_REFERENCIA INCORRECTO EN LA FUNCION AND(VALORES VALIDOS 0 Y 1)\n");
		exit(1):	
	}

	if(es_referencia1 == 1){ /* ES UNA REFERENCIA*/
		fprintf(fpasm, "\tmov ecx, [eax]\n");
		fprintf(fpasm, "\tmov eax, ecx\n");
	}

	if(es_referencia2 == 1){ /* ES UNA REFERENCIA */
		fprintf(fpasm, "\tmov ecx, [ebx]\n");
		fprintf(fpasm, "\tmov ebx, ecx\n");
	}

	fprintf(fpasm, "\tand eax, ebx\n");
	fprintf(fpasm, "\tpush dword eax\n");

	return;
}

void cambiar_signo(FILE* fpasm, int es_referencia){
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_referencia !=1 || es_referencia != 0){
		fprintf(stderr, "ERROR: VALOR DE ES_REFERENCIA INCORRECTO EN LA FUNCION CAMBIAR_SIGNO(VALORES VALIDOS 0 Y 1)\n");
		exit(1);
	}

	if(es_referencia == 1){ /* ES UNA REFERENCIA*/
		fprintf(fpasm, "\tmov ecx, [eax]\n");
		fprintf(fpasm, "\tmov eax, ecx\n");
	}

	fprintf(fpasm, "\tmov ebx, eax\n");
	fprintf(fpasm, "\tsub eax, ebx\n");
	fprintf(fpasm, "\tsub eax, ebx\n");

	fprintf(fpasm, "\tpush dword eax\n");
	return;
}

