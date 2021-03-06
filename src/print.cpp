//
// Created by alex on 30/09/16.
//

#include "string"
#include "iomanip"
#include "sstream"
#include "graph_ir.h"

namespace md{
    namespace gir{
        std::string to_string(Precision const precision) {
            switch (precision){
                case p8: return "p8";
                case p16: return "p16";
                case p32: return "p32";
                default: return "p64";
            }
        }

        std::string to_string(DataType const data_type) {
            switch (data_type.type){
                case BOOLEAN: return "b8";
                case UNSIGNED_INT: switch (data_type.precision){
                        case p8 : return "u8";
                        case p16 : return "u16";
                        case p32 : return "u32";
                        default: return "u64";
                    };
                case SIGNED_INT: switch (data_type.precision){
                        case p8 : return "i8";
                        case p16 : return "i16";
                        case p32 : return "i32";
                        default: return "i64";
                    }
                case FLOAT: switch (data_type.precision){
                        case p8 : return "f8";
                        case p16 : return "f16";
                        case p32 : return "f32";
                        default: return "f64";
                    }
                default: switch (data_type.precision){
                        case p8 : return "c8";
                        case p16 : return "c16";
                        case p32 : return "c32";
                        default: return "c64";
                    }
            }
        }

        std::string to_string(DeviceType const device_type) {
            switch (device_type){
                case CPU: return "CPU";
                default: return "GPU";
//                case GPU: return "GPU";
            }
        }

        std::string to_string(Policy const policy) {
            switch (policy){
                case QUIET: return "Quiet";
                case WARN: return "Warn";
                default: return "Raise";
//                case RAISE: return "Raise";
            }
        }

        std::string to_string(Device const device){
            return fmt::format("{}[{}]", to_string(device.type), device.id);
        }

        std::string to_string(Shape const shape){
            return "(" + sym::to_string(shape[0], backend::print_str) + "," +
                   sym::to_string(shape[1], backend::print_str) + "," +
                   sym::to_string(shape[2], backend::print_str) + "," +
                   sym::to_string(shape[3], backend::print_str) + ")";
        }

        std::string to_string(Node const node){
            std::string s = fmt::format("Node[{},{}]{} = {}(", node->id,
                                        to_string(node->data_type),
                                        to_string(node->shape), node->op->name);
            auto ancestors = node->op->get_ancestors();
            if(ancestors.size() > 0) {
                s += std::to_string(ancestors[0]->id);
            }
            for(auto i=1; i< ancestors.size(); ++i){
                s += ", " + std::to_string(ancestors[i]->id);
            }
            return s + ")";
//            ss << "|"  << std::setw(4) << node->id << "|"
//               << int(node->is_input_dependent) << int(node->is_differentiable) << "|"
//               << std::setw(20) << node->shape << "|" << node->data_type << "|" << node->op->name;
        }

        std::string to_string(NodeVec const & nodes){
            std::stringstream ss;
            for (size_t i = 0; i < nodes.size(); i++) {
                ss << nodes[i];
                if (i < nodes.size() - 1) {
                    ss << std::endl;
                }
            }
            return ss.str();
        }
    }
}

