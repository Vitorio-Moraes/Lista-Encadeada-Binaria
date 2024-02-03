#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "funcoes_man.h"
#include "funcoes_arq.h"
#include "menu.h"
#include "structs.h"

int main(){
    FILE * fb_cursos = open_arq("cursos.bin");
    FILE * fb_prof = open_arq("professores.bin");
    FILE * fb_disc =  open_arq("disciplinas.bin");
    FILE * fb_dist =  open_arq("distribuicoes.bin");

    menu_principal(fb_cursos,fb_disc,fb_dist,fb_prof);

    
/*
    fclose(Cursos);
    fclose(Profs);
    fclose(Disc);
    fclose(Dist);
  */  
    return 0;
}
