#ifndef Grafo_H
#define Grafo_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>  

#include <queue>

namespace ExpertoLib {

    struct NodoGrafo
    {
        std::string valor;
        std::vector<std::string> arco;
        std::vector<NodoGrafo*> hijo;
        bool apuntaAPadre = false;
    };

    NodoGrafo* nuevoNodoGrafo(std::string valor)
    {
        NodoGrafo* temp = new NodoGrafo;
        temp->valor = valor;
        return temp;
    }

    /*NodoGrafo* buscaNodoGrafo(std::string valor, NodoGrafo* nodo)
    {
        std::cout << nodo->valor << " el nodo raiz \n";
        if (valor == nodo->valor) {
            return nodo;
        }
        for (unsigned int i = 0; i < (nodo->hijo.size()); i++) {
            NodoGrafo* temp = NULL;
            if (!(nodo->hijo[i]->apuntaAPadre)) {
                temp = buscaNodoGrafo(valor, (nodo->hijo[i]));
            }
            if (temp != NULL) {
                return temp;
            }
        }
        return NULL;
    }*/

    NodoGrafo* buscaNodoGrafo(std::string valor, NodoGrafo* nodo)
    {
        //std::cout << nodo->valor << " el nodo raiz \n";
        if (valor == nodo->valor) {
            return nodo;
        }
        for (unsigned int i = 0; i < nodo->hijo.size(); i++) {
            NodoGrafo* temp = NULL;
            if (nodo->hijo[i]->hijo.size() > 0) {
                bool conectadoConPadre = false;
                for (unsigned int j = 0; j < nodo->hijo[i]->hijo.size(); j++) {
                    if (nodo->hijo[i]->hijo[j]->valor == nodo->valor && nodo->hijo[i]->arco[j] == nodo->arco[i]) {
                        conectadoConPadre = true;
                    }
                }
                if (!conectadoConPadre) {
                    temp = buscaNodoGrafo(valor,nodo->hijo[i]);
                }
                if (temp != NULL) {
                    return temp;
                }
            }
            else {
                temp = buscaNodoGrafo(valor, nodo->hijo[i]);
                if (temp != NULL) {
                    return temp;
                }
            }

        }
        return NULL;
    }


    bool existeLaRelacionHereditaria(std::string nombreArco, NodoGrafo* ng, std::string elemento) {
        std::vector <int> posiciones;
        posiciones.clear();
        if (ng->valor == elemento) {
            return true;
        }
        for (unsigned int i = 0; i < ng->arco.size(); i++) {
            if (ng->arco[i] == nombreArco) {
                posiciones.push_back(i);
            }
        }
        if (posiciones.size() > 0) {
            for (unsigned int i = 0; i < posiciones.size();i++) {
                return existeLaRelacionHereditaria(nombreArco,ng->hijo[posiciones[i]],elemento);
            }
        }
        return false;
    }

    bool existeLaRelacionSimple(std::string nombreArco, NodoGrafo* ng, std::string elemento) {
        std::vector <int> posiciones;
        posiciones.clear();
        if (ng->valor == elemento) {
            return true;
        }
        for (unsigned int i = 0; i < ng->arco.size();i++) {
            if (ng->arco[i] == nombreArco) {
                posiciones.push_back(i);
            }
        }
        if (posiciones.size() > 0) {           
            for (unsigned int x = 0; x < posiciones.size(); x++) {              
                if (ng->hijo[posiciones[x]]->valor == elemento) {
                    return true;
                }
            }
            return false;
        }
        else {
            //arreglar acá
            return false;
        }
    }

    std::vector <std::string> todosLosHijos(std::string nombreArco, NodoGrafo* ng) {
        std::vector <int> posiciones;
        std::vector <std::string> hijos;
        hijos.clear();
        posiciones.clear();
        for (unsigned int i = 0; i < ng->arco.size(); i++) {
            if (ng->arco[i] == nombreArco) {
                posiciones.push_back(i);
            }
        }
        if (posiciones.size() > 0) {
            for (unsigned int x = 0; x < posiciones.size(); x++) {
                hijos.push_back(ng->hijo[posiciones[x]]->valor);
            }
            return hijos;
        }
        else {
            //arreglar acá
            return hijos;
        }
    }

    void insertaANodoGrafo(NodoGrafo* Padre, NodoGrafo* Hijo, NodoGrafo* raizGrafo, std::string arco, bool apuntaAPadre) {
        bool nodoPosicionado = false;
        for (unsigned int i = 0; i < (raizGrafo->hijo).size(); i++) {
            if (nodoPosicionado == false) {
                if (raizGrafo->hijo[i]->valor == Padre->valor) {
                    (raizGrafo->hijo[i]->arco).push_back(arco);
                    (raizGrafo->hijo[i]->hijo).push_back(Hijo);
                    Padre->apuntaAPadre = apuntaAPadre;
                    nodoPosicionado = true;
                }
                else {
                    if(!(raizGrafo->hijo[i]->apuntaAPadre)){
                        insertaANodoGrafo(Padre,Hijo,raizGrafo->hijo[i],arco, apuntaAPadre);
                    }
                }
            }
        }
    }

    bool estaEnElVector(std::string valor, std::vector<std::string> valores) {
        std::vector<std::string>::iterator it = std::find(valores.begin(), valores.end(), valor);
        if (it != valores.end()) {
            return true;
        }
        return false;
    }

    std::vector<std::string> buscarValores(NodoGrafo* p, std::vector<std::string> v) {
        std::vector<std::string> valores = v;
        std::vector<std::string> valoresAux;
        if (!estaEnElVector(p->valor,valores) && p->valor != "Raiz") {
            
            valores.push_back(p->valor);
        }
        for (unsigned int i = 0; i < p->hijo.size();i++) {
            if (p->hijo[i]->hijo.size() > 0) {
                bool conectadoConPadre = false;
                for (unsigned int j = 0; j < p->hijo[i]->hijo.size(); j++) {
                    if (p->hijo[i]->hijo[j]->valor == p->valor && p->hijo[i]->arco[j] == p->arco[i]) {
                        conectadoConPadre = true;
                    }
                }
                if (!conectadoConPadre) {
                    valoresAux = buscarValores(p->hijo[i], valores);
                    if (valores.size() != valoresAux.size()) {
                        for (unsigned int i = valores.size(); i < valoresAux.size(); i++) {
                            valores.push_back(valoresAux[i]);
                        }
                    }
                }
            }
            else {
                valoresAux = buscarValores(p->hijo[i], valores);
                if (valores.size() != valoresAux.size()) {
                    for (unsigned int i = valores.size(); i < valoresAux.size(); i++) {
                        valores.push_back(valoresAux[i]);
                    }
                }
            }
            
        }
        return valores;  
    }

    std::vector<std::string> buscarValoresArcos(NodoGrafo* p, std::vector<std::string> v) {
        std::vector<std::string> valores = v;
        std::vector<std::string> valoresAux;
        for (unsigned int i = 0; i < p->arco.size();i++) {
            if (!estaEnElVector(p->arco[i], valores)) {

                valores.push_back(p->arco[i]);
            }
        }
        
        for (unsigned int i = 0; i < p->hijo.size(); i++) {
            if (p->hijo[i]->hijo.size() > 0) {
                bool conectadoConPadre = false;
                for (unsigned int j = 0; j < p->hijo[i]->hijo.size(); j++) {
                    if (p->hijo[i]->hijo[j]->valor == p->valor && p->hijo[i]->arco[j] == p->arco[i]) {
                        conectadoConPadre = true;
                    }
                }
                if (!conectadoConPadre) {
                    valoresAux = buscarValoresArcos(p->hijo[i], valores);
                    if (valores.size() != valoresAux.size()) {
                        for (unsigned int i = valores.size(); i < valoresAux.size(); i++) {
                            valores.push_back(valoresAux[i]);
                        }
                    }
                }
            }
            else {
                valoresAux = buscarValoresArcos(p->hijo[i], valores);
                if (valores.size() != valoresAux.size()) {
                    for (unsigned int i = valores.size(); i < valoresAux.size(); i++) {
                        valores.push_back(valoresAux[i]);
                    }
                }
            }

        }
        return valores;
    }

    

    void recorreGrafo(NodoGrafo* p, std::ofstream& outfile)
    {
        char comilla = '"';
        std::string padre = p->valor;
        for (unsigned int i = 0; i < p->hijo.size(); i++)
        {
            if (padre != "Raiz") {
                outfile << comilla << padre << comilla << "->";
                outfile << comilla << p->hijo[i]->valor << comilla << std::endl;
                if ((p->arco).size() > 0) {
                    outfile << "[label = " << comilla << p->arco[i] << comilla << "];" << std::endl;
                }
            }
            if (p->hijo[i]->hijo.size() > 0) {
                bool conectadoConPadre = false;
                for (unsigned int j = 0; j < p->hijo[i]->hijo.size(); j++) {
                    if (p->hijo[i]->hijo[j]->valor == padre && p->hijo[i]->arco[j] == p->arco[i]) {
                        conectadoConPadre = true;              
                    }
                }
                if (!conectadoConPadre) {
                    recorreGrafo(p->hijo[i], outfile);
                }
            }
            else {
                recorreGrafo(p->hijo[i], outfile);
            }
            
        }
    }



    void generaGraficoGrafo(NodoGrafo* raiz)
    {
        if (!raiz)
            return;
        char comilla = '"';
        std::ofstream outfile("red_semantica.dot");
        outfile << "strict digraph G {" << std::endl;
        outfile << "rankdir = LR;" << std::endl;
        outfile << "graph [ordering=" << comilla << "out" << comilla << "];" << std::endl;
        outfile << "graph [ranksep=" << comilla << "1.5" << comilla << "];" << std::endl;
        recorreGrafo(raiz, outfile);
        outfile << "}" << std::endl;
        outfile.close();
    }

}

#endif
