#ifndef DEFINES_H_
#define DEFINES_H_

#include "ap_fixed.h"
#include "ap_int.h"
#include "nnet_utils/nnet_types.h"
#include <array>
#include <cstddef>
#include <cstdio>
#include <tuple>
#include <tuple>


// hls-fpga-machine-learning insert numbers

// hls-fpga-machine-learning insert layer-precision
typedef ap_fixed<16,6> input_t;
typedef ap_ufixed<8,2,AP_RND_CONV,AP_SAT,0> layer71_t;
typedef ap_fixed<18,8> Quant_8_act_table_t;
typedef ap_fixed<21,9> Conv2D_Conv_0_accum_t;
typedef ap_fixed<21,9> Conv2D_Conv_0_result_t;
typedef ap_fixed<8,2,AP_RND_CONV,AP_SAT_SYM,0> weight79_t;
typedef ap_fixed<8,-1,AP_RND_CONV,AP_SAT,0> bias79_t;
typedef ap_ufixed<8,1,AP_RND_CONV,AP_SAT,0> layer57_t;
typedef ap_fixed<18,8> Relu_0_table_t;
typedef ap_ufixed<8,1,AP_RND_CONV,AP_SAT,0> MaxPool_0_accum_t;
typedef ap_ufixed<8,1,AP_RND_CONV,AP_SAT,0> layer59_t;
typedef ap_fixed<24,10> Conv2D_Conv_1_accum_t;
typedef ap_fixed<24,10> Conv2D_Conv_1_result_t;
typedef ap_fixed<8,1,AP_RND_CONV,AP_SAT_SYM,0> weight80_t;
typedef ap_fixed<8,0,AP_RND_CONV,AP_SAT,0> bias80_t;
typedef ap_ufixed<8,2,AP_RND_CONV,AP_SAT,0> layer61_t;
typedef ap_fixed<18,8> Relu_1_table_t;
typedef ap_ufixed<8,2,AP_RND_CONV,AP_SAT,0> MaxPool_1_accum_t;
typedef ap_ufixed<8,2,AP_RND_CONV,AP_SAT,0> layer63_t;
typedef ap_fixed<25,13> Dense_MatMul_0_accum_t;
typedef ap_fixed<25,13> Dense_MatMul_0_result_t;
typedef ap_fixed<8,2,AP_RND_CONV,AP_SAT_SYM,0> weight77_t;
typedef ap_fixed<8,4,AP_RND_CONV,AP_SAT,0> bias77_t;
typedef ap_uint<1> layer77_index;
typedef ap_ufixed<8,5,AP_RND_CONV,AP_SAT,0> layer67_t;
typedef ap_fixed<18,8> Relu_2_table_t;
typedef ap_fixed<21,12> Dense_MatMul_1_accum_t;
typedef ap_fixed<21,12> result_t;
typedef ap_fixed<8,2,AP_RND_CONV,AP_SAT_SYM,0> weight78_t;
typedef ap_fixed<8,4,AP_RND_CONV,AP_SAT,0> bias78_t;
typedef ap_uint<1> layer78_index;

// hls-fpga-machine-learning insert emulator-defines


#endif
