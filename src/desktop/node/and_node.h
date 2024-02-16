#ifndef ONIKEISO_AND_NODE_H
#define ONIKEISO_AND_NODE_H

#include "node.h"

namespace onik {
    using Vec2f = bebone::core::Vec2f;

    class AndNode : public Node {
        private:

        public:
            AndNode() { make_and_gate(this); }
    };
};

#endif