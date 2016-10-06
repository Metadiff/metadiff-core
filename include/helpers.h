//
// Created by alex on 06/10/16.
//

#ifndef METADIFF_CORE_HELPERS_H
#define METADIFF_CORE_HELPERS_H

namespace md{
    namespace core{
        /**
         * Calculates the total number of elements given the shape
         * @param shape
         * @return
         */
        SymInt elements_number(Shape const shape);

        /**
         * Skips any alias operators to get the base operator
         */
        Operator get_base_op(Operator const op);

        /**
          * Helper function to validate axes argument
          * Checks if each axes is a distinct integer between [0,3]
          */
        bool validate_axes(Axes axes);

        /**
         * Helper function to verify shapes of elementwise operators
         * Verifies that the shapes of the inputs are equal
         */
        Shape verify_elementwise_shapes(NodeVec nodes);

        /**
         * Tries to evaluate that two nodes are symbolically equals
         */
        bool symbolic_equals(Node const & node1, Node const & node2);
    }
}
#endif //METADIFF_CORE_HELPERS_H