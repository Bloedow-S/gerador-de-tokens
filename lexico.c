#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>


typedef struct {
    int id;
    char lexema[100];
    char categoria[50];
} ElementoTabela;

ElementoTabela tabela[100];
int contador_simbolos = 0;


int inserir_ou_buscar(char *item, char *classe) {
    int i;
   
    for (i = 0; i < contador_simbolos; i++) {
        if (strcmp(tabela[i].lexema, item) == 0) {
            return tabela[i].id;
        }
    }
      tabela[contador_simbolos].id = contador_simbolos + 1;
    strcpy(tabela[contador_simbolos].lexema, item);
    strcpy(tabela[contador_simbolos].categoria, classe);
    contador_simbolos++;
    return contador_simbolos;
}


int testar_regex(char *texto, const char *expressao) {
    regex_t reg;
    int resultado;
    if (regcomp(&reg, expressao, REG_EXTENDED | REG_NOSUB) != 0) return 0;
    resultado = regexec(&reg, texto, 0, NULL, 0);
    regfree(&reg);
    return (resultado == 0);
}

int main() {
    char linha[500];
    char *pedaco;
    
    printf("--- INICIANDO ANALISE LEXICA ---\n");

    
    while (fgets(linha, sizeof(linha), stdin)) {
        
       
        char *ponto_comentario = strchr(linha, '#');
        if (ponto_comentario) *ponto_comentario = '\0';

       
        pedaco = strtok(linha, " \t\n\r");
        
        while (pedaco != NULL) {
           
            if (testar_regex(pedaco, "^(int|double|char|float|if|while|for)$")) {
                int id = inserir_ou_buscar(pedaco, "reservada");
                printf("<reservada,%d> ", id);
            } 
            else if (testar_regex(pedaco, "^[A-Z][a-zA-Z]*$")) {
                int id = inserir_ou_buscar(pedaco, "identificador");
                printf("<identificador,%d> ", id);
            } 
            else if (testar_regex(pedaco, "^[0-9]+(,[0-9]+)?$")) {
                int id = inserir_ou_buscar(pedaco, "numero");
                printf("<numero,%d> ", id);
            } 
            else if (testar_regex(pedaco, "^(==|<=|>=|!=|<|>|=|[\\+\\-\\*/])$")) {
                printf("<%s,> ", pedaco);
            }
            else if (testar_regex(pedaco, "^[;\\(\\)\\{\\}]$")) {
                printf("<%s,> ", pedaco);
            }
           

            pedaco = strtok(NULL, " \t\n\r");
        }
        printf("\n");
    }

   
    printf("\nTABELA DE SIMBOLOS FINAL:\n");
    printf("ID\t| Lexema\t| Tipo\n");
    printf("---------------------------------------\n");
    for (int j = 0; j < contador_simbolos; j++) {
        printf("%d\t| %s\t\t| %s\n", tabela[j].id, tabela[j].lexema, tabela[j].categoria);
    }

    return 0;
}
