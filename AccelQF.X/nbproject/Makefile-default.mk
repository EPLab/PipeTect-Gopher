#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile

# Environment
SHELL=cmd.exe
# Adding MPLAB X bin directory to path
PATH:=C:/Program Files/Microchip/MPLABX/mplab_ide/mplab_ide/modules/../../bin/:$(PATH)
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/AccelQF.X.${IMAGE_TYPE}.cof
else
IMAGE_TYPE=production
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/AccelQF.X.${IMAGE_TYPE}.cof
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1728301206/Demo02.o ${OBJECTDIR}/_ext/1728301206/ECANPoll.o ${OBJECTDIR}/_ext/1728301206/Msp430-SPI.o ${OBJECTDIR}/_ext/1728301206/Platform.o ${OBJECTDIR}/_ext/1728301206/Qf4a512-access.o ${OBJECTDIR}/_ext/1728301206/Qf4a512-functional.o ${OBJECTDIR}/_ext/1728301206/accel_handler.o ${OBJECTDIR}/_ext/1728301206/can_outgoing_queue.o ${OBJECTDIR}/_ext/1728301206/can_parameter.o ${OBJECTDIR}/_ext/1728301206/circular_queue.o ${OBJECTDIR}/_ext/1728301206/command_hq.o ${OBJECTDIR}/_ext/1728301206/switcher.o ${OBJECTDIR}/_ext/1728301206/vector_mapper.o

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1728301206/Demo02.o ${OBJECTDIR}/_ext/1728301206/ECANPoll.o ${OBJECTDIR}/_ext/1728301206/Msp430-SPI.o ${OBJECTDIR}/_ext/1728301206/Platform.o ${OBJECTDIR}/_ext/1728301206/Qf4a512-access.o ${OBJECTDIR}/_ext/1728301206/Qf4a512-functional.o ${OBJECTDIR}/_ext/1728301206/accel_handler.o ${OBJECTDIR}/_ext/1728301206/can_outgoing_queue.o ${OBJECTDIR}/_ext/1728301206/can_parameter.o ${OBJECTDIR}/_ext/1728301206/circular_queue.o ${OBJECTDIR}/_ext/1728301206/command_hq.o ${OBJECTDIR}/_ext/1728301206/switcher.o ${OBJECTDIR}/_ext/1728301206/vector_mapper.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

# Path to java used to run MPLAB X when this makefile was created
MP_JAVA_PATH="C:\Program Files\Java\jre6/bin/"
OS_CURRENT="$(shell uname -s)"
############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
MP_CC="C:\Program Files\Microchip\mplabc18\v3.40\bin\mcc18.exe"
# MP_BC is not defined
MP_AS="C:\Program Files\Microchip\mplabc18\v3.40\bin\..\mpasm\MPASMWIN.exe"
MP_LD="C:\Program Files\Microchip\mplabc18\v3.40\bin\mplink.exe"
MP_AR="C:\Program Files\Microchip\mplabc18\v3.40\bin\mplib.exe"
DEP_GEN=${MP_JAVA_PATH}java -jar "C:/Program Files/Microchip/MPLABX/mplab_ide/mplab_ide/modules/../../bin/extractobjectdependencies.jar" 
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps
MP_CC_DIR="C:\Program Files\Microchip\mplabc18\v3.40\bin"
# MP_BC_DIR is not defined
MP_AS_DIR="C:\Program Files\Microchip\mplabc18\v3.40\bin\..\mpasm"
MP_LD_DIR="C:\Program Files\Microchip\mplabc18\v3.40\bin"
MP_AR_DIR="C:\Program Files\Microchip\mplabc18\v3.40\bin"
# MP_BC_DIR is not defined

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/AccelQF.X.${IMAGE_TYPE}.cof

MP_PROCESSOR_OPTION=18F2580
MP_PROCESSOR_OPTION_LD=18f2580
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0x7dc0 -u_DEBUGCODELEN=0x240 -u_DEBUGDATASTART=0x5f4 -u_DEBUGDATALEN=0xb
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1728301206/can_outgoing_queue.o: ../Source/can_outgoing_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/can_outgoing_queue.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/can_outgoing_queue.o   ../Source/can_outgoing_queue.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/can_outgoing_queue.o 
	
${OBJECTDIR}/_ext/1728301206/Platform.o: ../Source/Platform.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Platform.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/Platform.o   ../Source/Platform.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/Platform.o 
	
${OBJECTDIR}/_ext/1728301206/Qf4a512-access.o: ../Source/Qf4a512-access.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Qf4a512-access.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/Qf4a512-access.o   ../Source/Qf4a512-access.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/Qf4a512-access.o 
	
${OBJECTDIR}/_ext/1728301206/Msp430-SPI.o: ../Source/Msp430-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Msp430-SPI.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/Msp430-SPI.o   ../Source/Msp430-SPI.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/Msp430-SPI.o 
	
${OBJECTDIR}/_ext/1728301206/vector_mapper.o: ../Source/vector_mapper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/vector_mapper.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/vector_mapper.o   ../Source/vector_mapper.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/vector_mapper.o 
	
${OBJECTDIR}/_ext/1728301206/switcher.o: ../Source/switcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/switcher.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/switcher.o   ../Source/switcher.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/switcher.o 
	
${OBJECTDIR}/_ext/1728301206/can_parameter.o: ../Source/can_parameter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/can_parameter.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/can_parameter.o   ../Source/can_parameter.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/can_parameter.o 
	
${OBJECTDIR}/_ext/1728301206/Demo02.o: ../Source/Demo02.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Demo02.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/Demo02.o   ../Source/Demo02.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/Demo02.o 
	
${OBJECTDIR}/_ext/1728301206/circular_queue.o: ../Source/circular_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/circular_queue.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/circular_queue.o   ../Source/circular_queue.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/circular_queue.o 
	
${OBJECTDIR}/_ext/1728301206/Qf4a512-functional.o: ../Source/Qf4a512-functional.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Qf4a512-functional.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/Qf4a512-functional.o   ../Source/Qf4a512-functional.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/Qf4a512-functional.o 
	
${OBJECTDIR}/_ext/1728301206/accel_handler.o: ../Source/accel_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/accel_handler.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/accel_handler.o   ../Source/accel_handler.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/accel_handler.o 
	
${OBJECTDIR}/_ext/1728301206/ECANPoll.o: ../Source/ECANPoll.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/ECANPoll.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/ECANPoll.o   ../Source/ECANPoll.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/ECANPoll.o 
	
${OBJECTDIR}/_ext/1728301206/command_hq.o: ../Source/command_hq.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/command_hq.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/command_hq.o   ../Source/command_hq.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/command_hq.o 
	
else
${OBJECTDIR}/_ext/1728301206/can_outgoing_queue.o: ../Source/can_outgoing_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/can_outgoing_queue.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/can_outgoing_queue.o   ../Source/can_outgoing_queue.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/can_outgoing_queue.o 
	
${OBJECTDIR}/_ext/1728301206/Platform.o: ../Source/Platform.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Platform.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/Platform.o   ../Source/Platform.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/Platform.o 
	
${OBJECTDIR}/_ext/1728301206/Qf4a512-access.o: ../Source/Qf4a512-access.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Qf4a512-access.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/Qf4a512-access.o   ../Source/Qf4a512-access.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/Qf4a512-access.o 
	
${OBJECTDIR}/_ext/1728301206/Msp430-SPI.o: ../Source/Msp430-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Msp430-SPI.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/Msp430-SPI.o   ../Source/Msp430-SPI.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/Msp430-SPI.o 
	
${OBJECTDIR}/_ext/1728301206/vector_mapper.o: ../Source/vector_mapper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/vector_mapper.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/vector_mapper.o   ../Source/vector_mapper.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/vector_mapper.o 
	
${OBJECTDIR}/_ext/1728301206/switcher.o: ../Source/switcher.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/switcher.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/switcher.o   ../Source/switcher.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/switcher.o 
	
${OBJECTDIR}/_ext/1728301206/can_parameter.o: ../Source/can_parameter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/can_parameter.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/can_parameter.o   ../Source/can_parameter.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/can_parameter.o 
	
${OBJECTDIR}/_ext/1728301206/Demo02.o: ../Source/Demo02.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Demo02.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/Demo02.o   ../Source/Demo02.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/Demo02.o 
	
${OBJECTDIR}/_ext/1728301206/circular_queue.o: ../Source/circular_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/circular_queue.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/circular_queue.o   ../Source/circular_queue.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/circular_queue.o 
	
${OBJECTDIR}/_ext/1728301206/Qf4a512-functional.o: ../Source/Qf4a512-functional.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Qf4a512-functional.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/Qf4a512-functional.o   ../Source/Qf4a512-functional.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/Qf4a512-functional.o 
	
${OBJECTDIR}/_ext/1728301206/accel_handler.o: ../Source/accel_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/accel_handler.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/accel_handler.o   ../Source/accel_handler.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/accel_handler.o 
	
${OBJECTDIR}/_ext/1728301206/ECANPoll.o: ../Source/ECANPoll.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/ECANPoll.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/ECANPoll.o   ../Source/ECANPoll.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/ECANPoll.o 
	
${OBJECTDIR}/_ext/1728301206/command_hq.o: ../Source/command_hq.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/command_hq.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -D__YEB_IMMEDIATE__ -I"../../../../../MCC18/h" -I"../../Source" -I"../../Header" -I"../Header" -I"../../../../../Program Files/Microchip/mplabc18/v3.40/h"  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1728301206/command_hq.o   ../Source/command_hq.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1728301206/command_hq.o 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/AccelQF.X.${IMAGE_TYPE}.cof: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -l"../../../../../MCC18/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -odist/${CND_CONF}/${IMAGE_TYPE}/AccelQF.X.${IMAGE_TYPE}.cof  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/AccelQF.X.${IMAGE_TYPE}.cof: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -l"../../../../../MCC18/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -odist/${CND_CONF}/${IMAGE_TYPE}/AccelQF.X.${IMAGE_TYPE}.cof  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard $(addsuffix .d, ${OBJECTFILES}))
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
