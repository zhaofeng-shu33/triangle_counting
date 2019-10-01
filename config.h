#if SMARTGRAPH
    #include <lemon/smart_graph.h>
#else
    #include <lemon/static_graph.h>
#endif
using namespace lemon;
#if SMARTGRAPH
    typedef SmartGraph Graph;
#else
    typedef StaticDigraph Graph;
#endif