#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define FILE_NAME "senhasUsers.txt"
//======================================================================================================//
//======================================================================================================//
    /*Função responsavel por chamar as outras funções, porem sem retorno, garantindo que o codigo consiga identificar e ativar todas quando forem chamadas, evitando assim possiveis erros.*/
void incluirUsuario();
void alterarSenha();
void excluirUsuario();
void listarUsuarios();
void apresentarCreditos();
void menuDlogin();
void criptografar(char* senha);
void descriptografar(char* senha);
void removerNovaLinha(char *str);
//======================================================================================================//
//======================================================================================================//
    /*STRUCT DE INFORMAÇÕES*/
struct infos {
    char nomeUsuario[21];
    char senhaConta[11];
};
struct infos F1;
//======================================================================================================//
//======================================================================================================//
    /*Função de criptografia (Cifra de César)*/
void criptografar(char* senha) {
    for (int i = 0; senha[i] != '\0'; i++) {
        senha[i] += 5;
    }
}

    /*Função de descriptografia (Cifra de César)*/
void descriptografar(char* senha) {
    for (int i = 0; senha[i] != '\0'; i++) {
        senha[i] -= 5;
    }
}
//======================================================================================================//
//======================================================================================================//
    /*Remover o caractere '\n' do final da stringr*/
void removerNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}
//======================================================================================================//
//======================================================================================================//
    /*PROCEDIMENTO DO MENU INICIAL*/
void menuDlogin() {
    int escolha;
    
    printf("\n  Menu Inicial.\n\n");
    printf("1- Incluir Usuario\n");
    printf("2- Alterar Senha\n");
    printf("3- Excluir Usuario\n");
    printf("4- Listar Usuarios\n");
    printf("5- Apresentar Creditos\n");
    printf("6- Sair\n\n");
    printf("Escolha uma opção: ");
    scanf("%i", &escolha);
    getchar();

    if (escolha >= 1 && escolha <= 6) {
        switch (escolha) {
            case 1:
                incluirUsuario();
                break;
            case 2:
                alterarSenha();
                break;
            case 3:
                excluirUsuario();
                break;
            case 4:
                listarUsuarios();
                break;
            case 5:
                apresentarCreditos();
                break;
            case 6:
                printf("\n \n");
                printf("\nFIM DA SESSÃO!!!\n");
                exit(0);
        }
    } else {
        printf("\nOpção inválida!!!\n");
        menuDlogin();
    }
}
//======================================================================================================//
//======================================================================================================//
    /*PROCEDIMENTO DAS OPÇÕES DO MENU*/

/*-------------------------------------------------------------------------------*/
 /*(1) Inclusão de Usuarios*/
void incluirUsuario() {
    char confirmaUser[21], confirmaSenha[11];
    int usuarioExistente = 0;
    
    FILE *file = fopen(FILE_NAME, "a+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    printf("\nInforme um nome de usuario (Limite maximo de 20 caracteres): ");
    fgets(F1.nomeUsuario, 20, stdin);
    fflush(stdin);
    removerNovaLinha(F1.nomeUsuario);

    rewind(file);
    while (fgets(confirmaUser, sizeof(confirmaUser), file) != NULL) {
        removerNovaLinha(confirmaUser);
        fgets(confirmaSenha, sizeof(confirmaSenha), file);

        removerNovaLinha(confirmaSenha);
        if (strcmp(F1.nomeUsuario, confirmaUser) == 0) {
            usuarioExistente = 1;
            break;
        }
    }

    if (usuarioExistente) {
        printf("\nUsuario já cadastrado! Por favor, informe outro nome de usuario!\n");
        fclose(file);
        return;
    }

    printf("Informe uma senha (Limite maximo de 10 caracteres): ");
    fgets(F1.senhaConta,10, stdin);
    fflush(stdin);
    removerNovaLinha(F1.senhaConta);

    printf("Confirme sua senha: ");
    fgets(confirmaSenha, 10, stdin);
    fflush(stdin);
    removerNovaLinha(confirmaSenha);

    if (strcmp(F1.senhaConta, confirmaSenha) == 0) {
        criptografar(F1.senhaConta);
        fprintf(file, "%s\n%s\n", F1.nomeUsuario, F1.senhaConta);
        printf("\nUsuario cadastrado com sucesso!\n");
    } else {
        printf("\nSenhas não coincidem. Tente novamente.\n");
    }

    fclose(file);
    menuDlogin();
}
//----------------------------------------------------------------------------*/
 /*(2) Alteração de senhas*/
void alterarSenha() {
    char confirmaUser[21], novaSenha[11], confirmaSenha[11]; 
    int usuarioEncontrado = 0;

    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("\nInforme seu nome de usuario: ");
    fgets(confirmaUser, 20, stdin);
    fflush(stdin);
    removerNovaLinha(confirmaUser);

    while (fgets(F1.nomeUsuario, sizeof(F1.nomeUsuario), file) != NULL) {
        removerNovaLinha(F1.nomeUsuario);
        if (fgets(F1.senhaConta, sizeof(F1.senhaConta), file) == NULL) {
            printf("Arquivo corrompido.\n");
            fclose(file);
            fclose(tempFile);
            remove("temp.txt");
            return;
        }
        removerNovaLinha(F1.senhaConta);
        char senhaDescriptografada[11];
        strcpy(senhaDescriptografada, F1.senhaConta);
        descriptografar(senhaDescriptografada);

        if (strcmp(F1.nomeUsuario, confirmaUser) == 0) {
            usuarioEncontrado = 1;

            printf("Informe sua senha atual: ");
            fgets(confirmaSenha, 10, stdin);
            fflush(stdin);
            removerNovaLinha(confirmaSenha);

            if (strcmp(senhaDescriptografada, confirmaSenha) == 0) {
                printf("Senha confirmada! Prossiga com a alteração.\n");

                printf("Informe sua nova senha: ");
                fgets(novaSenha, 10, stdin);
                fflush(stdin);
                removerNovaLinha(novaSenha);

                printf("Confirme sua nova senha: ");
                fgets(confirmaSenha, 10, stdin);
                fflush(stdin);
                removerNovaLinha(confirmaSenha);

                if (strcmp(novaSenha, confirmaSenha) == 0) {
                    criptografar(novaSenha);
                    fprintf(tempFile, "%s\n%s\n", F1.nomeUsuario, novaSenha);
                    printf("Senha alterada com sucesso!\n");
                } else {
                    printf("Senhas não coincidem. Alteração cancelada.\n");
                    fprintf(tempFile, "%s\n%s\n", F1.nomeUsuario, F1.senhaConta);
                }
            } else {
                printf("Senha atual incorreta.\n");
                fprintf(tempFile, "%s\n%s\n", F1.nomeUsuario, F1.senhaConta);
            }
        } else {
            fprintf(tempFile, "%s\n%s\n", F1.nomeUsuario, F1.senhaConta);
        }
    }

    if (!usuarioEncontrado) {
        printf("Usuário não encontrado.\n");
    }

    fclose(file);
    fclose(tempFile);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    menuDlogin();
}
/*-------------------------------------------------------------------------------*/
 /*(3) Exclusão de Usuarios*/
void excluirUsuario() {
    char confirmaUser[21], confirmaSenha[11]; 
    int usuarioEncontrado = 0;

    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        if (file != NULL) fclose(file);
        if (tempFile != NULL) fclose(tempFile);
        return;
    }

	printf("\n \n");
    printf("Informe seu nome do usuario que deseja excluir: ");
    fgets(confirmaUser, 20, stdin);
    fflush(stdin);
    removerNovaLinha(confirmaUser);

    while (fgets(F1.nomeUsuario, sizeof(F1.nomeUsuario), file) != NULL) {
        removerNovaLinha(F1.nomeUsuario);
        if (fgets(F1.senhaConta, sizeof(F1.senhaConta), file) == NULL) {

            printf("Arquivo corrompido.\n");
            fclose(file);
            fclose(tempFile);
            remove("temp.txt");
            return;
        }
        removerNovaLinha(F1.senhaConta);
        char senhaDescriptografada[11];
        strcpy(senhaDescriptografada, F1.senhaConta);
        descriptografar(senhaDescriptografada);

        if (strcmp(F1.nomeUsuario, confirmaUser) == 0) {
            usuarioEncontrado = 1;

            printf("Informe sua senha atual: ");
            fgets(confirmaSenha, 10, stdin);
            fflush(stdin);
            removerNovaLinha(confirmaSenha);

            if (strcmp(senhaDescriptografada, confirmaSenha) == 0) {
                printf("\nUsuario excluido com sucesso.\n");

            } else {
                printf("Senha atual incorreta.\n");
                fprintf(tempFile, "%s\n%s\n", F1.nomeUsuario, F1.senhaConta);
            }
        } else {
            fprintf(tempFile, "%s\n%s\n", F1.nomeUsuario, F1.senhaConta);
        }
    }

    if (!usuarioEncontrado) {
        printf("Usuário não encontrado.\n");
    }

    fclose(file);
    fclose(tempFile);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    menuDlogin();
}
/*-------------------------------------------------------------------------------*/
 /*(4) Listar Usuarios*/
void listarUsuarios() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("\nLista de Usuarios Cadastrados:\n");
    while (fgets(F1.nomeUsuario, sizeof(F1.nomeUsuario), file) != NULL) {
        removerNovaLinha(F1.nomeUsuario);
        if (fgets(F1.senhaConta, sizeof(F1.senhaConta), file) == NULL) {

            printf("Arquivo corrompido.\n");
            break;
        }
        removerNovaLinha(F1.senhaConta);
        char senhaDescriptografada[11];
        strcpy(senhaDescriptografada, F1.senhaConta);
        descriptografar(senhaDescriptografada);

        printf("Usuário: %s | Senha: %s\n", F1.nomeUsuario, senhaDescriptografada);
    }

    fclose(file);
    menuDlogin();
}
/*-------------------------------------------------------------------------------*/
 /*(5) Apresentar Creditos*/
void apresentarCreditos() {
    printf("\nAlunos {\n");
    printf("   1-Ramon Gabriel de Oliveira Olimpio - RA: 24150616-2\n");
    printf("   2-Ettore Luiz Petta Dianin - RA: 24062158-2\n");
    printf("   3-Murilo Xavier Martinez - RA: 24247432-2\n");
    printf("}\n");
    menuDlogin();
}
//======================================================================================================//
//======================================================================================================//
int main() {
    setlocale(LC_ALL, "portuguese");
    menuDlogin();
    return 0;
}
