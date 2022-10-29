Algoritmo Matrices
	Definir Fil,Col,f,c Como Entero
	Definir matriz Como Entero
	Dimension matriz[100,100]
	Escribir 'Digite el numero de Filas de la matriz '
	Leer k
	Leer z
	Para f<-1 Hasta k Hacer
		Para c<-1 Hasta z Hacer
			Escribir 'Ingrese valor en ',f,' ',c
			Leer matriz[f,c]
		FinPara
	FinPara
	Escribir ''
	Escribir 'Este es el mapa del Robot'
	Escribir ''
	Para f<-1 Hasta k Hacer
		Para c<-1 Hasta z Hacer
			Escribir matriz[f,c],' ' Sin Saltar
		FinPara
		Escribir ' '
	FinPara
FinAlgoritmo
