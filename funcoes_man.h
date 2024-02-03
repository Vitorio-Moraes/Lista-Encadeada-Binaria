#ifndef FUNCOES_MAN
#define FUNCOES_MAN

#include "structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void insert_lote(FILE * file_bin, FILE * fb_cursos, FILE* fb_disc, FILE* fb_dist, FILE* fb_prof);

ListaCurso * scan_curso();

ListaProfessor * scan_professor();

ListaDisc * scan_disciplina(FILE * fbcurso);

ListaDistribuicao * scan_distribuicao(FILE * fb_disciplina, FILE * fb_prof);

void ler_arquivoTexto_curso(FILE* fr, FILE* fbCurso);

void ler_arquivoTexto_professsor(FILE* fr, FILE* fbProfessor);

void ler_arquivoTexto_disc(FILE* fr, FILE* fbDisciplina);

void ler_arquivoTexto_dist(FILE* fr, FILE* fbDistribuicao);

int verifica_curso(FILE * fbCurso, InfosCurso curso);

int verifica_disc(FILE * fbdisc, infoDisc disc);

int verifica_prof(FILE * fbprof, infoProf prof);

int verifica_dist(FILE * fbdist, infoDist dist);

#endif