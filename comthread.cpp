#include<stdio.h>
#include<thread>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<iostream>
#define Max 1000000

using namespace std;

void Quick(int vetor[Max], int inicio, int fim){
   
   int pivo, aux, i, j, meio;
   
   i = inicio;
   j = fim;
   
   meio = (int) ((i + j) / 2);
   pivo = vetor[meio];
   
   do{
      while (vetor[i] < pivo) i = i + 1;
      while (vetor[j] > pivo) j = j - 1;
      
      if(i <= j){
         aux = vetor[i];
         vetor[i] = vetor[j];
         vetor[j] = aux;
         i = i + 1;
         j = j - 1;
      }
   }while(j > i);
   
   if(inicio < j) Quick(vetor, inicio, j);
   if(i < fim) Quick(vetor, i, fim);   

}


int main()
{
	int *vet0;
	int *vet1;
	int *vet2;
	int *vet3;
	int *vet4;
	int *vet5;

    //criando os vetores para armazenarem os valores do arquivo
	vet0 = new int [Max];
	vet1 = new int [Max];
	vet2 = new int [Max];
	vet3 = new int [Max];
	vet4 = new int [Max];
	vet5 = new int [Max];

	//Abrindo os arquivos para serem lidos
	FILE *file0;
	FILE *file1;
	FILE *file2;
	FILE *file3;
	FILE *file4;
	FILE *file5;
	file0=fopen("1000000(0).txt","r");
	file1=fopen("1000000(1).txt","r");
	file2=fopen("1000000(2).txt","r");
	file3=fopen("1000000(3).txt","r");
	file4=fopen("1000000(4).txt","r");
	file5=fopen("1000000(5).txt","r");

	//abrindo arquivos para serem escritos
	FILE *fil0;
	FILE *fil1;
	FILE *fil2;
	FILE *fil3;
	FILE *fil4;
	FILE *fil5;
	fil0=fopen("1000000(0)2.txt","wa");
	fil1=fopen("1000000(1)2.txt","wa");
	fil2=fopen("1000000(2)2.txt","a");
	fil3=fopen("1000000(3)2.txt","a");
	fil4=fopen("1000000(4)2.txt","a");
	fil5=fopen("1000000(5)2.txt","a");

	int i=0,j=0,k=0,l=0,m=0,o=0,n;

    //armazenando no vetor os valores do arquivo
	if(file0 == NULL)
	{
		cout<<"Erro ao abrir o arquivo"<<endl;
	}
	while(!feof(file0))
    {
       fscanf(file0,"%d\n",&n);
       vet0[i] = n;
       i++;
    }

    if(file1 == NULL)
	{
		cout<<"Erro ao abrir o arquivo"<<endl;
	}
	while(!feof(file1))
    {
       fscanf(file1,"%d\n",&n);
       vet1[j] = n;
       j++;
    }

    if(file2 == NULL)
	{
		cout<<"Erro ao abrir o arquivo"<<endl;
	}
	while(!feof(file2))
    {
       fscanf(file2,"%d\n",&n);
       vet2[k] = n;
       k++;
    }

    if(file3 == NULL)
	{
		cout<<"Erro ao abrir o arquivo"<<endl;
	}
	while(!feof(file3))
    {
       fscanf(file3,"%d\n",&n);
       vet3[l] = n;
       l++;
    }

    if(file4 == NULL)
	{
		cout<<"Erro ao abrir o arquivo"<<endl;
	}
	while(!feof(file4))
    {
       fscanf(file4,"%d\n",&n);
       vet4[m] = n;
       m++;
    }
    if(file5 == NULL)
	{
		cout<<"Erro ao abrir o arquivo"<<endl;
	}
	while(!feof(file5))
    {
       fscanf(file5,"%d\n",&n);
       vet5[o] = n;
       o++;
    }

    //ordenando todos os vetores utilizando 6threads
    clock_t end,start;

    thread t0(Quick, vet0,0,Max);
    thread t1(Quick,vet1,0,Max);
    thread t2(Quick,vet2,0,Max);
    thread t3(Quick,vet3,0,Max);
    thread t4(Quick,vet4,0,Max);
    thread t5(Quick,vet5,0,Max);
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    start = clock();
    end = clock();
    printf("Tempo gasto: %4.0f ms\n\n",1000*(double)(end-start)/(double)(CLOCKS_PER_SEC));

   //system("pause");
   
 
    //inserindo os valores ordenados em um novo arquivo
    if(fil0 == NULL)
	{
		cout<<"Erro ao abrir o arquivo"<<endl;
	}
	for(i=0;i<Max;i++)
	{
		fprintf(fil0, "%i\n", vet0[i]);
	}
	if(fil1 == NULL)
	{
		cout<<"Erro ao abrir o arquivo"<<endl;
	}
	for(j=0;j<Max;j++)
	{
		fprintf(fil1, "%i\n", vet1[j]);
	}
	if(fil2 == NULL)
	{
		cout<<"Erro ao abrir o arquivo"<<endl;
	}
	for(k=0;k<Max;k++)
	{
		fprintf(fil2, "%i\n", vet2[k]);
	}
	if(fil3 == NULL)
	{
		cout<<"Erro ao abrir o arquivo"<<endl;
	}
	for(l=0;l<Max;l++)
	{
		fprintf(fil3, "%i\n", vet3[l]);
	}
	if(fil4 == NULL)
	{
		cout<<"Erro ao abrir o arquivo"<<endl;
	}
	for(m=0;m<Max;m++)
	{
		fprintf(fil4, "%i\n", vet4[m]);
	}
	if(fil5 == NULL)
	{
		cout<<"Erro ao abrir o arquivo"<<endl;
	}
	for(o=0;o<Max;o++)
	{
		fprintf(fil5, "%i\n", vet5[o]);
	}
	

	
    //liberando os arquivos
    fclose(file0);
    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(file4);
    fclose(file5);

	return 0;
}
