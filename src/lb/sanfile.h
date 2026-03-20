//====================================================================================//
//                                                                                    //
//                           SAN File Declarations and includes                       //
//                                                                                    //
//====================================================================================//
//  This File:   sanfile.h                   Tool: C++                                //
//  Software:    PEPS                        Advisor: Paulof@inf.pucrs.br             //
//  Doc:                                                                              //
//====================================================================================//
//  Creation:    06/Mar/02                   by: lbrenner@inf.pucrs.br                //
//  Last Change: 18/Jun/02                   by: lbrenner@inf.pucrs.br                //
//====================================================================================//
//  This file has the declarations and includes that must to be used in all files of  //
// related with the recognition of SAN files.                                         //
//====================================================================================//

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h> 
#include <math.h>
#include <dlfcn.h>

#ifndef _SANFILE_H_
#define _SANFILE_H_
#include "../pf/peps.h"
#endif

#include "net.h"
#include "autom.h"
#include "state.h"
#include "trans.h"
#include "event.h"
#include "inf2pos.h"
#include "func.h"
#include "dom.h"
#include "edic.h"
#include "yacc.H"
#include "error_msgs.h"

class NET;
class AUTOMATON;
class STATE;
class TRANS;
class EVENT;
class FUNC;
class DOM;
class EDIC;

//===========================================================================//
//    Defines                                                                //
//===========================================================================//

#define MAX_NAME    200                        // Maximun length of file names
#define FUNCTION     4096                      // Maximun length of functions
#define MAX_SIZE     1024                      // Maximun length of vectors and
                                               // matrices dimentions 
                                               
#define YYMAXDEPTH      50000
                                               
#define DISCRETE 0
#define CONTINUOUS 1
#define MAX_MODEL_NAME 128
#define MAX_AUTOMATON_NAME 128
#define MAX_STATE_NAME 128
#define MAX_EVENT_NAME 128
#define MAX_FUNC_NAME 128
#define MAX_EXP_SIZE 4096
#define MAX_TABLE_SIZE 1024 

