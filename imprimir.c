#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<string.h>
#include<time.h>
#include <ctype.h>
#define N 6
#define ESPERA 0 //na fila inicial de prioridade
#define ESPERO 1 //na fila sa impressora
#define IMPRIMINDO 2

void *usuario(void *n);
void Esperando_Imprimir(int);
void impressao_finalizada(int);
void testar(int);

sem_t mutex;
sem_t mutex2;
sem_t S[N]; //inicializando o semáforo
int estado[N];//estado do usuario
int nusuario[N]={0,1,2,3,4,5};
int semente;

typedef struct pessoa{
   struct pessoa* prox;
   char nome[20];
   char arquivo[20];
   int cont;
   int prioridade;
}Pessoa;

Pessoa *p;//primeira fila p colocar os 6 usuários
Pessoa *p2;//segunda fila p colocar os 3 usuários q estarão ESPERO p IMPRIMINDO

//inicializa o processo
void *usuario(void *n)
{
   int randon,aux=1;
   srand(semente);//semente,11,22,33,44,55,66
   
   //cada usuario vai imprimir 5 arquivos
   for(j=0;j<N;j++)
   {
         
      while(aux==1)
      {
         randon =rand()%6;
         //printf("%i",randon);

         if(p[j].cont == N-1)
         {
            aux = 1;
         }else
         {
            aux = 0;
         }   

      }
      sleep(1);
      if(p[j].cont < N-1)
      {
         Esperando_Imprimir(randon);
         sleep(1);
      }
      int a = Prioridade(p);
      impressao_finalizada(a);

   }   
}

int Prioridade(Pessoa *p)
{
   int i, ret;
   for(i = 0; i < 4; i++)
   {
      if(p[i].prioridade == 2)
      {
         ret = i;
         return ret;
      }
   }
   return 0;
}
void Esperando_Imprimir(int nusuario)
{
   sem_wait(&mutex);
   estado[nusuario] = ESPERO;
   printf("usuario %d ta ESPERANDO.\n", nusuario);
   if(p[nusuario].cont <=5)
   {
      p[nusuario].cont += 1;
      if(p[nusuario].cont == 6)
      {
         p[nusuario].cont = 5;
      }
   }
   testar(nusuario);
   sem_post(&mutex);
   sem_wait(&S[nusuario]);
   sleep(1);
}

void impressao_finalizada(int nusuario)
{
   sem_wait(&mutex);
   estado[nusuario]=ESPERA;
   printf("usuario %d finalizou.\n", nusuario+1);
   sem_post(&mutex);
}

void testar(int nusuario)
{
   if(estado[nusuario]==ESPERO )
   {
      estado[nusuario]=IMPRIMINDO;
      sleep(2);
      printf("usuario %d esta  IMPRIMINDO.\n", nusuario);
      //printf("Imprimindo o arquivo %s",p2.arquivo);
      sem_post(&S[nusuario]);
   }
}


Pessoa* inicializa()
{
   return NULL;
}

int vazia(Pessoa* f)
{
   return (f==NULL);
}

void imprime(Pessoa* f)
{
   Pessoa* t=f;
   printf("%s(%d) - ", t->nome, t->prioridade);
   
   while(t->prox!=NULL)
   {
      t = t->prox;
      printf("%s(%d) - ", t->nome, t->prioridade);
   };
   
   return; 
}

Pessoa* cria()
{
   Pessoa* p = (Pessoa*) malloc (sizeof(Pessoa));
   
   return p;
}

void inserir_nome(Pessoa* f, char* nome, int prioridade,char* arquivo)
{
   Pessoa* novo = cria();
   Pessoa* ant = NULL;
   Pessoa* p = f;
   strcpy(p->nome,nome);
   strcpy(p->arquivo,arquivo);
   p->prioridade = prioridade;
   p->cont =0;
   
   while(p!=NULL && p->prioridade<=prioridade)
   {
      ant = p;
      p = p->prox;
   }
   
   if(ant == NULL)
   {
      novo->prox = f;
      ant->prox = novo;
   }
   else
   {
      novo->prox = ant->prox;
      ant->prox = novo;
   }

}

Pessoa* retira(Pessoa* f, char* v)
{
   Pessoa* ant = NULL;
   Pessoa* p = f;
   
   while(p!=NULL && p->nome!=v)
   {
      ant = p;
      p = p->prox;
   }
   
   if(p==NULL)
   {
      return f;
   }
   
   char prox_da_fila(Pessoa* f)
   {
      Pessoa* temp =f;
      return temp->nome;
   }
}


int main() 
{
   char name[20];
   char arq[20];
   pthread_t thread_id[N]; //identificadores das threads

   int i,a=0;
   int j,k,l,m,randon;

   for(i=0;i<N;i++)
   {
      printf("Digite o nome do %i usuario : ",i+1);
      scanf("%s",name);
      printf("O nome do arquivo:");
      scanf("%s",arq);
      printf("A sua prioridade :");
      scanf("%d",&a);
      inserir_nome(&p,name,a,arq);
   }

   printf("Digite uma semente: ");
   scanf("%d",&semente);

   /*for(j=0;j<3;j++)
   {
      //printf("a\n");
     pthread_create(&thread_id[i], NULL, usuario, &nusuario[i]);//criar as threads
   }*/

   sem_init(&mutex,0,1);
    sem_init(&mutex2,0,3);
   for(k=0;k<N;k++)
   sem_init(&S[k],0,0);

   for(l=0;l<N;l++)
   {
      pthread_create(&thread_id[i], NULL, usuario, &nusuario[i]);
      //criar as threads
      printf(" %d usuários esta a ESPERA.\n",nusuario[l]+1);
   }
   for(m=0;m<N;m++)
   pthread_join(thread_id[i],NULL); // junção das threads

   

         
   return(0);
}  