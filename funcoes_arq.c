#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "funcoes_arq.h"
#include "menu.h"
#include "funcoes_man.h"


//teste se o arquivo ja existe 
//se nao existir cria um
FILE* open_arq(char* str){
    FILE* arq = fopen(str, "r+b");
    if(arq==NULL){
        arq = fopen(str, "w+b");
        Cabecalho* cab = (Cabecalho*) malloc(sizeof(Cabecalho));
        cab->posCabeca = -1;
        cab->posLivre = -1;
        cab->posTopo = 0;
        escreveCabecalho(arq, cab);
        free(cab);
    }
    return arq;
}


//Escreve um cabeçalho ou atualiza o ja existente
void escreveCabecalho(FILE * fb, Cabecalho * cab){
    fseek(fb, 0, SEEK_SET);
    fwrite(cab, sizeof(Cabecalho), 1, fb);
}

//Le o cabeçalho atual
Cabecalho * lerCabecalho(FILE * fb){
    Cabecalho *cab = (Cabecalho*)malloc(sizeof(Cabecalho));

    fseek(fb, 0, SEEK_SET);

    fread(cab, sizeof(Cabecalho), 1, fb);

    return cab;
}
//---------------------------------------------------------------------------------------------------
//Le um nó no arquivo binario
ListaCurso * leCurso(FILE * fb_ListaCurso, int pos){
    ListaCurso * node = (ListaCurso*)malloc(sizeof(ListaCurso));

    fseek(fb_ListaCurso, sizeof(Cabecalho) + pos*sizeof(ListaCurso), SEEK_SET);
    fread(node, sizeof(ListaCurso), 1, fb_ListaCurso);

    return node;
}

ListaDistribuicao * leDist(FILE * fb_ListaDist, int pos){
    ListaDistribuicao * node = (ListaDistribuicao*)malloc(sizeof(ListaDistribuicao));

    fseek(fb_ListaDist, sizeof(Cabecalho) + pos*sizeof(ListaDistribuicao), SEEK_SET);
    fread(node, sizeof(ListaDistribuicao), 1, fb_ListaDist);

    return node;
}

ListaProfessor * leProf(FILE * fb_ListaProfs, int pos){
    ListaProfessor * node = (ListaProfessor*)malloc(sizeof(ListaProfessor));

    fseek(fb_ListaProfs, sizeof(Cabecalho) + pos*sizeof(ListaProfessor), SEEK_SET);
    fread(node, sizeof(ListaProfessor), 1, fb_ListaProfs);

    return node;
}

ListaDisc * leDisc(FILE * fb_ListaDisc, int pos){
    ListaDisc * node = (ListaDisc*)malloc(sizeof(ListaDisc));

    fseek(fb_ListaDisc, sizeof(Cabecalho) + pos*sizeof(ListaDisc), SEEK_SET);
    fread(node, sizeof(ListaDisc), 1, fb_ListaDisc);

    return node;
}
//-----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Escreve um nó no arquivo binario
void escreve_curso(FILE * fb_ListaCurso, ListaCurso * node, int pos){
    fseek(fb_ListaCurso, sizeof(Cabecalho) + pos*sizeof(ListaCurso), SEEK_SET);
    fwrite(node, sizeof(ListaCurso), 1, fb_ListaCurso);
}

void escreve_dist(FILE * fb_ListaDist, ListaDistribuicao * node, int pos){
    fseek(fb_ListaDist, sizeof(Cabecalho) + pos*sizeof(ListaDistribuicao), SEEK_SET);
    fwrite(node, sizeof(ListaDistribuicao), 1, fb_ListaDist);
}

void escreve_disc(FILE * fb_ListaDisc, ListaDisc * node, int pos){
    fseek(fb_ListaDisc, sizeof(Cabecalho) + pos*sizeof(ListaDisc), SEEK_SET);
    fwrite(node, sizeof(ListaDisc), 1, fb_ListaDisc);
}

void escreve_prof(FILE * fb_ListaProfs, ListaProfessor * node, int pos){
    fseek(fb_ListaProfs, sizeof(Cabecalho) + pos * sizeof(ListaProfessor), SEEK_SET);
    fwrite(node, sizeof(ListaProfessor), 1, fb_ListaProfs);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//insere um node na lista e altera o cabecalho
//pré-requisitos: Arquivo texto, informação a ser inserida;
//funcoes de inserção
void insere_curso(FILE * fb_ListaCurso, InfosCurso info){
    Cabecalho * cab = lerCabecalho(fb_ListaCurso);
    ListaCurso aux;
    
    aux.info.codigo = info.codigo;                       //passa a info para o auxiliar
    strcpy(aux.info.nome,info.nome);              //copia um nome para o outro
    aux.info.area = info.area;
    aux.prox = cab->posCabeca;//faz o prox apontar para onde começa a lista

    if(cab->posLivre == -1){ //não há nós livres
        escreve_curso(fb_ListaCurso, &aux, cab->posTopo);   //escreve o nó na proxima posição livre (topo)

        cab->posCabeca = cab->posTopo;
        cab->posTopo++;                                 //incrementa o topo
    }

    else {                  //usa nós livres
        ListaCurso * aux = leCurso(fb_ListaCurso,cab->posLivre);

        escreve_curso(fb_ListaCurso, aux, cab->posLivre);

        cab->posCabeca = cab->posLivre;
        cab->posLivre = aux->prox;

        free (aux);
    }
    escreveCabecalho(fb_ListaCurso, cab); free(cab);
}

void insere_professor(FILE * fb_ListaProfs, infoProf info){
    Cabecalho * cab = lerCabecalho(fb_ListaProfs);
    ListaProfessor aux;
    
    aux.info.codigo = info.codigo;                       //passa a info para o auxiliar
    strcpy(aux.info.nome,info.nome);              //copia um nome para o outro
    aux.prox = cab->posCabeca;                    //faz o prox apontar para onde começa a lista

    if(cab->posLivre == -1){ //não há nós livres
        escreve_prof(fb_ListaProfs, &aux, cab->posTopo);   //escreve o nó na proxima posição livre (topo)

        cab->posCabeca = cab->posTopo;
        cab->posTopo++;                                 //incrementa o topo
    }

    else {                  //usa nós livres
        ListaProfessor * aux = leProf(fb_ListaProfs,cab->posLivre);

        escreve_prof(fb_ListaProfs, aux, cab->posLivre);

        cab->posCabeca = cab->posLivre;
        cab->posLivre = aux->prox;

        free (aux);
    }
    escreveCabecalho(fb_ListaProfs, cab); free(cab);
}

void insere_disc(FILE * fb_ListaDisc, infoDisc info){
    Cabecalho * cab = lerCabecalho(fb_ListaDisc);
    ListaDisc aux;
    
    aux.info.cod_disc = info.cod_disc;                       //passa a info para o auxiliar
    strcpy(aux.info.nome_disc,info.nome_disc);              //copia um nome para o outro
    aux.info.cod_curso = info.cod_curso;
    aux.info.serie = info.serie;
    aux.prox = cab->posCabeca;                    //faz o prox apontar para onde começa a lista

    if(cab->posLivre == -1){ //não há nós livres
        escreve_disc(fb_ListaDisc, &aux, cab->posTopo);   //escreve o nó na proxima posição livre (topo)

        cab->posCabeca = cab->posTopo;
        cab->posTopo++;                                 //incrementa o topo
    }

    else {                  //usa nós livres
        ListaDisc * aux = leDisc(fb_ListaDisc,cab->posLivre);

        escreve_disc(fb_ListaDisc, aux, cab->posLivre);

        cab->posCabeca = cab->posLivre;
        cab->posLivre = aux->prox;

        free (aux);
    }
    escreveCabecalho(fb_ListaDisc, cab); free(cab);
}

void insere_dist(FILE * fb_ListaDist, infoDist info){
    Cabecalho * cab = lerCabecalho(fb_ListaDist);
    ListaDistribuicao aux;
    
    aux.info.codigo_professor = info.codigo_professor;   //passa a info para o auxiliar
    aux.info.ano_letivo = info.ano_letivo;
    aux.info.codigo_disciplina = info.codigo_disciplina;
    aux.prox = cab->posCabeca;                    //faz o prox apontar para onde começa a lista

    if(cab->posLivre == -1){ //não há nós livres
        escreve_dist(fb_ListaDist, &aux, cab->posTopo);   //escreve o nó na proxima posição livre (topo)

        cab->posCabeca = cab->posTopo;
        cab->posTopo++;                                 //incrementa o topo
    }

    else {                  //usa nós livres
        ListaDistribuicao * aux = leDist(fb_ListaDist,cab->posLivre);

        escreve_dist(fb_ListaDist, aux, cab->posLivre);

        cab->posCabeca = cab->posLivre;
        cab->posLivre = aux->prox;

        free (aux);
    }
    escreveCabecalho(fb_ListaDist, cab); free(cab);
}
//-----------------------------------------------------------------------------------------------------------------------

//Remove a Distribuição
//Pré-requisito: Cabeçalho valido e ser o do tipo manipulado
//entrada:arquivo, código da materia e o ano letivo
void retira(FILE* arq, int codDisciplina, int anoLetivo){
    Cabecalho* cab = lerCabecalho(arq);
    int pos_aux = cab->posCabeca;
    int pos_ant = cab->posCabeca;
    ListaDistribuicao* aux = NULL;

    /*while(pos_aux != -1 && // procura o elemento a ser retirado
         ((node = leDist(arq, pos_aux)) != NULL && 
         (node->info.codigo_disciplina != codDisciplina ||
         (node->info.codigo_disciplina == codDisciplina && node->info.ano_letivo != anoLetivo))))*/   
    while(pos_aux != -1 && ((aux = leDist(arq, pos_aux)) != NULL &&
         (aux->info.codigo_disciplina != codDisciplina ||
         (aux->info.codigo_disciplina == codDisciplina && aux->info.ano_letivo != anoLetivo))))
    {   
        pos_ant = pos_aux;
        pos_aux = aux->prox;
        free(aux);         
        aux = NULL;
    }
    if(pos_aux != -1) { //encontrou o elemento
        if(pos_ant == pos_aux){ // remoção na cabeça
            cab->posCabeca = aux->prox;
        }
        else { // remo¸c~ao no meio
            ListaDistribuicao * ant = leDist(arq,pos_ant);
            ant->prox = aux->prox;

            escreve_dist(arq,ant,pos_ant);
            free(ant);
        }
        aux->prox = cab->posLivre; // torna o nó removido um nó livre
        cab->posLivre = pos_aux;   

        escreve_dist(arq, aux, pos_aux);
        escreveCabecalho(arq,cab);
        free(aux);
    }

free(cab);
}

//pré requisito, estar lendo o código após o ";"
//pega a informação referente a um curso
//Arquivo txt ja aberto
InfosCurso get_curso(FILE * arq_txt){
    InfosCurso aux;

    fscanf(arq_txt,"%d;%[^;]%*c%c\n", &aux.codigo, aux.nome, &aux.area);

    printf("aux cod = %d\n", aux.codigo);
    printf("aux nome = %s\n", aux.nome);
    printf("aux area = %c\n", aux.area);
    
    return aux;
  
}//Possibilidade de mudar o formato do codigo
//ao inves de ler 1 por 1
//ler a string toda antes e jogar apenas a string para cá a ser desossada

//-------------------------------------------------------------------------------------------------------------------------
void print_curso(FILE* fbCurso){
    Cabecalho* cab = lerCabecalho(fbCurso);

    if(cab->posCabeca != -1){
        printf("*LISTA DE CURSOS*\n\n");
        printf("%-10s%-40s%-10s\n", "CODIGO", "NOME", "AREA");

        print_nodeCurso(fbCurso, cab->posCabeca);
    }
    else printf("NAO HA CURSOS...\n");

    free(cab);

}

void print_nodeCurso(FILE* fbCurso, int pos){
    if(pos != -1){
        ListaCurso* c = leCurso(fbCurso, pos);
        int c_prox = c->prox;

        printf("%-10d%-40s%-10c\n", c->info.codigo, c->info.nome, c->info.area);
        
        free(c);
        print_nodeCurso(fbCurso, c_prox);
    }
}

void print_prof(FILE* fbprof){
    Cabecalho* cab = lerCabecalho(fbprof);

    if(cab->posCabeca != -1){
        printf("*LISTA DE PROFESSORES*\n\n");
        printf("%-10s%-40s\n", "CODIGO", "NOME");

        print_nodeProf(fbprof, cab->posCabeca);
    }
    else printf("NAO HA PROFESSORES...\n");

    free(cab);

}

void print_nodeProf(FILE* fbprof, int pos){
    if(pos != -1){
        ListaProfessor* c = leProf(fbprof, pos);
        int c_prox = c->prox;

        printf("%-10d%-40s\n", c->info.codigo, c->info.nome);
        
        free(c);
        print_nodeProf(fbprof, c_prox);
    }
}

void print_disc(FILE* fbdisc){
    Cabecalho* cab = lerCabecalho(fbdisc);

    if(cab->posCabeca != -1){
        printf("*LISTA DE DISCIPLINAS*\n\n");
        printf("%-25s%-40s%-2s%-10s\n", "CODIGO DA DISCIPLINA", "NOME","CODIGO DO CURSO", "SERIE");

        print_nodeDisc(fbdisc, cab->posCabeca);
    }
    else printf("NAO HA DISCIPLINAS...\n");

    free(cab);
}

void print_nodeDisc(FILE* fbdisc, int pos){
    if(pos != -1){
        ListaDisc* c = leDisc(fbdisc, pos);
        int c_prox = c->prox;

        printf("%-25d%-40s%-10d%-10d\n", c->info.cod_disc, c->info.nome_disc,c->info.cod_curso,c->info.serie);
        
        free(c);
        print_nodeDisc(fbdisc, c_prox);
    }

}

void print_dist(FILE* fbdist){
    Cabecalho* cab = lerCabecalho(fbdist);

    if(cab->posCabeca != -1){
        printf("*LISTA DE DISTRIBUICOES*\n\n");
        printf("%-25s%-25s%-25s\n", "COD_DISCIPLINA", "ANO_LETIVO", "COD_PROFESSOR");

        print_nodeDist(fbdist, cab->posCabeca);
    }
    else printf("NAO HA DISTRIBUICOES...\n");

    free(cab);
}

void print_nodeDist(FILE* fbdist, int pos){
    if(pos != -1){
        ListaDistribuicao* c = leDist(fbdist, pos);
        int c_prox = c->prox;

        printf("%-25d%-25d%-25d\n", c->info.codigo_disciplina, c->info.ano_letivo,c->info.codigo_professor);
        
        free(c);
        print_nodeDist(fbdist, c_prox);
    }
}

void printListaDistPorCurso(FILE *fbdist, FILE *fbcurso, FILE *fbdisc) {
    // Verificar se os arquivos foram abertos corretamente
    if (fbdist == NULL || fbcurso == NULL || fbdisc == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    // Ler as informações dos cursos em um array
    InfosCurso cursos[100]; // Suponha que haja no máximo 100 cursos
     int i=0;
    Cabecalho* cab = lerCabecalho(fbcurso);
    int posc = cab->posCabeca;
    while(posc != -1){
        ListaCurso * cur = leCurso(fbcurso,posc);
        cursos[i].codigo = cur->info.codigo;
        strcpy(cursos[i].nome , cur->info.nome);
        posc = cur->prox;
        i++;
    }

   Cabecalho* cabdist = lerCabecalho(fbdist);
    Cabecalho * cabdisc = lerCabecalho(fbdisc);
    // Criar um mapeamento de código de curso para nome
    for (int i = 0; cursos[i].codigo!=0; i++) {
        printf("Curso %d: %s\n", cursos[i].codigo, cursos[i].nome);    
        // Iterar sobre as disciplinas e imprimir aquelas que estão relacionadas ao curso atual
        int posdisc = cabdisc->posCabeca;
        while (posdisc != -1) {
            ListaDisc *disciplina = leDisc(fbdisc, posdisc);
            if (disciplina->info.cod_curso == cursos[i].codigo) {
                printf("Disciplina %d: %s\n", disciplina->info.cod_disc, disciplina->info.nome_disc);

                // Iterar sobre as distribuições e imprimir aquelas relacionadas à disciplina
                int posdist = cabdist->posCabeca;
                while (posdist != -1) {
                    ListaDistribuicao *distribuicao = leDist(fbdist, posdist);
                    if (distribuicao->info.codigo_disciplina == disciplina->info.cod_disc) {
                        printf("Professor Responsavel:%-25d%s%d\n\n", distribuicao->info.codigo_professor,"Ano Letivo:", distribuicao->info.ano_letivo);
                    }
                    posdist = distribuicao->prox;
                }
            }
            posdisc = disciplina->prox;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------

int verificaDiscCurso(FILE * fbCurso, int disc){
    Cabecalho* cab = lerCabecalho(fbCurso);
    int pos = cab->posCabeca;
    while(pos != -1){
        ListaCurso* c = leCurso(fbCurso, pos);
        if(c->info.codigo == disc) return 1;
        pos = c->prox;
    }
    return -1;
}

int verificaDistProf(FILE * fbprof, int prof){
    Cabecalho* cab = lerCabecalho(fbprof);
    int pos = cab->posCabeca;
    while(pos != -1){
        ListaProfessor* c = leProf(fbprof, pos);
        if(c->info.codigo == prof) return 1;
        pos = c->prox;
    }
    return -1;
}


int verificaDistDisc(FILE * fbdisc, int dist){
    Cabecalho* cab = lerCabecalho(fbdisc);
    int pos = cab->posCabeca;
    while(pos != -1){
        ListaDisc* c = leDisc(fbdisc, pos);
        if(c->info.cod_disc == dist) return 1;
        pos = c->prox;
    }
    return -1;

}
