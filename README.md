# Analisador léxico simplificado
## Trabalho para a disciplina compiladores (Unilasalle)

No programa desenvolvido neste trabalho, as expressões regulares foram utilizadas para implementar um analisador léxico simplificado, responsável por identificar tokens a partir de um texto fornecido via entrada padrão.

O funcionamento do programa ocorre em etapas:
* **Leitura da entrada:** o programa lê o código digitado pelo usuário linha por linha
* **Remoção de comentários:** trechos iniciados por # são ignorados
* **Divisão da linha em pedaços, tokens:** Cada linha é desmembrada em palavras que são separadas por espaços ou tabulações
* **Classificação dos tokens em categorias:** os elementos reconhecidos são classificados como:
  * palavras reservadas: int, float, if, etc.
  * identificadores: Valor, Nome (começa com maiúscula).
  * números
  * operadores e símbolos
* **Impressão do token reconhecido:** Cada token é impresso no formato <categoria, id>
  * ex: <reservada,1> <identificador,2> <=> <numero,3>
* **Montagem da tabela de símbolos:** Palavras reservadas, identificadores e números são guardados em uma tabela com três informações: ID, lexema (o texto em si) e tipo. O programa evita duplicatas, se o mesmo identificador aparecer duas vezes, ele só é guardado uma vez.
* **Exibição da Tabela de Símbolos ao final:** Quando a entrada termina, o programa imprime a tabela completa com todos os símbolos encontrados.

As expressões regulares foram definidas conforme as regras do enunciado:
* **Palavras reservadas:** reconhecidas por comparação direta
* **Identificadores:** ^[A-Z][a-zA-Z]*$
* **Números com vírgula:** ^[0-9]+,[0-9]+$
* **Comentários:** ^#.*
