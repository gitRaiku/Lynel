#  TCL command to get clock capable pins
#  get_property IS_CLK_CAPABLE [get_package_pins]
#
set_property PACKAGE_PIN R2 [get_ports sys_clk]
set_property IOSTANDARD LVCMOS18 [get_ports sys_clk]
set_property PACKAGE_PIN H18 [get_ports rst_n]
set_property IOSTANDARD LVCMOS18 [get_ports rst_n]
set_property PACKAGE_PIN H17 [get_ports button_1]
set_property IOSTANDARD LVCMOS18 [get_ports button_1]

set_property PACKAGE_PIN C8 [get_ports led_1]
set_property IOSTANDARD LVCMOS18 [get_ports led_1]
set_property PACKAGE_PIN D8 [get_ports led_2]
set_property IOSTANDARD LVCMOS18 [get_ports led_2]

set_property PACKAGE_PIN E17 [get_ports sda]
set_property IOSTANDARD LVCMOS18 [get_ports sda]
set_property PACKAGE_PIN C13 [get_ports scl]
set_property IOSTANDARD LVCMOS18 [get_ports scl]

set_property CONFIG_VOLTAGE 3.3 [current_design]
set_property CFGBVS VCCO [current_design]

# Debug
