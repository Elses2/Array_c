#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


////si encuentra una letra me da un 1
int es_letra(char x[],int tam){

    int j=0,retorno=0,i=0;
    j=strlen(x);
    while(i<j && retorno==0){
    if(isdigit(x[i])==0){
        retorno=1;

    }
    else{
        i++;
    }
    }
    return retorno;

}
//// si encuentra un numero me da un 1
int es_numero(char x[],int tam){
    int j=0,retorno=0,i=0;
    j=strlen(x);
    while(i<j && retorno==0){
    if(isdigit(x[i])==1){
        retorno=1;

    }
    else{
        i++;
    }
    }
    return retorno;

}
///verifica que el dato ingresado sea un numero
void controlador_numero(char x[],int tam){

    while(es_letra(x,tam)==1){
        printf("Solo numeros:\n");
        fflush(stdin);
        strcpy(x,"");
        gets(x);
    }

}

///verifica que el dato ingresado sea una palabra
void controlador_caracter(char x[],int tam){

        while(es_numero(x,tam)==1){
        printf("Solo letras:\n");
        fflush(stdin);
        strcpy(x,"");
        gets(x);
    }


}
///verifica que el dato ingresado sea un numero y que este en el rango establecido
void controlador_entero(char x[],int tam,int *alm,int desde,int hasta){

    int parcial;
    parcial= atoi(x);
     while(es_letra(x,tam)==1 || parcial>hasta || parcial<desde){
        printf("Solo numeros del %d hasta %d:\n",desde,hasta);
        fflush(stdin);
        strcpy(x,"");
        gets(x);
        fflush(stdin);
        parcial= atoi(x);
    }
    *alm=parcial;

}

///limpia pantalla
void clear(){

    system("cls");

}

void presentacion(){
    printf(" 1:Insertar Trabajador\n 2:Mostrar personas estresadas \n 3:saber si un empleado se encuentra en peligro \n 4:Pares enemigos\n 5:trabajadores con mayor complejidad \n 6:Trabajadores con una sola tarea\n 7:cerrar programa \n ?");
}

struct Tarea{
    char des[100];///descripcion
    int comp;//complejidad

};
struct Trabajador{
    int dni;
    struct Tarea *tareas[5];//maximo 5 tareas por persona
    bool estres;// si esta estresado o no
    int lugar;//poder ejecutivo judicial, ejecutivo o prensa
    int partido ;// partidos politicos
    int comp_max;//la complejidad masa alta de todas las tareas que tiene
    int cant_t;//cantidad de tareas


};
typedef struct Tarea tarea;
typedef struct Trabajador trabajador;



////funciones de estructuras:

///Esta funcion devuelve una funcion tipo tarea--faltan aplicar controladores
tarea* crear_tarea (){///n es el numero de tareas

    tarea* nuevo=NULL;
    int complejidad=0;
    char descripcion[100];

        fflush(stdin);
        printf("Dime la descripcion de la tara: \n");
        gets(descripcion);
        fflush(stdin);
        printf("Dime la complejidad de esta tarea: \n");
        scanf("%d",&complejidad);
        fflush(stdin);

        nuevo= malloc(sizeof(tarea));
        nuevo->comp=complejidad;
        strcpy(nuevo->des, descripcion);

        return nuevo;
}
///esta funcion crea un trabajador-- faltan controladores

trabajador * crear_trabajador(){
    trabajador * nuevo=NULL;
    nuevo= malloc(sizeof(trabajador));
    ////sin sentido
    int dni;
    bool estres=false;
    int lugar;
    int partido;
    int comp_max=0;
    int cant_t;
    ////

    printf("Dame el dni\n");
    scanf("%d",&dni);
    printf("Dame el lugar 1:poder judicial, 2:legislativo,3:ejecutivo,4:prensa\n");
    scanf("%d",&lugar);
    printf("Dame el partido 1:derecha  2:izquierda \n");
    scanf("%d",&partido);
    printf("Dime la cantidad de tareas que tiene este trabajador:\n");
    scanf("%d",&cant_t);
    for(int i=0; i<cant_t; i++){
        nuevo->tareas[i]=malloc(sizeof(tarea));
        nuevo->tareas[i]=crear_tarea();
        ///si la complejidad de una tarea s mayor de 5 esta estresado osea estres es true
        if(nuevo->tareas[i]->comp>5){

            estres=true;
        }
        if(comp_max<nuevo->tareas[i]->comp)comp_max=nuevo->tareas[i]->comp;

    }
    nuevo->cant_t=cant_t;
    nuevo->comp_max=comp_max;
    nuevo->dni=dni;
    nuevo->estres=estres;
    nuevo->lugar=lugar;
    nuevo->partido=partido;
    return nuevo;
}


int main()
{
    int tam=10;///tamano de la array trs
    trabajador *trs[tam];
    for(int i=0; i<10; i++){

        trs[i]=NULL;

    }
    int trbj_may_compl[2]={0,0};////complejidad maxima de tarea posicion 0 es para almacenar mayor complejidad posicion 1 indice
    int cont_trs=0;////contador de trabajadores
    int n=2;
    char boton_c [20];
    int boton=0;

    while(n == 2){

        presentacion();
        gets(boton_c);
        fflush(stdin);

        controlador_entero(boton_c,20,&boton,1,7);



        switch(boton){
        case 1:

            if(cont_trs>9){

                printf("Lo sentimos solo se puede almacenar 10 trabajadores, por el momento");
            }
            else{

                trs[cont_trs]=crear_trabajador();
                cont_trs++;
                //clear();
                printf("Felicitaciones su trabajador se registro correctamente\n");
            }

            break;
        case 2:

            for(int i=0;i<tam;i++){
            if(trs[i]!=NULL){
                if(trs[i]->estres==true){

                    printf("%d: esta estresado\n", i);


                }
            }
            }



            break;
        case 3:

            for(int i=0;i<tam;i++){
                if(trs[i]!=NULL){
            if((trs[i]->estres==true && trs[i]->lugar!=2) || trs[i]->lugar==4){
                printf("el empleado con el dni:%d esta en peligro\n",trs[i]->dni);

            }

            }
            }

            break;
        case 4:

            for(int i=0; i<tam; i++){

                for(int j=0; j<tam;j++){

                    if(trs[i]->dni!=trs[j]->dni){

                         for(int i=0;i<tam;i++){
                if(trs[i+1]!=NULL && i!=tam-1){
                    ///a
                    if(((trs[i]->lugar==1) && (trs[i+1]->lugar==3))||((trs[i]->lugar==3) && (trs[i+1]->lugar==1))){

                        printf("el trabajador %d con dni: %d es enemigo del trabajador %d con el dni:%d \n",i+1,trs[i]->dni,i+2,trs[i+1]->dni);

                   }
                    ///b 1/2
                    if(((trs[i]->lugar==2) && (trs[i+1]->lugar==1))||((trs[i]->lugar==1) && (trs[i+1]->lugar==2))){



                        printf("el trabajador %d con dni: %d es enemigo del trabajador %d con el dni:%d \n",i+1,trs[i]->dni,i+2,trs[i+1]->dni);

                        }
                    ///b 2/2
                    if(((trs[i]->lugar==2) && (trs[i+1]->lugar==1))&&(trs[i]->partido!=trs[i+1]->partido)){
                        printf("el trabajador %d con dni: %d es enemigo del trabajador %d con el dni:%d \n",i+1,trs[i]->dni,i+2,trs[i+1]->dni);
                    }
                    ///c
                     if(trs[i]->lugar==4 || trs[i+1]->lugar==4){
                        if(trs[i]->lugar==4 && trs[i+1]!=4){

                            printf("el trabajador %d con dni: %d es enemigo del trabajador %d con el dni:%d \n",i+1,trs[i]->dni,i+2,trs[i+1]->dni);
                        }
                        if(trs[i+1]->lugar==4 && trs[i]!=4){

                            printf("el trabajador %d con dni: %d es enemigo del trabajador %d con el dni:%d \n",i+1,trs[i]->dni,i+2,trs[i+1]->dni);

                        }

                     }
                }

            }
                    }
                }

            }
            ///1:poder judicial, 2:legislativo,3:ejecutivo,4:prensa


            break;
        case 5:
            for(int i=0; i<tam; i++){
                    if(trs[i]!=NULL){
                if(trbj_may_compl[0]<trs[i]->comp_max){
                    trbj_may_compl[0]=trs[i]->comp_max;
                    trbj_may_compl[1]=i;
                }
            }
            }

            if(trs[trbj_may_compl[1]]!=NULL) printf("El trabajador con mayo complejidaad tiene el dni: %d con una complejidad de: %d \n",trs[trbj_may_compl[1]]->dni,trs[trbj_may_compl[1]]->comp_max );


            break;
        case 6:
            for(int i =0; i<tam; i++){

                if(trs[i]!=NULL && trs[i]->cant_t==1){

                    printf("El trabajador con el dni: %d tiene una sola tarea\n", trs[i]->dni);
                }

            }
            break;
        case 7:
            printf("Gracias por usarnos \n");
            n=4;
            break;
        default:
            printf("Lo sentimos valor fuera de rango\n");

        }

    }
    return 0;

}
