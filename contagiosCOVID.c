#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#define CELDAS 400
#define FC 20
#define min 0

#define SANO 0
#define ENFERMO 1
#define RECUPERADO 2
#define MUERTO 3

struct CELDA {
    char statusCelda;
    int id;
    int edad;
    char statusPersona;
    char vacunacion;
    char diasEnfermedad;
    char cubrebocas;
};

struct CELDA datos[FC][FC];//Matriz general
struct CELDA *pdatos=&datos; //Apuntador a matriz general
int totalenfermos; // Variable controladora del while que nos permite saber cuantos enfermos hay. 

//Declaracion de funciones
void init(struct CELDA *data); 
void age(struct CELDA *data); 
void iD(struct CELDA *data); 
int getRandom(int minimo, int max); 
void printMatrix(struct CELDA *c); 
void contagios(struct CELDA *data);
void procesoContagio(struct CELDA *data,int celda,int valor);

int main()
{
    srand(time(NULL)); //para aleatorios
    init(pdatos); //llena la matriz
    age(pdatos); //les da edad
    iD(pdatos); //les da ID
    printMatrix(pdatos);//imprime primera matriz
    contagios(pdatos);//ciclo de contagios e imprime matriz por ciclo
    return 0;
}

//////////////////////////////////////////

void init(struct CELDA *data)//Funcion para inicializar la matriz
{
    int exito=0; //bandera
    int ncelda;
    int d;
    int celdasOcupadas=(0.75*CELDAS);
    int porcentajeV=(0.25*celdasOcupadas); //Es el 25% de las celdas ocupadas 
    int count=0;
    
    while(exito<celdasOcupadas) // Ciclo while para poner el 75% de las celdas totales con estatus ocupado 
    {
        ncelda= getRandom(min,CELDAS); //obtener un numero aleatorio entre el 0 y el 400
        d = (data+ncelda)->statusCelda;//variable es el valor del estatus de la celda aleatoria
        
        if (d == 0){
            (data+ncelda)->statusCelda=1; //Se cambia el status a 1
            (data+ncelda)->statusPersona=SANO; //Se cambia el status de la persona a SANO

            //Empezamos la asignacion de ciertas cualidades diferentes a cada %25 de las celdas ocupadas
            if (count<porcentajeV) //cambiamos del primer 25% del 75%
                {
                    (data+ncelda)->vacunacion=0;
                    (data+ncelda)->cubrebocas=0;
                    count++;
                }
            else if (count>= porcentajeV && count<porcentajeV*2) //se cambia otro 25% 
                {
                    (data+ncelda)->vacunacion=0;
                    (data+ncelda)->cubrebocas=1;
                    count++;
                }
            else if (count>=porcentajeV*2 && count< porcentajeV*3)//Se cambia otro 25%
                {
                    (data+ncelda)->vacunacion=1;
                    (data+ncelda)->cubrebocas=0;
                    count++;
                }
            else if (count>=porcentajeV*3 && count < porcentajeV*4)//25% restante
                {
                    (data+ncelda)->vacunacion=1;
                    (data+ncelda)->cubrebocas=1;
                    count++;
                }
            exito++;//bandera
        }
    } 

    ncelda=getRandom(min,CELDAS);//Creamos el enfermo aleatorio
    (data+ncelda)->statusCelda=1;
    (data+ncelda)->statusPersona=ENFERMO;
    (data+ncelda)->diasEnfermedad=0;
    totalenfermos++;
}

//////////////////////////////////////////

void age(struct CELDA *data)
{
    int num = 0;
    int i = 0;
    for (i = 0; i < CELDAS; i++)
    {
        if ((data+i)->statusCelda == 1) //si hay persona, se le da edad
        {
            num = getRandom(min,91);
            (data+i)->edad = num;
        }
    }
}

//////////////////////////////////////////
void iD(struct CELDA *data)
{
    int num=1;
    for (int i = 0; i < CELDAS; i++)
    {
        (data+i)->id=num; //cada persona tiene el ID de su celda
        num++;
    }
    
}
//////////////////////////////////////////

int getRandom(int minimo, int max) //Funcion para obtener un numero aleatorio dentro del rango indicado
{
    int rnumber = rand() % max + minimo; 
    return rnumber;
}
//////////////////////////////////////////

void printMatrix(struct CELDA *c)
{
    int E=0,r=0,vacio=0,muertos=0; //Enfermos por día, recuperados, muertos y lugares vacios
    int enfermos=0;

    for (int filas = 0; filas < FC; filas++)
    {
        printf("[");
        for (int columnas = 0; columnas < FC; columnas++)
        {
            if (c->statusCelda==0){ //Celda vacía
                printf("   ");
                vacio++;
            }
            else
            {
                if (c->vacunacion==0)
                {
                    if (c->statusPersona==SANO){
                        if (c->cubrebocas==0){
                            printf(" S "); //sano, no vacuna y no cubrebocas
                        }
                        else{
                            printf(" s ");//sano, no vacuna y si cubrebocas
                        }
                    }
                }
                else
                {
                    if (c->vacunacion==1)
                    {
                        if (c->statusPersona==SANO){
                            if (c->cubrebocas==0){
                                printf(" V ");//Sano, vacuna y no cubrebocas
                            }
                            else{
                                printf(" v ");//Sano, vacuna y si cubrebocas
                            }
                        }       
                    }
                }
            }
            
            if (c->statusPersona==ENFERMO)
            {
                if (c->cubrebocas==0){
                    printf(" E ");//Enfermo, no cubrebocas
                    E++; //enfermos por día
                }
                else{
                    printf(" e ");//Enfermo, si cubrebocas
                    E++; //enfermos por día
                }
            }
            if (c->statusPersona==MUERTO)
            {
                printf(" + ");//Muerto
                muertos++;
            }
            else
            {
                if (c->statusPersona==RECUPERADO){
                    printf(" r ");//Recuperado
                    r++;
                }
            }
            c++;//Se mueve a la siguiente celda
        }
        printf("]\n");
    }
    
    printf("\nEnfermos: %d",E);
    printf("\nRecuperados: %d\n",r);
    printf("Celdas vacias: %d\n",vacio);
    printf("Muertos: %d\n",muertos);
}

//////////////////////////////////////////

void contagios(struct CELDA *data) //comparaciones de contagios
{
    char posicion = 0;
    int dia=1;
    while (totalenfermos>0)//Termina cuando ya nadie más se puede contagiar
    {
        printf("\nDia %d\n",dia);

        for (int i = 0; i < CELDAS; i++)
        {
            if ((data+i)->statusPersona==ENFERMO)//si encuentra enfermo
            {
                (data+i)->diasEnfermedad ++;
                if ((data+i)->diasEnfermedad==8 && (data+i)->statusPersona != MUERTO)//Proceso de recuperado
                {
                    (data+i)->statusPersona=RECUPERADO;
                    totalenfermos--;//Se resta 1 al total de enfermos porque ya esta recuperado
                }

                int probm = getRandom(0,100);// Proceso de muerte
                if ((data+i)->vacunacion==0)
                {
                    if (probm <= 10)
                    {
                        (data+i)->statusPersona=MUERTO;
                        totalenfermos--;
                    }
                }
                if ((data+i)->vacunacion==1)
                {
                    if (probm <= 2)
                    {
                        (data+i)->statusPersona=MUERTO;
                        totalenfermos--;
                    }
                }

                // Casos posibles 
                if( i <= 1 && i >= 18 ){ //Celdas de la primera fila sin contar las orillas
                    procesoContagio(data,i,1);
                    procesoContagio(data,i,-1); 
                    procesoContagio(data,i,20); 
                    procesoContagio(data,i,21); 
                    procesoContagio(data,i,19); 

                } else if ( i <= 376 && i >= 398 ){//celdas de la última fila sin contar las orillas
                    procesoContagio(data,i,1);
                    procesoContagio(data,i,-1);
                    procesoContagio(data,i,-20);
                    procesoContagio(data,i,-21);
                    procesoContagio(data,i,-19);

                } else if (i % 20 == 0 && i != 0  && i!=380){//celdas de la primera columna sin contar las esquinas
                    procesoContagio(data,i,-20); 
                    procesoContagio(data,i,-19);
                    procesoContagio(data,i,1);
                    procesoContagio(data,i,21);
                    procesoContagio(data,i,20);

                } else if ( (i+20) % 20 == 0 && i !=19 && i!=399){//celdas de la última columna sin contar las esquinas
                    procesoContagio(data,i,-20); 
                    procesoContagio(data,i,-21);
                    procesoContagio(data,i,-1);
                    procesoContagio(data,i,19);
                    procesoContagio(data,i,20);

                } else if ( i == 0 || i == 19 || i == 375 || i == 399 ){//las esquinas de la matriz
                    if(i == 0 ){//Primera celda
                        procesoContagio(data,i,1);
                        procesoContagio(data,i,21); 
                        procesoContagio(data,i,20);
                             
                    }else if(i == 19 ){//última celda de la primera fila
                        procesoContagio(data,i,-1);
                        procesoContagio(data,i,19); 
                        procesoContagio(data,i,20); 
                             
                    }else if(i == 375 ){//Primera celda de la ultima fila 
                        procesoContagio(data,i,-20); 
                        procesoContagio(data,i,-19);
                        procesoContagio(data,i,1);
                             
                    } else if(i == 399 ){//última celda de la ultima fila 
                        procesoContagio(data,i,-20);
                        procesoContagio(data,i,-21);
                        procesoContagio(data,i,-1);
                             
                    }
                }else {//Todas las celdas del centro
                    procesoContagio(data,i,-20);
                    procesoContagio(data,i,-21);
                    procesoContagio(data,i,-1);
                    procesoContagio(data,i,19);
                    procesoContagio(data,i,20); 
                    procesoContagio(data,i,21);
                    procesoContagio(data,i,1);
                    procesoContagio(data,i,-19);
                }
            }
        }
        dia++;
        printMatrix(data);
    } 
}

//////////////////////////////////////////

void procesoContagio(struct CELDA *data,int celda,int valor) //Proceso de contagios (matriz, numero de celda, numero de celda a comparar)
{
    int num=0;
    if ((data+(celda+valor))->statusCelda==1) //Si la celda vecina esta ocupada
    {
        if ((data+celda)->cubrebocas==0 && (data+(celda+valor))->cubrebocas==0)//NINGUNO TIENE CUBREBOCAS
        {
            if ((data+(celda+valor))->statusPersona==SANO && (data+(celda+valor))->vacunacion==0)//Si la persona vecina esta sana y no tiene vacuna
            {
                num=getRandom(1,100);
                if (num<=90)//se contagia
                {
                    (data+(celda+valor))->statusPersona=ENFERMO; 
                    (data+(celda+valor))->diasEnfermedad=0;
                    totalenfermos++;
                }
            }
            else
            {
                if ((data+(celda+valor))->statusPersona==SANO && (data+(celda+valor))->vacunacion==1)//si la persona vecina esta sana y tiene vacuna
                {
                    num=getRandom(1,100);//Se saca un numero aleatorio entre el 1 y el 100
                    if (num<=45)
                    {
                        (data+(celda+valor))->statusPersona=ENFERMO;
                        (data+(celda+valor))->diasEnfermedad=0;
                        totalenfermos++;
                    }
                }
            }
        }
        else if ((data+celda)->cubrebocas==1 || (data+(celda+valor))->cubrebocas==1)//EXISTE 1 CUBREBOCAS
        {
            if ((data+(celda+valor))->statusPersona==SANO && (data+(celda+valor))->vacunacion==0)//si la persona vecina esta sana y no tiene vacuna
            {
                num=getRandom(1,100);
                if (num<=20)
                {
                    (data+(celda+valor))->statusPersona=ENFERMO;
                    (data+(celda+valor))->diasEnfermedad=0;
                    totalenfermos++;
                }
            }
            else
            {
                if ((data+(celda+valor))->statusPersona==SANO && (data+(celda+valor))->vacunacion==1)//si la persona vecina esta sana y tiene vacuna
                {
                    num=getRandom(1,100);
                    if (num<=15)
                    {
                        (data+(celda+valor))->statusPersona=ENFERMO;
                        (data+(celda+valor))->diasEnfermedad=0;
                        totalenfermos++;
                    }
                }
            }
        }
        else if ((data+celda)->cubrebocas==1 && (data+(celda+valor))->cubrebocas==1)//EXISTEN 2 CUBREBOCAS
        {
            if ((data+(celda+valor))->statusPersona==SANO && (data+(celda+valor))->vacunacion==0)//Persona vecina no vacunada
            {
                num=getRandom(1,100);
                if (num<=10)
                {
                    (data+(celda+valor))->statusPersona=ENFERMO;
                    (data+(celda+valor))->diasEnfermedad=0;
                    totalenfermos++;
                }
            }
            else 
            {
                if ((data+(celda+valor))->statusPersona==SANO && (data+(celda+valor))->vacunacion==1)//Persona vecina esta vacunada
                {
                    num=getRandom(1,100);
                    if (num<=5)
                    {
                        (data+(celda+valor))->statusPersona=ENFERMO;
                        (data+(celda+valor))->diasEnfermedad=0;
                        totalenfermos++;
                    }
                }
            }
        }
    }
}