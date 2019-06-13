#ifndef NODE_H
#define NODE_H

namespace music
{
    class Node 
    {
        public:
            virtual ~Node() {}
            virtual void EventNode() = 0;
            virtual void DrawNode() = 0;
    };
}

#endif //NODE_H