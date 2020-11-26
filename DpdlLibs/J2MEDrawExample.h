#
# File: J2MEDrawExample.h
#
# Example application to draw on a J2ME MIDP canvas
#
# Author: A.Costa
# e-mail: armincosta(_a_t_)seesolutions.it
#
# License: GNU GPL
#
#
include("dpdlMIDP.h")
function initDrawTest()
  println("test init()")
end

#this method draws a grid
function draw()
     if(CANVAS != -1)
       gClear(CANVAS)
       gSetCurrent(CANVAS)
       gSetColor(CANVAS, 20, 20, 20)
       int x_, y_, old_y_
       x_ = 0
       y_ = 0
       old_y_ = y_
       int value
       string id
       int time_
       setStartTime()
       while x_ < 150
                y_ = 0
                while y_ < 100
                   gDrawRect(CANVAS, x_, y_, 5, 5)
                   gRepaint(CANVAS)
                   y_ = y_ + 5
               endwhile
               x_ = x_ + 5
               gFillRect(CANVAS, x_, x_, 5, 5)
       endwhile
       time_ = getEndTime()
       gDrawString(CANVAS, "Hello World from Dpdl in (ms):", 10, y_+12, LEFT)
       string time_str = "" + time_
       gDrawString(CANVAS, time_str, 10, y_+22, LEFT)
     endif
end

#main()
int CANVAS = 0
initDrawTest()
draw()
