#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "funcoes_arq.h"
#include "funcoes_man.h"
#include "structs.h"

//Cria uma struct auxiliar de armazenamento
//chama a função insere nó
ListaCurso * scan_curso(){
    ListaCurso * aux = (ListaCurso*) malloc(sizeof(ListaCurso));

    printf("Digite o codigo: \n");
    scanf("%d%*C", &aux->info.codigo);

    printf("Digite o nome do curso: \n");
    scanf("%[^\n]%*c", aux->info.nome);

    printf("Digite a Area do curso: \n");
    scanf("%c%*c", &aux->info.area);

    return aux;
}

//Cria uma struct auxiliar de armazenamento
//chama a função insere nó
ListaProfessor * scan_professor(){
    ListaProfessor * aux = (ListaProfessor *) malloc(sizeof(ListaProfessor));

    printf("Digite o codigo do professor: \n");
    scanf("%d%*C", &aux->info.codigo);

    printf("Digite o nome do professor: \n");
    scanf("%[^\n]%*c", aux->info.nome);

    return aux;
}

//Cria uma struct auxiliar de armazenamento
//chama a função insere nó
ListaDisc * scan_disciplina(FILE * fb_curso){
    ListaDisc * aux = (ListaDisc*)malloc(sizeof(ListaDisc));

    printf("Digite o codigo: \n");
    scanf("%d%*c", &aux->info.cod_disc);           //alterar struct

    printf("Digite o nome da disciplina: \n");
    scanf("%[^\n]%*c", aux->info.nome_disc);

    do{
    printf("Digite o codigo do curso: \n");
    scanf("%d", &aux->info.cod_curso);
    if (verificaDiscCurso(fb_curso,aux->info.cod_curso)==-1){
        printf("codigo do curso invalido, tente cadastrar a disciplina novamente\n ");
    }
    }while(verificaDiscCurso(fb_curso,aux->info.cod_curso)!=1);
    printf("Digite a serie da disciplina: \n");
    scanf("%d%*c", &aux->info.serie);

    return aux;

}

//Cria uma struct auxiliar de armazenamento
//chama a função insere nó
ListaDistribuicao * scan_distribuicao(FILE * fb_disciplina, FILE * fb_prof){
    ListaDistribuicao * aux = (ListaDistribuicao *)malloc(sizeof(ListaDistribuicao));

    do{
    printf("Digite o codigo do professor: \n");
    scanf("%d", &aux->info.codigo_professor);               //alterar a struct utilizada
    if(verificaDistProf(fb_prof,aux->info.codigo_professor)==-1){
        printf("codigo do professor invalido, tente cadastrar o professor novamente\n ");   
    }
    }while(verificaDistProf(fb_prof,aux->info.codigo_professor)!=1);

    printf("Digite o ano letivo: \n");
    scanf("%d", &aux->info.ano_letivo);

    do{
    printf("Digite o codigo da disciplina: \n");
    scanf("%d%*c", &aux->info.codigo_disciplina);
    if(verificaDistDisc(fb_disciplina,aux->info.codigo_disciplina)==-1){
        printf("codigo da discilina invalido, tente cadastrar a disciplina novamente\n ");
    }
    }while(verificaDistDisc(fb_disciplina,aux->info.codigo_disciplina)!=1);

    return aux;
}

void insert_lote(FILE* fr, FILE* fbCurso,FILE* fbDisc, FILE* fbDist, FILE* fbProfessor){
    char categoria;

    while(fscanf(fr,"%c;", &categoria) != EOF){
        
        if(categoria=='C'){
            ler_arquivoTexto_curso(fr, fbCurso);
        }
         else if(categoria =='D'){
            ler_arquivoTexto_disc(fr,fbDisc);
         }
        else if(categoria =='P'){
            ler_arquivoTexto_professsor(fr,fbProfessor);
        }
        else if(categoria =='M'){
            ler_arquivoTexto_dist(fr,fbDist);
        }
    }
}

void ler_arquivoTexto_curso(FILE* fr, FILE* fbCurso){
    InfosCurso aux;

    fscanf(fr, "%d;", &aux.codigo);
    fscanf(fr, "%[^;]%*c", aux.nome);
    fscanf(fr, "%c\n", &aux.area);
    if(!verifica_curso(fbCurso,aux)){
    insere_curso(fbCurso, aux);
    }
}

void ler_arquivoTexto_professsor(FILE* fr, FILE* fbProfessor){
    infoProf aux;

    fscanf(fr,"%d;",&aux.codigo);
    fscanf(fr,"%[^\n]%*c",aux.nome);
    if(!verifica_prof(fbProfessor,aux))
    insere_professor(fbProfessor,aux);

}


void ler_arquivoTexto_disc(FILE* fr, FILE* fbDisciplina){
    infoDisc aux;

    fscanf(fr,"%d;",&aux.cod_disc);
    fscanf(fr,"%[^;]%*c",aux.nome_disc);
    fscanf(fr,"%d;",&aux.cod_curso);
    fscanf(fr,"%d\n",&aux.serie);
    if(!verifica_disc(fbDisciplina,aux))
    insere_disc(fbDisciplina,aux);
}


void ler_arquivoTexto_dist(FILE* fr, FILE* fbDistribuicao){
    infoDist aux;

    fscanf(fr,"%d;",&aux.codigo_disciplina);
    fscanf(fr,"%d;",&aux.ano_letivo);
    fscanf(fr,"%d\n",&aux.codigo_professor);
    if(!verifica_dist(fbDistribuicao,aux))
    insere_dist(fbDistribuicao,aux);
}

//------------------------------------------------------------------------------------------------------------------

int verifica_curso(FILE * fbCurso, InfosCurso curso){     
    Cabecalho* cab = lerCabecalho(fbCurso);
    int pos = cab->posCabeca;
    while(pos != -1){
        ListaCurso* c = leCurso(fbCurso, pos);
         if(strcmp(curso.nome,c->info.nome) == 0|| curso.codigo == c->info.codigo) {
         printf("esse curso ja existe!\n");
         return 1;
         }
        pos = c->prox;
    }    
    return 0;
}

int verifica_disc(FILE * fbdisc, infoDisc disc){     
    Cabecalho* cab = lerCabecalho(fbdisc);
    int pos = cab->posCabeca;
    while(pos != -1){
        ListaDisc *c = leDisc(fbdisc, pos);
         if(strcmp(c->info.nome_disc,disc.nome_disc)==0 || c->info.cod_disc==disc.cod_disc) {
         printf("essa disciplina ja existe!\n");
         return 1;
         }
        pos = c->prox;
    }    
    return 0;
}

int verifica_prof(FILE * fbprof, infoProf prof){     
    Cabecalho* cab = lerCabecalho(fbprof);
    int pos = cab->posCabeca;
    while(pos != -1){
        ListaProfessor *c = leProf(fbprof, pos);
         if(strcmp(c->info.nome,prof.nome)==0 || c->info.codigo==prof.codigo) {
         printf("esse professor ja existe!\n");
         return 1;
         }
        pos = c->prox;
    }    
    return 0;
}

int verifica_dist(FILE * fbdist, infoDist dist){     
    Cabecalho* cab = lerCabecalho(fbdist);
    int pos = cab->posCabeca;
    while(pos != -1){
        ListaDistribuicao *c = leDist(fbdist, pos);
         if(dist.ano_letivo==c->info.ano_letivo && dist.codigo_disciplina == c->info.codigo_disciplina) {
         printf("essa distribuicao ja existe!\n");
         return 1;
         }
        pos = c->prox;
    }    
    return 0;
}






