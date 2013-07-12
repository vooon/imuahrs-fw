# -*- Makefile -*-
#
#

AHRS	?= .

CSRC = $(APPSRC)

CPPSRC = $(APPCPPSRC)

INCDIR = $(AHRS)/config $(APPINC)

include $(AHRS)/config/Makefile.inc
