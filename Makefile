# -*- Makefile -*-
#
#

AHRS	?= .
BOARD	?= IMU_AHRS

ALL_BOARDS := IMU_AHRS

CSRC = $(APPSRC)

CPPSRC = $(APPCPPSRC)

INCDIR = $(AHRS)/config/$(BOARD) $(APPINC)

include $(AHRS)/config/$(BOARD)/Makefile.inc
