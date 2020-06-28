#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

///--------------------

struct Contrato {
    int numero_contrato;
    float valor_total;
    float desconto;
    float valor_final;
    char forma_de_pagamento[40];
    char status[20];
    int codigo;
};

typedef struct Contrato contrato;

struct Festa {
    int codigo;
    int quant_convidados;
    char data[15];
    char dia_da_semana[15];
    char horario_inicio[6];
    char horario_final[6];
    char tema[80];
    int codigo_cliente;
    contrato contratoFesta;
};

typedef struct Festa festa;

struct Clientes{
    int codigo;
    char nome[80];
    char endereco[80];
    int telefone;
    char data_nascimento[15];
    festa festas[80];
    int quant_festas;
};
typedef struct Clientes cliente;

///-------------------
struct Funcionarios{
    int codigo;
    char nome[80];
    int telefone;
    char funcao[80];
    float salario;
    char tipo[11];
};
typedef struct Funcionarios funcionario;

///--------------------

struct Fornecedor {
    int codigo;
    char nome[80];
    int telefone;
    char produto_fornecido[40];
};

typedef struct Fornecedor fornecedor;


int gerarCodigoContrato(){
    contrato c;
    int encontrei = 0;
    FILE * arquivo;
    int codigo = 0;
    arquivo = fopen("cadastroContratos.txt", "r+b");
    while(encontrei == 0){
        codigo = rand() % 2000;
        fseek(arquivo, 0, SEEK_SET);
        fread(&c, sizeof(c), 1, arquivo);
        while(!feof(arquivo) && !encontrei){
            if(c.codigo == codigo){
                encontrei = 1;
            }
            fread(&c, sizeof(c), 1, arquivo);
        }
        if(encontrei){
            encontrei = 0;
        }
        else{
            fclose(arquivo);
            return codigo;
        }
    }
}

int verificarNumeroContratoValido(int numero) {
    contrato c;
    int encontrei = 0;
    FILE * arquivo;
    arquivo = fopen("cadastroContratos.txt", "r+b");
    fseek(arquivo, 0, SEEK_SET);
    fread(&c, sizeof(c), 1, arquivo);
    while(!feof(arquivo) && !encontrei){
        if(c.numero_contrato == numero){
            encontrei = 1;
        }
        fread(&c, sizeof(c), 1, arquivo);
    }
    if(encontrei){
        fclose(arquivo);
        return 0;
    }
    fclose(arquivo);
    return 1;
}


contrato funcaoCadastrarContrato(){
    FILE *arquivo;
    contrato c;
    int arquivoNaoCriado = 0;
    arquivo = fopen("cadastroContratos.txt", "r+b");
    if(arquivo == NULL){
        arquivo = fopen("cadastroContratos.txt", "w+b");
        if(arquivo == NULL){
            printf("Não foi possível criar o arquivo\n");
            arquivoNaoCriado = 1;
        }
    }
    if(arquivoNaoCriado){
        ///erro não deu para criar o arquivo
    }
    else{
        printf("Digite um número para este contrato: ");
        scanf("%d", &c.numero_contrato);

        if(!verificarNumeroContratoValido(c.numero_contrato)){
            return;
        }
        c.codigo = gerarCodigoContrato();

        fseek(arquivo,0, SEEK_END);

        fwrite(&c, sizeof(c), 1, arquivo);

        fflush(arquivo);

        fclose(arquivo);

        return c;
    }
}



int funcaoCadastrarFornecedor(){
    FILE *arquivo;
    fornecedor f;
    fornecedor aux;
    int arquivoNaoCriado = 0;
    int encontrado = 0;
    arquivo = fopen("cadastroFornecedores.txt", "r+b");
    if(arquivo == NULL){
        arquivo = fopen("cadastroFornecedores.txt", "w+b");
        if(arquivo == NULL){
            printf("Não foi possível criar o arquivo\n");
            arquivoNaoCriado = 1;
        }
    }
    if(arquivoNaoCriado){
        ///erro não deu para criar o arquivo
    }
    else{
        printf("Digite um código para este fornecedor: ");
        scanf("%d", &aux.codigo);

        printf("Digite um nome para este fornecedor: ");
        fflush(stdin);
        gets(aux.nome);


        printf("Digite um telefone para este fornecedor: ");
        scanf("%d", &aux.telefone);

        printf("Digite um produto ofertado por este fornecedor : ");
        fflush(stdin);
        gets(aux.produto_fornecido);

        fseek(arquivo,0,SEEK_SET);
        fread(&f, sizeof(f), 1, arquivo);
        ///validando código para não existirem códigos duplicados
        while(!feof(arquivo) && !encontrado){
            if(aux.codigo == f.codigo){
                encontrado = 1;
            }
            fread(&f, sizeof(f), 1, arquivo);
        }
        if(encontrado){
            fclose(arquivo);
            return 0;
        }
        else{
            fseek(arquivo,0, SEEK_END);
            fwrite(&aux, sizeof(aux), 1, arquivo);
            fflush(arquivo);
            fclose(arquivo);
            return 1;
        }
    }
}

void imprimiArquivoFornecedores(char* nome){
    FILE *arquivo;
    fornecedor f;
    int encontrado = 0;
    arquivo = fopen("cadastroFornecedores.txt", "r+b");
    if(arquivo == NULL){
        printf("Erro na leitura do arquivo!!! \n");
    }
    else{
        fseek(arquivo,0, SEEK_SET);
        fread(&f, sizeof(f), 1, arquivo);
        while(!feof(arquivo) && !encontrado){
            if(strcmp(f.nome, nome) == 0){
                encontrado = 1;
                printf("código : %d\n", f.codigo);
                printf("nome : %s\n", f.nome);
                printf("telefone : %d\n", f.telefone);
                printf("produto fornecido : %s\n", f.produto_fornecido);
            }
            else{
                fread(&f, sizeof(f), 1, arquivo);
            }
        }
    }
    fclose(arquivo);
}


int funcaoCadastrarFuncionarios(){
    FILE *arquivo;
    funcionario f;
    funcionario aux;
    int arquivoNaoCriado = 0;
    int encontrado = 0;
    arquivo = fopen("cadastroFuncionarios.txt", "r+b");
    if(arquivo == NULL){
        arquivo = fopen("cadastroFuncionarios.txt", "w+b");
        if(arquivo == NULL){
            printf("Não foi possível criar o arquivo\n");
            arquivoNaoCriado = 1;
        }
    }
    if(arquivoNaoCriado){
        ///erro não deu para criar o arquivo
    }
    else{
        printf("Digite um código para este funcionário: ");
        scanf("%d", &aux.codigo);

        printf("Digite um nome para este funcionário: ");
        fflush(stdin);
        gets(aux.nome);

        printf("Digite um telefone para este funcionário: ");
        scanf("%d", &aux.telefone);

        printf("Digite a função deste funcionário : ");
        fflush(stdin);
        gets(aux.funcao);

        printf("Digite o salário deste funcionário : ");
        scanf("%f", &aux.salario);

        printf("Digite o tipo de contratação do funcionário temporário ou fixo : ");
        fflush(stdin);
        gets(aux.tipo);

        if( strcmp(aux.tipo, "temporário") != 0 && strcmp(aux.tipo, "fixo") != 0 ) {
            return 0;
        }

        fseek(arquivo,0,SEEK_SET);
        fread(&f, sizeof(f), 1, arquivo);
        ///validando código para não existirem códigos duplicados
        while(!feof(arquivo) && !encontrado){
            if(aux.codigo == f.codigo){
                encontrado = 1;
            }
            fread(&f, sizeof(f), 1, arquivo);
        }
        if(encontrado){
            fclose(arquivo);
            return 0;
        }
        else{
            fseek(arquivo,0, SEEK_END);
            fwrite(&aux, sizeof(aux), 1, arquivo);
            fflush(arquivo);
            fclose(arquivo);
            return 1;
        }
    }
}

void imprimiArquivoFuncionarios(char* nome){
    FILE *arquivo;
    funcionario f;
    int encontrado = 0;
    arquivo = fopen("cadastroFuncionarios.txt", "r+b");
    if(arquivo == NULL){
        printf("Erro na leitura do arquivo!!! \n");
    }
    else{
        fseek(arquivo,0, SEEK_SET);
        fread(&f, sizeof(f), 1, arquivo);
        while(!feof(arquivo) && !encontrado){
            if(strcmp(f.nome, nome) == 0){
                encontrado = 1;
                printf("código : %d\n", f.codigo);
                printf("nome : %s\n", f.nome);
                printf("telefone : %d\n", f.telefone);
                printf("função : %s\n", f.funcao);
                printf("salário : %f\n", f.salario);
                printf("tipo de contratação : %s\n", f.tipo);
            }
            else{
                fread(&f, sizeof(f), 1, arquivo);
            }
        }
    }
    fclose(arquivo);
}

int funcaoCadastrarCliente(){
    FILE *arquivo;
    cliente c;
    cliente aux;
    int arquivoNaoCriado = 0;
    int encontrado = 0;
    arquivo = fopen("cadastroClientes.txt", "r+b");
    if(arquivo == NULL){
        arquivo = fopen("cadastroClientes.txt", "w+b");
        if(arquivo == NULL){
            printf("Não foi possível criar o arquivo\n");
            arquivoNaoCriado = 1;
        }
    }
    if(arquivoNaoCriado){
        ///erro não deu para criar o arquivo
    }
    else{
        printf("Digite um código para este cliente: ");
        scanf("%d", &aux.codigo);
        printf("Digite um nome para este cliente: ");
        fflush(stdin);
        gets(aux.nome);
        printf("Digite um endereco para este cliente: ");
        fflush(stdin);
        gets(aux.endereco);
        printf("Digite um telefone para este Cliente: ");
        scanf("%d", &aux.telefone);

        printf("Digite uma data no formato dd/mm/aaaa : ");
        fflush(stdin);
        gets(aux.data_nascimento);
        if( !funcaoValidarData(aux.data_nascimento) ) {
            return 0;
        }
        aux.quant_festas = 0;

        ///verificando se tem algum código repetido
        fseek(arquivo,0,SEEK_SET);
        fread(&c, sizeof(c), 1, arquivo);
        while(!feof(arquivo) && !encontrado){
            if(aux.codigo == c.codigo){
                encontrado = 1;
            }
            fread(&c, sizeof(c), 1, arquivo);
        }
        if(encontrado){
            fclose(arquivo);
            return 0;
        }
        fseek(arquivo,0, SEEK_END);
        fwrite(&aux, sizeof(aux), 1, arquivo);
        fflush(arquivo);
        fclose(arquivo);
        return 1;
    }
}


void imprimiArquivoClientes(char* nome){
    FILE *arquivo;
    cliente c;
    int encontrado = 0;
    arquivo = fopen("cadastroClientes.txt", "r+b");
    if(arquivo == NULL){
        printf("Erro na leitura do arquivo!!! \n");
    }
    else{
        fseek(arquivo,0, SEEK_SET);
        fread(&c, sizeof(c), 1, arquivo);
        while(!feof(arquivo) && !encontrado){
            if(strcmp(c.nome, nome) == 0){
                encontrado = 1;
                printf("código : %d\n", c.codigo);
                printf("nome : %s\n", c.nome);
                printf("endereço : %s\n", c.endereco);
                printf("telefone : %d\n", c.telefone);
                printf("data de nascimento : %s\n", c.data_nascimento);
            }
            else{
                fread(&c, sizeof(c), 1, arquivo);
            }
        }
    }
    fclose(arquivo);
}



int funcaoValidarData(char * saida){
    int tamanho = strlen(saida);
    int entradaEquivocada = 0;
    int quantBarras = 0;
    int dia = 0;
    int mes = 0;
    int ano = 0;

    if(tamanho != 10){
        printf("deu errado %d \n", tamanho);
        return 0;
    }
    else{
        char simbolo = '`';
        int i = 0;

        while(simbolo != '\0'){
            simbolo = saida[i];
            if( (simbolo >= '0' && simbolo <= '9') || simbolo == '/' ){
            }
            else{
                if(simbolo == NULL){

                }
                else{
                    entradaEquivocada = 1;
                }
            }
            if(simbolo == '/'){
                quantBarras++;
            }
            i++;
        }
        if(!entradaEquivocada  && quantBarras == 2 && saida[2] == '/' && saida[5] == '/'){


            dia = (  ( (saida[0] - '0') * 10 ) + ( (saida[1] - '0') * 1 ) );
            mes = (  ( (saida[3] - '0') * 10 ) + ( (saida[4] - '0') * 1 ) );
            ano = (  ( (saida[6] - '0') * 1000 ) + ( (saida[7] - '0') * 100 ) +  ( (saida[8] - '0') * 10 ) + ( (saida[9] - '0') * 1 ) );

            printf("\n dia = %i \n mes = %i \n ano = %i\n", dia, mes, ano );
            if( ano > 2020 || ano < 1999 || dia > 31 || dia < 1 || mes > 12 || mes < 1)
                return 0;
            return 1;
        }
        return 0;

    }
}

int funcaoDataPosterior (char *dataReferencia, char *dataComparavel) {
    int diaReferencia = (  ( (dataReferencia[0] - '0') * 10 ) + ( (dataReferencia[1] - '0') * 1 ) );
    int mesReferencia = (  ( (dataReferencia[3] - '0') * 10 ) + ( (dataReferencia[4] - '0') * 1 ) );
    int anoReferencia = (  ( (dataReferencia[6] - '0') * 1000 ) + ( (dataReferencia[7] - '0') * 100 ) +  ( (dataReferencia[8] - '0') * 10 ) + ( (dataReferencia[9] - '0') * 1 ) );

    int diaComparavel = (  ( (dataComparavel[0] - '0') * 10 ) + ( (dataComparavel[1] - '0') * 1 ) );
    int mesComparavel = (  ( (dataComparavel[3] - '0') * 10 ) + ( (dataComparavel[4] - '0') * 1 ) );
    int anoComparavel = (  ( (dataComparavel[6] - '0') * 1000 ) + ( (dataComparavel[7] - '0') * 100 ) +  ( (dataComparavel[8] - '0') * 10 ) + ( (dataComparavel[9] - '0') * 1 ) );

    int quantDias1 = ( (anoReferencia - 1) * 366) + ( (mesReferencia - 1) * 31) + (diaReferencia);
    int quantDias2 = ( (anoComparavel - 1) * 366) + ( (mesComparavel - 1) * 31) + (diaComparavel);//eu considerei que todos os meses e anos tem a mesma quantidade de dias pois isto mantém a proporção e a soma dá certo;

    if(quantDias2 > quantDias1) {
        return 1;
    }
    return 0;
}

int funcaoDataIgual (char *dataReferencia, char *dataComparavel) {
    int diaReferencia = (  ( (dataReferencia[0] - '0') * 10 ) + ( (dataReferencia[1] - '0') * 1 ) );
    int mesReferencia = (  ( (dataReferencia[3] - '0') * 10 ) + ( (dataReferencia[4] - '0') * 1 ) );
    int anoReferencia = (  ( (dataReferencia[6] - '0') * 1000 ) + ( (dataReferencia[7] - '0') * 100 ) +  ( (dataReferencia[8] - '0') * 10 ) + ( (dataReferencia[9] - '0') * 1 ) );

    int diaComparavel = (  ( (dataComparavel[0] - '0') * 10 ) + ( (dataComparavel[1] - '0') * 1 ) );
    int mesComparavel = (  ( (dataComparavel[3] - '0') * 10 ) + ( (dataComparavel[4] - '0') * 1 ) );
    int anoComparavel = (  ( (dataComparavel[6] - '0') * 1000 ) + ( (dataComparavel[7] - '0') * 100 ) +  ( (dataComparavel[8] - '0') * 10 ) + ( (dataComparavel[9] - '0') * 1 ) );

    int quantDias1 = ( (anoReferencia - 1) * 366) + ( (mesReferencia - 1) * 31) + (diaReferencia);
    int quantDias2 = ( (anoComparavel - 1) * 366) + ( (mesComparavel - 1) * 31) + (diaComparavel);//eu considerei que todos os meses e anos tem a mesma quantidade de dias pois isto mantém a proporção e a soma dá certo;

    if(quantDias2 == quantDias1) {
        return 1;
    }
    return 0;
}

    char* decideDia(int j) {
		switch (j) {
          case 0:
            return "Sábado";
          case 1:
            return "Domingo";
          case 2:
            return "Segunda";
          case 3:
            return "Terça";
          case 4:
            return "Quarta";
          case 5:
            return "Quinta";
          case 6:
            return "Sexta";
          default:
            return "Erro ao tentar retornar o dia da semana";
		}
	}

	char* diaDaSemana(char *saida) {
	    int dia = (  ( (saida[0] - '0') * 10 ) + ( (saida[1] - '0') * 1 ) );
        int mes = (  ( (saida[3] - '0') * 10 ) + ( (saida[4] - '0') * 1 ) );
        int ano = (  ( (saida[6] - '0') * 1000 ) + ( (saida[7] - '0') * 100 ) +  ( (saida[8] - '0') * 10 ) + ( (saida[9] - '0') * 1 ) );

		int a = ((12 - mes) / 10);
		int b = ano - a;
		int c = mes + (12 * a);
		int d = b / 100;
		int e = d / 4;
		int f = 2 - d + e;
		int g = (int) (365.25 * b);
		int h = (int) (30.6001 * (c + 1));
		int i = (int) ((f + g) + (h + dia) + 5);
		int j = (int) (i % 7);
		return decideDia(j);
	}

    int funcaoHorarioIgual(char *horarioInicio, char *horarioInicioComparavel){
        int horas = ( ( horarioInicio[0] - '0' ) * 10 ) +  ( ( horarioInicio[1] - '0' ) * 1 );
        int minutos = ( ( horarioInicio[3] - '0' ) * 10 ) +  ( ( horarioInicio[4] - '0' ) * 1 );
        int horasFinal = 0;

        if(horas > 20) {
            for(int i = 1; i <= 4; i++){
                horas++;
                if(horas > 24){
                    horas = 1;
                }
            }
        }
        else{
            horasFinal = horas + 4;
        }

        int horasComparavel = ( ( horarioInicioComparavel[0] - '0' ) * 10 ) +  ( ( horarioInicioComparavel[1] - '0' ) * 1 );
        int minutosComparavel = ( ( horarioInicioComparavel[3] - '0' ) * 10 ) +  ( ( horarioInicioComparavel[4] - '0' ) * 1 );
        int horasFinalComparavel = 0;

        if(horasComparavel > 20) {
            for(int i = 1; i <= 4; i++){
                horasComparavel++;
                if(horasComparavel > 24){
                    horasComparavel = 1;
                }
            }
        }
        else{
            horasFinalComparavel = horasComparavel + 4;
        }
        //printf("\nDebug horasFinalComparavel %d \nhorasFinal %d\nhorasComparavel %d\nhoras %d\n", horasFinalComparavel, horasFinal, horasComparavel, horas);

        if( ( ( ( (horas * 60) + minutos ) ==  ( (horasComparavel * 60) + minutosComparavel ) ) &&
            (  (horasFinal * 60) == (horasFinalComparavel * 60) ) ) ||
             (  (horas * 60 + minutos) > (horasComparavel * 60 + minutosComparavel)  && ( ( (horasFinal * 60 + minutos) - (horasFinalComparavel * 60 + minutosComparavel ) ) <= 240 ) ) ||
             (  (horasComparavel * 60 + minutosComparavel) > (horas * 60 + minutos)  && ( (  (horasFinalComparavel * 60 + minutosComparavel ) - (horasFinal * 60 + minutos) ) <= 240 ) ) ){
            return 1;
        }
        return 0;
    }

	int DatasEHorariosCoincidem(char *dataFesta, char *horarioInicio, char *dataComparavel, char *horarioInicioComparavel) {
        if(funcaoDataIgual(dataFesta, dataComparavel) && funcaoHorarioIgual(horarioInicio, horarioInicioComparavel)){
            return 1;
        }
        return 0;
	}



int posicaoCliente = 0;
int posicaoContrato = 0;
int codigo = 0;



int gerarCodigoFesta(){
    festa f;
    int encontrei = 0;
    FILE * arquivo;
    arquivo = fopen("cadastroFestas.txt", "r+b");
    while(encontrei == 0){
        codigo = rand() % 2000;
        fseek(arquivo, 0, SEEK_SET);
        fread(&f, sizeof(f), 1, arquivo);
        while(!feof(arquivo) && !encontrei){
            if(f.codigo == codigo){
                encontrei = 1;
            }
            fread(&f, sizeof(f), 1, arquivo);
        }
        if(encontrei){
            encontrei = 0;
        }
        else{
            fclose(arquivo);
            return codigo;
        }
    }
}

int funcaoHorarioValido(char *horarioInicio) {
    int length = 0;
    while(horarioInicio[length] != '\0'){
        length++;
    }
    if( horarioInicio[2] != ':' || length != 5 ){
        return 0;
    }
    int horas = ( ( horarioInicio[0] - '0' ) * 10 ) +  ( ( horarioInicio[1] - '0' ) * 1 );
    int minutos = ( ( horarioInicio[3] - '0' ) * 10 ) +  ( ( horarioInicio[4] - '0' ) * 1 );

    if(horas > 24 || horas < 1 || minutos > 59 || minutos < 0){
        return 0;
    }
    return 1;
}

int funcaoVerificaExistenciaDoCliente(char* nome){
    cliente c;
    posicaoCliente = 0;
    int encontrado = 0;
    FILE * arquivo;
    arquivo = fopen("cadastroClientes.txt", "r+b");
    if(arquivo == NULL){
        printf("ERRO NENHUM CLIENTE CADASTRADO !!! ");
    }
    else{
        fseek(arquivo, 0, SEEK_SET);
        fread(&c, sizeof(c), 1, arquivo);
        while(!feof(arquivo) && !encontrado){
            if(strcmp(c.nome, nome) == 0){
                encontrado = 1;
            }
            else{
                posicaoCliente++;
            }
            fread(&c, sizeof(c), 1, arquivo);
        }
        fclose(arquivo);
        return encontrado;
    }
}



int funcaoCadastrarFesta(){

    int problema = 0;
    cliente c;
    festa f;
    festa aux;
    int codigo = 0;
    char nome[80];
    int encontrado = 0;

    //Dados da festa

    printf("Digite a quantidade de convidados : ");
    scanf("%d", &f.quant_convidados);

    printf("Digite a data da festa no modelo dd/mm/aaaa : ");
    fflush(stdin);
    gets(f.data);

    if(!funcaoValidarData(f.data)){
        return 0;
    }



    strcpy(f.dia_da_semana, diaDaSemana(f.data));


    printf("Digite o tema da festa : ");
    fflush(stdin);
    gets(&f.tema);

    printf("Digite um horário para a festa no modelo hh:mm : ");
    fflush(stdin);
    gets(&f.horario_inicio);

    if(!funcaoHorarioValido(f.horario_inicio)){
        return 0;
    }
    int horas = ( ( f.horario_inicio[0] - '0' ) * 10 ) +  ( ( f.horario_inicio[1] - '0' ) * 1 );
    int minutos = ( ( f.horario_inicio[3] - '0' ) * 10 ) +  ( ( f.horario_inicio[4] - '0' ) * 1 );
    if(horas > 20) {
        for(int i = 1; i <= 4; i++){
            horas++;
            if(horas > 24){
                horas = 1;
            }
        }
    }
    else {
        horas += 4;
    }
    fflush(stdin);
    char horasFinal[4];

    horasFinal[0] = (horas / 10) + '0';
    horasFinal[1] = (horas % 10) + '0';
    horasFinal[2] = ':';
    horasFinal[3] = (minutos / 10) + '0';
    horasFinal[4] = (minutos % 10) + '0';

    printf("\ndebug horasFinal : %s\n", horasFinal);

    strcpy(f.horario_final, horasFinal);




    if(strcmp(f.dia_da_semana, "Sábado") == 0 && !funcaoHorarioIgual(f.horario_inicio, "12:00") && !funcaoHorarioIgual(f.horario_inicio, "18:00") ) {
        return 0;
    }

    f.contratoFesta = funcaoCadastrarContrato();

    printf("Digite o nome do cliente que deseja fazer a festa : ");
    fflush(stdin);
    gets(&nome);


    if(!funcaoVerificaExistenciaDoCliente(nome)) {
        return 0;
    }

    FILE * arquivoFesta;
    arquivoFesta = fopen("cadastroFestas.txt", "r+b");
    if(arquivoFesta == NULL){
       arquivoFesta = fopen("cadastroFestas.txt", "w+b");
       if(arquivoFesta == NULL){
          problema = 1;
       }
    }
    if(!problema){
        FILE * arquivoClientes;
        codigo = gerarCodigoFesta();
       ///abrindo arquivos para leitura e escrita
        arquivoClientes = fopen("cadastroClientes.txt", "r+b");

        ///posicionando no local desejado dentro do arquivo
        fseek(arquivoClientes, sizeof(c)*posicaoCliente, SEEK_SET);

        fseek(arquivoFesta, 0, SEEK_SET);

        fread(&aux, sizeof(aux), 1, arquivoFesta);

        while(!feof(arquivoFesta) && !encontrado){
            if(DatasEHorariosCoincidem(f.data, f.horario_inicio, aux.data, aux.horario_inicio)){
                encontrado = 1;
            }
            fread(&aux, sizeof(aux), 1, arquivoFesta);
        }
        if(encontrado) {
            return 0;
        }

        fseek(arquivoFesta, 0, SEEK_END);

        fread(&c, sizeof(c), 1, arquivoClientes);
        if(c.quant_festas <= 80){
            f.codigo = codigo;

            f.codigo_cliente = c.codigo;

            fseek(arquivoClientes, sizeof(c)*posicaoCliente, SEEK_SET);

            c.festas[c.quant_festas] = f;

            c.quant_festas++;



            fwrite(&c, sizeof(c), 1, arquivoClientes);

            fwrite(&f, sizeof(f), 1, arquivoFesta);

            fflush(arquivoClientes);
            fflush(arquivoFesta);

            fclose(arquivoClientes);
            fclose(arquivoFesta);

            return 1;
        }
    }
    return 0;
}


int funcaoMostrarFestasDoCliente(char *nome) {
    if(!funcaoVerificaExistenciaDoCliente(nome)) {
        return 0;
    }

    cliente c;
    festa festaEspecifica;

    FILE * arquivoClientes;

    arquivoClientes = fopen("cadastroClientes.txt", "r+b");

    fseek(arquivoClientes, sizeof(c)*posicaoCliente, SEEK_SET);
    fread(&c, sizeof(c), 1, arquivoClientes);

    for(int i = 0; i < c.quant_festas; i++) {
        festaEspecifica = c.festas[i];
        printf("\n\n------- Festa %d ----------\n\n", i+1);
            printf("\n Código : %d\n", festaEspecifica.codigo);
            printf("\n Data : %s\n", festaEspecifica.data);
            printf("\n Horário início : %s\n", festaEspecifica.horario_inicio);
            printf("\n Horário final : %s\n", festaEspecifica.horario_final);
            printf("\n Quantidade de convidados : %d\n", festaEspecifica.quant_convidados);
            printf("\n Tema : %s\n", festaEspecifica.tema);
            printf("\n Dia da semana : %s\n", festaEspecifica.dia_da_semana);
            printf("\n Número contrato : %d\n", festaEspecifica.contratoFesta.numero_contrato);
        printf("\n--------------------------------\n");
    }
    fclose(arquivoClientes);
    return 1;
}


int funcaoVerificaExistenciaDoContrato(int numero_contrato){
    festa f;
    posicaoContrato = 0;
    int encontrado = 0;
    FILE *arquivo;
    arquivo = fopen("cadastroFestas.txt", "r+b");
    if(arquivo == NULL){
        printf("ERRO NENHUM CLIENTE CADASTRADO !!! ");
    }
    else{
        fseek(arquivo, 0, SEEK_SET);
        fread(&f, sizeof(f), 1, arquivo);
        while(!feof(arquivo) && !encontrado){
            if(f.contratoFesta.numero_contrato == numero_contrato){
                encontrado = 1;
            }
            else{
                posicaoContrato++;
            }
            fread(&f, sizeof(f), 1, arquivo);
        }
        fclose(arquivo);
        return encontrado;
    }
}


float funcaoValorTotal(char *dia_da_semana, int quant_convidados){
    switch(quant_convidados){
        case 30 :
            if(strcmp(dia_da_semana, "Domingo") == 0 || strcmp(dia_da_semana, "Sábado") == 0 || strcmp(dia_da_semana, "Sexta") == 0){
                return 2099;
            }
            return 1899;
        case 50 :
            if(strcmp(dia_da_semana, "Domingo") == 0 || strcmp(dia_da_semana, "Sábado") == 0 || strcmp(dia_da_semana, "Sexta") == 0){
                return 2299;
            }
            return 2199;
        case 80 :
            if(strcmp(dia_da_semana, "Domingo") == 0 || strcmp(dia_da_semana, "Sábado") == 0 || strcmp(dia_da_semana, "Sexta") == 0){
                return 3499;
            }
            return 3199;
        case 100 :
            if(strcmp(dia_da_semana, "Domingo") == 0 || strcmp(dia_da_semana, "Sábado") == 0 || strcmp(dia_da_semana, "Sexta")){
                return 3999;
            }
            return 3799;
        default :
            printf("Ih rapaz aglomeração hein");
            return 0;
    }
}


int funcaoTotalAserPagoPelaFesta(int numero_contrato){
    if(!funcaoVerificaExistenciaDoContrato(numero_contrato)){
        return 0;
    }
    festa f;

    FILE *arquivo;

    arquivo = fopen("cadastroFestas.txt", "r+b");

    fseek(arquivo, sizeof(f)*posicaoContrato, SEEK_SET);

    fread(&f, sizeof(f), 1, arquivo);

    strcpy(f.contratoFesta.status, "a pagar");

    int opcao_pagamento = 0;
    float valorTotal = funcaoValorTotal(f.dia_da_semana, f.quant_convidados);
    f.contratoFesta.valor_total = valorTotal;
    do {
        printf("\nFormas de pagamento -> \n\n 1 - A vista\n2- Duas Vezes\n3 - Três vezes\n4 - Quatro ou mais vezes\n");
        printf("Digite uma forma de pagamento : ");
        scanf("%d", &opcao_pagamento);
        switch(opcao_pagamento){
            case 1 :
                strcpy(f.contratoFesta.forma_de_pagamento, "A vista");
                f.contratoFesta.desconto = 10;
                f.contratoFesta.valor_final = valorTotal - (valorTotal * 10 / 100);
                break;
            case 2 :
                strcpy(f.contratoFesta.forma_de_pagamento, "Duas Vezes");
                f.contratoFesta.desconto = 5;
                f.contratoFesta.valor_final = valorTotal - (valorTotal * 5 / 100);
                break;
            case 3 :
                strcpy(f.contratoFesta.forma_de_pagamento, "Três vezes");
                f.contratoFesta.desconto = 2;
                f.contratoFesta.valor_final = valorTotal - (valorTotal * 2 / 100);
                break;
            case 4 :
                strcpy(f.contratoFesta.forma_de_pagamento, "Quatro ou mais vezes");
                f.contratoFesta.desconto = 0;
                f.contratoFesta.valor_final = valorTotal;
                break;
            default :
                printf("Error opção de pagamento inválida");
        }
    } while(opcao_pagamento > 4 && opcao_pagamento < 1);




    fseek(arquivo, sizeof(f)*posicaoContrato, SEEK_SET);

    fwrite(&f, sizeof(f), 1, arquivo);

    fflush(arquivo);

    fclose(arquivo);

    return 1;
}

int atualizaStatusContrato(int numero_contrato, char *status){
    if(!funcaoVerificaExistenciaDoContrato(numero_contrato) || ( strcmp(status, "pago") != 0 && strcmp(status, "cancelado") != 0 ) ){
        return 0;
    }

    festa f;

    FILE *arquivo;

    arquivo = fopen("cadastroFestas.txt", "r+b");

    fseek(arquivo, sizeof(f)*posicaoContrato, SEEK_SET);

    fread(&f, sizeof(f), 1, arquivo);

    strcpy(f.contratoFesta.status, status);



    fseek(arquivo, sizeof(f)*posicaoContrato, SEEK_SET);

    fwrite(&f, sizeof(f), 1, arquivo);

    fflush(arquivo);

    fclose(arquivo);
    return 1;
}


int funcaoRelatorioFestasApartirDe(char *dataReferencia){
    if(!funcaoValidarData(dataReferencia)){
        return 0;
    }
    festa f;
    FILE *arquivo;
    arquivo = fopen("cadastroFestas.txt", "r+b");
    if(arquivo == NULL){
        printf("ERRO NENHUM CLIENTE CADASTRADO !!! ");
    }
    else{
        fseek(arquivo, 0, SEEK_SET);
        fread(&f, sizeof(f), 1, arquivo);
        while(!feof(arquivo)){
            if(funcaoDataPosterior(dataReferencia, f.data)){
                printf("\n\n-------------------------\n\n");
                printf("\n Código : %d\n", f.codigo);
                printf("\n Data : %s\n", f.data);
                printf("\n Horário início : %s\n", f.horario_inicio);
                printf("\n Horário final : %s\n", f.horario_final);
                printf("\n Quantidade de convidados : %d\n", f.quant_convidados);
                printf("\n Tema : %s\n", f.tema);
                printf("\n Dia da semana : %s\n", f.dia_da_semana);

                printf("\n\n -------- Contrato ------\n\n");
                printf("\n Número contrato : %d\n", f.contratoFesta.numero_contrato);
                printf("\n Forma de pagamento : %s\n", f.contratoFesta.forma_de_pagamento);
                printf("\n Desconto : %f\n", f.contratoFesta.desconto);
                printf("\n Status : %s\n", f.contratoFesta.status);
                printf("\n\n\n----------------------------\n Valor total : %f\n", f.contratoFesta.valor_total);
                printf("\n Valor final : %f\n", f.contratoFesta.valor_final);
                printf("\n--------------------------------\n");
            }
            fread(&f, sizeof(f), 1, arquivo);
        }
        fclose(arquivo);
        return 1;
    }
}

int main()
{
    /*if(funcaoCadastrarFesta()){
        printf("Deu para cadastrar !!! ");
    }
    else {
        printf("Erro!!!");
    }

    char nomeCliente[80];

    printf("Digite um nome : ");
    fflush(stdin);
    gets(&nomeCliente);
    fflush(stdin);

    if(funcaoMostrarFestasDoCliente(nomeCliente)){
        printf("\n\nCliente encontrado!!\n");
    }
    else{
        printf("\n\nCliente NÃO encontrado!!\n");
    }
    printf("\n\n------------------\n\n");

    int numero_contrato = 0;
    printf("Digite o número do contrato da festa para ser calculado o total a ser pago : ");
    scanf("%d", &numero_contrato);
    funcaoTotalAserPagoPelaFesta(numero_contrato);*/

    funcaoTotalAserPagoPelaFesta(2);

    /*if(atualizaStatusContrato(2, "pago")){
        printf("\nStatus atualizado com sucesso !!!\n");
    }
    else {
        printf("Status ou número do contrato inválidos !!! \n");
    }*/

    funcaoRelatorioFestasApartirDe("21/07/2004");

    /*
    if(funcaoCadastrarFesta()){
        printf("Deu para cadastrar !!! ");
    }
    else {
        printf("Erro!!!");
    }

    char nomeFor[80];
    int forCadastrado = 0;
    do {
        forCadastrado = funcaoCadastrarFornecedor();
        if(!forCadastrado){
            printf("\nErro!!!\n");
        }
    } while(!forCadastrado);

    printf("\n\nDigite um nome de fornecedor : ");
    scanf("%s", &nomeFor);

    imprimiArquivoFornecedores(nomeFor);

    char nomeFunc[80];
    int funcCadastrado = 0;
    do {
        funcCadastrado = funcaoCadastrarFuncionarios();
        if(!funcCadastrado){
            printf("\nErro!!!\n");
        }
    } while(!funcCadastrado);

    printf("\n\nDigite um nome de funcionário : ");
    scanf("%s", &nomeFunc);

    imprimiArquivoFuncionarios(nomeFunc);

    char nome[80];
    int cadastrado = 0;
    do{
        cadastrado = funcaoCadastrarCliente();
        if(!cadastrado) {
            printf("\nErro no código!!!\n");
        }
    }while(!cadastrado);

    printf("Digite um nome : ");
    scanf("%s", &nome);

    imprimiArquivoClientes(nome);

    char data[80];
    char dataComparavel[80];
    char horas[80];
    char horasComparavel[80];

    printf("Digite uma data : ");
    scanf("%s", &data);

    printf("Digite uma data 1 : ");
    scanf("%s", &dataComparavel);

    printf("Digite um horario : ");
    scanf("%s", &horas);

    printf("Digite um horario : ");
    scanf("%s", &horasComparavel);

    if( DatasEHorariosCoincidem(data, horas, dataComparavel, horasComparavel) ) {
        printf("\nDatas e horarios coincidem\n");
    }
    else {
        printf("\nDatas e horarios NAO coincidem\n");
    }

    if(funcaoValidarData(data)) {
        printf("\ndia da semana : %s \n", diaDaSemana(data));
        if(funcaoDataPosterior(data, dataComparavel)){
            printf("\nData maior\n");
        }
        else {
            printf("\nData menor\n");
        }
    }
    else {
        printf("\nInválida\n");
    }*/
    return 0;
}
