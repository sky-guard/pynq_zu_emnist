#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "ap_fixed.h"
#include "ap_int.h"

#include "nnet_utils/nnet_code_gen.h"
#include "nnet_utils/nnet_helpers.h"
// hls-fpga-machine-learning insert includes
#include "nnet_utils/nnet_activation.h"
#include "nnet_utils/nnet_activation_stream.h"
#include "nnet_utils/nnet_conv2d.h"
#include "nnet_utils/nnet_conv2d_stream.h"
#include "nnet_utils/nnet_dense.h"
#include "nnet_utils/nnet_dense_compressed.h"
#include "nnet_utils/nnet_dense_stream.h"
#include "nnet_utils/nnet_padding.h"
#include "nnet_utils/nnet_padding_stream.h"
#include "nnet_utils/nnet_pooling.h"
#include "nnet_utils/nnet_pooling_stream.h"
#include "nnet_utils/nnet_transpose.h"
#include "nnet_utils/nnet_transpose_stream.h"

// hls-fpga-machine-learning insert weights
#include "weights/w79.h"
#include "weights/b79.h"
#include "weights/w80.h"
#include "weights/b80.h"
#include "weights/w77.h"
#include "weights/b77.h"
#include "weights/w78.h"
#include "weights/b78.h"


// hls-fpga-machine-learning insert layer-config
// Transpose_0
struct config54 {
    static const unsigned dims = 3;
    static const unsigned N = 784;
    static const unsigned* const from_shape;
    static const unsigned* const to_shape;
    static const unsigned* const perm;
    static const unsigned* const perm_strides;
};

unsigned config54_from_shape[3] = {1, 28, 28};
unsigned config54_to_shape[3] = {28, 28, 1};
unsigned config54_perm[3] = {1, 2, 0};
unsigned config54_perm_strides[3] = {28, 1, 784};

const unsigned* const config54::from_shape = config54_from_shape;
const unsigned* const config54::to_shape = config54_to_shape;
const unsigned* const config54::perm = config54_perm;
const unsigned* const config54::perm_strides = config54_perm_strides;

// Quant_8_act
struct linear_config71 : nnet::activ_config {
    static const unsigned n_in = 784;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 1;
    typedef Quant_8_act_table_t table_t;
};

// zp2d_Conv2D_Conv_0
struct config81 : nnet::padding2d_config {
    static const unsigned in_height = 28;
    static const unsigned in_width = 28;
    static const unsigned n_chan = 1;
    static const unsigned out_height = 30;
    static const unsigned out_width = 30;
    static const unsigned pad_top = 1;
    static const unsigned pad_bottom = 1;
    static const unsigned pad_left = 1;
    static const unsigned pad_right = 1;
};

// Conv2D_Conv_0
struct config79_mult : nnet::dense_config {
    static const unsigned n_in = 9;
    static const unsigned n_out = 8;
    static const unsigned reuse_factor = 1;
    static const unsigned strategy = nnet::resource;
    static const unsigned n_zeros = 28;
    static const unsigned multiplier_limit = DIV_ROUNDUP(n_in * n_out, reuse_factor) - n_zeros / reuse_factor;
    typedef Conv2D_Conv_0_accum_t accum_t;
    typedef bias79_t bias_t;
    typedef weight79_t weight_t;
    template<class data_T, class res_T, class CONFIG_T>
    using kernel = nnet::DenseResource_rf_leq_nin<data_T, res_T, CONFIG_T>;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

struct config79 : nnet::conv2d_config {
    static const unsigned pad_top = 0;
    static const unsigned pad_bottom = 0;
    static const unsigned pad_left = 0;
    static const unsigned pad_right = 0;
    static const unsigned in_height = 30;
    static const unsigned in_width = 30;
    static const unsigned n_chan = 1;
    static const unsigned filt_height = 3;
    static const unsigned filt_width = 3;
    static const unsigned kernel_size = filt_height * filt_width;
    static const unsigned n_filt = 8;
    static const unsigned stride_height = 1;
    static const unsigned stride_width = 1;
    static const unsigned out_height = 28;
    static const unsigned out_width = 28;
    static const unsigned reuse_factor = 1;
    static const unsigned n_zeros = 28;
    static const unsigned multiplier_limit =
        DIV_ROUNDUP(kernel_size * n_chan * n_filt, reuse_factor) - n_zeros / reuse_factor;
    static const bool store_weights_in_bram = false;
    static const unsigned strategy = nnet::resource;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned min_height = 30;
    static const unsigned min_width = 30;
    static const ap_uint<filt_height * filt_width> pixels[min_height * min_width];
    static const unsigned n_partitions = 784;
    static const unsigned n_pixels = out_height * out_width / n_partitions;
    template<class data_T, class CONFIG_T>
    using fill_buffer = nnet::FillConv2DBuffer<data_T, CONFIG_T>;
    typedef Conv2D_Conv_0_accum_t accum_t;
    typedef bias79_t bias_t;
    typedef weight79_t weight_t;
    typedef config79_mult mult_config;
    template<unsigned K, unsigned S, unsigned W>
    using scale_index_height = nnet::scale_index_regular<K, S, W>;
    template<unsigned K, unsigned S, unsigned W>
    using scale_index_width = nnet::scale_index_regular<K, S, W>;
};
const ap_uint<config79::filt_height * config79::filt_width> config79::pixels[] = {0};

// Relu_0
struct ReLU_config57 : nnet::activ_config {
    static const unsigned n_in = 6272;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 1;
    typedef Relu_0_table_t table_t;
};

// MaxPool_0
struct config59 : nnet::pooling2d_config {
    static const unsigned in_height = 28;
    static const unsigned in_width = 28;
    static const unsigned n_filt = 8;
    static const unsigned stride_height = 2;
    static const unsigned stride_width = 2;
    static const unsigned pool_height = 2;
    static const unsigned pool_width = 2;

    static const unsigned filt_height = pool_height;
    static const unsigned filt_width = pool_width;
    static const unsigned n_chan = n_filt;

    static const unsigned out_height = 14;
    static const unsigned out_width = 14;
    static const unsigned pad_top = 0;
    static const unsigned pad_bottom = 0;
    static const unsigned pad_left = 0;
    static const unsigned pad_right = 0;
    static const bool count_pad = false;
    static const nnet::Pool_Op pool_op = nnet::Max;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned reuse_factor = 1;
    typedef MaxPool_0_accum_t accum_t;
};

// zp2d_Conv2D_Conv_1
struct config82 : nnet::padding2d_config {
    static const unsigned in_height = 14;
    static const unsigned in_width = 14;
    static const unsigned n_chan = 8;
    static const unsigned out_height = 16;
    static const unsigned out_width = 16;
    static const unsigned pad_top = 1;
    static const unsigned pad_bottom = 1;
    static const unsigned pad_left = 1;
    static const unsigned pad_right = 1;
};

// Conv2D_Conv_1
struct config80_mult : nnet::dense_config {
    static const unsigned n_in = 72;
    static const unsigned n_out = 4;
    static const unsigned reuse_factor = 1;
    static const unsigned strategy = nnet::resource;
    static const unsigned n_zeros = 108;
    static const unsigned multiplier_limit = DIV_ROUNDUP(n_in * n_out, reuse_factor) - n_zeros / reuse_factor;
    typedef Conv2D_Conv_1_accum_t accum_t;
    typedef bias80_t bias_t;
    typedef weight80_t weight_t;
    template<class data_T, class res_T, class CONFIG_T>
    using kernel = nnet::DenseResource_rf_leq_nin<data_T, res_T, CONFIG_T>;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

struct config80 : nnet::conv2d_config {
    static const unsigned pad_top = 0;
    static const unsigned pad_bottom = 0;
    static const unsigned pad_left = 0;
    static const unsigned pad_right = 0;
    static const unsigned in_height = 16;
    static const unsigned in_width = 16;
    static const unsigned n_chan = 8;
    static const unsigned filt_height = 3;
    static const unsigned filt_width = 3;
    static const unsigned kernel_size = filt_height * filt_width;
    static const unsigned n_filt = 4;
    static const unsigned stride_height = 1;
    static const unsigned stride_width = 1;
    static const unsigned out_height = 14;
    static const unsigned out_width = 14;
    static const unsigned reuse_factor = 1;
    static const unsigned n_zeros = 108;
    static const unsigned multiplier_limit =
        DIV_ROUNDUP(kernel_size * n_chan * n_filt, reuse_factor) - n_zeros / reuse_factor;
    static const bool store_weights_in_bram = false;
    static const unsigned strategy = nnet::resource;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned min_height = 16;
    static const unsigned min_width = 16;
    static const ap_uint<filt_height * filt_width> pixels[min_height * min_width];
    static const unsigned n_partitions = 196;
    static const unsigned n_pixels = out_height * out_width / n_partitions;
    template<class data_T, class CONFIG_T>
    using fill_buffer = nnet::FillConv2DBuffer<data_T, CONFIG_T>;
    typedef Conv2D_Conv_1_accum_t accum_t;
    typedef bias80_t bias_t;
    typedef weight80_t weight_t;
    typedef config80_mult mult_config;
    template<unsigned K, unsigned S, unsigned W>
    using scale_index_height = nnet::scale_index_regular<K, S, W>;
    template<unsigned K, unsigned S, unsigned W>
    using scale_index_width = nnet::scale_index_regular<K, S, W>;
};
const ap_uint<config80::filt_height * config80::filt_width> config80::pixels[] = {0};

// Relu_1
struct ReLU_config61 : nnet::activ_config {
    static const unsigned n_in = 784;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 1;
    typedef Relu_1_table_t table_t;
};

// MaxPool_1
struct config63 : nnet::pooling2d_config {
    static const unsigned in_height = 14;
    static const unsigned in_width = 14;
    static const unsigned n_filt = 4;
    static const unsigned stride_height = 2;
    static const unsigned stride_width = 2;
    static const unsigned pool_height = 2;
    static const unsigned pool_width = 2;

    static const unsigned filt_height = pool_height;
    static const unsigned filt_width = pool_width;
    static const unsigned n_chan = n_filt;

    static const unsigned out_height = 7;
    static const unsigned out_width = 7;
    static const unsigned pad_top = 0;
    static const unsigned pad_bottom = 0;
    static const unsigned pad_left = 0;
    static const unsigned pad_right = 0;
    static const bool count_pad = false;
    static const nnet::Pool_Op pool_op = nnet::Max;
    static const nnet::conv_implementation implementation = nnet::conv_implementation::linebuffer;
    static const unsigned reuse_factor = 1;
    typedef MaxPool_1_accum_t accum_t;
};

// Dense_MatMul_0
struct config77 : nnet::dense_config {
    static const unsigned n_in = 196;
    static const unsigned n_out = 16;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned strategy = nnet::resource;
    static const unsigned reuse_factor = 1;
    static const unsigned n_zeros = 1345;
    static const unsigned n_nonzeros = 1791;
    static const unsigned multiplier_limit = DIV_ROUNDUP(n_in * n_out, reuse_factor) - n_zeros / reuse_factor;
    static const bool store_weights_in_bram = false;
    typedef Dense_MatMul_0_accum_t accum_t;
    typedef bias77_t bias_t;
    typedef weight77_t weight_t;
    typedef layer77_index index_t;
    template<class data_T, class res_T, class CONFIG_T>
    using kernel = nnet::DenseResource_rf_leq_nin<data_T, res_T, CONFIG_T>;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};

// Relu_2
struct ReLU_config67 : nnet::activ_config {
    static const unsigned n_in = 16;
    static const unsigned table_size = 1024;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned reuse_factor = 1;
    typedef Relu_2_table_t table_t;
};

// Dense_MatMul_1
struct config78 : nnet::dense_config {
    static const unsigned n_in = 16;
    static const unsigned n_out = 26;
    static const unsigned io_type = nnet::io_stream;
    static const unsigned strategy = nnet::resource;
    static const unsigned reuse_factor = 1;
    static const unsigned n_zeros = 107;
    static const unsigned n_nonzeros = 309;
    static const unsigned multiplier_limit = DIV_ROUNDUP(n_in * n_out, reuse_factor) - n_zeros / reuse_factor;
    static const bool store_weights_in_bram = false;
    typedef Dense_MatMul_1_accum_t accum_t;
    typedef bias78_t bias_t;
    typedef weight78_t weight_t;
    typedef layer78_index index_t;
    template<class data_T, class res_T, class CONFIG_T>
    using kernel = nnet::DenseResource_rf_leq_nin<data_T, res_T, CONFIG_T>;
    template<class x_T, class y_T>
    using product = nnet::product::mult<x_T, y_T>;
};



#endif
