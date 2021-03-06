//
// Created by alex on 03/05/16.
//

#ifndef METADIFF_GRAPH_IR_OPERATORS_INPUT_H
#define METADIFF_GRAPH_IR_OPERATORS_INPUT_H

namespace md {
    namespace gir {
        namespace op {
            /** Input variables */
            class Input : public InputOperator {
            public:
                DataType  data_type;
                Shape shape;

                Input(GraphInPtr graph, DataType data_type, Shape shape) :
                        AbstractOperator(graph, "Input"),
                        data_type(data_type), shape(shape) {}

                Operator copy_to(GraphInPtr graph, std::vector<Node> ancestors) const {
                    return std::make_shared<Input>(graph, data_type, shape);
                }

                DataType get_data_type() const {
                    return data_type;
                }

                Shape get_shape() const {
                    return shape;
                }
            };

            /** Parameter variables */
            class Parameter : public InputOperator {
            public:
                std::string full_name;
                DataType data_type;
                Shape shape;


                Parameter(GraphInPtr graph, std::string full_name, DataType data_type, Shape shape) :
                        AbstractOperator(graph, "Parameter"),
                        full_name(full_name), data_type(data_type), shape(shape) {}

                Operator copy_to(GraphInPtr graph, NodeVec ancestors) const {
                    return std::make_shared<Parameter>(graph, full_name, data_type, shape);
                }

                DataType get_data_type() const {
                    return data_type;
                }

                Shape get_shape() const {
                    return shape;
                }

//                bool equals(Operator const op) const {
//                    if (name == op->name) {
//                        auto cast_op = std::static_pointer_cast<const SharedInput>(op);
//                        return var->id == cast_op->var->id;
//                    }
//                    return false;
//                }
            };
        }
    }
}
#endif //METADIFF_GRAPH_IR_OPERATORS_H
