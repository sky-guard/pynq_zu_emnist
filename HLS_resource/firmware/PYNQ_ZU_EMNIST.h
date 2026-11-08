#ifndef PYNQ_ZU_EMNIST_H_
#define PYNQ_ZU_EMNIST_H_

#include "ap_fixed.h"
#include "ap_int.h"
#include "hls_stream.h"

#include "defines.h"


// Prototype of top level function for C-synthesis
void PYNQ_ZU_EMNIST(
    hls::stream<input_t> &global_in,
    hls::stream<result_t> &layer78_out
);

// hls-fpga-machine-learning insert emulator-defines


#endif
