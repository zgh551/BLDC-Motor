;***************************************************************
;* TMS320C2000 C/C++ Codegen                   PC v15.12.1.LTS *
;* Date/Time created: Mon Aug 29 15:38:15 2016                 *
;***************************************************************
	.compiler_opts --abi=coffabi --float_support=fpu32 --hll_source=on --mem_model:code=flat --mem_model:data=large --object_format=coff --quiet --silicon_version=28 --symdebug:dwarf --symdebug:dwarf_version=3 
FP	.set	XAR2

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c")
	.dwattr $C$DW$CU, DW_AT_producer("TI TMS320C2000 C/C++ Codegen PC v15.12.1.LTS Copyright (c) 1996-2015 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("D:\work\DSP\ProgramBomb\ProgramBombDebug\math\IQmath\v160\examples_ccsv4\C\2833x\Debug")
;**************************************************************
;* CINIT RECORDS                                              *
;**************************************************************
	.sect	".cinit"
	.align	1
	.field  	-2,16
	.field  	_GlobalQ+0,32
	.bits	24,32			; _GlobalQ @ 0


$C$DW$1	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$1, DW_AT_name("puts")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("_puts")
	.dwattr $C$DW$1, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$1, DW_AT_declaration
	.dwattr $C$DW$1, DW_AT_external
$C$DW$2	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$26)

	.dwendtag $C$DW$1


$C$DW$3	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$3, DW_AT_name("_IQ24mag")
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("__IQ24mag")
	.dwattr $C$DW$3, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$3, DW_AT_declaration
	.dwattr $C$DW$3, DW_AT_external
$C$DW$4	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$12)

$C$DW$5	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$5, DW_AT_type(*$C$DW$T$12)

	.dwendtag $C$DW$3


$C$DW$6	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$6, DW_AT_name("_IQ24exp")
	.dwattr $C$DW$6, DW_AT_TI_symbol_name("__IQ24exp")
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$6, DW_AT_declaration
	.dwattr $C$DW$6, DW_AT_external
$C$DW$7	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$7, DW_AT_type(*$C$DW$T$12)

	.dwendtag $C$DW$6


$C$DW$8	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$8, DW_AT_name("_IQ24mpyI32int")
	.dwattr $C$DW$8, DW_AT_TI_symbol_name("__IQ24mpyI32int")
	.dwattr $C$DW$8, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$8, DW_AT_declaration
	.dwattr $C$DW$8, DW_AT_external
$C$DW$9	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$9, DW_AT_type(*$C$DW$T$12)

$C$DW$10	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$10, DW_AT_type(*$C$DW$T$12)

	.dwendtag $C$DW$8


$C$DW$11	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$11, DW_AT_name("_IQ24log")
	.dwattr $C$DW$11, DW_AT_TI_symbol_name("__IQ24log")
	.dwattr $C$DW$11, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$11, DW_AT_declaration
	.dwattr $C$DW$11, DW_AT_external
$C$DW$12	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$12, DW_AT_type(*$C$DW$T$12)

	.dwendtag $C$DW$11


$C$DW$13	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$13, DW_AT_name("_atoIQN")
	.dwattr $C$DW$13, DW_AT_TI_symbol_name("__atoIQN")
	.dwattr $C$DW$13, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$13, DW_AT_declaration
	.dwattr $C$DW$13, DW_AT_external
$C$DW$14	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$14, DW_AT_type(*$C$DW$T$26)

$C$DW$15	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$15, DW_AT_type(*$C$DW$T$12)

	.dwendtag $C$DW$13

	.global	_GlobalQ
_GlobalQ:	.usect	".ebss",2,1,1
$C$DW$16	.dwtag  DW_TAG_variable
	.dwattr $C$DW$16, DW_AT_name("GlobalQ")
	.dwattr $C$DW$16, DW_AT_TI_symbol_name("_GlobalQ")
	.dwattr $C$DW$16, DW_AT_location[DW_OP_addr _GlobalQ]
	.dwattr $C$DW$16, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$16, DW_AT_external


$C$DW$17	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$17, DW_AT_name("gets")
	.dwattr $C$DW$17, DW_AT_TI_symbol_name("_gets")
	.dwattr $C$DW$17, DW_AT_type(*$C$DW$T$40)
	.dwattr $C$DW$17, DW_AT_declaration
	.dwattr $C$DW$17, DW_AT_external
$C$DW$18	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$18, DW_AT_type(*$C$DW$T$40)

	.dwendtag $C$DW$17


$C$DW$19	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$19, DW_AT_name("_IQ24div")
	.dwattr $C$DW$19, DW_AT_TI_symbol_name("__IQ24div")
	.dwattr $C$DW$19, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$19, DW_AT_declaration
	.dwattr $C$DW$19, DW_AT_external
$C$DW$20	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$20, DW_AT_type(*$C$DW$T$12)

$C$DW$21	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$21, DW_AT_type(*$C$DW$T$12)

	.dwendtag $C$DW$19


$C$DW$22	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$22, DW_AT_name("labs")
	.dwattr $C$DW$22, DW_AT_TI_symbol_name("_labs")
	.dwattr $C$DW$22, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$22, DW_AT_declaration
	.dwattr $C$DW$22, DW_AT_external
$C$DW$23	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$23, DW_AT_type(*$C$DW$T$12)

	.dwendtag $C$DW$22


$C$DW$24	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$24, DW_AT_name("_IQ24acos")
	.dwattr $C$DW$24, DW_AT_TI_symbol_name("__IQ24acos")
	.dwattr $C$DW$24, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$24, DW_AT_declaration
	.dwattr $C$DW$24, DW_AT_external
$C$DW$25	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$25, DW_AT_type(*$C$DW$T$12)

	.dwendtag $C$DW$24


$C$DW$26	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$26, DW_AT_name("_IQ24atan2PU")
	.dwattr $C$DW$26, DW_AT_TI_symbol_name("__IQ24atan2PU")
	.dwattr $C$DW$26, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$26, DW_AT_declaration
	.dwattr $C$DW$26, DW_AT_external
$C$DW$27	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$27, DW_AT_type(*$C$DW$T$12)

$C$DW$28	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$28, DW_AT_type(*$C$DW$T$12)

	.dwendtag $C$DW$26


$C$DW$29	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$29, DW_AT_name("__IQmpy")
	.dwattr $C$DW$29, DW_AT_TI_symbol_name("___IQmpy")
	.dwattr $C$DW$29, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$29, DW_AT_declaration
	.dwattr $C$DW$29, DW_AT_external
$C$DW$30	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$30, DW_AT_type(*$C$DW$T$12)

$C$DW$31	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$31, DW_AT_type(*$C$DW$T$12)

$C$DW$32	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$32, DW_AT_type(*$C$DW$T$10)

	.dwendtag $C$DW$29


$C$DW$33	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$33, DW_AT_name("_IQ24sin")
	.dwattr $C$DW$33, DW_AT_TI_symbol_name("__IQ24sin")
	.dwattr $C$DW$33, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$33, DW_AT_declaration
	.dwattr $C$DW$33, DW_AT_external
$C$DW$34	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$34, DW_AT_type(*$C$DW$T$12)

	.dwendtag $C$DW$33

	.global	_Step
_Step:	.usect	".ebss",18,1,1
$C$DW$35	.dwtag  DW_TAG_variable
	.dwattr $C$DW$35, DW_AT_name("Step")
	.dwattr $C$DW$35, DW_AT_TI_symbol_name("_Step")
	.dwattr $C$DW$35, DW_AT_location[DW_OP_addr _Step]
	.dwattr $C$DW$35, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$35, DW_AT_external

	.global	_Dlog
_Dlog:	.usect	".ebss",768,1,1
$C$DW$36	.dwtag  DW_TAG_variable
	.dwattr $C$DW$36, DW_AT_name("Dlog")
	.dwattr $C$DW$36, DW_AT_TI_symbol_name("_Dlog")
	.dwattr $C$DW$36, DW_AT_location[DW_OP_addr _Dlog]
	.dwattr $C$DW$36, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$36, DW_AT_external

;	C:\ti\ccsv6\tools\compiler\ti-cgt-c2000_15.12.1.LTS\bin\ac2000.exe -@C:\\Users\\RJKJ_ZGH\\AppData\\Local\\Temp\\1197212 
	.sect	".text"
	.clink
	.global	_main

$C$DW$37	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$37, DW_AT_name("main")
	.dwattr $C$DW$37, DW_AT_low_pc(_main)
	.dwattr $C$DW$37, DW_AT_high_pc(0x00)
	.dwattr $C$DW$37, DW_AT_TI_symbol_name("_main")
	.dwattr $C$DW$37, DW_AT_external
	.dwattr $C$DW$37, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$37, DW_AT_TI_begin_file("D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c")
	.dwattr $C$DW$37, DW_AT_TI_begin_line(0x3a)
	.dwattr $C$DW$37, DW_AT_TI_begin_column(0x05)
	.dwattr $C$DW$37, DW_AT_TI_max_frame_size(-46)
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 59,column 1,is_stmt,address _main,isa 0

	.dwfde $C$DW$CIE, _main

;***************************************************************
;* FNAME: _main                         FR SIZE:  44           *
;*                                                             *
;* FUNCTION ENVIRONMENT                                        *
;*                                                             *
;* FUNCTION PROPERTIES                                         *
;*                            2 Parameter, 42 Auto,  0 SOE     *
;***************************************************************

_main:
	.dwcfi	cfa_offset, -2
	.dwcfi	save_reg_to_mem, 26, 0
        ADDB      SP,#44                ; [CPU_U] 
	.dwcfi	cfa_offset, -46
$C$DW$38	.dwtag  DW_TAG_variable
	.dwattr $C$DW$38, DW_AT_name("i")
	.dwattr $C$DW$38, DW_AT_TI_symbol_name("_i")
	.dwattr $C$DW$38, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$38, DW_AT_location[DW_OP_breg20 -3]

$C$DW$39	.dwtag  DW_TAG_variable
	.dwattr $C$DW$39, DW_AT_name("tempX")
	.dwattr $C$DW$39, DW_AT_TI_symbol_name("_tempX")
	.dwattr $C$DW$39, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$39, DW_AT_location[DW_OP_breg20 -6]

$C$DW$40	.dwtag  DW_TAG_variable
	.dwattr $C$DW$40, DW_AT_name("tempY")
	.dwattr $C$DW$40, DW_AT_TI_symbol_name("_tempY")
	.dwattr $C$DW$40, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$40, DW_AT_location[DW_OP_breg20 -8]

$C$DW$41	.dwtag  DW_TAG_variable
	.dwattr $C$DW$41, DW_AT_name("tempP")
	.dwattr $C$DW$41, DW_AT_TI_symbol_name("_tempP")
	.dwattr $C$DW$41, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$41, DW_AT_location[DW_OP_breg20 -10]

$C$DW$42	.dwtag  DW_TAG_variable
	.dwattr $C$DW$42, DW_AT_name("tempM")
	.dwattr $C$DW$42, DW_AT_TI_symbol_name("_tempM")
	.dwattr $C$DW$42, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$42, DW_AT_location[DW_OP_breg20 -12]

$C$DW$43	.dwtag  DW_TAG_variable
	.dwattr $C$DW$43, DW_AT_name("tempMmax")
	.dwattr $C$DW$43, DW_AT_TI_symbol_name("_tempMmax")
	.dwattr $C$DW$43, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$43, DW_AT_location[DW_OP_breg20 -14]

$C$DW$44	.dwtag  DW_TAG_variable
	.dwattr $C$DW$44, DW_AT_name("buffer")
	.dwattr $C$DW$44, DW_AT_TI_symbol_name("_buffer")
	.dwattr $C$DW$44, DW_AT_type(*$C$DW$T$43)
	.dwattr $C$DW$44, DW_AT_location[DW_OP_breg20 -34]

$C$DW$45	.dwtag  DW_TAG_variable
	.dwattr $C$DW$45, DW_AT_name("WatchdogWDCR")
	.dwattr $C$DW$45, DW_AT_TI_symbol_name("_WatchdogWDCR")
	.dwattr $C$DW$45, DW_AT_type(*$C$DW$T$30)
	.dwattr $C$DW$45, DW_AT_location[DW_OP_breg20 -36]

	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 64,column 23,is_stmt,isa 0
        MOVL      XAR4,#28713           ; [CPU_U] |64| 
        MOVL      *-SP[36],XAR4         ; [CPU_] |64| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 67,column 5,is_stmt,isa 0
 EALLOW 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 68,column 5,is_stmt,isa 0
        MOVB      *+XAR4[0],#104,UNC    ; [CPU_] |68| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 69,column 5,is_stmt,isa 0
 EDIS 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 71,column 5,is_stmt,isa 0
        MOV       AL,#25900             ; [CPU_] |71| 
        MOV       AH,#89                ; [CPU_] |71| 
        SPM       #0                    ; [CPU_] 
$C$DW$46	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$46, DW_AT_low_pc(0x00)
	.dwattr $C$DW$46, DW_AT_name("__IQ24acos")
	.dwattr $C$DW$46, DW_AT_TI_call

        LCR       #__IQ24acos           ; [CPU_] |71| 
        ; call occurs [#__IQ24acos] ; [] |71| 
        MOVL      *-SP[6],ACC           ; [CPU_] |71| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 73,column 5,is_stmt,isa 0
        MOVW      DP,#_Step             ; [CPU_U] 
        MOV       AL,#27838             ; [CPU_] |73| 
        MOV       AH,#80                ; [CPU_] |73| 
        MOVL      @_Step,ACC            ; [CPU_] |73| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 74,column 5,is_stmt,isa 0
        MOV       AL,#27838             ; [CPU_] |74| 
        MOV       AH,#80                ; [CPU_] |74| 
        MOVL      @_Step+2,ACC          ; [CPU_] |74| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 75,column 5,is_stmt,isa 0
        MOVB      ACC,#0                ; [CPU_] |75| 
        MOVL      @_Step+4,ACC          ; [CPU_] |75| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 76,column 5,is_stmt,isa 0
        MOVL      @_Step+6,ACC          ; [CPU_] |76| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 77,column 5,is_stmt,isa 0
        MOVL      ACC,@_Step+4          ; [CPU_] |77| 
        MOVL      @_Step+8,ACC          ; [CPU_] |77| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 80,column 9,is_stmt,isa 0
        MOV       *-SP[3],#0            ; [CPU_] |80| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 80,column 14,is_stmt,isa 0
        MOV       AL,*-SP[3]            ; [CPU_] |80| 
        CMPB      AL,#64                ; [CPU_] |80| 
        B         $C$L2,HIS             ; [CPU_] |80| 
        ; branchcc occurs ; [] |80| 
        CLRC      SXM                   ; [CPU_] 
        MOVB      XAR6,#0               ; [CPU_] |82| 
$C$L1:    
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 82,column 9,is_stmt,isa 0
        MOV       ACC,*-SP[3] << 1      ; [CPU_] |82| 
        MOVL      XAR4,#_Dlog           ; [CPU_U] |82| 
        ADDL      XAR4,ACC              ; [CPU_] |82| 
        MOVL      *+XAR4[0],XAR6        ; [CPU_] |82| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 83,column 9,is_stmt,isa 0
        MOV       ACC,*-SP[3] << 1      ; [CPU_] |83| 
        MOVL      XAR4,#_Dlog+128       ; [CPU_U] |83| 
        ADDL      XAR4,ACC              ; [CPU_] |83| 
        MOVL      *+XAR4[0],XAR6        ; [CPU_] |83| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 84,column 9,is_stmt,isa 0
        MOV       ACC,*-SP[3] << 1      ; [CPU_] |84| 
        MOVL      XAR4,#_Dlog+384       ; [CPU_U] |84| 
        ADDL      XAR4,ACC              ; [CPU_] |84| 
        MOVL      *+XAR4[0],XAR6        ; [CPU_] |84| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 85,column 9,is_stmt,isa 0
        MOV       ACC,*-SP[3] << 1      ; [CPU_] |85| 
        MOVL      XAR4,#_Dlog+256       ; [CPU_U] |85| 
        ADDL      XAR4,ACC              ; [CPU_] |85| 
        MOVL      *+XAR4[0],XAR6        ; [CPU_] |85| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 86,column 9,is_stmt,isa 0
        MOVL      XAR4,#_Dlog+512       ; [CPU_U] |86| 
        MOV       ACC,*-SP[3] << 1      ; [CPU_] |86| 
        ADDL      XAR4,ACC              ; [CPU_] |86| 
        MOVL      *+XAR4[0],XAR6        ; [CPU_] |86| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 87,column 9,is_stmt,isa 0
        MOVL      XAR4,#_Dlog+640       ; [CPU_U] |87| 
        MOV       ACC,*-SP[3] << 1      ; [CPU_] |87| 
        ADDL      XAR4,ACC              ; [CPU_] |87| 
        MOVL      *+XAR4[0],XAR6        ; [CPU_] |87| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 80,column 33,is_stmt,isa 0
        INC       *-SP[3]               ; [CPU_] |80| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 80,column 14,is_stmt,isa 0
        MOV       AL,*-SP[3]            ; [CPU_] |80| 
        CMPB      AL,#64                ; [CPU_] |80| 
        B         $C$L1,LO              ; [CPU_] |80| 
        ; branchcc occurs ; [] |80| 
$C$L2:    
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 91,column 5,is_stmt,isa 0
        MOVL      XAR4,#$C$FSL1         ; [CPU_U] |91| 
$C$DW$47	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$47, DW_AT_low_pc(0x00)
	.dwattr $C$DW$47, DW_AT_name("_puts")
	.dwattr $C$DW$47, DW_AT_TI_call

        LCR       #_puts                ; [CPU_] |91| 
        ; call occurs [#_puts] ; [] |91| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 92,column 5,is_stmt,isa 0
        MOVZ      AR4,SP                ; [CPU_] |92| 
        SUBB      XAR4,#34              ; [CPU_U] |92| 
        MOVZ      AR4,AR4               ; [CPU_] |92| 
$C$DW$48	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$48, DW_AT_low_pc(0x00)
	.dwattr $C$DW$48, DW_AT_name("_gets")
	.dwattr $C$DW$48, DW_AT_TI_call

        LCR       #_gets                ; [CPU_] |92| 
        ; call occurs [#_gets] ; [] |92| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 93,column 5,is_stmt,isa 0
        MOVZ      AR4,SP                ; [CPU_] |93| 
        MOVB      ACC,#24               ; [CPU_] |93| 
        SUBB      XAR4,#34              ; [CPU_U] |93| 
        MOVZ      AR4,AR4               ; [CPU_] |93| 
$C$DW$49	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$49, DW_AT_low_pc(0x00)
	.dwattr $C$DW$49, DW_AT_name("__atoIQN")
	.dwattr $C$DW$49, DW_AT_TI_call

        LCR       #__atoIQN             ; [CPU_] |93| 
        ; call occurs [#__atoIQN] ; [] |93| 
        MOVW      DP,#_Step+10          ; [CPU_U] 
        MOVL      @_Step+10,ACC         ; [CPU_] |93| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 94,column 5,is_stmt,isa 0
        MOVL      ACC,@_Step+10         ; [CPU_] |94| 
        B         $C$L3,NEQ             ; [CPU_] |94| 
        ; branchcc occurs ; [] |94| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 95,column 9,is_stmt,isa 0
        MOV       ACC,#512 << 15        ; [CPU_] |95| 
        MOVL      @_Step+10,ACC         ; [CPU_] |95| 
$C$L3:    
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 97,column 5,is_stmt,isa 0
        MOVL      XAR4,#$C$FSL2         ; [CPU_U] |97| 
$C$DW$50	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$50, DW_AT_low_pc(0x00)
	.dwattr $C$DW$50, DW_AT_name("_puts")
	.dwattr $C$DW$50, DW_AT_TI_call

        LCR       #_puts                ; [CPU_] |97| 
        ; call occurs [#_puts] ; [] |97| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 98,column 5,is_stmt,isa 0
        MOVZ      AR4,SP                ; [CPU_] |98| 
        SUBB      XAR4,#34              ; [CPU_U] |98| 
        MOVZ      AR4,AR4               ; [CPU_] |98| 
$C$DW$51	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$51, DW_AT_low_pc(0x00)
	.dwattr $C$DW$51, DW_AT_name("_gets")
	.dwattr $C$DW$51, DW_AT_TI_call

        LCR       #_gets                ; [CPU_] |98| 
        ; call occurs [#_gets] ; [] |98| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 99,column 5,is_stmt,isa 0
        MOVZ      AR4,SP                ; [CPU_] |99| 
        MOVB      ACC,#24               ; [CPU_] |99| 
        SUBB      XAR4,#34              ; [CPU_U] |99| 
        MOVZ      AR4,AR4               ; [CPU_] |99| 
$C$DW$52	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$52, DW_AT_low_pc(0x00)
	.dwattr $C$DW$52, DW_AT_name("__atoIQN")
	.dwattr $C$DW$52, DW_AT_TI_call

        LCR       #__atoIQN             ; [CPU_] |99| 
        ; call occurs [#__atoIQN] ; [] |99| 
        MOVW      DP,#_Step+14          ; [CPU_U] 
        MOVL      @_Step+14,ACC         ; [CPU_] |99| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 100,column 5,is_stmt,isa 0
        MOVL      ACC,@_Step+14         ; [CPU_] |100| 
        B         $C$L4,NEQ             ; [CPU_] |100| 
        ; branchcc occurs ; [] |100| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 101,column 9,is_stmt,isa 0
        MOV       ACC,#512 << 15        ; [CPU_] |101| 
        MOVL      @_Step+14,ACC         ; [CPU_] |101| 
$C$L4:    
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 103,column 5,is_stmt,isa 0
        MOVL      XAR4,#$C$FSL3         ; [CPU_U] |103| 
$C$DW$53	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$53, DW_AT_low_pc(0x00)
	.dwattr $C$DW$53, DW_AT_name("_puts")
	.dwattr $C$DW$53, DW_AT_TI_call

        LCR       #_puts                ; [CPU_] |103| 
        ; call occurs [#_puts] ; [] |103| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 104,column 5,is_stmt,isa 0
        MOVZ      AR4,SP                ; [CPU_] |104| 
        SUBB      XAR4,#34              ; [CPU_U] |104| 
        MOVZ      AR4,AR4               ; [CPU_] |104| 
$C$DW$54	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$54, DW_AT_low_pc(0x00)
	.dwattr $C$DW$54, DW_AT_name("_gets")
	.dwattr $C$DW$54, DW_AT_TI_call

        LCR       #_gets                ; [CPU_] |104| 
        ; call occurs [#_gets] ; [] |104| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 105,column 5,is_stmt,isa 0
        MOVZ      AR4,SP                ; [CPU_] |105| 
        MOVB      ACC,#24               ; [CPU_] |105| 
        SUBB      XAR4,#34              ; [CPU_U] |105| 
        MOVZ      AR4,AR4               ; [CPU_] |105| 
$C$DW$55	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$55, DW_AT_low_pc(0x00)
	.dwattr $C$DW$55, DW_AT_name("__atoIQN")
	.dwattr $C$DW$55, DW_AT_TI_call

        LCR       #__atoIQN             ; [CPU_] |105| 
        ; call occurs [#__atoIQN] ; [] |105| 
        MOVW      DP,#_Step+12          ; [CPU_U] 
        MOVL      @_Step+12,ACC         ; [CPU_] |105| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 106,column 5,is_stmt,isa 0
        MOVL      ACC,@_Step+12         ; [CPU_] |106| 
        B         $C$L5,NEQ             ; [CPU_] |106| 
        ; branchcc occurs ; [] |106| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 107,column 9,is_stmt,isa 0
        MOV       ACC,#512 << 15        ; [CPU_] |107| 
        MOVL      @_Step+12,ACC         ; [CPU_] |107| 
$C$L5:    
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 109,column 5,is_stmt,isa 0
        MOVL      XAR4,#$C$FSL4         ; [CPU_U] |109| 
$C$DW$56	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$56, DW_AT_low_pc(0x00)
	.dwattr $C$DW$56, DW_AT_name("_puts")
	.dwattr $C$DW$56, DW_AT_TI_call

        LCR       #_puts                ; [CPU_] |109| 
        ; call occurs [#_puts] ; [] |109| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 110,column 5,is_stmt,isa 0
        MOVZ      AR4,SP                ; [CPU_] |110| 
        SUBB      XAR4,#34              ; [CPU_U] |110| 
        MOVZ      AR4,AR4               ; [CPU_] |110| 
$C$DW$57	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$57, DW_AT_low_pc(0x00)
	.dwattr $C$DW$57, DW_AT_name("_gets")
	.dwattr $C$DW$57, DW_AT_TI_call

        LCR       #_gets                ; [CPU_] |110| 
        ; call occurs [#_gets] ; [] |110| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 111,column 5,is_stmt,isa 0
        MOVZ      AR4,SP                ; [CPU_] |111| 
        MOVB      ACC,#24               ; [CPU_] |111| 
        SUBB      XAR4,#34              ; [CPU_U] |111| 
        MOVZ      AR4,AR4               ; [CPU_] |111| 
$C$DW$58	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$58, DW_AT_low_pc(0x00)
	.dwattr $C$DW$58, DW_AT_name("__atoIQN")
	.dwattr $C$DW$58, DW_AT_TI_call

        LCR       #__atoIQN             ; [CPU_] |111| 
        ; call occurs [#__atoIQN] ; [] |111| 
        MOVW      DP,#_Step+16          ; [CPU_U] 
        MOVL      @_Step+16,ACC         ; [CPU_] |111| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 112,column 5,is_stmt,isa 0
        MOVL      ACC,@_Step+16         ; [CPU_] |112| 
        B         $C$L6,NEQ             ; [CPU_] |112| 
        ; branchcc occurs ; [] |112| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 113,column 9,is_stmt,isa 0
        MOV       ACC,#512 << 15        ; [CPU_] |113| 
        MOVL      @_Step+16,ACC         ; [CPU_] |113| 
$C$L6:    
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 116,column 5,is_stmt,isa 0
        MOVL      ACC,@_Step+12         ; [CPU_] |116| 
        MOVL      *-SP[2],ACC           ; [CPU_] |116| 
        MOVL      ACC,@_Step+10         ; [CPU_] |116| 
$C$DW$59	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$59, DW_AT_low_pc(0x00)
	.dwattr $C$DW$59, DW_AT_name("__IQ24mag")
	.dwattr $C$DW$59, DW_AT_TI_call

        LCR       #__IQ24mag            ; [CPU_] |116| 
        ; call occurs [#__IQ24mag] ; [] |116| 
        MOVL      *-SP[14],ACC          ; [CPU_] |116| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 118,column 9,is_stmt,isa 0
        MOV       *-SP[3],#0            ; [CPU_] |118| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 118,column 14,is_stmt,isa 0
        MOV       AL,*-SP[3]            ; [CPU_] |118| 
        CMPB      AL,#64                ; [CPU_] |118| 
        B         $C$L10,HIS            ; [CPU_] |118| 
        ; branchcc occurs ; [] |118| 
$C$L7:    
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 121,column 9,is_stmt,isa 0
        MOVW      DP,#_Step+6           ; [CPU_U] 
        MOVL      ACC,@_Step+6          ; [CPU_] |121| 
$C$DW$60	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$60, DW_AT_low_pc(0x00)
	.dwattr $C$DW$60, DW_AT_name("__IQ24sin")
	.dwattr $C$DW$60, DW_AT_TI_call

        LCR       #__IQ24sin            ; [CPU_] |121| 
        ; call occurs [#__IQ24sin] ; [] |121| 
        MOVW      DP,#_Step+10          ; [CPU_U] 
        CLRC      SXM                   ; [CPU_] 
        MOVL      XT,ACC                ; [CPU_] |121| 
        MOVL      XAR4,#_Dlog           ; [CPU_U] |121| 
        IMPYL     P,XT,@_Step+10        ; [CPU_] |121| 
        QMPYL     ACC,XT,@_Step+10      ; [CPU_] |121| 
        LSL64     ACC:P,#8              ; [CPU_] |121| 
        MOVL      XAR6,ACC              ; [CPU_] |121| 
        MOVL      *-SP[6],ACC           ; [CPU_] |121| 
        MOV       ACC,*-SP[3] << 1      ; [CPU_] |121| 
        ADDL      XAR4,ACC              ; [CPU_] |121| 
        MOVL      *+XAR4[0],XAR6        ; [CPU_] |121| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 122,column 9,is_stmt,isa 0
        MOVL      ACC,@_Step+8          ; [CPU_] |122| 
$C$DW$61	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$61, DW_AT_low_pc(0x00)
	.dwattr $C$DW$61, DW_AT_name("__IQ24sin")
	.dwattr $C$DW$61, DW_AT_TI_call

        LCR       #__IQ24sin            ; [CPU_] |122| 
        ; call occurs [#__IQ24sin] ; [] |122| 
        MOVW      DP,#_Step+12          ; [CPU_U] 
        ABS       ACC                   ; [CPU_] |122| 
        CLRC      SXM                   ; [CPU_] 
        MOVL      XAR4,#_Dlog+128       ; [CPU_U] |122| 
        MOVL      XT,ACC                ; [CPU_] |122| 
        IMPYL     P,XT,@_Step+12        ; [CPU_] |122| 
        QMPYL     ACC,XT,@_Step+12      ; [CPU_] |122| 
        LSL64     ACC:P,#8              ; [CPU_] |122| 
        MOVL      XAR6,ACC              ; [CPU_] |122| 
        MOVL      *-SP[8],ACC           ; [CPU_] |122| 
        MOV       ACC,*-SP[3] << 1      ; [CPU_] |122| 
        ADDL      XAR4,ACC              ; [CPU_] |122| 
        MOVL      *+XAR4[0],XAR6        ; [CPU_] |122| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 127,column 9,is_stmt,isa 0
        MOVL      ACC,*-SP[8]           ; [CPU_] |127| 
        MOVL      *-SP[2],ACC           ; [CPU_] |127| 
        MOVL      ACC,*-SP[6]           ; [CPU_] |127| 
$C$DW$62	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$62, DW_AT_low_pc(0x00)
	.dwattr $C$DW$62, DW_AT_name("__IQ24mag")
	.dwattr $C$DW$62, DW_AT_TI_call

        LCR       #__IQ24mag            ; [CPU_] |127| 
        ; call occurs [#__IQ24mag] ; [] |127| 
        MOVL      *-SP[12],ACC          ; [CPU_] |127| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 128,column 9,is_stmt,isa 0
        MOVL      ACC,*-SP[14]          ; [CPU_] |128| 
        MOVL      *-SP[2],ACC           ; [CPU_] |128| 
        MOVL      ACC,*-SP[12]          ; [CPU_] |128| 
$C$DW$63	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$63, DW_AT_low_pc(0x00)
	.dwattr $C$DW$63, DW_AT_name("__IQ24div")
	.dwattr $C$DW$63, DW_AT_TI_call

        LCR       #__IQ24div            ; [CPU_] |128| 
        ; call occurs [#__IQ24div] ; [] |128| 
        CLRC      SXM                   ; [CPU_] 
        MOVL      XAR6,ACC              ; [CPU_] |128| 
        MOVL      XAR4,#_Dlog+384       ; [CPU_U] |128| 
        MOV       ACC,*-SP[3] << 1      ; [CPU_] |128| 
        ADDL      XAR4,ACC              ; [CPU_] |128| 
        MOVL      *+XAR4[0],XAR6        ; [CPU_] |128| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 133,column 9,is_stmt,isa 0
        MOVL      ACC,*-SP[6]           ; [CPU_] |133| 
        MOVL      *-SP[2],ACC           ; [CPU_] |133| 
        MOVL      ACC,*-SP[8]           ; [CPU_] |133| 
$C$DW$64	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$64, DW_AT_low_pc(0x00)
	.dwattr $C$DW$64, DW_AT_name("__IQ24atan2PU")
	.dwattr $C$DW$64, DW_AT_TI_call

        LCR       #__IQ24atan2PU        ; [CPU_] |133| 
        ; call occurs [#__IQ24atan2PU] ; [] |133| 
        MOVL      *-SP[10],ACC          ; [CPU_] |133| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 134,column 9,is_stmt,isa 0
        MOVL      XAR4,#360             ; [CPU_U] |134| 
        MOVL      *-SP[2],XAR4          ; [CPU_] |134| 
        MOVL      ACC,*-SP[10]          ; [CPU_] |134| 
$C$DW$65	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$65, DW_AT_low_pc(0x00)
	.dwattr $C$DW$65, DW_AT_name("__IQ24mpyI32int")
	.dwattr $C$DW$65, DW_AT_TI_call

        LCR       #__IQ24mpyI32int      ; [CPU_] |134| 
        ; call occurs [#__IQ24mpyI32int] ; [] |134| 
        MOVL      XAR6,ACC              ; [CPU_] |134| 
        CLRC      SXM                   ; [CPU_] 
        MOVL      XAR4,#_Dlog+256       ; [CPU_U] |134| 
        MOV       ACC,*-SP[3] << 1      ; [CPU_] |134| 
        ADDL      XAR4,ACC              ; [CPU_] |134| 
        MOVL      *+XAR4[0],XAR6        ; [CPU_] |134| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 137,column 9,is_stmt,isa 0
        MOVZ      AR4,SP                ; [CPU_] |137| 
        MOV       AL,*-SP[3]            ; [CPU_] |137| 
        SUBB      XAR4,#44              ; [CPU_U] |137| 
        MOVZ      AR6,AR4               ; [CPU_] |137| 
$C$DW$66	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$66, DW_AT_low_pc(0x00)
	.dwattr $C$DW$66, DW_AT_name("U$$TOFD")
	.dwattr $C$DW$66, DW_AT_TI_call

        LCR       #U$$TOFD              ; [CPU_] |137| 
        ; call occurs [#U$$TOFD] ; [] |137| 
        MOVZ      AR4,SP                ; [CPU_] |137| 
        MOVZ      AR6,SP                ; [CPU_] |137| 
        MOVL      XAR5,#$C$FL1          ; [CPU_U] |137| 
        SUBB      XAR4,#44              ; [CPU_U] |137| 
        SUBB      XAR6,#40              ; [CPU_U] |137| 
        MOVZ      AR4,AR4               ; [CPU_] |137| 
        MOVZ      AR6,AR6               ; [CPU_] |137| 
$C$DW$67	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$67, DW_AT_low_pc(0x00)
	.dwattr $C$DW$67, DW_AT_name("FD$$MPY")
	.dwattr $C$DW$67, DW_AT_TI_call

        LCR       #FD$$MPY              ; [CPU_] |137| 
        ; call occurs [#FD$$MPY] ; [] |137| 
        MOVZ      AR4,SP                ; [CPU_] |137| 
        SUBB      XAR4,#40              ; [CPU_U] |137| 
        MOVZ      AR4,AR4               ; [CPU_] |137| 
$C$DW$68	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$68, DW_AT_low_pc(0x00)
	.dwattr $C$DW$68, DW_AT_name("FD$$TOL")
	.dwattr $C$DW$68, DW_AT_TI_call

        LCR       #FD$$TOL              ; [CPU_] |137| 
        ; call occurs [#FD$$TOL] ; [] |137| 
        MOVL      XAR4,#1258291         ; [CPU_U] |137| 
        MOVL      XT,XAR4               ; [CPU_] |137| 
        IMPYL     P,XT,ACC              ; [CPU_] |137| 
        QMPYL     ACC,XT,ACC            ; [CPU_] |137| 
        LSL64     ACC:P,#8              ; [CPU_] |137| 
$C$DW$69	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$69, DW_AT_low_pc(0x00)
	.dwattr $C$DW$69, DW_AT_name("__IQ24exp")
	.dwattr $C$DW$69, DW_AT_TI_call

        LCR       #__IQ24exp            ; [CPU_] |137| 
        ; call occurs [#__IQ24exp] ; [] |137| 
        CLRC      SXM                   ; [CPU_] 
        MOVL      XAR6,ACC              ; [CPU_] |137| 
        MOVL      XAR4,#_Dlog+512       ; [CPU_U] |137| 
        MOV       ACC,*-SP[3] << 1      ; [CPU_] |137| 
        ADDL      XAR4,ACC              ; [CPU_] |137| 
        MOVL      *+XAR4[0],XAR6        ; [CPU_] |137| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 140,column 9,is_stmt,isa 0
        MOV       ACC,*-SP[3] << 1      ; [CPU_] |140| 
        MOVL      XAR4,#_Dlog+512       ; [CPU_U] |140| 
        ADDL      XAR4,ACC              ; [CPU_] |140| 
        MOVL      ACC,*+XAR4[0]         ; [CPU_] |140| 
$C$DW$70	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$70, DW_AT_low_pc(0x00)
	.dwattr $C$DW$70, DW_AT_name("__IQ24log")
	.dwattr $C$DW$70, DW_AT_TI_call

        LCR       #__IQ24log            ; [CPU_] |140| 
        ; call occurs [#__IQ24log] ; [] |140| 
        CLRC      SXM                   ; [CPU_] 
        MOVL      XAR6,ACC              ; [CPU_] |140| 
        MOVL      XAR4,#_Dlog+640       ; [CPU_U] |140| 
        MOV       ACC,*-SP[3] << 1      ; [CPU_] |140| 
        ADDL      XAR4,ACC              ; [CPU_] |140| 
        MOVL      *+XAR4[0],XAR6        ; [CPU_] |140| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 143,column 9,is_stmt,isa 0
        MOVW      DP,#_Step             ; [CPU_U] 
        MOVL      XT,@_Step             ; [CPU_] |143| 
        IMPYL     P,XT,@_Step+14        ; [CPU_] |143| 
        QMPYL     ACC,XT,@_Step+14      ; [CPU_] |143| 
        LSL64     ACC:P,#8              ; [CPU_] |143| 
        ADDL      @_Step+6,ACC          ; [CPU_] |143| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 144,column 9,is_stmt,isa 0
        MOV       AL,#32472             ; [CPU_] |144| 
        MOV       AH,#1608              ; [CPU_] |144| 
        CMPL      ACC,@_Step+6          ; [CPU_] |144| 
        B         $C$L8,GEQ             ; [CPU_] |144| 
        ; branchcc occurs ; [] |144| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 145,column 13,is_stmt,isa 0
        SUBL      @_Step+6,ACC          ; [CPU_] |145| 
$C$L8:    
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 147,column 9,is_stmt,isa 0
        MOVL      XT,@_Step+2           ; [CPU_] |147| 
        IMPYL     P,XT,@_Step+16        ; [CPU_] |147| 
        QMPYL     ACC,XT,@_Step+16      ; [CPU_] |147| 
        LSL64     ACC:P,#8              ; [CPU_] |147| 
        ADDL      @_Step+8,ACC          ; [CPU_] |147| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 148,column 9,is_stmt,isa 0
        MOV       AL,#32472             ; [CPU_] |148| 
        MOV       AH,#1608              ; [CPU_] |148| 
        CMPL      ACC,@_Step+8          ; [CPU_] |148| 
        B         $C$L9,GEQ             ; [CPU_] |148| 
        ; branchcc occurs ; [] |148| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 149,column 13,is_stmt,isa 0
        SUBL      @_Step+8,ACC          ; [CPU_] |149| 
$C$L9:    
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 118,column 33,is_stmt,isa 0
        INC       *-SP[3]               ; [CPU_] |118| 
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 118,column 14,is_stmt,isa 0
        MOV       AL,*-SP[3]            ; [CPU_] |118| 
        CMPB      AL,#64                ; [CPU_] |118| 
        B         $C$L7,LO              ; [CPU_] |118| 
        ; branchcc occurs ; [] |118| 
$C$L10:    
	.dwpsn	file "D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c",line 152,column 1,is_stmt,isa 0
        MOVB      AL,#0                 ; [CPU_] |152| 
        SUBB      SP,#44                ; [CPU_U] 
	.dwcfi	cfa_offset, -2
$C$DW$71	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$71, DW_AT_low_pc(0x00)
	.dwattr $C$DW$71, DW_AT_TI_return

        LRETR     ; [CPU_] 
        ; return occurs ; [] 
	.dwattr $C$DW$37, DW_AT_TI_end_file("D:/work/DSP/ProgramBomb/ProgramBombDebug/math/IQmath/v160/examples_ccsv4/C/source/IQsample.c")
	.dwattr $C$DW$37, DW_AT_TI_end_line(0x98)
	.dwattr $C$DW$37, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$37

;***************************************************************
;* FLOATING-POINT CONSTANTS                                    *
;***************************************************************
	.sect	".econst"
	.align	2
$C$FL1:	.xldouble	$strtod("0x1p+24")
;***************************************************************
;* FAR STRINGS                                                 *
;***************************************************************
	.sect	".econst:.string"
	.align	2
$C$FSL1:	.string	10,"Enter waveform X gain (default = 1.0)= ",0
	.align	2
$C$FSL2:	.string	10,"Enter waveform X freq (default = 1.0)= ",0
	.align	2
$C$FSL3:	.string	10,"Enter waveform Y gain (default = 1.0)= ",0
	.align	2
$C$FSL4:	.string	10,"Enter waveform Y freq (default = 1.0)= ",0
;**************************************************************
;* UNDEFINED EXTERNAL REFERENCES                              *
;**************************************************************
	.global	_puts
	.global	__IQ24mag
	.global	__IQ24exp
	.global	__IQ24mpyI32int
	.global	__IQ24log
	.global	__atoIQN
	.global	_gets
	.global	__IQ24div
	.global	__IQ24acos
	.global	__IQ24atan2PU
	.global	__IQ24sin
	.global	FD$$MPY
	.global	U$$TOFD
	.global	FD$$TOL

;***************************************************************
;* TYPE INFORMATION                                            *
;***************************************************************

$C$DW$T$22	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$22, DW_AT_name("DATA_LOG_C")
	.dwattr $C$DW$T$22, DW_AT_byte_size(0x300)
$C$DW$72	.dwtag  DW_TAG_member
	.dwattr $C$DW$72, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$72, DW_AT_name("Xwaveform")
	.dwattr $C$DW$72, DW_AT_TI_symbol_name("_Xwaveform")
	.dwattr $C$DW$72, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$72, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$73	.dwtag  DW_TAG_member
	.dwattr $C$DW$73, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$73, DW_AT_name("Ywaveform")
	.dwattr $C$DW$73, DW_AT_TI_symbol_name("_Ywaveform")
	.dwattr $C$DW$73, DW_AT_data_member_location[DW_OP_plus_uconst 0x80]
	.dwattr $C$DW$73, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$74	.dwtag  DW_TAG_member
	.dwattr $C$DW$74, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$74, DW_AT_name("Phase")
	.dwattr $C$DW$74, DW_AT_TI_symbol_name("_Phase")
	.dwattr $C$DW$74, DW_AT_data_member_location[DW_OP_plus_uconst 0x100]
	.dwattr $C$DW$74, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$75	.dwtag  DW_TAG_member
	.dwattr $C$DW$75, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$75, DW_AT_name("Mag")
	.dwattr $C$DW$75, DW_AT_TI_symbol_name("_Mag")
	.dwattr $C$DW$75, DW_AT_data_member_location[DW_OP_plus_uconst 0x180]
	.dwattr $C$DW$75, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$76	.dwtag  DW_TAG_member
	.dwattr $C$DW$76, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$76, DW_AT_name("Exp")
	.dwattr $C$DW$76, DW_AT_TI_symbol_name("_Exp")
	.dwattr $C$DW$76, DW_AT_data_member_location[DW_OP_plus_uconst 0x200]
	.dwattr $C$DW$76, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$77	.dwtag  DW_TAG_member
	.dwattr $C$DW$77, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$77, DW_AT_name("Log")
	.dwattr $C$DW$77, DW_AT_TI_symbol_name("_Log")
	.dwattr $C$DW$77, DW_AT_data_member_location[DW_OP_plus_uconst 0x280]
	.dwattr $C$DW$77, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$22


$C$DW$T$23	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$23, DW_AT_name("STEP")
	.dwattr $C$DW$T$23, DW_AT_byte_size(0x12)
$C$DW$78	.dwtag  DW_TAG_member
	.dwattr $C$DW$78, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$78, DW_AT_name("Xsize")
	.dwattr $C$DW$78, DW_AT_TI_symbol_name("_Xsize")
	.dwattr $C$DW$78, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$78, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$79	.dwtag  DW_TAG_member
	.dwattr $C$DW$79, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$79, DW_AT_name("Ysize")
	.dwattr $C$DW$79, DW_AT_TI_symbol_name("_Ysize")
	.dwattr $C$DW$79, DW_AT_data_member_location[DW_OP_plus_uconst 0x2]
	.dwattr $C$DW$79, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$80	.dwtag  DW_TAG_member
	.dwattr $C$DW$80, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$80, DW_AT_name("Yoffset")
	.dwattr $C$DW$80, DW_AT_TI_symbol_name("_Yoffset")
	.dwattr $C$DW$80, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$80, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$81	.dwtag  DW_TAG_member
	.dwattr $C$DW$81, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$81, DW_AT_name("X")
	.dwattr $C$DW$81, DW_AT_TI_symbol_name("_X")
	.dwattr $C$DW$81, DW_AT_data_member_location[DW_OP_plus_uconst 0x6]
	.dwattr $C$DW$81, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$82	.dwtag  DW_TAG_member
	.dwattr $C$DW$82, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$82, DW_AT_name("Y")
	.dwattr $C$DW$82, DW_AT_TI_symbol_name("_Y")
	.dwattr $C$DW$82, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$82, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$83	.dwtag  DW_TAG_member
	.dwattr $C$DW$83, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$83, DW_AT_name("GainX")
	.dwattr $C$DW$83, DW_AT_TI_symbol_name("_GainX")
	.dwattr $C$DW$83, DW_AT_data_member_location[DW_OP_plus_uconst 0xa]
	.dwattr $C$DW$83, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$84	.dwtag  DW_TAG_member
	.dwattr $C$DW$84, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$84, DW_AT_name("GainY")
	.dwattr $C$DW$84, DW_AT_TI_symbol_name("_GainY")
	.dwattr $C$DW$84, DW_AT_data_member_location[DW_OP_plus_uconst 0xc]
	.dwattr $C$DW$84, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$85	.dwtag  DW_TAG_member
	.dwattr $C$DW$85, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$85, DW_AT_name("FreqX")
	.dwattr $C$DW$85, DW_AT_TI_symbol_name("_FreqX")
	.dwattr $C$DW$85, DW_AT_data_member_location[DW_OP_plus_uconst 0xe]
	.dwattr $C$DW$85, DW_AT_accessibility(DW_ACCESS_public)

$C$DW$86	.dwtag  DW_TAG_member
	.dwattr $C$DW$86, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$86, DW_AT_name("FreqY")
	.dwattr $C$DW$86, DW_AT_TI_symbol_name("_FreqY")
	.dwattr $C$DW$86, DW_AT_data_member_location[DW_OP_plus_uconst 0x10]
	.dwattr $C$DW$86, DW_AT_accessibility(DW_ACCESS_public)

	.dwendtag $C$DW$T$23

$C$DW$T$2	.dwtag  DW_TAG_unspecified_type
	.dwattr $C$DW$T$2, DW_AT_name("void")

$C$DW$T$4	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$4, DW_AT_encoding(DW_ATE_boolean)
	.dwattr $C$DW$T$4, DW_AT_name("bool")
	.dwattr $C$DW$T$4, DW_AT_byte_size(0x01)

$C$DW$T$5	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$5, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$5, DW_AT_name("signed char")
	.dwattr $C$DW$T$5, DW_AT_byte_size(0x01)

$C$DW$T$6	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$6, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$6, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$6, DW_AT_byte_size(0x01)

$C$DW$T$7	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$7, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$7, DW_AT_name("wchar_t")
	.dwattr $C$DW$T$7, DW_AT_byte_size(0x01)

$C$DW$T$8	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$8, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$8, DW_AT_name("short")
	.dwattr $C$DW$T$8, DW_AT_byte_size(0x01)

$C$DW$T$9	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$9, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$9, DW_AT_name("unsigned short")
	.dwattr $C$DW$T$9, DW_AT_byte_size(0x01)

$C$DW$T$10	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$10, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$10, DW_AT_name("int")
	.dwattr $C$DW$T$10, DW_AT_byte_size(0x01)

$C$DW$T$30	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$30, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$30, DW_AT_address_class(0x20)

$C$DW$T$11	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$11, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$11, DW_AT_name("unsigned int")
	.dwattr $C$DW$T$11, DW_AT_byte_size(0x01)

$C$DW$T$12	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$12, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$12, DW_AT_name("long")
	.dwattr $C$DW$T$12, DW_AT_byte_size(0x02)


$C$DW$T$21	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$21, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$21, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$21, DW_AT_byte_size(0x80)
$C$DW$87	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$87, DW_AT_upper_bound(0x3f)

	.dwendtag $C$DW$T$21

$C$DW$T$19	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$19, DW_AT_name("_iq")
	.dwattr $C$DW$T$19, DW_AT_type(*$C$DW$T$12)
	.dwattr $C$DW$T$19, DW_AT_language(DW_LANG_C)


$C$DW$T$20	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$20, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$T$20, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$20, DW_AT_byte_size(0x80)
$C$DW$88	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$88, DW_AT_upper_bound(0x3f)

	.dwendtag $C$DW$T$20

$C$DW$T$13	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$13, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$13, DW_AT_name("unsigned long")
	.dwattr $C$DW$T$13, DW_AT_byte_size(0x02)

$C$DW$T$14	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$14, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$14, DW_AT_name("long long")
	.dwattr $C$DW$T$14, DW_AT_byte_size(0x04)

$C$DW$T$15	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$15, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$15, DW_AT_name("unsigned long long")
	.dwattr $C$DW$T$15, DW_AT_byte_size(0x04)

$C$DW$T$16	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$16, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$16, DW_AT_name("float")
	.dwattr $C$DW$T$16, DW_AT_byte_size(0x02)

$C$DW$T$17	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$17, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$17, DW_AT_name("double")
	.dwattr $C$DW$T$17, DW_AT_byte_size(0x02)

$C$DW$T$18	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$18, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$18, DW_AT_name("long double")
	.dwattr $C$DW$T$18, DW_AT_byte_size(0x04)

$C$DW$89	.dwtag  DW_TAG_TI_far_type
	.dwattr $C$DW$89, DW_AT_type(*$C$DW$T$5)

$C$DW$T$25	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$25, DW_AT_type(*$C$DW$89)

$C$DW$T$26	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$26, DW_AT_type(*$C$DW$T$25)
	.dwattr $C$DW$T$26, DW_AT_address_class(0x20)

$C$DW$T$40	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$40, DW_AT_type(*$C$DW$T$5)
	.dwattr $C$DW$T$40, DW_AT_address_class(0x20)


$C$DW$T$43	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$43, DW_AT_type(*$C$DW$T$5)
	.dwattr $C$DW$T$43, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$43, DW_AT_byte_size(0x14)
$C$DW$90	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$90, DW_AT_upper_bound(0x13)

	.dwendtag $C$DW$T$43

	.dwattr $C$DW$CU, DW_AT_language(DW_LANG_C)

;***************************************************************
;* DWARF CIE ENTRIES                                           *
;***************************************************************

$C$DW$CIE	.dwcie 26
	.dwcfi	cfa_register, 20
	.dwcfi	cfa_offset, 0
	.dwcfi	undefined, 0
	.dwcfi	undefined, 1
	.dwcfi	undefined, 2
	.dwcfi	undefined, 3
	.dwcfi	undefined, 20
	.dwcfi	undefined, 21
	.dwcfi	undefined, 22
	.dwcfi	undefined, 23
	.dwcfi	undefined, 24
	.dwcfi	undefined, 25
	.dwcfi	undefined, 26
	.dwcfi	same_value, 28
	.dwcfi	undefined, 29
	.dwcfi	undefined, 30
	.dwcfi	undefined, 31
	.dwcfi	undefined, 32
	.dwcfi	undefined, 33
	.dwcfi	undefined, 34
	.dwcfi	undefined, 35
	.dwcfi	undefined, 36
	.dwcfi	undefined, 37
	.dwcfi	undefined, 38
	.dwcfi	undefined, 75
	.dwcfi	undefined, 76
	.dwcfi	undefined, 77
	.dwcfi	undefined, 4
	.dwcfi	undefined, 5
	.dwcfi	same_value, 6
	.dwcfi	same_value, 7
	.dwcfi	same_value, 8
	.dwcfi	same_value, 9
	.dwcfi	same_value, 10
	.dwcfi	same_value, 11
	.dwcfi	undefined, 12
	.dwcfi	undefined, 13
	.dwcfi	undefined, 14
	.dwcfi	undefined, 15
	.dwcfi	undefined, 16
	.dwcfi	undefined, 17
	.dwcfi	undefined, 18
	.dwcfi	undefined, 19
	.dwcfi	undefined, 43
	.dwcfi	undefined, 44
	.dwcfi	undefined, 47
	.dwcfi	undefined, 48
	.dwcfi	undefined, 51
	.dwcfi	undefined, 52
	.dwcfi	undefined, 55
	.dwcfi	undefined, 56
	.dwcfi	same_value, 59
	.dwcfi	same_value, 60
	.dwcfi	same_value, 63
	.dwcfi	same_value, 64
	.dwcfi	same_value, 67
	.dwcfi	same_value, 68
	.dwcfi	same_value, 71
	.dwcfi	same_value, 72
	.dwcfi	undefined, 73
	.dwcfi	undefined, 74
	.dwcfi	undefined, 39
	.dwcfi	undefined, 40
	.dwcfi	undefined, 27
	.dwendentry

;***************************************************************
;* DWARF REGISTER MAP                                          *
;***************************************************************

$C$DW$91	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$91, DW_AT_name("AL")
	.dwattr $C$DW$91, DW_AT_location[DW_OP_reg0]

$C$DW$92	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$92, DW_AT_name("AH")
	.dwattr $C$DW$92, DW_AT_location[DW_OP_reg1]

$C$DW$93	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$93, DW_AT_name("PL")
	.dwattr $C$DW$93, DW_AT_location[DW_OP_reg2]

$C$DW$94	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$94, DW_AT_name("PH")
	.dwattr $C$DW$94, DW_AT_location[DW_OP_reg3]

$C$DW$95	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$95, DW_AT_name("SP")
	.dwattr $C$DW$95, DW_AT_location[DW_OP_reg20]

$C$DW$96	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$96, DW_AT_name("XT")
	.dwattr $C$DW$96, DW_AT_location[DW_OP_reg21]

$C$DW$97	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$97, DW_AT_name("T")
	.dwattr $C$DW$97, DW_AT_location[DW_OP_reg22]

$C$DW$98	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$98, DW_AT_name("ST0")
	.dwattr $C$DW$98, DW_AT_location[DW_OP_reg23]

$C$DW$99	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$99, DW_AT_name("ST1")
	.dwattr $C$DW$99, DW_AT_location[DW_OP_reg24]

$C$DW$100	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$100, DW_AT_name("PC")
	.dwattr $C$DW$100, DW_AT_location[DW_OP_reg25]

$C$DW$101	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$101, DW_AT_name("RPC")
	.dwattr $C$DW$101, DW_AT_location[DW_OP_reg26]

$C$DW$102	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$102, DW_AT_name("FP")
	.dwattr $C$DW$102, DW_AT_location[DW_OP_reg28]

$C$DW$103	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$103, DW_AT_name("DP")
	.dwattr $C$DW$103, DW_AT_location[DW_OP_reg29]

$C$DW$104	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$104, DW_AT_name("SXM")
	.dwattr $C$DW$104, DW_AT_location[DW_OP_reg30]

$C$DW$105	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$105, DW_AT_name("PM")
	.dwattr $C$DW$105, DW_AT_location[DW_OP_reg31]

$C$DW$106	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$106, DW_AT_name("OVM")
	.dwattr $C$DW$106, DW_AT_location[DW_OP_regx 0x20]

$C$DW$107	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$107, DW_AT_name("PAGE0")
	.dwattr $C$DW$107, DW_AT_location[DW_OP_regx 0x21]

$C$DW$108	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$108, DW_AT_name("AMODE")
	.dwattr $C$DW$108, DW_AT_location[DW_OP_regx 0x22]

$C$DW$109	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$109, DW_AT_name("INTM")
	.dwattr $C$DW$109, DW_AT_location[DW_OP_regx 0x23]

$C$DW$110	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$110, DW_AT_name("IFR")
	.dwattr $C$DW$110, DW_AT_location[DW_OP_regx 0x24]

$C$DW$111	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$111, DW_AT_name("IER")
	.dwattr $C$DW$111, DW_AT_location[DW_OP_regx 0x25]

$C$DW$112	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$112, DW_AT_name("V")
	.dwattr $C$DW$112, DW_AT_location[DW_OP_regx 0x26]

$C$DW$113	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$113, DW_AT_name("PSEUDOH")
	.dwattr $C$DW$113, DW_AT_location[DW_OP_regx 0x4c]

$C$DW$114	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$114, DW_AT_name("VOL")
	.dwattr $C$DW$114, DW_AT_location[DW_OP_regx 0x4d]

$C$DW$115	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$115, DW_AT_name("AR0")
	.dwattr $C$DW$115, DW_AT_location[DW_OP_reg4]

$C$DW$116	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$116, DW_AT_name("XAR0")
	.dwattr $C$DW$116, DW_AT_location[DW_OP_reg5]

$C$DW$117	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$117, DW_AT_name("AR1")
	.dwattr $C$DW$117, DW_AT_location[DW_OP_reg6]

$C$DW$118	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$118, DW_AT_name("XAR1")
	.dwattr $C$DW$118, DW_AT_location[DW_OP_reg7]

$C$DW$119	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$119, DW_AT_name("AR2")
	.dwattr $C$DW$119, DW_AT_location[DW_OP_reg8]

$C$DW$120	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$120, DW_AT_name("XAR2")
	.dwattr $C$DW$120, DW_AT_location[DW_OP_reg9]

$C$DW$121	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$121, DW_AT_name("AR3")
	.dwattr $C$DW$121, DW_AT_location[DW_OP_reg10]

$C$DW$122	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$122, DW_AT_name("XAR3")
	.dwattr $C$DW$122, DW_AT_location[DW_OP_reg11]

$C$DW$123	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$123, DW_AT_name("AR4")
	.dwattr $C$DW$123, DW_AT_location[DW_OP_reg12]

$C$DW$124	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$124, DW_AT_name("XAR4")
	.dwattr $C$DW$124, DW_AT_location[DW_OP_reg13]

$C$DW$125	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$125, DW_AT_name("AR5")
	.dwattr $C$DW$125, DW_AT_location[DW_OP_reg14]

$C$DW$126	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$126, DW_AT_name("XAR5")
	.dwattr $C$DW$126, DW_AT_location[DW_OP_reg15]

$C$DW$127	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$127, DW_AT_name("AR6")
	.dwattr $C$DW$127, DW_AT_location[DW_OP_reg16]

$C$DW$128	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$128, DW_AT_name("XAR6")
	.dwattr $C$DW$128, DW_AT_location[DW_OP_reg17]

$C$DW$129	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$129, DW_AT_name("AR7")
	.dwattr $C$DW$129, DW_AT_location[DW_OP_reg18]

$C$DW$130	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$130, DW_AT_name("XAR7")
	.dwattr $C$DW$130, DW_AT_location[DW_OP_reg19]

$C$DW$131	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$131, DW_AT_name("R0HL")
	.dwattr $C$DW$131, DW_AT_location[DW_OP_regx 0x2b]

$C$DW$132	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$132, DW_AT_name("R0H")
	.dwattr $C$DW$132, DW_AT_location[DW_OP_regx 0x2c]

$C$DW$133	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$133, DW_AT_name("R1HL")
	.dwattr $C$DW$133, DW_AT_location[DW_OP_regx 0x2f]

$C$DW$134	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$134, DW_AT_name("R1H")
	.dwattr $C$DW$134, DW_AT_location[DW_OP_regx 0x30]

$C$DW$135	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$135, DW_AT_name("R2HL")
	.dwattr $C$DW$135, DW_AT_location[DW_OP_regx 0x33]

$C$DW$136	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$136, DW_AT_name("R2H")
	.dwattr $C$DW$136, DW_AT_location[DW_OP_regx 0x34]

$C$DW$137	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$137, DW_AT_name("R3HL")
	.dwattr $C$DW$137, DW_AT_location[DW_OP_regx 0x37]

$C$DW$138	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$138, DW_AT_name("R3H")
	.dwattr $C$DW$138, DW_AT_location[DW_OP_regx 0x38]

$C$DW$139	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$139, DW_AT_name("R4HL")
	.dwattr $C$DW$139, DW_AT_location[DW_OP_regx 0x3b]

$C$DW$140	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$140, DW_AT_name("R4H")
	.dwattr $C$DW$140, DW_AT_location[DW_OP_regx 0x3c]

$C$DW$141	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$141, DW_AT_name("R5HL")
	.dwattr $C$DW$141, DW_AT_location[DW_OP_regx 0x3f]

$C$DW$142	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$142, DW_AT_name("R5H")
	.dwattr $C$DW$142, DW_AT_location[DW_OP_regx 0x40]

$C$DW$143	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$143, DW_AT_name("R6HL")
	.dwattr $C$DW$143, DW_AT_location[DW_OP_regx 0x43]

$C$DW$144	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$144, DW_AT_name("R6H")
	.dwattr $C$DW$144, DW_AT_location[DW_OP_regx 0x44]

$C$DW$145	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$145, DW_AT_name("R7HL")
	.dwattr $C$DW$145, DW_AT_location[DW_OP_regx 0x47]

$C$DW$146	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$146, DW_AT_name("R7H")
	.dwattr $C$DW$146, DW_AT_location[DW_OP_regx 0x48]

$C$DW$147	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$147, DW_AT_name("RBL")
	.dwattr $C$DW$147, DW_AT_location[DW_OP_regx 0x49]

$C$DW$148	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$148, DW_AT_name("RB")
	.dwattr $C$DW$148, DW_AT_location[DW_OP_regx 0x4a]

$C$DW$149	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$149, DW_AT_name("STFL")
	.dwattr $C$DW$149, DW_AT_location[DW_OP_regx 0x27]

$C$DW$150	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$150, DW_AT_name("STF")
	.dwattr $C$DW$150, DW_AT_location[DW_OP_regx 0x28]

$C$DW$151	.dwtag  DW_TAG_TI_assign_register
	.dwattr $C$DW$151, DW_AT_name("FPUHAZ")
	.dwattr $C$DW$151, DW_AT_location[DW_OP_reg27]

	.dwendtag $C$DW$CU

