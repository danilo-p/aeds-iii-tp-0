# Trabalho Prático 0 - AEDS III

A especificação dada está no arquivo `Especificação.pdf`. A documentação do trabalho está disponível no arquivo `Documentação.pdf`.

## Compilação

Para compilar o programa, execute o comando `make`. Ele executará as tasks `setup` e `main`. A task `setup` criará duas pastas na raíz do projeto, `bin` e `obj`, e a task `main` compilará o código. A pasta `bin` conterá os arquivos executáveis do programa, e a pasta `obj` conterá os arquivos objeto necessários para a compilação do programa.

## Execução

Para executar o programa, execute o comando `make TARGET="nome do executável" ARGS="argumentos para o programa" run`. Um exemplo de como executar o programa `arvore` seria `make TARGET="arvore" ARGS="in_1.in out_1.out" run`.
