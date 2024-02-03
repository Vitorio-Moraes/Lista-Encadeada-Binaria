
#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct{
    char nome[60];
    char area;
    int codigo;
}InfosCurso;

typedef struct {
    int codigo;
    char nome[50];
}infoProf;

typedef struct {
    int cod_disc;
    char nome_disc[50];
    int cod_curso;
    int serie;
}infoDisc;

typedef struct {
    int codigo_professor;
    int ano_letivo;
    int codigo_disciplina;
}infoDist;

typedef struct{
    int posCabeca;
    int posTopo;
    int posLivre;
}Cabecalho;

typedef struct{
    InfosCurso info;
    int prox;
}ListaCurso;

typedef struct{
    infoDist info;
    int prox;
}ListaDistribuicao;

typedef struct{
    infoProf info;
    int prox;
}ListaProfessor;

typedef struct{
    infoDisc info;
    int prox;
}ListaDisc;



#endif