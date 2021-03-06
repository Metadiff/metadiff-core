//
// Created by alex on 19/10/16.
//

#include "graph_ir.h"

namespace md{
    namespace gir{

        Node GraphInternal::gemm(NodeVec nodes, std::vector<bool> transpositions){
            // TODO check if some of them is not inverse to each other
            for(auto i=0; i < nodes.size(); ++i){
                nodes[i] = get_base_node(nodes[i]);
            }
            // Standard
            auto op = std::make_shared<op::MatrixMul>(this, nodes, transpositions);
            return derived_node(op);
        }

        Node GraphInternal::dot(Node left, Node right, bool transpose_left, bool transpose_right){
            return gemm({left, right}, {transpose_left, transpose_right});
        }

        Node GraphInternal::matrix_inverse(Node node){
            // inv(inv(x)) = x
            auto base = get_base_node(node);
            if(base->op->name == "MatrixInv"){
                return api::alias(base->op->get_parents()[0]);
            }
            // Standard
            return apply<op::MatrixInverse>(node);
        }

        Node GraphInternal::matrix_inverse_mul(Node node1, Node node2, bool transpose){
            // inv(inv(x)) = x
            Operator op = std::make_shared<op::MatrixInverseMul>(this, node1, node2, transpose);
            return derived_node(op);
        }

        Node GraphInternal::determinant(Node node){
            // If scalar do nothing
            if(node.order() == 0){
                return api::alias(node);
            }
            // Standard
            return apply<op::Determinant>(node);
        }

        Node GraphInternal::log_det(Node node){
            // If scalar return just the log
            if(node.order() == 0){
                return log(node);
            }
            // Standard
            return apply<op::LogDeterminant>(node);
        }

        Node GraphInternal::trace(Node node){
            // If scalar do nothing
            if(node.order() == 0){
                return api::alias(node);
            }
            // Standard
            return apply<op::Trace>(node);
        }
    }
}