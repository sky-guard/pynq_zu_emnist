#include <iostream>

#include "PYNQ_ZU_EMNIST.h"
#include "parameters.h"


void PYNQ_ZU_EMNIST(
    input_t global_in[28*28*1],
    result_t layer78_out[26]
) {

    // hls-fpga-machine-learning insert IO
    #pragma HLS ARRAY_RESHAPE variable=global_in complete dim=0
    #pragma HLS ARRAY_PARTITION variable=layer78_out complete dim=0
    #pragma HLS INTERFACE ap_vld port=global_in,layer78_out 
    #pragma HLS DATAFLOW

    // hls-fpga-machine-learning insert load weights
#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        nnet::load_weights_from_txt<weight79_t, 144>(w79, "w79.txt");
        nnet::load_weights_from_txt<bias79_t, 16>(b79, "b79.txt");
        nnet::load_weights_from_txt<weight80_t, 4608>(w80, "w80.txt");
        nnet::load_weights_from_txt<bias80_t, 32>(b80, "b80.txt");
        nnet::load_weights_from_txt<weight77_t, 25088>(w77, "w77.txt");
        nnet::load_weights_from_txt<bias77_t, 16>(b77, "b77.txt");
        nnet::load_weights_from_txt<weight78_t, 416>(w78, "w78.txt");
        nnet::load_weights_from_txt<bias78_t, 26>(b78, "b78.txt");
        loaded_weights = true;    }
#endif
    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

    layer71_t layer71_out[28*28*1];
    #pragma HLS ARRAY_PARTITION variable=layer71_out complete dim=0

    Conv2D_Conv_0_result_t layer79_out[28*28*16];
    #pragma HLS ARRAY_PARTITION variable=layer79_out complete dim=0

    layer57_t layer57_out[28*28*16];
    #pragma HLS ARRAY_PARTITION variable=layer57_out complete dim=0

    layer59_t layer59_out[14*14*16];
    #pragma HLS ARRAY_PARTITION variable=layer59_out complete dim=0

    Conv2D_Conv_1_result_t layer80_out[14*14*32];
    #pragma HLS ARRAY_PARTITION variable=layer80_out complete dim=0

    layer61_t layer61_out[14*14*32];
    #pragma HLS ARRAY_PARTITION variable=layer61_out complete dim=0

    layer63_t layer63_out[7*7*32];
    #pragma HLS ARRAY_PARTITION variable=layer63_out complete dim=0

    auto& layer64_out = layer63_out;
    Dense_MatMul_0_result_t layer77_out[16];
    #pragma HLS ARRAY_PARTITION variable=layer77_out complete dim=0

    layer67_t layer67_out[16];
    #pragma HLS ARRAY_PARTITION variable=layer67_out complete dim=0

    nnet::linear<input_t, layer71_t, linear_config71>(global_in, layer71_out); // Quant_8_act

    nnet::conv_2d_cl<layer71_t, Conv2D_Conv_0_result_t, config79>(layer71_out, layer79_out, w79, b79); // Conv2D_Conv_0

    nnet::relu<Conv2D_Conv_0_result_t, layer57_t, ReLU_config57>(layer79_out, layer57_out); // Relu_0

    nnet::pooling2d_cl<layer57_t, layer59_t, config59>(layer57_out, layer59_out); // MaxPool_0

    nnet::conv_2d_cl<layer59_t, Conv2D_Conv_1_result_t, config80>(layer59_out, layer80_out, w80, b80); // Conv2D_Conv_1

    nnet::relu<Conv2D_Conv_1_result_t, layer61_t, ReLU_config61>(layer80_out, layer61_out); // Relu_1

    nnet::pooling2d_cl<layer61_t, layer63_t, config63>(layer61_out, layer63_out); // MaxPool_1

    nnet::dense<layer63_t, Dense_MatMul_0_result_t, config77>(layer64_out, layer77_out, w77, b77); // Dense_MatMul_0

    nnet::relu<Dense_MatMul_0_result_t, layer67_t, ReLU_config67>(layer77_out, layer67_out); // Relu_2

    nnet::dense<layer67_t, result_t, config78>(layer67_out, layer78_out, w78, b78); // Dense_MatMul_1

}

