#ifndef ExpertoDifuso_H
#define ExpertoDifuso_H

#include <fl/Headers.h>

using namespace fl;

namespace ExpertoLib {

    class ExpertoDifuso
    {
    private:
        Engine* engine = new Engine;

    public:
        ExpertoDifuso();
        void testDifuso();
    };

}

#endif

