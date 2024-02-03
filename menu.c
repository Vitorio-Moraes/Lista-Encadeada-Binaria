#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "funcoes_arq.h"
#include "funcoes_man.h"
#include "structs.h"



void menu_principal(FILE* fb_cursos, FILE* fb_disc, FILE* fb_dist, FILE* fb_prof){
    char user[20], txt[20]; 
    int menu = 0;
    FILE *arq_txt;
    int codDisciplina, anoLetivo;

    while(menu != 5){

    printf("\n -1- para inserir em Lote \n -2- para inserir manual\n -3- para remover distribuicao\n -4- para imprimir\n -5- para sair\n");

    /*scanf("%[^\n]%*c", user);
    menu = atoi(user);*/

    scanf("%d%*c", &menu);

    switch (menu)
    {
    case 1:
        printf("Digite o arquivo a ser lido: \n");
        scanf("%[^\n]%*c", txt); //le o arquivo txt a ser aberto
        arq_txt = fopen(txt, "r");

        if(arq_txt == NULL){  //Testa se existe, se não existir da erro e volta ao menu
            printf("Erro\n\n");
            menu_principal(fb_cursos,fb_disc,fb_dist,fb_prof);
        }

        insert_lote(arq_txt, fb_cursos,fb_disc,fb_dist,fb_prof);

        //print_curso(fb_cursos);
        break;
    case 2:
        menu_manual(fb_cursos,fb_disc,fb_dist,fb_prof);

        break;
   case 3:
        //retira();
        printf("\n-> DIGITE O COD_DISCIPLINA: ");
        scanf("%d%*c", &codDisciplina);
        printf("\n -> DIGITE O ANO_LETIVO: ");
        scanf("%d%*c", &anoLetivo);
        retira(fb_dist, codDisciplina, anoLetivo);
        break;


    case 4:
        print_menu(fb_cursos,fb_disc,fb_dist,fb_prof);
        break;
    case 5:
        break;

    default:
        printf("opcao invalida\n");
        break;
    }
    }
    
}

void menu_manual(FILE* fb_cursos, FILE* fb_disc, FILE* fb_dist, FILE* fb_prof){
    char var;

        ListaCurso * auxc = (ListaCurso *) malloc(sizeof(ListaCurso));
        ListaProfessor * auxp = (ListaProfessor *)malloc(sizeof(ListaProfessor));
        ListaDisc * auxdisc = (ListaDisc*)malloc(sizeof(ListaDisc));
        ListaDistribuicao * auxdist = (ListaDistribuicao *)malloc(sizeof(ListaDistribuicao));

    while(var!='S'){
        printf("\nQual insercao deseja fazer?\nC-inserir curso\nD-inserir disciplina\nP-inserir professor\nM-inserir nova distribuicao de disciplina\nS-Sair\n");
        scanf("%c", &var);
            switch(var){
                case 'C':
                auxc = scan_curso();
                if(!verifica_curso(fb_cursos,auxc->info))
                insere_curso(fb_cursos,auxc->info);
                break;

                case 'D':
                auxdisc = scan_disciplina(fb_cursos);
                if(!verifica_disc(fb_disc,auxdisc->info))
                insere_disc(fb_disc,auxdisc->info);
                //print_disc(fb_disc);
                break;

                case 'P':
                auxp = scan_professor();
                if(!verifica_prof(fb_prof,auxp->info))
                insere_professor(fb_prof, auxp->info);
                break;

                case 'M':
                auxdist= scan_distribuicao(fb_disc,fb_prof);
                if(!verifica_dist(fb_dist,auxdist->info))
                insere_dist(fb_dist, auxdist->info);
                break;
                
                case 'S':
                break;

                default:
                printf("Opcao invalida\n");
                break;
            }
    }
}

//Direciona o scanner
void print_menu(FILE* fb_cursos, FILE* fb_disc, FILE* fb_dist, FILE* fb_prof){

    int menu = 0;
    char user[20];

    while (menu!=6)
    {
        printf("\nQual print deseja fazer?\n1-print curso\n2-print disciplina\n3-print professor\n4-print distribuicao\n5-print distribuicao de disciplina por curso\n6-sair\n");
        scanf("%[^\n]%*c", user);
        menu = atoi(user);

        switch (menu)
            {
            case 1:
                print_curso(fb_cursos);
                break;
            case 2:
                print_disc(fb_disc);
            break;
            case 3:
                print_prof(fb_prof);
            break;
            case 4:
                print_dist(fb_dist);
            break;
            case 5:
                printListaDistPorCurso(fb_dist,fb_cursos,fb_disc);
            break;
            case 6:
            break;
            default:
                break;
            }
    }
}
void print_info(InfosCurso info){
    printf("codigo: %d", info.codigo);
    printf("nome: %s", info.nome);
    printf("area: %c", info.area);

}
