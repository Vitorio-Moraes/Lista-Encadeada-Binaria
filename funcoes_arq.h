#ifndef FUNCOES_H
#define FUNCOES_H

#include "structs.h"


FILE * open_arq(char* str);

Cabecalho* lerCabecalho(FILE * fb);

void escreveCabecalho(FILE * fb, Cabecalho * cab);

ListaCurso * leCurso(FILE * fb_ListaCurso, int pos);

ListaDistribuicao * leDist(FILE * fb_ListaDist, int pos);

ListaDisc * leDisc(FILE * fb_ListaDisc, int pos);

ListaProfessor * leProf(FILE * fb_ListaProfs, int pos);

void escreve_curso(FILE * fb_ListaCurso, ListaCurso * node, int pos);

void escreve_dist(FILE * fb_ListaDist, ListaDistribuicao * node, int pos);

void escreve_disc(FILE * fb_ListaDisc, ListaDisc * node, int pos);

void escreve_prof(FILE * fb_ListaProfs, ListaProfessor * node, int pos);

void insere_curso(FILE * fb_ListaCurso, InfosCurso info);

void insere_dist(FILE * fb_ListaDist, infoDist info);

void insere_professor(FILE * fb_ListaProfs, infoProf info);

void insere_disc(FILE * fb_ListaDisc, infoDisc info);

void insere_curso(FILE * fb_ListaCurso, InfosCurso info);

void retira(FILE* arq, int codDisciplina, int anoLetivo);

//imprimir lista de distribuicao de disciplina, organizadas por curso
//void print_list();

InfosCurso get_curso(FILE * arq_txt);

void print_curso(FILE* fbCurso);

void print_nodeCurso(FILE* fbCurso, int pos);

void print_prof(FILE* fbprof);

void print_nodeProf(FILE* fbprof, int pos);

void print_disc(FILE* fbdisc);

void print_nodeDisc(FILE* fbdisc, int pos);

void print_dist(FILE* fbdist);

void print_nodeDist(FILE* fbdist, int pos);

void print_dist_curso(FILE * fb_curso, FILE * fb_dist);

int compareInt(const void *a, const void *b);

int jatem(int vetor[],int verifica, int tam);

void printListaDistPorCurso(FILE *fbdist, FILE *fbcurso, FILE *fbdisc);

void printDisciplinasPorCurso(FILE *fbdist, FILE *fbcurso, FILE *fbdisc);

int verificaDiscCurso(FILE * fbCurso, int disc);

int verificaDistProf(FILE * fbprof, int prof);

int verificaDistDisc(FILE * fbdisc, int disc);

#endif