#DpdlConsolseProtocolV1.0 description for the DPDL Console Communication
#
#Author: A.Costa
# 
#Filename: DPDLProt.h
#License: GNU GPL
#
function init()
    println("DPDL Console Protocol loaded")
end

string dpdl_echo = "dpdl_echo"
string dpdl_list = "dpdl_list"
string dpdl_install = "dpdl_install"
string dpdl_get = "dpdl_get"
string dpdl_update = "dpdl_update"
string dpdl_restore = "dpdl_restore"
string dpdl_run = "dpdl_run"
string dpdl_reboot = "dpdl_reboot"

string dpdl_console_cmd = "dpdl_console_cmd"
string dpdl_ok_cmd = "dpdl_ok_cmd"
string dpdl_end_cmd = "dpdl_end_cmd"
string dpdl_exec_cmd = "dpdl_exec_cmd"
string dpdl_save_cmd = "dpdl_save_cmd"
string dpdl_reg_cmd = "dpdl_reg_cmd"
string dpdl_savers_cmd = "dpdl_savers_cmd"
string dpdl_del_cmd = "dpdl_del_cmd"

#module entry point
init()


