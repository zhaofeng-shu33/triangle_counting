#if SMARTGRAPH
    #include <lemon/smart_graph.h>
#else
    #include <lemon/list_graph.h>
#endif
using namespace lemon;
#if SMARTGRAPH
    typedef SmartGraph Graph;
#else
    typedef ListGraph Graph;
#endif