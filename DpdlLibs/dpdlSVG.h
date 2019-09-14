#dpdlSVG.h V1.0      info@seesolutions.it
#
#Author: Armin Costa
#
#This library is implemented with Dpdl-Control-Script and comes with the standard Dpdl core Engine.
#This module implements SVG functions for imaging applications.
#
#Filename: dpdlSVG.h
#
func createImgCanvas()

endfunc

func destroyImgCanvas()

endfunc

func loadSVG(string file)

endfunc

#this function has to be called before drawLine(..) drawRect(..) etc.
func setColor(int col)

endfunc

func drawLine(int x1, int y1, int x2, int y2)

endfunc

func drawRect(int x, int y, int w, int h)

endfunc

#this function has to be called before drawLine(..) drawRect(..) etc.
func rotateObj(int deg)

endfunc





