#ifndef COS_H
#define COS_H

**
*  System Action Request Numbers
*
F$ADV:   =         O'000          ; Advance job
F$ABT:   =         O'001          ; Abort
F$DAT:   =         O'002          ; Get current date
F$TIM:   =         O'003          ; Get current time
F$MSG:   =         O'004          ; Enter message in log file
F$RCL:   =         O'005          ; Dataset recall
F$TRM:   =         O'006          ; Terminate job
F$SSW:   =         O'007          ; Set pseudo-sense switch
F$OPN:   =         O'010          ; Open dataset
F$MEM:   =         O'011          ; Request memory
F$LBN:   =         O'012          ; Return last block number
F$CLS:   =         O'013          ; Close dataset
F$DNT:   =         O'014          ; Create/modify local dataset
F$MDE:   =         O'015          ; Set exchange package mode
F$GNS:   =         O'016          ; Get next control statement
F$RLS:   =         O'020          ; Release dataset
F$PDM:   =         O'021          ; Permanent dataset managment request
F$RDC:   =         O'022          ; Read device circular
F$WDC:   =         O'023          ; Write device circular
F$GRN:   =         O'024          ; Get system revision numbers
F$DIS:   =         O'025          ; Dispose dataset
F$JDA:   =         O'026          ; Get current Julian date
F$JTI:   =         O'027          ; Return accumulated CPU time
F$ACT:   =         O'030          ; Return accounting information
F$SPS:   =         O'031          ; Set P register and suspend user
F$CSW:   =         O'032          ; Clear sense switch
F$TSW:   =         O'033          ; Test sense switch
F$BIO:   =         O'034          ; Buffered I/O request
F$DLY:   =         O'035          ; Delay job
F$AQR:   =         O'036          ; Acquire dataset from frontend
F$NRN:   =         O'037          ; Enable/disable not rerunnable checks
F$RRN:   =         O'040          ; Enable/disable job rerun
F$IOA:   =         O'041          ; Set/clear IOA bits
F$LFT:   =         O'042          ; Delete/change/create LFT
F$INV:   =         O'043          ; Invoke a job class structure
F$DJA:   =         O'044          ; Dump job area
F$RPV:   =         O'045          ; Enable/disable reprieve processing
F$BGN:   =         O'046          ; Begin user code execution
F$RCS:   =         O'047          ; Rewind current control statement file
F$PRC:   =         O'050          ; Procedure dataset invocation
F$RTN:   =         O'051          ; Procedure return
F$LIB:   =         O'052          ; Library searchlist maintenance
F$INS:   =         O'053          ; Jump to installation-defined function
F$UROLL: =         O'054          ; User-requested rollout
F$ASD:   =         O'055          ; Access system dataset
F$SYM:   =         O'056          ; JCL symbol manipulation
F$CSB:   =         O'057          ; Conditiona control statement maintenance
F$ISB:   =         O'060          ; Interative control statement maintenance
F$EKO:   =         O'061          ; Alter user's ECHO status
F$OPT:   =         O'062          ; Change user-specifiable options
F$POS:   =         O'063          ; Tape dataset position request
F$SPM:   =         O'064          ; Ready system performance monitor
F$FCH:   =         O'065          ; Fetch dataset from frontend
F$TDT:   =         O'066          ; Convert timestamp to ASCII
F$DTT:   =         O'067          ; Convert ASCII to timestamp
F$MTT:   =         O'070          ; Convert machine time to timestamp
F$TMT:   =         O'071          ; Convert timestamp to machine time
F$SPY:   =         O'072          ; Enable/disable user execution profile
F$MEMORY:=         O'073          ; Request memory
F$PRV:   =         O'074          ; Process user security requests
F$DSD:   =         O'075          ; Define secure dataset
F$ENC:   =         O'076          ; Encrypt password
F$TASK:  =         O'077          ; Create/manipulate tasks
F$CRASH: =         O'100          ; Halt COS
F$SYNCH: =         O'101          ; Synchronize tape dataset
F$TPOS:  =         O'102          ; Get tape position information
F$TBL:   =         O'103          ; Return copy of system table

**
*  Job Communication Block Offsets
*
JCCCI:   =         O'005          ; Control statement image
JCCPR:   =         O'020          ; Control statement parameters, 2 words each
JCJN:    =         O'100          ; Job name (bits 0-55)
JCLPP:   =         O'101          ; Lines per page (bits 0-7)
JCRMSG:  =         O'101          ; RFL message sent (bit 11)
JCU:     =         O'101          ; User mode indicator (bits 14-15)
JCUL:    =         O'101          ;   Local  (bit 14)
JCUG:    =         O'101          ;   Global (bit 15)
JCHLM:   =         O'101          ; High limit of user code (bits 16-39)
JCFL:    =         O'101          ; Current field length (bits 40-63)
JCNPF:   =         O'102          ; Number of buffers and datasets (bits 0-15)
JCBFB:   =         O'102          ; Base address of I/O buffers (bits 16-39)
JCDSP:   =         O'102          ; Base address of DSP area (bits 40-63)
JCNLE:   =         O'103          ; Number of entries in LFT (bits 0-15)
JCMFL:   =         O'103          ; Maximum field length allowed (bits 16-39)
JCLFT:   =         O'103          ; Base of LFT (bits 40-63)
JCDCS:   =         O'104          ; CSP dynamic control statement flag (bit 0)
JCCSDB:  =         O'104          ; CSP debug flag (bit 1)
JCBP:    =         O'104          ; Job statement breakpoint flag (bit 2)
JCNTB:   =         O'104          ; CSP traceback suppression flag (bit 3)
JCIOAC:  =         O'104          ; I/O area current status flag (bit 4)
                                  ;   0 User's I/O area is unlocked
                                  ;   1 User's I/O area is locked
JCIOAP:  =         O'104          ; I/O area previous status flag (bit 5)
                                  ;   0 User's I/O area is unlocked
                                  ;   1 User's I/O area is locked
JCIA:    =         O'104          ; Interactive flag (bit 6)
JCCHG:   =         O'104          ; Execute CHARGES utility for trailer message (bit 7)
JCJBS:   =         O'104          ; Job statement flag (bit 8)
JCCSIM:  =         O'104          ; CRAY-1 simulator running (bit 9)
JCDLIT:  =         O'104          ; Display literal delimiters (bit 10)
JCRPRN:  =         O'104          ; Retain level 1 parentheses (bit 11)
JCVSEP:  =         O'104          ; Last character was valid separator (bit 12)
JCSDM:   =         O'104          ; NOECHO of current statement (bit 13)
JCPDMS:  =         O'104          ; Suppress PDM user logfile messages (bit 14)
JCCSQ:   =         O'104          ; New CFT calling sequence in effort (bit 15)
JCOVT:   =         O'104          ; Overlay type (bit 16)
JCULFT:  =         O'104          ; Base of user LFT's (JCB-REL) (bits 17-47)
JCPNST:  =         O'104          ; Parentheses nesting level (bits 48-55)
JCSTRM:  =         O'104          ; Control statement termination (bits 56-63)
JCEFI:   =         O'105          ; Enable floating point interrupt (bit 0)
JCOVL:   =         O'105          ; Overlay flag (bit 1)
JCSBC:   =         O'105          ; SBCA flag (bit 2)
JCBDM:   =         O'105          ; Enable bidirectional mode (bit 3)
JCORI:   =         O'105          ; Interrupt on operand range flag (bit 4)
JCCYCL:  =         O'105          ; CPU cycle time (picosecs) bits (5-20)
JCCPTP:  =         O'105          ; CPU type (bits 21-29)
JCMCP:   =         O'105          ; Maximum number logical CPU's (bits 30-34)
JCNLCP:  =         O'105          ; Current number logical CPU's (bits 35-39)
JCEMA:   =         O'105          ; 1=Extended mem addressing enabled (bit 40)
JCAVL:   =         O'105          ; 1=Additional vector until enabled (bit 41)
JCIAC:   =         O'105          ; Number account processing retries allowed (bits 42-49)
JCACRQ:  =         O'105          ; Accounting mandatory flag (bit 50)
JCPWRQ:  =         O'105          ; Password required flag (bit 51)
JCRYPT:  =         O'105          ; Encryption flag (bit 52)
JCSLVL:  =         O'105          ; Security level flag (bit 53)
JCSJOB:  =         O'105          ; S on job card (bit 54)
JCFRLS:  =         O'105          ; Flag set when FRLS executes at job end (bit 55)
JCCRL:   =         O'106          ; COS revision level (bits 0-63)
JCCRLS:  =         O'106          ; COS revision number (bits 32-63)
JCACN:   =         O'107          ; 1-15 character account number
JCACN1:  =         O'107          ; Characters 1-8 of account number
JCACN2:  =         O'110          ; Characters 9-15 of account number
JCPWD:   =         O'111          ; 1-15 character password
JCPWD1:  =         O'111          ; Characters 1-8 of password
JCPWD2:  =         O'112          ; Characters 9-15 of password
JCPROM:  =         O'113          ; Current interactive prompt (L format)
JCNULE:  =         O'114          ; Number of user LFT entries below HLM (bits 0-15)
JCPLEV:  =         O'114          ; Current procedure nesting level (bits 16-31)
JCILEV:  =         O'114          ; Current iterative nexting level (bits 32-47)
JCCLEV:  =         O'114          ; Current conditional nesting level (bits 48-63)
*  The next four words are used by the run-time memory manager:
JCMMIN:  =         O'115          ; Size of increments to managed mem (bits 0-31)
JCMMIS:  =         O'115          ; Initial size of managed memory (bits 32-63)
JCMMBA:  =         O'116          ; Base address of managed space (bits 0-31)
JCMMEP:  =         O'116          ; Size of smallest block added (bits 32-63)
JCSTIN:  =         O'117          ; Size of stack increments (bits 0-30)
JCSTRT:  =         O'117          ; Flag to indicate stack for root task (bit 31)
JCSTIS:  =         O'117          ; Initial stack size (bits 32-63)
JCAVBA:  =         O'120          ; Base of available space (bits 32-63)
JCTCF:   =         O'121          ; Task scheduling flag (bits 0-63)
JCPSM:   =         O'122          ; Pseudo-semaphore registers (bits 0-31)
JCPSMR:  =         O'122          ; Required zeroes (bits 32-63)
JCSNGL:  =         O'123          ; Single threading flag (bit 0)
JCSNGC:  =         O'123          ; Reserved for use in single thread code (1-63)
JCNUDP:  =         O'126          ; Number of system DSP's in user (bits 0-15)
JCTPTR:  =         O'127          ; Pointer to list of all tasks (bits 32-63)
JCRDYQ:  =         O'130          ; Multitasking ready queue header
JCRUNQ:  =         O'131          ; Multitasking run queue header
JCLDR:   =         O'146          ; Unsatisfied externals
JCSTN:   =         O'164          ; Job step count
JCSTF:   =         O'165          ; Job step failure flag
JCBDAT:  =         O'166          ; Date of absolute load module generation
JCBTIM:  =         O'167          ; Time of absolute load module generation
JCDIG:   =         O'170          ; Reserved for diagnostics

**
*  Open Dataset Name (ODN) table definitions
*
ODDN:    =         O'000          ; Dataset name
ODV:     =         O'001          ; Close volume (bit 1)
ODM:     =         O'001          ; Open for 'mod' (append) (bit 2)
ODS:     =         O'001          ; Close or open saved position (bit 3)
ODH:     =         O'001          ; Hold resources (bit 4)
ODUDS:   =         O'001          ; Open as unblocked (bit 5)
ODLDT:   =         O'001          ; LDT address (bits 8-31)
ODOST:   =         O'001          ; Type of open requested (bits 36-39)
ODDSP:   =         O'001          ; DSP pointer
                                  ;   Negative: negative offset
                                  ;   Positive: absolute address
OSTDEF:  =         D'00           ; COS 1.15 and earlier
OSTSA:   =         D'00           ; Open system-managed, system-resident
OSTUA:   =         D'01           ; Open user-managed, user-resident
OSTMSY:  =         D'02           ; Open system-managed, user-resident
OSTS2U:  =         D'03           ; Switch system-managed to user-managed
OSTS2S:  =         D'04           ; Switch user-managed to system-managed

**
*  Dataset Parameter (DSP) table definitions
*
DPCWF:   =         O'005          ; Control word types detected (bits 0-3)
DPEOR:   =         O'10           ;   End of record
DPEOF:   =         O'02           ;   End of file
DPEOD:   =         O'01           ;   End of data
DPBIO:   =         O'007          ; Buffered I/O busy (bit 0)
DPBER:   =         O'007          ; Buffered I/O error flag (bit 1)
DPBF:    =         O'007          ; Function code (bits 2-9)
BIOFRRP: =         O'00           ;   Read partial
BIOFRR:  =         O'10           ;   Read record
BIOFWRP: =         O'40           ;   Write partial
BIOFWR:  =         O'50           ;   Write record
BIOFEOF: =         O'52           ;   Write EOF
BIOFEOD: =         O'56           ;   Write EOD
BIOFREW: =         O'156          ;   Rewind
DPBPD:   =         O'007          ; Processing direction: (bit 4)
                                  ;   0 Read
                                  ;   1 Write
DPBEO:   =         O'007          ; Termination condition: (bits 6-9)
                                  ;   00 Partial
                                  ;   10 Record
                                  ;   12 File, write only
                                  ;   16 Dataset, write only
DPBUBC:  =         O'007          ; Unused bit count (bits 10-15)
                                  ;   Value must be specified on Write Record
                                  ;   Value returned on Read Record
DPBWC:   =         O'007          ; Word count (bits 16-39)
                                  ;   Number of words at DPBWA to read or write
                                  ;   Contains actual number read when read complete
DPBWA:   =         O'007          ; Word address of user data area (bits 40-63)

**
*  ABORT - Abort Program
*
*  The ABORT request provides for abnormal termination of the current
*  job step without terminating the entire job. Processing resumes with
*  the job control statement that follows the first EXIT statement after
*  the aborted job step. If no EXIT statement exists, the job is
*  terminated.
*
         MACRO
OPLABEL  ABORT
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         S0        F$ABT
         EX
ABORT    ENDM

**
*  CLOSE - Close Dataset
*
*  CLOSE releases the buffer, the Logical File Table (LFT) , and the
*  Dataset Parameter Table (DSP) for a COS-managed dataset. Disk space
*  is not released (as opposed to RELEASE which gives up the DNT as
*  well) and the dataset remains accessible to the job.
*
*  The buffers are flushed, if all of the following conditions are true
*  for the dataset:
*
*  - The dataset is currently opened for output.
*  - No end-of-data is written.
*  - The dataset is being written sequentially.
*  - The dataset's DSP is managed by COS.
*  - The dataset has COS blocked dataset structure.
*  - The dataset is not memory resident.
*
*    OPLABEL Optional label.
*
*    DN      Dataset name. Symbolic address of the Open Dataset Name
*            Table (ODN) for this dataset or an A, S, or T (not A0 or
*            S0) register containing the address of the ODN. See the
*            description of the OPEN macro later in this file.
*    
         MACRO
OPLABEL  CLOSE     DN
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         S0        F$CLS
         IFC       'DN',NE,'S1',1
         S1        DN
         EX
CLOSE    ENDM

**
*  DSP - Create Dataset Parameter Table
*
*  The DSP macro creates a table in the user field called the Dataset
*  Parameter Table (DSP). This table holds information concerning the
*  status of the named dataset and the location of the I/O buffer for
*  the dataset.
*
*  You should use the DSP macro only when you need the DSP and I/O
*  buffer in the user-managed memory portion of the job. Normally, a DSP
*  and buffer for a dataset are created in the upper end of the job's
*  memory (above JCHLM) or in the user heap space, if you are using
*  stack versions of library routines, by execution of an OPEN macro.
*
*  When using the DSP macro, you must also set up a 2-word Open Dataset
*  Name Table (ODN). You must define ODN before using an OPEN macro
*  specifying this dataset. For more information on ODN, see the CRAY-OS
*  Version I Reference Manual, publication number SR-OOll.
*
*  The DSP macro is not executable; it merely sets up a DSP table with
*  the dataset name, first, in, out, and limit fields initialized. An
*  OPEN macro must be executed to make the DSP known to the system. See
*  the CRAY-OS Version 1 Reference Manual, publication SR-OOIl for a
*  detailed description of the DSP.
*
*    LOC     Symbolic address of DSP. If LOC is not specified, a symbol
*            is defined. The default symbolic name is generated by
*            appending @ to the dataset name.
*
*    DN      Dataset name.
*
*    FIRST   Address of the first word of the user-allocated buffer for
*            this dataset.
*
*    NB      Number of 5l2-word blocks in the dataset buffer.
*
         MACRO
LOC      DSP       DN,FIRST,NB
         IFC       'LOC',NE,'',1
LOC:     BSS       0
         IFC       'LOC',EQ,'',1
DN_@:    BSS       0
         DATA      'DN'L
         VWD       40/0,24/FIRST
         VWD       40/0,24/FIRST
         VWD       40/0,24/FIRST
         VWD       40/0,24/FIRST+(NB*D'512)
         BSSZ      D'19
DSP      ENDM

**
*  ENDP - End Program
*
*  The ENDP request causes normal termination of the current program.
*  Processing resumes with the next job control statement if reprieve
*  processing is not enabled for normal job step termination. If
*  reprieve processing is enabled for normal job step termination, the
*  user's reprieve code is entered.
*
         MACRO
OPLABEL  ENDP
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         S0        F$ADV
         EX
ENDP     ENDM

**
*  ENTER - Subroutine entry
*
*  The ENTER macro generates code to save B00 on the stack. The
*  RETURN macro restores B00 from stack.
*
*  Uses
*    A0
*
         MACRO
OPLABEL  ENTER
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         A0        B00
         A7        A7-1
         ,A7       A0
ENTER    ENDM

**
*  MESSAGE - Enter message in log file
*
*  The MESSAGE macro causes the printable ASCII message at the location
*  specified in the macro call to be entered in the job and system
*  logfile. The message must be 1 through 80 characters, terminated by a
*  zero byte.
*
*    OPLABEL Optional label.
*
*    ADDRESS A symbol or an A, S, or T register (except A0, S0, and S2)
*            containing the starting address of the ASCII message. This
*            parameter is required.
*
*    DEST    Destination for message; this parameter is optional and can
*            be any of the following:
*
*              U  User logfile only; specified register=1.
*              S  System logfile only; specified register=2.
*              US User and system logfiles; specified register=3.
*
*    MSGCLASS Assign the message to class MSGCLASS. MSGCLASS can be a
*            symbol or an A, S, or T register (except A0, S0, S2, S3, or
*            S4) containing the message class. See the ECHO control
*            statment in the CRAY-OS Version 1 Reference Manual,
*            publication SR-OO11, for the available message classes.
*            This parameter is optional.
*
*    OVERRIDE Message Suppression Override flag; if present, message is
*            to go to $LOG regardless of ECHO status. All messages
*            destined for system logfile are written to system log
*            regardless of ECHO status. This parameter is optional.
*
         MACRO
OPLABEL  MESSAGE   ADDRESS,DEST,MSGCLASS,OVERRIDE
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         S0        F$MSG
         IFC       $ADDRESS$,NE,$S1$,1
         S1        ADDRESS
         IFC       'DEST',EQ,'',1
         S2        1
MSG1     IFC       'DEST',NE,''
MSG2     IFA       REG,DEST
         IFC       'DEST'.NE.'S2',1
         S2        DEST
MSG2     ELSE
MSG3     IFC       'DEST',EQ,'U'
         S2        1
MSG3     ELSE
MSG4     IFC       'DEST',EQ,'S'
         S2        2
MSG4     ELSE
         S2        3
MSG4     ENDIF
MSG3     ENDIF
MSG2     ENDIF
MSG1     ENDIF
         IFC       'MSGCLASS',EQ,'',1
         S3        1
         IFC       'MSGCLASS',NE,'',1
         S3        MSGCLASS
         S3        S3<3
         S2        S2!S3
MSG5     IFC       'OVERRIDE',NE,''
         S3        4
         S2        S2!S3
MSG5     ENDIF
         EX
MESSAGE  ENDM

**
*  OPEN - Open Dataset
*
*  The OPEN macro prepares a dataset for processing. When an OPEN macro
*  is executed, the dataset is made known to the system if it is not an
*  existing dataset. I/O tables are created in the upper end of the
*  job's memory or in the heap, including the DSP (Dataset Parameter
*  Table) and the LFT (Logical File Table). An I/O buffer is created if
*  the dataset is COS blocked format, but not for an unblocked dataset.
*  The address or offset of the DSP table is returned to the user.
*
*  An OPEN macro can be executed on a dataset that is already open.
*
*    OPLABEL Optional label. If oplabel is not specified, the address
*            of the dataset name is generated.
*
*    DN      Dataset name. The OPEN macro generates a 2-word Open
*            Dataset Name Table (ODN) the first time an OPEN of the
*            dataset is encountered, unless you previously generated an
*            ODN for the dataset. The ODN is illustrated in CRAY-OS
*            Version 1 Reference Manual, publication SR-OOll. The DN
*            becomes the symbolic address of the ODN and is used in all
*            references to the dataset in other I/O requests.
*
*            As an alternative, dn can be an A, S, or T register (not
*            A0, S0, or S2) containing the ODN address.
*
*    PD      Processing direction. Can be any of the following:
*              I  Dataset opened for input
*              O  Dataset opened for output
*              IO Dataset opened for input/output (default)
*            pd can alternatively be an S or T register (but not an A
*            register) with bit 0 set for input and/or bit 1 set for
*            output.
*
*    LDT     Label Definition Table (LDT); an optional parameter that is
*            the name of a previously defined LDT for tape processing.
*            The pointer to this field is placed in the ODN built by the
*            macro. The parameter applies to tape datasets only. See
*            part 1, section 4 of this manual for a complete description
*            of the LDT macro.
*
*    U       Unblocked. If the U parameter is specified, the DSP has
*            DPUDS set and no buffer is allocated. The default is
*            blocked. The U parameter is used only as a keyword; no
*            registers are allowed.
*
         MACRO
OPLABEL  OPEN      DN,PD,LDT,U
         S0        F$OPN
OPN1     IFA       REG,DN
         IFC       'DN',NE,'S1',1
         S1        DN
OPN1     ELSE
OPN2     IFA       DEF,DN
         S1        DN
OPN2     ELSE
         SECTION   DATA
         IFC       'OPLABEL',EQ,'',1
DN:      BSS       0
         IFC       'OPLABEL',NE,'',1
OPLABEL: BSS       0
         DATA      'DN'L
         IFC       'U',NE,'',1
         VWD       6/1,2/0
         IFC       'U',EQ,'',1
         VWD       8/0
         IFC       'LDT',EQ,'',1
         VWD       56/0
         IFC       'LDT',NE,'',1
         VWD       24/LDT,32/0
         SECTION   *
         IFC       'OPLABEL',EQ,'',1
         S1        DN
         IFC       'OPLABEL',NE,'',1
         S1        OPLABEL
OPN2     ENDIF
OPN1     ENDIF
OPN3     IFA       REG,PD
         S1        S1!PD
OPN3     ELSE
OPN4     IFC       'PD',EQ,'I'
         S2        O'2
OPN4     ELSE
OPN5     IFC       'PD',EQ,'O'
         S2        O'1
OPN5     ELSE
         S2        O'3
OPN5     ENDIF
OPN4     ENDIF
         S2        S2<62
         S1        S1!S2
OPN3     ENDIF
         EX
OPEN     ENDM

**
*  READ/READP - Read words
*
*  The READ and READP macros transfer words of data that are resident on
*  a dataset into the user's data area. Blank compression characters are
*  not recognized, nor are any compressed blanks expanded with these
*  macros (see CRAY-OS Version 1 Reference Manual, publication SR-OO11).
*
*  The READ macro causes one record to be processed at a time. Each
*  macro call causes the dataset to be positioned after the end of
*  record (EOR) that terminated the read.
*
*  With the READP macro, words are transmitted to the user's data area
*  if requested. Each call is terminated by reaching an EOR or by
*  satisfying the word count, whichever occurs first. If you specify
*  READP with a word count of 0, an EOR is forced after a series of
*  READP calls.
*
*  No blank decompression is performed
*
*  When EOR is reached as a result of reading in word mode, the unused
*  bit count from the EOR is placed in the field DPBUBC of the Dataset
*  Parameter Table (DSP). Also, the unused bits are zeroed in the user's
*  record area.
*
*  Unrecovered data errors do not abort the job; instead, control is
*  returned to the caller. The caller can use the good data read, (A2)
*  through (A4)-1, and then abort. The caller can also skip or accept
*  the bad data. If the caller does nothing, the job aborts when the
*  next read request occurs. See the Library Reference Manual, CRI
*  publication SR-0014, for detailed descriptions of SKIPBAD and
*  ACPTBAD.
*
*  When a READ or READP macro refers to a memory-resident dataset, the
*  first such reference causes the dataset to be loaded into the buffer
*  from mass storage, if it exists there. If it does not exist on mass
*  storage, the system I/O routines set the DSP so that it appears that
*  the buffer is filled with data and no attempt is made to read data.
*  Note that the I/O routines cannot distinguish between the cases (1)
*  an existing dataset is declared memory resident, read in, modified in
*  the buffer, rewound, and read again, and (2) no modification of data
*  in the buffer occurs. In either case, the first read following a
*  REWIND reads the unmodified data from disk. If an existing dataset is
*  declared memory resident and is to be modified and reread, use
*  backspace positioning macros rather than REWIND to reposition to
*  beginning-of-data to preserve the modifications. This is necessary
*  only when a memory-resident dataset already exists on mass storage.
*
*    OPLABEL Optional label.
*
*    DN      Symbolic address of the Dataset Parameter Table (DSP), or
*            an A, B, or S register (not A0 or S0) containing the DSP
*            address or negative DSP offset relative to JCDSP.
*
*    UDA     User data area first word address (FWA) or an A, B, or S
*            register (not A1) containing the UDA address.
*
*    CT      Word count or an A, B, or S register (not A1 or A2)
*            containing the number of words to be read.
*
*  Return conditions:
*    (A1) DSP address
*    (A2) FWA of user data area (UDA)
*    (A3) Requested word count (CT)
*    (A4) Actual LWA+1 of data transferred to UDA. (A4)=(A2) if a null
*         record was read.
*    (S0) Condition of termination:
*           < 0 EOR encountered.
*           = 0 Null record, EOF, EOD, or unrecovered data error
*               encountered.
*           > 0 User-specified count (A3) exhausted before EOR is
*               encountered. For partial read (READP) if EOR and end of
*               count coincide, EOR takes precedence.
*    (S1) Error status:
*           = 0 No errors encountered.
*           = 1 Unrecovered data error encountered.
*    (S6) Contents of DPCWF if (S0)<=O and (S1)=O, otherwise, meaningless.
*         Note that for READ/READP, the unused bit count can also be
*         obtained from S6 if (S0)<O.
*
         MACRO
OPLABEL  READ      DN,UDA,CT
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         EXT       $RWDR
         IFC       'DN',NE,'A1',1
         A1        DN
         IFC       'UDA',NE,'A2',1
         A2        UDA
         IFC       'CT',NE,'A3',1
         A3        CT
         R         $RWDR
READ     ENDM

         MACRO
OPLABEL  READP     DN,UDA,CT
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         EXT       $RWDP
         IFC       'DN',NE,'A1',1
         A1        DN
         IFC       'UDA',NE,'A2',1
         A2        UDA
         IFC       'CT',NE,'A3',1
         A3        CT
         R         $RWDP
READP    ENDM

**
*  RECALL - Recall job upon I/O request completion
*
*  The RECALL macro removes a job from processing. The job does not
*  become a candidate for processing until the previously issued I/O
*  request for the specified dataset is completed or partially
*  completed: that is, the job is resumed when another physical request
*  is completed, which may be more then one block of data.
*
*    OPLABEL Optional label.
*
*    ADDRESS Symbolic address of the Open Dataset Name Table (ODN) or
*            Dataset Parameter Table (DSP) for this dataset or an A, S,
*            or T register containing the ODN or DSP address. See
*            description of OPEN macro earlier in this file.
*
         MACRO
OPLABEL  RECALL    ADDRESS
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         S0        F$RCL
         IFC       'ADDRESS',NE,'S1',1
         S1        ADDRESS
         EX
RECALL   ENDM

**
*  RELEASE - Release Dataset
*
*  The RELEASE macro causes the dataset whose Dataset Parameter Table
*  (DSP) address is at the location specified in the macro call to be
*  returned to the system. The dataset is closed and the Dataset Name
*  Table (DNT) entry is released. Additional system action depends on
*  the type of dataset. Output datasets are routed to a front end. If a
*  dataset is not a permanent dataset, the disk space associated with
*  that dataset is returned to the system. The dataset is no longer
*  accessible to the job.
*
*    OPLABEL Optional label.
*
*    ADDRESS Symbolic address of the Open Dataset Name Table (ODN) or
*            Dataset Parameter Table (DSP) for this dataset or an A,
*            S, or T register (not A0 or S0) containing the ODN or DSP
*            address. See description of OPEN and DSP macros in this
*            file. This parameter is required.
*
*    HOLD    Hold generic device. If you specify HOLD, the generic
*            system resource (the peripheral) associated with this
*            dataset is not returned to the system pool. This
*            parmeter is optional.
*
         MACRO
OPLABEL  RELEASE   ADDRESS,HOLD
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         S0        F$RLS
         IFC       'ADDRESS',NE,'S1',1
         S1        ADDRESS
RLS1     IFC       'HOLD',NE,''
         IFC       'ADDRESS',NE,'A1',1
         A1        ADDRESS
         S2        1,A1
         S3        1
         S3        S3<(D'63-D'4)
         S2        S2!S3
         1,A1      S2
RLS1     ENDIF
         EX
RELEASE  ENDM

**
*  RETURN - Subroutine return
*
*  The RETURN macro generates code to restore B00 from the stack
*  and branches to the restored value. Ordinarily, the ENTER macro
*  begins a subroutine, and it pushes B00 on the stack.
*
*  Uses
*    A0
*
         MACRO
OPLABEL  RETURN
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         A0         ,A7
         A7         A7+1
         B00        A0
         J          B00
RETURN   ENDM

**
*  WRITE/WRITEP - Write words
*
*  The WRITE macro writes words from the user's data area. An EOR is
*  written following each WRITE. The EOR indicates how many bits in the
*  last words are unused, if any. No blank compression is performed.
*  When a WRITE macro has written an EOR, the user program cannot write
*  any more data before issuing the STARTSP macro.
*
*  With the WRITEP macro, no EOR is written, nor is blank compression
*  performed. If you specify WRITEP with a word count of 0, the request
*  is treated as a no-op. If the dataset is memory resident and the
*  WRITE or WRITEP causes the buffer to become full, the memory-resident
*  flags are cleared and the buffers are flushed to mass storage.
*
*  To write only an EOR, use the WRITE macro with a word count of O.
*
*    OPLABEL Optional label.
*
*    DN      Symbolic address of the Dataset Parameter Table (DSP), or
*            an A, B, or S register (not A0 or S0) containing the DSP
*            address or negative DSP offset relative to JCDSP.
*
*    UDA     User data area first word address (FWA) or an A, B, or S
*            register (not A1) containing the UDA address.
*
*    CT      Word count or an A, B, or S register (not A1 or A2)
*            containing the number of words to be written.
*
*    UBC     Unused bit count or an A, B, or S register (not A1, A2, or
*            A3) containing the unused bit count or null. If null,
*            record contains no unused bits. Not applicable in WRITEP.
*
*  Return conditions:
*    (A1) DSP address
*    (A2) FWA of user data area (UDA)
*    (A3) Requested word count (CT)
*
         MACRO
OPLABEL  WRITE     DN,UDA,CT,UBC
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         EXT       $WWDR
         IFC       'DN',NE,'A1',1
         A1        DN
         IFC       'UDA',NE,'A2',1
         A2        UDA
         IFC       'CT',NE,'A3',1
         A3        CT
WRITE1   IFC       'UBC',EQ,''
         S2        0
WRITE1   ELSE
         IFC       'UBC',NE,'S1',1
         S2        UBC
WRITE1   ENDIF
         R         $WWDR
WRITE    ENDM

         MACRO
OPLABEL  WRITEP    DN,UDA,CT
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         EXT       $WWDS
         IFC       'DN',NE,'A1',1
         A1        DN
         IFC       'UDA',NE,'A2',1
         A2        UDA
         IFC       'CT',NE,'A3',1
         A3        CT
         R         $WWDS
WRITEP   ENDM

**
*  WRITED - Write end-of-data
*
*  The WRITED macro causes an EOR (if not previously written), an EOF
*  (if not previously written), and an EOD to be written.
*
*  The WRITED macro causes buffers to be flushed. If the dataset is
*  memory resident, buffers are flushed to mass storage only if the EOD
*  occurs within the last block of the buffer. In this case, the
*  memory-resident flags are also cleared.
*
*    OPLABEL Optional label.
*
*    DN      Symbolic address of the Dataset Parameter Table (DSP), or
*            an A, B, or S register (not A0 or S0) containing the DSP
*            address or negative DSP offset relative to JCDSP.
*
*  Return conditions:
*    (A1) DSP address
*
         MACRO
OPLABEL  WRITED    DN
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         EXT       $WEOD
         IFC       'DN',NE,'A1',1
         A1        DN
         R         $WEOD
WRITED   ENDM

**
*  WRITEF - Write end-of-file
*
*  The WRITEF macro causes an EOR (if not previously written) and an EOF
*  to be written.
*
*  If the WRITEF macro causes the buffer for a memory-resident dataset
*  to be full, the memory-resident flags are cleared and the buffers are
*  flushed to mass storage.
*
*    OPLABEL Optional label.
*
*    DN      Symbolic address of the Dataset Parameter Table (DSP), or
*            an A, B, or S register (not A0 or S0) containing the DSP
*            address or negative DSP offset relative to JCDSP.
*
*  Return conditions:
*    (A1) DSP address
*
         MACRO
OPLABEL  WRITEF    DN
         IFC       'OPLABEL',NE,'',1
OPLABEL: =         *
         EXT       $WEOF
         IFC       'DN',NE,'A1',1
         A1        DN
         R         $WEOF
WRITEF   ENDM

#endif
