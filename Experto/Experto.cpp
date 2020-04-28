#include "Experto.h"
#include "ArbolDinamico.h"
#include "Regla.h"
#include <vector>
#include <string>
#include <algorithm>

namespace ExpertoLib {

	Experto::Experto() {
		raiz = nuevoNodo("Raiz", "", false);
		raizGrafo = nuevoNodoGrafo("Raiz");
	}

	void Experto::infiereBackwardChaining()
	{
		for (unsigned int i = 0; i < raiz->hijo.size(); i++) {
			if (esEstaConsecuencia(raiz->hijo[i])) {
				std::cout << "Resultado: " << raiz->hijo[i]->valor << " \n";
				std::cout << raiz->hijo[i]->comentario << " \n";
				return;
			}
		}
		std::cout << "Resultado: Desconocido \n";
	}

	std::vector<std::vector<std::string>> Experto::infiereTodasLasSolucionesBC( std::vector<std::string> input)
	{
		std::vector<std::vector<std::string>> soluciones;
		std::vector<std::string> parcial;
		std::cout << "infiere todas las soluciones" << std::endl;
		for (unsigned int i = 0; i < raiz->hijo.size(); i++) {
			if (esEstaConsecuenciaInput(raiz->hijo[i],input)) {
				std::string valor = raiz->hijo[i]->valor;
				std::string delimiter = "/";
				std::string token = valor.substr(0, valor.find(delimiter));
				token.erase(std::remove(token.begin(), token.end(), '-'), token.end());
				parcial.push_back(token);
				parcial.push_back(raiz->hijo[i]->comentario);
				soluciones.push_back(parcial);
				parcial.clear();
			}
		}
		for (unsigned int i = 0; i < soluciones.size(); i++) {
			std::cout << "solucion [" << i << "]: " << soluciones[i][0] << std::endl;
			std::cout << "comentario [" << i << "]: " << soluciones[i][1] << std::endl;
		}
		//infiereTodasLasSolucionesBC( std::vector<std::string> input)
		return soluciones;
	}

	void Experto::infiereForwardChaining()
	{
		int respuesta;
		unsigned int i = 0;
		for (i = 0; i < raiz->hijo.size(); i++) {
			respuesta = 0;
			while (respuesta != 1 && respuesta != 2) {
				std::cout << raiz->hijo[i]->valor << " ? (1:si/2:no)\n";
				std::cin >> respuesta;
			}
			if (respuesta == 1)
				raiz->hijo[i]->fueAceptado = true;
			if (respuesta == 2)
				raiz->hijo[i]->fueRechazado = true;		
		}
		//una vez conseguidas todas las respuestas, comienza el BFS deductivo
		if(!obtenConsecuenciaForward(raiz))
			std::cout << "Resultado: Desconocido \n";
	}

	void Experto::insertaRegla(Regla nuevaRegla) {

		Nodo* consecuencia = buscaNodo(nuevaRegla.getConsecuencia(), raiz);
		Nodo* temp;
		if (!consecuencia) {
			temp = nuevoNodo(nuevaRegla.getConsecuencia(), nuevaRegla.getComentario(), false);
			(raiz->hijo).push_back(temp);
		}
		//ya existía el nodo con hijos
		else if (consecuencia && consecuencia->esHoja == false) {
			return;
		}

		/* nodos CONDICIONES (recorrer el vector de condiciones)*/
		std::vector<std::string> condiciones = nuevaRegla.getCondiciones();
		Nodo* condicion;
		for (unsigned int i = 0; i < condiciones.size(); i++) {
			condicion = buscaNodo(condiciones.at(i), raiz);
			if (!condicion) {
				//creamos el nodo y lo agregamos a la consecuencia solicitada
				temp = nuevoNodo(condiciones.at(i), " ", true);
				agregaCondicionANodo(temp, nuevaRegla.getConsecuencia(), raiz); // setear esCondicion = true
			}
			//si es que existe el nodo y es condicion de otra consecuencia
			else {
				if (condicion->esHoja == false) {
					//quita el nodo de la raiz y lo deja como hijo de la consecuencia adecuada
					agregaCondicionANodo(condicion, nuevaRegla.getConsecuencia(), raiz); // setear esCondicion = true
					eliminaNodoDeRaiz(condicion, raiz);
				}
				else if (condicion->esHoja == true) {
					agregaCondicionANodo(condicion, nuevaRegla.getConsecuencia(), raiz); // setear esCondicion = true
				}
			}
		}
	}

	void Experto::insertaReglaForward(Regla nuevaRegla)
	{
		Nodo* temp;
		Nodo* consecuencia = buscaNodo(nuevaRegla.getConsecuencia(), raiz);
		if (!consecuencia) {
			consecuencia = nuevoNodo(nuevaRegla.getConsecuencia(), nuevaRegla.getComentario(), true);
		}
		else {
			eliminaNodoDeRaiz(consecuencia, raiz);
		}
		/* nodos CONDICIONES (recorrer el vector de condiciones)*/
		std::vector<std::string> condiciones = nuevaRegla.getCondiciones();
		Nodo* condicion;
		for (unsigned int i = 0; i < condiciones.size(); i++) {
			condicion = buscaNodo(condiciones.at(i), raiz);
			if (!condicion) {
				//creamos el nodo y lo agregamos a la raiz
				temp = nuevoNodo(condiciones.at(i), " ", false);
				(raiz->hijo).push_back(temp);
				//agregamos la consecuencia al nodo
				int posicion = (raiz->hijo).size() - 1;
				(raiz->hijo[posicion]->hijo).push_back(consecuencia);
			}
			else {
				agregaCondicionANodoForward(condicion, consecuencia, raiz);
			}
		}
	}

	void Experto::insertaReglaSemantica(ReglaSemantica nuevaRegla)
	{
		NodoGrafo* Padre = buscaNodoGrafo(nuevaRegla.getValorPadre(), raizGrafo);
		NodoGrafo* Hijo = buscaNodoGrafo(nuevaRegla.getValorHijo(), raizGrafo);
		if (!Padre && !Hijo) {
			Padre = nuevoNodoGrafo(nuevaRegla.getValorPadre());
			(raizGrafo->hijo).push_back(Padre);
			int posicion = (raizGrafo->hijo).size() - 1;
			(raizGrafo->hijo[posicion]->arco).push_back(nuevaRegla.getValorArco());

			Hijo = nuevoNodoGrafo(nuevaRegla.getValorHijo());
			(raizGrafo->hijo[posicion]->hijo).push_back(Hijo);
		}
		else if (Padre && !Hijo) {
			Hijo = nuevoNodoGrafo(nuevaRegla.getValorHijo());
			insertaANodoGrafo(Padre, Hijo, raizGrafo, nuevaRegla.getValorArco(),false);
		}
		else if (!Padre && Hijo) {
			Padre = nuevoNodoGrafo(nuevaRegla.getValorPadre());
			(raizGrafo->hijo).push_back(Padre);
			insertaANodoGrafo(Padre, Hijo, raizGrafo, nuevaRegla.getValorArco(), false);
		}
		else if (Padre && Hijo) {
			bool nodoUnico = true;
			for (unsigned int i = 0; i < Padre->hijo.size(); i++) {
				if ((Padre->hijo[i]->valor == Hijo->valor) && Padre->arco[i] == nuevaRegla.getValorArco()) {//revisar
					nodoUnico = false;
				}
			}
			if (nodoUnico/* && !(Padre->apuntaAPadre)*/) {
				insertaANodoGrafo(Padre, Hijo, raizGrafo, nuevaRegla.getValorArco(),true);
			}
		}
		bool padreEnRaiz = false;
		for (unsigned int i = 0; i < raizGrafo->hijo.size(); i++) {
			if (raizGrafo->hijo[i]->valor == Padre->valor) {
				padreEnRaiz = true;
			}
		}
		if (!padreEnRaiz) {
			(raizGrafo->hijo).push_back(Padre);
		}
	}


	void Experto::mostrarValores() {
		std::vector<std::string> v;
		v = buscarValores(raizGrafo, v);

		for (unsigned int i = 0; i < v.size(); i++) {
			std::cout << v[i] << '\n';
		}
		v.clear();
		v = buscarValoresArcos(raizGrafo,v);

		for (unsigned int i = 0; i < v.size(); i++) {
			std::cout << v[i] << '\n';
		}

	}

	bool Experto::preguntaBasicaHijos(std::string elemento1, std::string relacion, std::string elemento2) {
		NodoGrafo* n = buscaNodoGrafo(elemento1,raizGrafo);
		if (n != NULL) {
			return existeLaRelacionSimple(relacion,n,elemento2);
		}
		return false;
	}


	std::vector <std::string> Experto::preguntaBasicaTodosLosHijos(std::string elemento, std::string relacion) {
		NodoGrafo* n = buscaNodoGrafo(elemento,raizGrafo);
		std::vector <std::string> hijos;
		hijos.clear();
		if (n != NULL) {
			hijos = todosLosHijos(relacion, n);
			return hijos;
		}
		return hijos;
	}

	bool Experto::preguntaBasicaHereditaria(std::string elemento1, std::string relacion, std::string elemento2) {
		NodoGrafo* n = buscaNodoGrafo(elemento1, raizGrafo);
		if (n != NULL) {
			return existeLaRelacionHereditaria(relacion,n,elemento2);
		}
		return false;
	}

	

	void Experto::generaGraficoRedSemantica() {
		generaGraficoGrafo(raizGrafo);
	}

	void Experto::generaGrafico()
	{
		std::string tipoEncadenamiento = "backward";
		generaGraficoArbol(raiz, tipoEncadenamiento);
	}

	void Experto::generaGrafico(std::string tipoEncadenamiento)
	{
		generaGraficoArbol(raiz, tipoEncadenamiento);
	}

}