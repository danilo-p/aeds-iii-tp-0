# Trabalho Prático 0 - AEDS III

A especificação dada está no arquivo `Especificação.pdf`. A documentação do trabalho está disponível no arquivo `Documentação.pdf`.

## Compilação

Para compilar os programas, execute o comando `make`. Ele executará as tasks `setup` e `main`. A task `setup` criará duas pastas na raíz do projeto, `bin` e `obj`, e a task `main` compilará o código. A pasta `bin` conterá os arquivos executáveis dos programas, e a pasta `obj` conterá os arquivos objeto necessários para a compilação dos programas.

## Execução

Para executar um dos programas, entre na pasta `bin` e execute normalmente ou execute o comando `make TARGET="nome do executável" run`. Um exemplo de como executar o programa `arvore` seria `make TARGET="arvore" run`.
