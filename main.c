#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct{
	char rua[50];
	char cidade[20];
	char estado[20];
}Endereco;


typedef struct{
	char nome[50];
	Endereco endereco;
	float salario;
	char estadoCivil[15];
	int idade;
	char sexo;
}Cadastro;


void testarArquivo(FILE* arq){
	if(arq == NULL)
	{
			printf("Erro ao abrir o arquivo! Tente novamente.\n");
			exit(1);
	}//if
}

void testarAlocacao(Cadastro* cadastros){
	if(cadastros==NULL){
    	printf("Erro: Memória Insuficiente!\n");
    	exit(1);
	}
}

void preencheCadastro(Cadastro* cadastros, FILE* arq, int qtdDeFuncionarios){
 	for(int i = 0; i < qtdDeFuncionarios; i++)
    	{

        	fscanf(arq,"\n{%[^;]; {%[^;]; %[^;]; %[^}]} ; %f; %[^;]; %i; %c}\n",cadastros[i].nome,cadastros[i].endereco.rua,
                	cadastros[i].endereco.cidade, cadastros[i].endereco.estado, &cadastros[i].salario,
                	cadastros[i].estadoCivil, &cadastros[i].idade, &cadastros[i].sexo);
    	}
}
int menu(){
  int opcao;
  do {
    printf("\nMenu:\n");
    printf("1 - Pesquisar funcionario por nome\n");
    printf("2 - Pesquisar funcionario por salario\n");
    printf("3 - Pesquisar funcionario por sexo\n");
    printf("4 - Alterar idade do funcionario \n");
    printf("Digite uma opcao: ");
    scanf("%d", &opcao);
    fflush(stdin);
    if(opcao!=1 && opcao!=2 && opcao!=3 && opcao!=4){
      printf("\nOpcao invalida!\n");
    }
  } while(opcao!=1 && opcao!=2 && opcao!=3 && opcao!=4);
  return opcao;
}
void buscaFuncionario(int opcao,  int qtdDeFuncionarios, Cadastro* cadastros){
  char nome[50];
  float salario;
  char sexo;
  int idade, j;
    switch (opcao) {
      case 1:
      j=0;
      printf("\nDigite o nome do funcionario que deseja pesquisar: \n");
      fgets(nome, 49, stdin);
      nome[strcspn(nome,"\n")]='\0';
      fflush(stdin);
      for(int i=0; i<qtdDeFuncionarios; i++){
          if(strcasecmp(nome,cadastros[i].nome)==0){
              printf("Idade do funcionario: %d\n", cadastros[i].idade);
              printf("Salario do funcionario: R$%.2f\n", cadastros[i].salario);
          }else{
            j++;
          }//else
        }//for
        if(j==qtdDeFuncionarios){
          printf("Funcionario nao encontrado!\n");
        }//if 2
        break;
        case 2:
        j=0;
        printf("\nDigito o salario: \n");
        scanf("%f", &salario);
        fflush(stdin);
        for(int i=0; i<qtdDeFuncionarios; i++){
          if (salario<=cadastros[i].salario) {
            printf("%s\n", cadastros[i].nome);
          }else{
            j++;
          }
        }//for
        if(j==qtdDeFuncionarios){
          printf("Nao foram encontrados funcionarios com salario superior a %.2f\n", salario);
        }
        break;
        case 3:
        j=0;
        printf("\nDigite o sexo\n");
        scanf("%c", &sexo);
        fflush(stdin);
        for(int i=0; i<qtdDeFuncionarios; i++){
          if(toupper(sexo)==cadastros[i].sexo){
            printf("Nome: %s , idade: %d, salario: R$%.2f\n", cadastros[i].nome, cadastros[i].idade, cadastros[i].salario);
          }else{
            j++;
          }//else
        }//for
          if(j==qtdDeFuncionarios){
            printf("Nao foram encontrados funcionarios desse sexo!\n");
          }
        break;
        case 4:
        j=0;
        printf("\nDigite o nome do funcionario que deseja pesquisar: \n");
        fgets(nome, 49, stdin);
        nome[strcspn(nome,"\n")]='\0';
        fflush(stdin);
        for(int i=0; i<qtdDeFuncionarios; i++){
            if(strcasecmp(nome,cadastros[i].nome)==0){
                printf("Digite a nova idade: \n");
                scanf("%d", &idade);
                fflush(stdin);
                cadastros[i].idade = idade;
            }else{
              j++;
            }//else
          }//for
          if(j==qtdDeFuncionarios){
            printf("Funcionario nao encontrado!\n");
          }//if 2
        break;
        default:
        printf("Opcao invalida!\n");
        break;
    }//switch
}
char voltarMenu(int opcao,  int qtdDeFuncionarios, Cadastro* cadastros){
  char resposta;
  printf("Deseja voltar para o menu? (S/N)\n");
  scanf("%c", &resposta);
  fflush(stdin);
  if(toupper(resposta)=='S'){
    opcao = menu();
    buscaFuncionario(opcao, qtdDeFuncionarios,cadastros);
    return resposta;
  }else if(toupper(resposta)=='N'){
    return resposta;
  }else{
    printf("Opcao invalida!\n");
    voltarMenu(opcao, qtdDeFuncionarios, cadastros);
  }
}
void salvarDados(Cadastro* cadastros, FILE* arq, int qtdDeFuncionarios){
	fprintf(arq, "%d\n", qtdDeFuncionarios);
	for(int i = 0; i < qtdDeFuncionarios; i++){
		fprintf(arq, "{%s; {%s; %s; %s} ; %f; %s; %i; %c}\n", cadastros[i].nome,cadastros[i].endereco.rua,
						cadastros[i].endereco.cidade, cadastros[i].endereco.estado, cadastros[i].salario,
						cadastros[i].estadoCivil, cadastros[i].idade, cadastros[i].sexo);
	}
}
int main(int argc, char *argv[]){


	Cadastro *cadastros;
	int opcao;
  char resposta;
	//abrir arquivo
	FILE *arq = fopen(argv[1], "r");
	testarArquivo(arq);

	//alocacao
	int qtdDeFuncionarios;
	fscanf(arq, "%d", &qtdDeFuncionarios);
	cadastros = (Cadastro*)calloc(qtdDeFuncionarios,sizeof(Cadastro));
	testarAlocacao(cadastros);

	preencheCadastro(cadastros, arq, qtdDeFuncionarios);
	opcao = menu();
  buscaFuncionario(opcao, qtdDeFuncionarios, cadastros);
  do{
    resposta = voltarMenu(opcao, qtdDeFuncionarios, cadastros);
  }while(toupper(resposta)=='S');

	fclose(arq);
  //salvar novo arquivo
  arq = fopen(argv[1], "w");
	testarArquivo(arq);
	salvarDados(cadastros, arq, qtdDeFuncionarios);
	fclose(arq);
	free(cadastros);
	return 0;
}
