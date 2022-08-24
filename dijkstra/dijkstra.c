#include <assert.h>
#include <stdlib.h>

#include "cost.h"
#include "graph.h"
#include "set.h"

int min(set C, cost_t D[]){
	int vmin, minimo; // vmin sera un elemento de C, minimo es la variable que guardará el valor mínimo actual en cada paso
	set temp = set_empty(); //Creamos una set vacío temporal
	temp = set_copy(C);//Agregamos los valores del set C al set temp
	vmin = set_get(temp);//Declaramos el primer elemento del set temporal como el mínimo actual

	while(!set_is_empty(temp)){   //Revisamos el set temporal hasta que esté vacío, para ello:
		minimo = set_get(temp); //(1)Obtenemos el primer elemento de temporal, para este punto minimo=vmin.			
		if(cost_le(D[minimo] , D[vmin]) ){//(2)Comparamos utilizando cost_le, que compara tanto si el valor es menor como si es igual.
			vmin = minimo;//Si se cumple la condición actualizamos el valor mínimo actual con el valor encontrado que es menor o igual.
		}
		temp = set_elim(temp, minimo); //(3)Eliminamos el elemento ya revisado para poder analizar el siguiente.
	}
	temp = set_destroy(temp);//Liberamos memoria
	return vmin; 
}

cost_t *dijkstra(graph_t graph, vertex_t init)
{
	//Declaramos las variables c y var, c la utilizaremos para revisar el grafo, var será una variable auxiliar
	int c, var;
	//Declaramos un set C y un set temp que servirá de variable auxiliar para no remover elementos del set original
	set C,temp;
	//i y j servirán de índices para revisar el grafo, n será el tamaño máximo del arreglo
	unsigned int n, i, j;
	n = graph_max_size(graph);
	//C es vacío, temp es vacío
	C = set_empty();
	temp = set_empty();	
	//Alojamos memoria
	cost_t* D = calloc(n, sizeof(cost_t));
	//Agregamos n elementos a C
	 for(i=0u; i<n; i++) { 
	 	C = set_add(C,i);
	 }
	 //Eliminamos el primer nodo
	 C= set_elim(C,init);
	 //Obtenemos el costo de revisar los vértices
	 for (j=0u; j<n; j++){ 
	 	D[j]= graph_get_cost(graph,init,j);
	 }
	 //Revisamos el set tomando el primer elemento y eliminadolo al final
	 while(!set_is_empty(C)){
	 	c = min(C,D);
	 	C = set_elim(C,c);
	 	temp = set_copy(C);
	 	while(!set_is_empty(temp)){
	 		var = set_get(temp); 
	 		//Comparamos los costos anteriores con el nuevo
	 		if(cost_le(cost_sum(D[c],graph_get_cost(graph,c,var)), D[var])){
				//Actualizamos el valor D[var] con la suma de D[c] y el costo de ir desde el vertice c a var
	 			D[var] = cost_sum(D[c], graph_get_cost(graph,c,var));
	 		}
	 		//Eliminamos el set temporal para liberar memoria
	 		temp = set_elim(temp,var);
		}
	}
	//Liberamos memoria
	C = set_destroy(C);
	temp = set_destroy(temp);
	return D;
}
