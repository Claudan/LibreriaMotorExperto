#ifndef ExpertoDifuso_H
#define ExpertoDifuso_H

#include <fl/Headers.h>

using namespace fl;

namespace ExpertoLib {

    class ExpertoDifuso
    {
    private:
        Engine* engine = new Engine;
        std::vector<InputVariable> variablesEntrada;
        std::vector<OutputVariable> variablesSalida;

    public:
        ExpertoDifuso();
        void insertaReglas(std::vector<std::string> reglasDifusas);
        void agregaVariableEntrada(InputVariable* entrada);
        void agregaVariableSalida(OutputVariable* salida);
        Engine* getEngine();
    };

}

#endif

