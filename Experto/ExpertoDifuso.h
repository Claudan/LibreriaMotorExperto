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
        void agregaVariable(std::string nombre);
        void testDifuso();
    };

}

#endif

