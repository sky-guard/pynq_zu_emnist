#ifndef PYNQ_ZU_EMNIST_H_
#define PYNQ_ZU_EMNIST_H_

#include "ap_fixed.h"
#include "ap_int.h"
#include "hls_stream.h"

#include "defines.h"


// Prototype of top level function for C-synthesis
void PYNQ_ZU_EMNIST(
    input_t global_in[28*28*1],
    result_t layer78_out[26]
);

// hls-fpga-machine-learning insert emulator-defines


#endif
