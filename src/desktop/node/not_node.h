#ifndef ONIKEISO_NOT_NODE_H
#define ONIKEISO_NOT_NODE_H

#include "node.h"

namespace onik {
    class NotNode : public Node {
        private:

        public:
            NotNode() { make_not_gate(this); }
    };
};

#endif