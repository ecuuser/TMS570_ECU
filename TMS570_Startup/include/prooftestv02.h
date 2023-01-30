#ifndef __prooftestv02_h
#define __prooftestv02_h

#define AID1_7

#include "std_nhet.h"

/* define e_HETPROGRAM7_UN to dereference a pointer which is defined in AppStartup.c */
/* needed to enable using the same NHET program in both NHETs for startup testing only */
#define e_HETPROGRAM7_UN (*HetProgAtStartup_ptr)

#define HET_FRCTR_7	(e_HETPROGRAM7_UN.Program7_ST.FRCTR_7)
#define pHET_FRCTR_7  	0

#define HET_Transst_7	(e_HETPROGRAM7_UN.Program7_ST.Transst_7)
#define pHET_Transst_7  	1

#define HET_trans1_7	(e_HETPROGRAM7_UN.Program7_ST.trans1_7)
#define pHET_trans1_7  	2

#define HET_mvstrt2_7	(e_HETPROGRAM7_UN.Program7_ST.mvstrt2_7)
#define pHET_mvstrt2_7  	3

#define HET_trans2_7	(e_HETPROGRAM7_UN.Program7_ST.trans2_7)
#define pHET_trans2_7  	4

#define HET_trans3_7	(e_HETPROGRAM7_UN.Program7_ST.trans3_7)
#define pHET_trans3_7  	5

#define HET_mvstrt4_7	(e_HETPROGRAM7_UN.Program7_ST.mvstrt4_7)
#define pHET_mvstrt4_7  	6

#define HET_trans4_7	(e_HETPROGRAM7_UN.Program7_ST.trans4_7)
#define pHET_trans4_7  	7

#define HET_transend_7	(e_HETPROGRAM7_UN.Program7_ST.transend_7)
#define pHET_transend_7  	8

#define HET_END_7	(e_HETPROGRAM7_UN.Program7_ST.END_7)
#define pHET_END_7  	9



typedef union 
{ 
 	HET_MEMORY	Memory7_PST[10];
	struct
	{
		CNT_INSTRUCTION FRCTR_7;
		MOV32_INSTRUCTION Transst_7;
		ECMP_INSTRUCTION trans1_7;
		MOV32_INSTRUCTION mvstrt2_7;
		ECMP_INSTRUCTION trans2_7;
		ECMP_INSTRUCTION trans3_7;
		MOV32_INSTRUCTION mvstrt4_7;
		ECMP_INSTRUCTION trans4_7;
		MOV32_INSTRUCTION transend_7;
		BR_INSTRUCTION END_7;
	} Program7_ST; 

} HETPROGRAM7_UN;

/* comment out the generated extern declaration 
 * replaced by the pointer define near the top of the file */
/*   
extern volatile HETPROGRAM7_UN e_HETPROGRAM7_UN;
*/
extern const HET_MEMORY HET_INIT7_PST[10];

#endif

