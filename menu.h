#ifndef MENU_H
#define MENU_H  

#include "structs.h"

void menu_principal(FILE* fb_cursos, FILE* fb_disc, FILE* fb_dist, FILE* fb_prof);

void menu_manual(FILE* fb_cursos, FILE* fb_disc, FILE* fb_dist, FILE* fb_prof);

//void insert_menu();

void print_menu(FILE* fb_cursos, FILE* fb_disc, FILE* fb_dist, FILE* fb_profc);

void print_info(InfosCurso info);

#endif