# THIS FILE IS AUTOMATICALLY GENERATED
# Project: E:\_CODE\PSoC Projektai\PSoC_MIS2\stendo_MIS.cydsn\stendo_MIS.cyprj
# Date: Sat, 28 Jul 2018 15:23:25 GMT
#set_units -time ns
create_clock -name {CyXTAL_32kHz} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/clk_32k_xtal}]]
create_clock -name {CyXTAL} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/xtal}]]
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 16.666666666666664 -waveform {0 8.33333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 16.666666666666664 -waveform {0 8.33333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {spiclk} -source [get_pins {ClockBlock/clk_sync}] -edges {1 61 121} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {timer_clock_7} -source [get_pins {ClockBlock/clk_sync}] -edges {1 61 121} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_clock -name {timer_clock_7(fixed-function)} -period 1000 -waveform {0 16.6666666666667} [get_pins {ClockBlock/dclk_glb_ff_1}]
create_generated_clock -name {UART_1_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 781 1563} [list [get_pins {ClockBlock/dclk_glb_2}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for E:\_CODE\PSoC Projektai\PSoC_MIS2\stendo_MIS.cydsn\TopDesign\TopDesign.cysch
# Project: E:\_CODE\PSoC Projektai\PSoC_MIS2\stendo_MIS.cydsn\stendo_MIS.cyprj
# Date: Sat, 28 Jul 2018 15:21:57 GMT
