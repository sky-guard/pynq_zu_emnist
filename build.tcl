# =====================================================================
# Vivado Batch Mode Build Script for PYNQ-ZU + AXI DMA + PYNQ_ZU_EMNIST
# =====================================================================

set project_name "PYNQ_ZU_EMNIST"
set project_dir "./vivado_output"
set board_part_str "tul.com.tw:pynqzu:part0:1.1"
set part_num "xczu5eg-sfvc784-1-e"
set ip_repo_path "./HLS_resource/PYNQ_ZU_EMNIST_prj/solution1/impl/ip"

# 1. Create project using the correct board part
create_project $project_name $project_dir -part $part_num -force
set_property board_part $board_part_str [current_project]

# 2. Register and refresh custom HLS IP repository
set_property IP_REPO_PATHS $ip_repo_path [current_project]
update_ip_catalog

# 3. Create Block Design canvas
create_bd_design "system"

# 4. Instantiate and configure Zynq UltraScale+ Processing System
set zynq_ps [create_bd_cell -type ip -vlnv xilinx.com:ip:zynq_ultra_ps_e zynq_ultra_ps_e_0]
apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1"} $zynq_ps

# Enable HP0 and disable unused Master GP1
set_property -dict [list \
    CONFIG.PSU__USE__S_AXI_GP2 {1} \
    CONFIG.PSU__USE__M_AXI_GP1 {0} \
] $zynq_ps

# 5. Create System Reset Generator for PL fabric
set rst_gen [create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset rst_ps8_0_99M]
connect_bd_net [get_bd_pins zynq_ultra_ps_e_0/pl_clk0] [get_bd_pins rst_ps8_0_99M/slowest_sync_clk]
connect_bd_net [get_bd_pins zynq_ultra_ps_e_0/pl_resetn0] [get_bd_pins rst_ps8_0_99M/ext_reset_in]

# 6. Instantiate AXI DMA IP 
set axi_dma [create_bd_cell -type ip -vlnv xilinx.com:ip:axi_dma axi_dma_0]
set_property -dict [list \
    CONFIG.c_include_sg {0} \
    CONFIG.c_m_axis_mm2s_tdata_width {512} \
    CONFIG.c_s_axis_s2mm_tdata_width {1024} \
] $axi_dma

# 7. Instantiate HLS IP Core
set hls_ip [create_bd_cell -type ip -vlnv xilinx.com:hls:PYNQ_ZU_EMNIST PYNQ_ZU_EMNIST_0]

# 8. Instantiate AXI Stream Subset Converters to bridge width & TLAST gaps
set axis_subset_in [create_bd_cell -type ip -vlnv xilinx.com:ip:axis_subset_converter axis_subset_in_0]
set axis_subset_out [create_bd_cell -type ip -vlnv xilinx.com:ip:axis_subset_converter axis_subset_out_0]

# Configure subset converters to map data streams cleanly
# Input side: DMA (512-bit / 64 bytes) to HLS input (448-bit / 56 bytes)
set_property CONFIG.M_TDATA_NUM_BYTES {56} $axis_subset_in
set_property CONFIG.S_TDATA_NUM_BYTES {64} $axis_subset_in

# Output side: HLS output (104 bytes) to DMA (1024-bit / 128 bytes), injecting TLAST generation
set_property -dict [list \
    CONFIG.M_HAS_TLAST {1} \
    CONFIG.S_HAS_TLAST {0} \
    CONFIG.DEFAULT_TLAST {1} \
    CONFIG.M_TDATA_NUM_BYTES {128} \
    CONFIG.S_TDATA_NUM_BYTES {104} \
] $axis_subset_out

# 9. Connect AXI-Stream interfaces through the subset converters
connect_bd_intf_net [get_bd_intf_pins axi_dma_0/M_AXIS_MM2S] [get_bd_intf_pins axis_subset_in_0/S_AXIS]
connect_bd_intf_net [get_bd_intf_pins axis_subset_in_0/M_AXIS] [get_bd_intf_pins PYNQ_ZU_EMNIST_0/global_in]

connect_bd_intf_net [get_bd_intf_pins PYNQ_ZU_EMNIST_0/layer78_out] [get_bd_intf_pins axis_subset_out_0/S_AXIS]
connect_bd_intf_net [get_bd_intf_pins axis_subset_out_0/M_AXIS] [get_bd_intf_pins axi_dma_0/S_AXIS_S2MM]

# 10. Connect AXI DMA Control Port (S_AXI_LITE) to Zynq PS
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { \
    Clk_auto {Auto} \
    Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} \
    Slave {/axi_dma_0/S_AXI_LITE} \
    intc_ip {New AXI Interconnect} \
    master_apm {0} \
} [get_bd_intf_pins axi_dma_0/S_AXI_LITE]

# 11. Connect both DMA Memory-Mapped ports to Zynq HP0 via an AXI SmartConnect
set smartconnect_0 [create_bd_cell -type ip -vlnv xilinx.com:ip:smartconnect smartconnect_0]
set_property CONFIG.NUM_SI {2} $smartconnect_0
set_property CONFIG.NUM_MI {1} $smartconnect_0

connect_bd_intf_net [get_bd_intf_pins axi_dma_0/M_AXI_MM2S] [get_bd_intf_pins smartconnect_0/S00_AXI]
connect_bd_intf_net [get_bd_intf_pins axi_dma_0/M_AXI_S2MM] [get_bd_intf_pins smartconnect_0/S01_AXI]
connect_bd_intf_net [get_bd_intf_pins smartconnect_0/M00_AXI] [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_HP0_FPD]

# 12. Connect Clocks, Resets, and Control Signals
connect_bd_net [get_bd_pins zynq_ultra_ps_e_0/pl_clk0] [get_bd_pins PYNQ_ZU_EMNIST_0/ap_clk]
connect_bd_net [get_bd_pins rst_ps8_0_99M/peripheral_aresetn] [get_bd_pins PYNQ_ZU_EMNIST_0/ap_rst_n]

# Tie ap_start high
set xlconstant_0 [create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant xlconstant_0]
set_property -dict [list CONFIG.CONST_VAL {1} CONFIG.CONST_WIDTH {1}] $xlconstant_0
connect_bd_net [get_bd_pins xlconstant_0/dout] [get_bd_pins PYNQ_ZU_EMNIST_0/ap_start]

# Connect clocks & resets for subset converters, HP0, SmartConnect, and DMA
connect_bd_net [get_bd_pins zynq_ultra_ps_e_0/pl_clk0] [get_bd_pins zynq_ultra_ps_e_0/saxihp0_fpd_aclk]
connect_bd_net [get_bd_pins zynq_ultra_ps_e_0/pl_clk0] [get_bd_pins smartconnect_0/aclk]
connect_bd_net [get_bd_pins rst_ps8_0_99M/peripheral_aresetn] [get_bd_pins smartconnect_0/aresetn]

connect_bd_net [get_bd_pins zynq_ultra_ps_e_0/pl_clk0] [get_bd_pins axi_dma_0/m_axi_mm2s_aclk]
connect_bd_net [get_bd_pins zynq_ultra_ps_e_0/pl_clk0] [get_bd_pins axi_dma_0/m_axi_s2mm_aclk]

connect_bd_net [get_bd_pins zynq_ultra_ps_e_0/pl_clk0] [get_bd_pins axis_subset_in_0/aclk]
connect_bd_net [get_bd_pins rst_ps8_0_99M/peripheral_aresetn] [get_bd_pins axis_subset_in_0/aresetn]
connect_bd_net [get_bd_pins zynq_ultra_ps_e_0/pl_clk0] [get_bd_pins axis_subset_out_0/aclk]
connect_bd_net [get_bd_pins rst_ps8_0_99M/peripheral_aresetn] [get_bd_pins axis_subset_out_0/aresetn]

# Automatically assign address ranges
assign_bd_address

# 13. Validate and save block design
validate_bd_design
save_bd_design

# 14. Generate Top-Level HDL Wrapper and Run Synthesis/Bitstream
set design_name [get_bd_designs system]
make_wrapper -files [get_files ${design_name}.bd] -top -import
update_compile_order -fileset sources_1

launch_runs synth_1 -jobs 4
wait_on_run synth_1

launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1

# 15. Export the unified XSA hardware package for PYNQ
write_hw_platform -fixed -include_bit -force -file ./vivado_output/system_wrapper.xsa

puts "INFO: Bitstream generation completed successfully!"
exit
