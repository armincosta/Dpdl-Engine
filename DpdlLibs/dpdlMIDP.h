#dpdlMIDP.h V1.0      info@seesolutions.it
#
#Author: Armin Costa
#
#This library is implemented with Dpdl-Control-Script and comes with the standard Dpdl core Engine,
#It contains basic system abstraction functions and internal system variables.
#
#Filename: dpdlMIDP.h
#This library provides basic a basic interaction layer for accessing MIDP functions
#
include("dpdlMIDPUI.h")
include("dpdlMIDPGraphics.h")
include("dpdlMIDPRS.h")
include("dpdlProtocols.h")
include("dpdllib.h")
func initMIDP()
    println("dpdlMIDP.h loaded")
endfunc

#start of execution
initMIDP()
#system variable definition
string DpdlMIDPLibVersion = " <= 2.0"

#start Library execution











