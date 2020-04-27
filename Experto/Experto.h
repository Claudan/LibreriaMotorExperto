#ifndef Experto_H
#define Experto_H

#include "ArbolDinamico.h"
#include "Grafo.h"
#include "Regla.h"
#include "ReglaSemantica.h"

namespace ExpertoLib{

	class Experto
	{
    private:
        Nodo* raiz;
        NodoGrafo* raizGrafo;

    public:
        Experto();
        void insertaRegla(Regla nuevaRegla);
        void insertaReglaForward(Regla nuevaRegla);
        void insertaReglaSemantica(ReglaSemantica nuevaRegla);
        void infiereBackwardChaining();
        void infiereForwardChaining();
        std::vector<std::vector<std::string>> infiereTodasLasSolucionesBC(std::vector<std::string> input);
        //void InfiereRedSemantica();
        void mostrarValores();
        bool preguntaBasicaHijos(std::string elemento1, std::string relacion, std::string elemento2);
        bool preguntaBasicaHereditaria(std::string elemento1, std::string relacion, std::string elemento2);
        std::vector <std::string> preguntaBasicaTodosLosHijos(std::string elemento,std::string relacion);
        void generaGrafico();
        void generaGrafico(std::string tipoEncadenamiento);
        void generaGraficoRedSemantica();
    };

}

#endif

