//
// Created by alex on 11/10/16.
//

#ifndef METADIFF_CORE_OPERATORS_SPECIAL_H
#define METADIFF_CORE_OPERATORS_SPECIAL_H

namespace md{
    namespace core{
        namespace op{
            class Cast : public UnaryOperator {
            public:
                dataType data_type;

                Cast(GraphInPtr graph, Node parent, dataType data_type) :
                        UnaryOperator("Cast", graph, parent),
                        data_type(data_type) {};

                dataType get_data_type() const {
                    return data_type;
                };

                Operator copy_to(GraphInPtr graph, NodeVec ancestors) const {
                    return std::make_shared<Cast>(graph, ancestors[0], data_type);
                }

                Node get_parent_grad(Node my_grad, short index) {
                    return graph->cast(my_grad, parent->data_type);
                }

                bool equals(Operator const op) const {
//                    if (name == op->name) {
//                        auto cast_op = std::static_pointer_cast<const Cast>(op);
//                        return symbolic_equals(parent, cast_op->parent) and data_type == cast_op->data_type;
//                    }
                    return false;
                }
            };

            /**
             * Represents an alias for another node
             * This could be particularly useful for multiple device case
             * where an Alias with another device would mean a transfer
             */
            class Alias : public UnaryOperator {
            public:
                Alias(GraphInPtr graph, Node parent) :
                        UnaryOperator("Alias", graph, parent) {};

                Operator copy_to(GraphInPtr graph, NodeVec ancestors) const {
                    return std::make_shared<Alias>(graph, ancestors[0]);
                }

                Node get_parent_grad(Node my_grad, short index) {
                    return my_grad;
                }

                bool equals(Operator const op) const {
//                    Operator my_op = get_base_op(parent->op);
//                    return my_op->equals(op) or op->equals(my_op);
                    return false;
                }
            };

            /** Broadcasts the parent to the specified shape */
            class Broadcast : public UnaryOperator {
            public:
                Shape to_shape;

                Broadcast(GraphInPtr graph,
                          Node parent,
                          Shape to_shape) :
                        UnaryOperator("Broadcast", graph, parent),
                        to_shape(to_shape) {
                    for (int i = 0; i < 4; i++) {
                        if (parent->shape[i] != 1 and parent->shape[i] != to_shape[i]) {
                            auto err = std::make_shared<InvalidArguments>
                                    (NodeVec{parent}, name, "Can not broadcast to shape " +
                                                            core::to_string(to_shape));
                            err->log(logger());
                            throw err;
                        }
                    }
                }

                Operator copy_to(GraphInPtr graph, NodeVec ancestors) const {
                    return std::make_shared<Broadcast>(graph, ancestors[0], to_shape);
                }

                Shape get_shape() const {
                    return to_shape;
                }

                Axes get_broadcast_axes() const {
                    Axes axes;
                    auto p1_shape = this->parent->shape;
                    for (size_t i = 0; i < 4; i++) {
                        if (p1_shape[i] != to_shape[i]) {
                            axes.push_back(i);
                        }
                    }
                    return axes;
                }

                Node get_parent_grad(Node my_grad, short index) {
                    return graph->sum(my_grad, get_broadcast_axes());
                }

                bool equals(Operator const op) const {
//                    if (name == op->name) {
//                        auto cast_op = std::static_pointer_cast<const Broadcast>(op);
//                        return symbolic_equals(parent, cast_op->parent) and to_shape == cast_op->to_shape;
//                    }
                    return false;
                }
            };
        }
    }
}
#endif //METADIFF_CORE_OPERATORS_SPECIAL_H