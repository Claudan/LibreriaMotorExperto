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
        //void InfiereRedSemantica();
        void generaGrafico();
        void generaGrafico(std::string tipoEncadenamiento);
        void generaGraficoRedSemantica();
    };

}

#endif

