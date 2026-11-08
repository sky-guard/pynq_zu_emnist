#include <iostream>

#include "PYNQ_ZU_EMNIST.h"
#include "parameters.h"


void PYNQ_ZU_EMNIST(
    hls::stream<input_t> &global_in,
    hls::stream<result_t> &layer78_out
) {

    // hls-fpga-machine-learning insert IO
    #pragma HLS INTERFACE axis port=global_in,layer78_out 
    #pragma HLS DATAFLOW

    // hls-fpga-machine-learning insert load weights
#ifndef __SYNTHESIS__
    static bool loaded_weights = false;
    if (!loaded_weights) {
        nnet::load_weights_from_txt<weight79_t, 72>(w79, "w79.txt");
        nnet::load_weights_from_txt<bias79_t, 8>(b79, "b79.txt");
        nnet::load_weights_from_txt<weight80_t, 288>(w80, "w80.txt");
        nnet::load_weights_from_txt<bias80_t, 4>(b80, "b80.txt");
        nnet::load_weights_from_txt<weight77_t, 3136>(w77, "w77.txt");
        nnet::load_weights_from_txt<bias77_t, 16>(b77, "b77.txt");
        nnet::load_weights_from_txt<weight78_t, 416>(w78, "w78.txt");
        nnet::load_weights_from_txt<bias78_t, 26>(b78, "b78.txt");
        loaded_weights = true;    }
#endif
    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    // hls-fpga-machine-learning insert layers

    hls::stream<layer54_t> layer54_out("layer54_out");
    #pragma HLS STREAM variable=layer54_out depth=784

    hls::stream<layer71_t> layer71_out("layer71_out");
    #pragma HLS STREAM variable=layer71_out depth=784

    hls::stream<layer81_t> layer81_out("layer81_out");
    #pragma HLS STREAM variable=layer81_out depth=900

    hls::stream<Conv2D_Conv_0_result_t> layer79_out("layer79_out");
    #pragma HLS STREAM variable=layer79_out depth=784

    hls::stream<layer57_t> layer57_out("layer57_out");
    #pragma HLS STREAM variable=layer57_out depth=784

    hls::stream<layer59_t> layer59_out("layer59_out");
    #pragma HLS STREAM variable=layer59_out depth=196

    hls::stream<layer82_t> layer82_out("layer82_out");
    #pragma HLS STREAM variable=layer82_out depth=256

    hls::stream<Conv2D_Conv_1_result_t> layer80_out("layer80_out");
    #pragma HLS STREAM variable=layer80_out depth=196

    hls::stream<layer61_t> layer61_out("layer61_out");
    #pragma HLS STREAM variable=layer61_out depth=196

    hls::stream<layer63_t> layer63_out("layer63_out");
    #pragma HLS STREAM variable=layer63_out depth=49

    auto& layer64_out = layer63_out;
    hls::stream<Dense_MatMul_0_result_t> layer77_out("layer77_out");
    #pragma HLS STREAM variable=layer77_out depth=1

    hls::stream<layer67_t> layer67_out("layer67_out");
    #pragma HLS STREAM variable=layer67_out depth=1

    nnet::transpose<input_t, layer54_t, config54>(global_in, layer54_out); // Transpose_0

    nnet::linear<layer54_t, layer71_t, linear_config71>(layer54_out, layer71_out); // Quant_8_act

    nnet::zeropad2d_cl<layer71_t, layer81_t, config81>(layer71_out, layer81_out); // zp2d_Conv2D_Conv_0

    nnet::conv_2d_cl<layer81_t, Conv2D_Conv_0_result_t, config79>(layer81_out, layer79_out, w79, b79); // Conv2D_Conv_0

    nnet::relu<Conv2D_Conv_0_result_t, layer57_t, ReLU_config57>(layer79_out, layer57_out); // Relu_0

    nnet::pooling2d_cl<layer57_t, layer59_t, config59>(layer57_out, layer59_out); // MaxPool_0

    nnet::zeropad2d_cl<layer59_t, layer82_t, config82>(layer59_out, layer82_out); // zp2d_Conv2D_Conv_1

    nnet::conv_2d_cl<layer82_t, Conv2D_Conv_1_result_t, config80>(layer82_out, layer80_out, w80, b80); // Conv2D_Conv_1

    nnet::relu<Conv2D_Conv_1_result_t, layer61_t, ReLU_config61>(layer80_out, layer61_out); // Relu_1

    nnet::pooling2d_cl<layer61_t, layer63_t, config63>(layer61_out, layer63_out); // MaxPool_1

    nnet::dense<layer63_t, Dense_MatMul_0_result_t, config77>(layer64_out, layer77_out, w77, b77); // Dense_MatMul_0

    nnet::relu<Dense_MatMul_0_result_t, layer67_t, ReLU_config67>(layer77_out, layer67_out); // Relu_2

    nnet::dense<layer67_t, result_t, config78>(layer67_out, layer78_out, w78, b78); // Dense_MatMul_1

}

