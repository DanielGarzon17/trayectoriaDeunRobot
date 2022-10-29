#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
using namespace std;

int posicionx, posiciony, finposicionx, finposiciony, movimientos, pfinalizado;
string direccion, Mswitch;


int **ejecutar(char *nombreArchivo){
	
    FILE *archivo = fopen(nombreArchivo, "r+"); //abrimos el archivo
    
    if (archivo == NULL) {
        printf("Error en la apertura del archivo"); //Si el archivo no existe el programa no se ejecutara
        return 0;
}
    
    
    char linea[150];
    fgets(linea, 150, archivo); 
    char *token = strtok(linea, " "); 	//encontramos el tamaño de la matriz
    int filas = atoi(token);
    token = strtok(NULL, " ");
    int columnas = atoi(token);
    if (filas<1 || filas>=100 || columnas<1 || columnas>=100 ){
			cout<<"No es posible ingresar una matriz de este tamano"<<endl;
			return 0;
		}
    
    char convertida[filas][columnas];   //creamos una  matriz de char 
    
    
    int **matriz = new int *[filas];    //creamos una matriz de enteros
    for (int i = 0; i < filas; i++){
        matriz[i] = new int[columnas];
        fgets(linea,150, archivo);		 //Recorremos la matriz de enteros y la rellenamos con la informacion del archivo de texto
        token = strtok(linea, " ");
        matriz[i][0] = atoi(token);
        for (int j = 1; j < columnas; j++){
            token = strtok(NULL, " ");
            matriz[i][j] = atoi(token);
        }
    }


		fgets(linea,150, archivo);
		token = strtok(linea, " ");			//guardamos la posicion inicial del robot
		posicionx = atoi(token);
		token = strtok(NULL, " ");
		posiciony= atoi(token);
		if (posicionx<1 || posicionx>filas || posiciony<1 || posiciony>columnas ){
			cout<<"no es posible colocar estas coordenadas de incio en la matriz"<<endl;
			return 0;
		}
		
		//cout<<"posicion en x "<<posicionx<<" posicion en y"<<posiciony<<endl;
	
		
		fgets(linea,150, archivo);
		token = strtok(linea, " ");
		finposicionx = atoi(token);			//guardamos el destino  del robot	
		token = strtok(NULL, " ");
		finposiciony= atoi(token);
		if (finposicionx<1 || finposicionx>filas || finposiciony<1 || finposiciony>columnas ){
			cout<<"no es posible colocar estas coordenadas de posicion final en la matriz"<<endl;
			return 0;
		}
		
		//cout<<"llegada posicion en x "<<finposicionx<<" posicion en y "<<finposiciony<<endl;

		fgets(linea,150, archivo);
		token = strtok(linea, " ");			//guardamos la direccion inicial 
		direccion=token;
		
		//cout<<"direccion inicial "<<direccion<<endl;
		
		
		fgets(linea,150, archivo);
		token = strtok(linea, " ");		//Guardamos la cantidad de movimientos 
		movimientos=atoi(token);
		if (movimientos <1 || movimientos>40 ){
			cout<<"la cantidad de movimientos es excedida"<<endl;
			return 0;
		}
		
		//cout<<"cantidad de movimientos "<<movimientos<<endl;
	
		

		
		
		if(matriz[posicionx-1][posiciony-1]==1){
			cout<<"el robot inicio sobre una mina y fue destruido"<<endl;  //verificamos que en la posicion inicial del robot no se encuentre una mina
			return 0;
		}else{
			
			int flecha;
			if(direccion=="N"){
				flecha=30;
			}
			if(direccion=="S"){
				flecha=31;
			}
			if(direccion=="E"){
				flecha=16;
			}
			if(direccion=="O"){
				flecha=17;
			}
			
			
			
			
			
			matriz[finposicionx-1][finposiciony-1]=15;    //ubicamos el robot y el punto de llegada
			matriz[posicionx-1][posiciony-1]=flecha;    
			
		

		
		
		int orientacion;
																	//con el string orientacion sabremos a donde esta mirando el robot 
			if(direccion=="N"){
				
				orientacion=1;		//Orientacion 1 norte
			}							
			if(direccion=="S"){
				
				orientacion=2;		//Orientacion 2 sur
			}
			if(direccion=="E"){
				
				orientacion=3;		//Orientacion 3 este
			}
			if(direccion=="O"){
				
				orientacion=4;		//Orientacion 4 oeste
			}
		
		
		
			fgets(linea,150, archivo);
			token = strtok(linea, " ");	
			
			
		
		cout<<"-------------MATRIZ INICIAL---------------"<<endl;
		cout<<endl;	
			
			
			for (int i = 0; i < filas; i++) {
			for (int j = 0; j < columnas; j++) {
				int temporal = matriz[i][j];
				convertida[i][j]=temporal;
								}			

						}											//actualizamos la matriz de char y la imprimimos
		
	
    	for (int i = 0; i < filas; i++) {						//imprimir la primer matriz
			for (int j = 0; j < columnas; j++) {
				cout<<"[ "<<convertida[i][j]<<" ]";
								}
					cout<<endl;
					cout<<endl;
		
				}  
			
			for(int o=1;o<=movimientos; o++){
			Mswitch = token; 
			
							
			if(Mswitch=="D"){
				
				switch(orientacion){
					case 1:					//norte gira a la derecha = este
						orientacion=3;
						flecha=16;
						matriz[posicionx-1][posiciony-1]=flecha;   
						break;
					case 2:					//sur gira a la derecha  = oeste
						orientacion=4;
						flecha=17 ;
						matriz[posicionx-1][posiciony-1]=flecha;   
						break;
					case 3:					//este gira a la derecha = sur
						orientacion=2;
						flecha=31;
						matriz[posicionx-1][posiciony-1]=flecha;   
						break;
					case 4:					//oeste gira a la derecha = norte
						orientacion=1;
						flecha=30;
						matriz[posicionx-1][posiciony-1]=flecha;   
						break;
					
				}
				
			}	
			
			if(Mswitch=="A"){
				
				if((orientacion==1 && posicionx-1==0 || orientacion==2 && posicionx==filas || orientacion==3 && posiciony==columnas || orientacion==4 && posiciony-1==0 )){
					cout<<"el robot se estrello con una pared en su intento de movimiento "<<o<<endl;
					return 0;
					
				}else{
				switch(orientacion){
					case 1:
						matriz[posicionx-1][posiciony-1]=179;			//mirando al norte
						posicionx=posicionx-1;							//sube en la matriz
						if(matriz[posicionx-1][posiciony-1]==1){
						cout<<"el robot Toco una mina en el movimiento "<<movimientos<<endl;			//VERIFICACION DE QUE EL ROBOT TOCO UNA MINA
					    o = 100;
					    pfinalizado =1;
						}else if(matriz[posicionx-1][posiciony-1]==15){								
						cout<<"el robot Llego al objetivo  "<<endl;
					    o = 100;
						pfinalizado = 2;	
						
						matriz[posicionx-1][posiciony-1]=flecha;
						}else{
						matriz[posicionx-1][posiciony-1]=flecha;	
						}
						break;
					case 2:													//mirando al sur
						matriz[posicionx-1][posiciony-1]=179;
						posicionx=posicionx+1;								//baja en la matriz
						if(matriz[posicionx-1][posiciony-1]==1){
						cout<<"el robot Toco una mina en el movimiento "<<movimientos<<endl;
					    o = 100;	
					    pfinalizado =1;
						}else if(matriz[posicionx-1][posiciony-1]==1){
						cout<<"el robot Llego al objetivo  "<<endl;
					    o = 100;
						pfinalizado =2;
						matriz[posicionx-1][posiciony-1]=flecha;
						}
						else{
						matriz[posicionx-1][posiciony-1]=flecha;	
						}
						
						break;
					case 3:													//mirando al este
						matriz[posicionx-1][posiciony-1]=196;
						posiciony=posiciony+1;
						if(matriz[posicionx-1][posiciony-1]==1){
						cout<<"el robot Toco una mina en el movimiento "<<movimientos<<endl;
					    o = 100;
						pfinalizado =1;	
						}else if(matriz[posicionx-1][posiciony-1]==15){
						cout<<"el robot Llego al objetivo  "<<endl;
					    o = 100;
						pfinalizado =2;
						matriz[posicionx-1][posiciony-1]=flecha;	
						}else{
						matriz[posicionx-1][posiciony-1]=flecha;
							
						}
						
						break;
					case 4:														//mirando al oeste
						
						 
						matriz[posicionx-1][posiciony-1]=196;
						posiciony=posiciony-1;
						if(matriz[posicionx-1][posiciony-1]==1){
						cout<<"el robot Toco una mina en el movimiento "<<movimientos<<endl;
					    o = 100;
						pfinalizado =1;	
						}else if(matriz[posicionx-1][posiciony-1]==15){
						cout<<"el robot Llego al objetivo  "<<endl;
					    o = 100;
						pfinalizado =2;
						matriz[posicionx-1][posiciony-1]=flecha;
						}else{
						
						matriz[posicionx-1][posiciony-1]=flecha;	
						}
						
						break;
					
				}
			}
				
				
			}
			if(Mswitch=="I"){
				
				switch(orientacion){
					case 1:
						orientacion=4;
						flecha=17;
						matriz[posicionx-1][posiciony-1]=flecha;   					//norte gira a la izquierda = oeste
						break;
					case 2:
						orientacion=3;
						flecha=16;
						matriz[posicionx-1][posiciony-1]=flecha; 					//sur gira a la izquierda = este
						break;
					case 3:	
						orientacion=1;
						flecha=30;
						matriz[posicionx-1][posiciony-1]=flecha; 					//este gira a la izquierda = norte
						break;
					case 4:	
					orientacion=2;
						flecha=31;
						matriz[posicionx-1][posiciony-1]=flecha; 					//oeste gira a la izquierda = sur
						break;
					
				}
				
			}
			token = strtok(NULL, " ");	
			
			
		cout<<endl;
		cout<<"/////////////////////////////////////////////////////////"<<endl;
		cout<<"/////////////////////////////////////////////////////////"<<endl;
		cout<<endl;
		cout<<"movimiento: "<<o<<endl;
		
		for (int i = 0; i < filas; i++) {								//cambiar de int a char
			for (int j = 0; j < columnas; j++) {
				int temporal = matriz[i][j];
				convertida[i][j]=temporal;
								}			

						}											//actualizamos la matriz de char y la imprimimos
	
	
    	for (int i = 0; i < filas; i++) {								//Imprimir como char
			for (int j = 0; j < columnas; j++) {
				cout<<"[ "<<convertida[i][j]<<" ]";
								}
					cout<<endl;
					cout<<endl;
				}  
			if(o==1){
			
			Sleep (4000);	
			}
			if(o==movimientos || o==100){
				Sleep (1000);
			}
			else{
				Sleep (1000);
				system ("cls");
			}
		}
			
	}
	
  	switch(pfinalizado){
  		
  		case 1:
  		fgets(linea, 150, archivo);	
  		fputs( "E", archivo);
  		cout<<"El robot choco contra una mina"<<endl;
  		break;
  		case 2:	
  		fgets(linea, 150, archivo);
		fputs( "C", archivo);
		cout<<"El robot llego al objetivo"<<endl;	
		break;
	  }

    fclose(archivo); 
}

int main(int argc, char** argv) {
	
	ejecutar("ROBCOM.TXT"); //ejecutamos la funcion y se pasa por argumento el ARCHIVO DE PRUEBA
	system("PAUSE");
	return 0;
}
