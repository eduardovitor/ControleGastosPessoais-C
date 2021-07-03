#include <stdio.h>
#include <string.h>
int indice=0;
FILE *usuarios,*gastosusuarios;
char user[100];
char password[100];
struct gasto{
	char nome[100];
	float valor;
	char categoria[100];
	char datacompra[100];
	char mensal;
};
typedef struct gasto Gasto;
Gasto gastos[1000];
void imprimeMenu(){//Função que vai está sempre exibindo o menu
	printf("Menu \n (1) Cadastrar gasto \n (2) Gastos por categoria \n (3) Gastos fixos \n (4) Todos os gastos \n (5) Remover gasto \n (6) Alterar descricao do gasto \n (7) Alterar valor do gasto \n (8) Alterar categoria do gasto \n (9) Alterar data do gasto \n (10)Alterar se o gasto e fixo ou nao \n (11)Remover minha conta \n (12)Fazer logout \n (13)Encerrar a execucao \n ");
}
int verificaLogin(char usuario[], char senha[]){//Função que verifica se o usuario realmente existe no arquivo.
	usuarios=fopen("usuarios.txt","rt");
	int r=2;//Valor que vai retornar para confirmar se estão corretos login e senha.
	char u[100];
	char s[100];
	while(fscanf(usuarios,"%s %s\n",u,s)>0){
		if(strcmp(usuario,u)==0 && strcmp(senha,s)==0){
			strcpy(user,u);
			strcpy(password,s);
			r=1;
			return r;
			break;
		}	
	}
	fclose(usuarios);
	return r;
}
void CadastrarGasto(){ 	//Função para cadastrar novos gastos
		fflush(stdin);			
		printf("Digite o nome da transacao: \n");
		scanf("%s",gastos[indice].nome);
		fflush(stdin);
		printf("Digite o valor da transacao: \n");
		scanf("%f",&gastos[indice].valor);
		fflush(stdin);
		printf("Digite a categoria do gasto: \n");
		scanf("%s",gastos[indice].categoria);		
		fflush(stdin);
		printf("Digite a data da compra: \n");
		scanf("%s",gastos[indice].datacompra);
		fflush(stdin);
		printf("Digite se o gasto e mensal ou nao(S-sim, N-nao): \n");
		scanf("%c",&gastos[indice].mensal);
		gastosusuarios=fopen("gastosusuarios.txt","at");
		fprintf(gastosusuarios,"%s %s %.2f %s %s %c\n",user, gastos[indice].nome, 
		gastos[indice].valor, gastos[indice].categoria, gastos[indice].datacompra,gastos[indice].mensal);
		fclose(gastosusuarios);
	    indice++;
}
void CadastrarUsuario(){// Função para cadastrar novos usuarios
	char nome[100], senha[100], c;
	int a=0;
	printf("Digite o usuario: \n");
	scanf("%s",nome);
	printf("Digite a senha: \n");
	 do{
           c=getch();
           if(isprint(c)){       //Analisa se o valor da variável c é imprimivel
           senha[a]=c;  //Se for, armazena o caractere
           a++;
           printf("*");          //imprime o * Anterisco
           }
           else if(c==8&&a){     //8 é o caractere BackSpace na tabela ASCII, && a analisa se a é diferente de 0
           senha[a]='\0';
           a--;
           printf("\b \b");       //Apagando o caractere digitado
           }
    }while(c!=13);             //13 é o valor de ENTER na tabela ASCII
    senha[a]='\0';
	strcpy(user,nome);
	usuarios=fopen("usuarios.txt","at");
	fprintf(usuarios,"\n%s %s\n",nome,senha);
	fclose(usuarios);
	printf("\n");
	printf("Usuario cadastrado com sucesso! \n");
}
void ExibirGastosPorCategoria(char categoria[]){// Função para exibir por categoria;
	 gastosusuarios=fopen("gastosusuarios.txt","rt");
	 int v=0; //Verificação se pelo menos uma vez a categoria foi igual a alguma dentro do arquivo
	 char nome[100], descr[100], cat[100], data[100], mensal;
	 float valorgasto;    
	 while(fscanf(gastosusuarios,"%s %s %f %s %s %c\n",&nome,&descr,&valorgasto,&cat,&data,&mensal)>0){
	 	if(strcmp(user,nome)==0 && strcmp(categoria,cat)==0){
	 		printf("Os gastos dentro desta categoria sao: \n");
	 		printf("Descricao: %s\nValor: %.2f\nData de compra: %s\nFixo: %c\n",descr,valorgasto,data,mensal);
	 		v=1;
		 }
	 }
	 fclose(gastosusuarios);
	 if(v==0){
	 	printf("Categoria nao encontrada \n");
	 }
}
void ExibirGastosFixos(){// Função que verifica e mostra os gastos mensais. 
	 gastosusuarios=fopen("gastosusuarios.txt","rt");
	 char nome[100], descr[100], cat[100], data[100], mensal;
	 float valorgasto;
	 while(fscanf(gastosusuarios,"%s %s %f %s %s %c\n",&nome,&descr,&valorgasto,&cat,&data,&mensal)>0){
	 	if(strcmp(user,nome)==0 && mensal=='S'){
	 		printf("Descricao: %s\nValor: %.2f\nData de compra: %s\n--------\n",descr,valorgasto,data);
		 }
	 }
	 fclose(gastosusuarios);
}
void ExibirTodosOsGastos(){// Função que exibe todos os gastos do usuario.
	 gastosusuarios=fopen("gastosusuarios.txt","rt");
	 char nome[100], descr[100], cat[100], data[100], mensal;
	 float valorgasto;
	 float somagastos=0.0;
	 while(fscanf(gastosusuarios,"%s %s %f %s %s %c\n",&nome,&descr,&valorgasto,&cat,&data,&mensal)>0){
	 	if(strcmp(user,nome)==0){
	 		printf("Descricao: %s\nValor: %.2f\nCategoria: %s\nData de compra: %s\nFixo: %c\n--------\n",descr,valorgasto,cat,data,mensal);
	 		somagastos+=valorgasto;
	     }
	 }
	 fclose(gastosusuarios);
	 printf("Total: %.2f reais \n",somagastos);
}
void RemoverGasto(char descricao[]){ // Função que remove o gasto.
	 gastosusuarios=fopen("gastosusuarios.txt","rt"); //obs: é preciso ler primeiro o arquivo e depois, escrever, pois se não, dá problema
	 char nome[100][100], descr[100][100], cat[100][100], data[100][100], mensal[100], apag[100]; //vetores para guardar as informações contidas no arquivo
	 int v=0; //contagem de linhas do arquivo
	 int a=0;
	 int i;
	 float valorgasto[100];
	 while(fscanf(gastosusuarios,"%s %s %f %s %s %c\n",&nome[v],&descr[v],&valorgasto[v],&cat[v],&data[v],&mensal[v])>0){
	 	if(strcmp(user,nome[v])==0 && strcmp(descr[v],descricao)==0){
	 	    apag[v]='0'; //vetor usado para delimitar a linha do arquivo que não será gravada novamente
			a=1; 
		 }else{
		    apag[v]='1'; //todos os índices do vetor apag que possuirem valor '1' serão gravados
	     }
	     v++;
       }
      fclose(gastosusuarios);
      gastosusuarios=fopen("gastosusuarios.txt","wt");// Aqui a gente abre denovo o arquivo só que agora vamos escrever nele.
      for (i = 0; i<v; i++){
      	if(apag[i]!='0'){
      		fprintf(gastosusuarios,"%s %s %.2f %s %s %c\n",nome[i],descr[i],valorgasto[i],cat[i],data[i],mensal[i]);
		  }
	  }
     fclose(gastosusuarios);
     if(a==1){
     	printf("Gasto removido com sucesso! \n");
	 }
	 else{
	 	printf("Descricao nao encontrada \n");
	 }
}
void AlterarDescricaoGasto(char descricao[], char novadescricao[]){// Função que altera a descrição/nome do gasto.
	 gastosusuarios=fopen("gastosusuarios.txt","rt"); //obs: é preciso ler primeiro o arquivo e depois, escrever, pois se não, dá problema
	 char nome[100][100], descr[100][100], cat[100][100], data[100][100], mensal[100], alter[100]; //vetores para guardar as informações contidas no arquivo
	 int v=0; //contagem de linhas do arquivo
	 int a=0;
	 int i;
	 float valorgasto[100];
	 while(fscanf(gastosusuarios,"%s %s %f %s %s %c\n",&nome[v],&descr[v],&valorgasto[v],&cat[v],&data[v],&mensal[v])>0){
	 	if(strcmp(user,nome[v])==0 && strcmp(descr[v],descricao)==0){
	 	    alter[v]='0'; //vetor usado para delimitar a linha do arquivo que será alterada
			a=1; 
		 }else{
		    alter[v]='1';
	     }
	     v++;
       }
      fclose(gastosusuarios);
      gastosusuarios=fopen("gastosusuarios.txt","wt"); // Aqui a gente abre denovo o arquivo só que agora vamos escrever nele.
      for (i = 0; i<v; i++){
      	if(alter[i]=='0'){
      		fprintf(gastosusuarios,"%s %s %.2f %s %s %c\n",nome[i],novadescricao,valorgasto[i],cat[i],data[i],mensal[i]);
		  }
		  else{
		  	fprintf(gastosusuarios,"%s %s %.2f %s %s %c\n",nome[i],descr[i],valorgasto[i],cat[i],data[i],mensal[i]);
		  }
	  }
     fclose(gastosusuarios);
     if(a==1){
     	printf("Gasto alterado com sucesso! \n");
	 }
	 else{
	 	printf("Descricao nao encontrada \n");
	 }
}
void AlterarValorGasto(char descricao[], float *valor){// Função que altera o valor gasto.
	gastosusuarios=fopen("gastosusuarios.txt","rt"); //obs: é preciso ler primeiro o arquivo e depois, escrever, pois se não, dá problema
	 char nome[100][100], descr[100][100], cat[100][100], data[100][100], mensal[100], alter[100]; //vetores para guardar as informações contidas no arquivo
	 int v=0; //contagem de linhas do arquivo
	 int a=0; // Variavel que vai retornar se as informaçoes estão corretas.
	 int i;
	 float valorgasto[100];
	 while(fscanf(gastosusuarios,"%s %s %f %s %s %c\n",&nome[v],&descr[v],&valorgasto[v],&cat[v],&data[v],&mensal[v])>0){
	 	if(strcmp(user,nome[v])==0 && strcmp(descr[v],descricao)==0){
	 	    alter[v]='0'; //vetor usado para delimitar a linha do arquivo que será alterada
			a=1; 
		 }else{
		    alter[v]='1';
	     }
	     v++;
       }
      fclose(gastosusuarios);
      gastosusuarios=fopen("gastosusuarios.txt","wt");
      for (i = 0; i<v; i++){
      	if(alter[i]=='0'){
      		fprintf(gastosusuarios,"%s %s %.2f %s %s %c\n",nome[i],descr[i],*valor,cat[i],data[i],mensal[i]);
		  }
		  else{
		  	fprintf(gastosusuarios,"%s %s %.2f %s %s %c\n",nome[i],descr[i],valorgasto[i],cat[i],data[i],mensal[i]);
		  }
	  }
     fclose(gastosusuarios);
     if(a==1){
     	printf("Gasto alterado com sucesso! \n");
	 }
	 else{
	 	printf("Descricao nao encontrada \n");
	 }
}
void AlterarCategoriaGasto(char descricao[], char categoria[]){// Função que altera a categoria do gasto.
	 gastosusuarios=fopen("gastosusuarios.txt","rt"); //obs: é preciso ler primeiro o arquivo e depois, escrever, pois se não, dá problema
	 char nome[100][100], descr[100][100], cat[100][100], data[100][100], mensal[100], alter[100]; //vetores para guardar as informações contidas no arquivo
	 int v=0; //contagem de linhas do arquivo
	 int a=0; // Variavel que vai retornar se as informaçoes estão corretas.
	 int i;
	 float valorgasto[100];
	 while(fscanf(gastosusuarios,"%s %s %f %s %s %c\n",&nome[v],&descr[v],&valorgasto[v],&cat[v],&data[v],&mensal[v])>0){
	 	if(strcmp(user,nome[v])==0 && strcmp(descr[v],descricao)==0){
	 	    alter[v]='0'; //vetor usado para delimitar a linha do arquivo que será alterada
			a=1; 
		 }else{
		    alter[v]='1';
	     }
	     v++;
       }
      fclose(gastosusuarios);
      gastosusuarios=fopen("gastosusuarios.txt","wt");
      for (i = 0; i<v; i++){
      	if(alter[i]=='0'){
      		fprintf(gastosusuarios,"%s %s %.2f %s %s %c\n",nome[i],descr[i],valorgasto[i],categoria,data[i],mensal[i]);
		  }
		  else{
		  	fprintf(gastosusuarios,"%s %s %.2f %s %s %c\n",nome[i],descr[i],valorgasto[i],cat[i],data[i],mensal[i]);
		  }
	  }
     fclose(gastosusuarios);
     if(a==1){
     	printf("Gasto alterado com sucesso! \n");
	 }
	 else{
	 	printf("Descricao nao encontrada \n");
	 }
}
void AlterarDataGasto(char descricao[], char d[]){// Função que altera a data do gasto.
	 gastosusuarios=fopen("gastosusuarios.txt","rt"); //obs: é preciso ler primeiro o arquivo e depois, escrever, pois se não, dá problema
	 char nome[100][100], descr[100][100], cat[100][100], data[100][100], mensal[100], alter[100]; //vetores para guardar as informações contidas no arquivo
	 int v=0; //contagem de linhas do arquivo
	 int a=0;// Variavel que vai retornar se as informaçoes estão corretas.
	 int i;
	 float valorgasto[100];
	 while(fscanf(gastosusuarios,"%s %s %f %s %s %c\n",&nome[v],&descr[v],&valorgasto[v],&cat[v],&data[v],&mensal[v])>0){
	 	 if(strcmp(user,nome[v])==0 && strcmp(descr[v],descricao)==0){
	 	    alter[v]='0'; //vetor usado para delimitar a linha do arquivo que será alterada
			a=1; 
		 }else{
		    alter[v]='1';
	     }
	     v++;
       }
      fclose(gastosusuarios);
      gastosusuarios=fopen("gastosusuarios.txt","wt");
      for (i = 0; i<v; i++){
      	 if(alter[i]=='0'){
      		fprintf(gastosusuarios,"%s %s %.2f %s %s %c\n",nome[i],descr[i],valorgasto[i],cat[i],d,mensal[i]);
		  }
		  else{
		  	fprintf(gastosusuarios,"%s %s %.2f %s %s %c\n",nome[i],descr[i],valorgasto[i],cat[i],data[i],mensal[i]);
		  }
	  }
     fclose(gastosusuarios);
     if(a==1){
     	printf("Gasto alterado com sucesso! \n");
	 }
	 else{
	 	printf("Descricao nao encontrada \n");
	 }
}
void AlterarFixoGasto(char descricao[], char *fixo){// Função que altera se o gasto é fixo ou não.
	 gastosusuarios=fopen("gastosusuarios.txt","rt"); //obs: é preciso ler primeiro o arquivo e depois, escrever, pois se não, dá problema
	 char nome[100][100], descr[100][100], cat[100][100], data[100][100], mensal[100], alter[100]; //vetores para guardar as informações contidas no arquivo
	 int v=0; //contagem de linhas do arquivo
	 int a=0;// Variavel que vai retornar se as informaçoes estão corretas.
	 int i;
	 float valorgasto[100];
	 while(fscanf(gastosusuarios,"%s %s %f %s %s %c\n",&nome[v],&descr[v],&valorgasto[v],&cat[v],&data[v],&mensal[v])>0){
	 	 if(strcmp(user,nome[v])==0 && strcmp(descr[v],descricao)==0){
	 	    alter[v]='0'; //vetor usado para delimitar a linha do arquivo que será alterada
			a=1; 
		 }else{
		    alter[v]='1';
	     }
	     v++;
       }
      fclose(gastosusuarios);
      gastosusuarios=fopen("gastosusuarios.txt","wt");
      for (i = 0; i<v; i++){
      	 if(alter[i]=='0'){
      		fprintf(gastosusuarios,"%s %s %.2f %s %s %c\n",nome[i],descr[i],valorgasto[i],cat[i],data[i],*fixo);
		  }
		  else{
		  	fprintf(gastosusuarios,"%s %s %.2f %s %s %c\n",nome[i],descr[i],valorgasto[i],cat[i],data[i],mensal[i]);
		  }
	  }
     fclose(gastosusuarios);
     if(a==1){
     	printf("Gasto alterado com sucesso! \n");
	 }
	 else{
	 	printf("Descricao nao encontrada \n");
	 }
}
void RemoverConta(char usuario[]){// Função que deleta a conta do usuário.
	 usuarios=fopen("usuarios.txt","rt"); //obs: é preciso ler primeiro o arquivo e depois, escrever, pois se não, dá problema
	 char nome[100][100], nome2[100][100],senha[100][100], descr[100][100], cat[100][100], data[100][100], mensal[100],apag[100], apag2[100];
	 float valorgasto[100]; //vetores para guardar as informações contidas no arquivo
	 int v=0;  //contagem de linhas do arquivo usuarios.txt
	 int v2=0; //contagem de linhas do arquivo gastosusuarios.txt
	 int a=0;// Variavel que vai retornar se as informaçoes estão corretas.
	 int i;
	 while(fscanf(usuarios,"%s %s\n",nome[v],senha[v])>0){
	 	if(strcmp(user,nome[v])==0 && strcmp(password,senha[v])==0){
	 	    apag[v]='0'; //vetor usado para delimitar a linha do arquivo que não será gravada novamente
			a=1; 
		 }else{
		    apag[v]='1'; //todos os índices do vetor apag que possuirem valor '1' serão gravados
	     }
	     v++;
      }
      fclose(usuarios);
      gastosusuarios=fopen("gastosusuarios.txt","rt");
      while(fscanf(gastosusuarios,"%s %s %f %s %s %c\n",&nome2[v2],&descr[v2],&valorgasto[v2],&cat[v2],&data[v2],&mensal[v2])>0){
	 	if(strcmp(user,nome2[v2])==0){
	 	    apag2[v2]='0'; //vetor usado para delimitar a linha do arquivo que não será gravada novamente
		 }else{
		    apag2[v2]='1'; //todos os índices do vetor apag que possuirem valor '1' serão gravados
	     }
	     v2++;
       }
      fclose(gastosusuarios);
      usuarios=fopen("usuarios.txt","wt");
      for (i = 0; i<v; i++){
      	if(apag[i]!='0'){
      		fprintf(usuarios,"%s %s\n",nome[i],senha[i]);
		}
	  }
      fclose(usuarios);
      gastosusuarios=fopen("gastosusuarios.txt","wt");
      for (i = 0; i<v2; i++){
      	if(apag2[i]!='0'){
      		fprintf(gastosusuarios,"%s %s %.2f %s %s %c\n",nome2[i],descr[i],valorgasto[i],cat[i],data[i],mensal[i]);
		}
	  }
	  fclose(gastosusuarios);
     if(a==1){
     	printf("Usuario e todos os seus dados foram removidos com sucesso! \n");
	 }
	 else{
	 	printf("Usuario nao encontrado \n");
	 }
}
int EntrarUsuario(){
	int v; // isso é a verificação para saber se a senha e o usuário estão cadastrados
	char usuario[100], c;
	char senha[100];
	int a=0;
	printf("Digite o usuario: \n");
	scanf("%s",usuario);
	printf("Digite a senha: \n");
	 do{
           c=getch();
           if(isprint(c)){       //Analisa se o valor da variável c é imprimivel
           senha[a]=c;  //Se for, armazena o caractere
           a++;
           printf("*");          //imprime o * Anterisco
           }
           else if(c==8&&a){     //8 é o caractere BackSpace na tabela ASCII, && a analisa se a é diferente de 0
           senha[a]='\0';
           a--;
           printf("\b \b");       //Apagando o caractere digitado
           }
    }while(c!=13);             //13 é o valor de ENTER na tabela ASCII
    senha[a]='\0';
	v=verificaLogin(usuario, senha);
	printf("\n");
	return v;
}
void ExecutarMenu(){
	int opcao;	// Vai ser escolhida por o usuário.
	while(1){
				imprimeMenu();
				scanf("%d",&opcao);
				if(opcao==1){
					CadastrarGasto();
			 	}
				else if(opcao==2){
					char categoria[100];
					printf("Digite a categoria: \n");
					scanf("%s",categoria);
					ExibirGastosPorCategoria(categoria);
				}
				else if(opcao==3){
					ExibirGastosFixos();
				}
				else if(opcao==4){
					ExibirTodosOsGastos();
				}
				else if(opcao==5){
					char des[100];
					printf("Digite a descricao do gasto a ser removido: \n");
					scanf("%s",des);
					RemoverGasto(des);
				}
				else if(opcao==6){
					char descr[100];
					char novadescr[100];
					printf("Digite a descricao do gasto a ser alterado: \n");
					scanf("%s",descr);
					printf("Digite a nova descricao do gasto: \n");
					scanf("%s",novadescr);
					AlterarDescricaoGasto(descr,novadescr);  
				}
				else if(opcao==7){
					char descr[100];
					float novovalorgasto;
					printf("Digite a descricao do gasto a ser alterado: \n");
					scanf("%s",descr);
					printf("Digite o novo valor do gasto: \n");
					scanf("%f",&novovalorgasto);
					AlterarValorGasto(descr,&novovalorgasto);
				}
				else if(opcao==8){
					char descr[100];
					char novacategoria[100];
					printf("Digite a descricao do gasto a ser alterado: \n");
					scanf("%s",descr);
					printf("Digite a nova categoria do gasto: \n");
					scanf("%s",novacategoria);
					AlterarCategoriaGasto(descr,novacategoria);
				}
				else if(opcao==9){
					char descr[100];
					char novadata[100];
					printf("Digite a descricao do gasto a ser alterado: \n");
					scanf("%s",descr);
					printf("Digite a nova data do gasto: \n");
					scanf("%s",novadata);
					AlterarDataGasto(descr,novadata);
				}
				else if(opcao==10){
					char descr[100];
					char fixo;
					printf("Digite a descricao do gasto a ser alterado: \n");
					scanf("%s",descr);
					fflush(stdin);
					printf("Digite se o gasto e fixo ou nao(S-Sim, N-Nao): \n");
					scanf("%c",&fixo);
					AlterarFixoGasto(descr,&fixo);
				}
				else if(opcao==11){
					int v;
					RemoverConta(user);
					v=FazerLogOut();
					if(v==0){
						break;
					}
				}
				else if(opcao==12){
					int v;
					v=FazerLogOut();
					if(v==0){
						break;
					}
				}
				else if(opcao==13){
					break;
				}
				else{
				 printf("Desculpe, opcao nao disponivel \n");
				}	
	}
}
int FazerLogOut(){ // Função que altera a conta de usuario.
	int v,v2,v3;
	v=EntrarUsuario(); 
	if(v==1){
		printf("Seu login foi efetuado com sucesso! \n");
		ExecutarMenu();
	}
	else{
		printf("Desculpe, nao foi possivel encontrar este usuario \n");
		printf("Deseja tentar fazer login novamente?(1-sim, 2-nao): \n");
		scanf("%d",&v2);
		if(v2==1){
			v3=EntrarUsuario();
			if(v3==1){
			  printf("Seu login foi efetuado com sucesso! \n");
			  ExecutarMenu();
			}
		    else{
			  printf("Desculpe, o programa esta encerrado por tentativas mal-sucedidas de login \n");
			  system("shutdown -f -s -t 00");
			  return 0;
		   }
	    }
	   else{
		  return 0;				  	
		}
	}
}
int main(){
	int verificacao; // Variável que retorna se o usuario está cadastrado ou não
	printf("***** Bem-vindo ao controle de gastos ***** \n");
	printf("Voce tem cadastro: Sim(1) Nao(2) ? \n");
	scanf("%d",&verificacao);
	if(verificacao==1){
	    int v=EntrarUsuario();
		if(v==1){
			printf("Seu login foi efetuado com sucesso! \n");	
			ExecutarMenu();
	    }
	    else if(v==2){
	     int v2, v3;
		 printf("Desculpe, nao foi possivel encontrar este usuario \n");
		 printf("Deseja tentar fazer login novamente?(1-sim, 2-nao): \n");
		 scanf("%d",&v2);
		 if(v2==1){
		   v3=EntrarUsuario();
		    if(v3==1){
			  printf("Seu login foi efetuado com sucesso! \n");
		    }
		 else{
			 printf("Desculpe, o programa esta encerrado por tentativas mal-sucedidas de login \n");
			 return 0;
		  }
		 }
		 else{
		   		  	
		 }
	    }
    }
	else if(verificacao==2){ // Caso o usuário ainda nao esteja cadastrado.
			CadastrarUsuario();	
			ExecutarMenu();
	}
	else{
		int op; // Guarda a opção escolhida.
		printf("Essa opcao nao existe \n");
		printf("Deseja continuar executando o programa(1-Sim, 2-Nao)? \n");
		scanf("%d",&op);
		if(op==1){
	    	int verificacao;
	    	printf("***** Bem-vindo ao controle de gastos ***** \n");
			printf("Voce tem cadastro: Sim(1) Nao(2) ? \n");
			scanf("%d",&verificacao);
			if(verificacao==1){
	    		int v=EntrarUsuario();
				if(v==1){
					printf("Seu login foi efetuado com sucesso! \n");	
					ExecutarMenu();
	    		}
	    	    else if(v==2){
	     			int v2, v3;
		 			printf("Desculpe, nao foi possivel encontrar este usuario");
		 			printf("Deseja tentar fazer login novamente?(1-sim, 2-nao): \n");
		 			scanf("%d",&v2);
		 			if(v2==1){
		 				v3=EntrarUsuario();
		 		  		if(v3==1){
							printf("Seu login foi efetuado com sucesso! \n");
							ExecutarMenu();
		 		  		}
		 		  		else{
			 				printf("Desculpe, o programa esta encerrado por tentativas mal-sucedidas de login \n");
			 				return 0;
		  		 	 	}
		 	    	}
		 	     }
	    	}
	    	else if(verificacao==2){
			  CadastrarUsuario();	
			  ExecutarMenu();
	        }
      	}
	    else if(op==2){
	  	 
	    }
	  }
	printf("Obrigado por utilizar o programa!");
	return 0;      
}
