/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : EPS_DiagSrvcs_XCP.Vector.c file
* Module Description: Common Manufacturing Program Interface for XCP and ISO services
* Product           : Gen II Plus - EA3.0
* Author            : Kevin Smith
*
* Notes:
* This file contains the functions that are vector SIP specific, this should
* be modified to match the functions in the XcpProf.c file (if changes are required).
*
*****************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Apr 12 10:20:00 2012
 * %version:          1 %
 * %derived_by:       cz7lt6 %
 * %date_modified:    Wed Jun  6 17:18:36 2012 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 06/06/12 	1		KS		Initial Component Release
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "EPS_DiagSrvcs_SrvcLUTbl.h"
#include "EPS_DiagSrvcs_XCP.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* Source */

/*****************************************************************************
 *
 *	XCP Supporting Functions
 *
 *  These functions are based on the functions used in the XcpCommand that
 *  is provided by Vector. The functions here were removed from the XcpCommand
 *  switch statement to be used locally in these functions. No functional changes
 *  were made to the code unless clearly noted.
 *
 *  Note: On newer versions of the XCP protocol, these functions may need to be
 *  updated.
 *
 *****************************************************************************/

/*****************************************************************************
 *
 *	Function Name: 	   XcpUserFreeDaq
 *
 *	Description:       XCP Command similar to (0xD6 Free DAQ). Removes all
 * 					   configured DAQ lists. This is also called when a
 * 					   connect command is sent.
 *
 *	Inputs:		       N/A
 *
 *	Outputs:	       N/A
 *
 *****************************************************************************/
FUNC(void, EPSDIAGSRVCS_CODE) XcpUserFreeDaq(void)
{
	xcp.SessionStatus &= (vuint8)((~SS_DAQ) & 0xFFu);

	xcp.Daq.DaqCount = 0;
	xcp.Daq.OdtCount = 0;
	xcp.Daq.OdtEntryCount = 0;

	xcp.pOdt = (tXcpOdt*)0;
	xcp.pOdtEntryAddr = 0;
	xcp.pOdtEntrySize = 0;

	/*XcpMemClr((BYTEPTR)&xcp.Daq.u.b[0], (vuint16)kXcpDaqMemSize);  <KS> Removed */ /* Deviation of MISRA rule 44. */
	XcpUserMemSet((BYTEPTR)&xcp.Daq.u.b[0], (vuint16)kXcpDaqMemSize,(vuint8)0u);	/* <KS> Added: Replaces above function call */
	#if defined ( kXcpMaxEvent ) && ! defined ( XCP_ENABLE_STIM )
		XcpUserMemSet( (BYTEPTR)&xcp.Daq.EventDaq[0], (vuint16)sizeof(xcp.Daq.EventDaq), (vuint8)0xFFu);  /* Deviation of MISRA rule 44. */
	#endif

	#if defined ( XCP_ENABLE_SEND_QUEUE )
		/* XcpQueueInit(); <KS> Removed, not needed */
		xcp.QueueLen = (vuint16)0u;
  		xcp.QueueRp = (vuint16)0u;
	#endif

	return;
}


/*****************************************************************************
 *
 *	Function Name: 	   XcpUserMemSet
 *
 *	Description:       Sets the memory range to a given value.
 *
 *	Inputs:		       p - memory location
 * 					   n - Number of writes to perform
 * 					   b - data to write
 *
 *	Outputs:	       N/A
 *
 *****************************************************************************/
#if defined ( XcpMemSet )
 /* XcpMemSet is overwritten */
#else
FUNC(void, EPSDIAGSRVCS_CODE) XcpUserMemSet( BYTEPTR p, vuint16 n, vuint8 b )
{
  for ( ; n > 0; n-- )
  {
    *p = b;
    p++;
  }
}
#endif

/*****************************************************************************
 *
 *	Function Name: 	   XcpUserAllocDaq
 *
 *	Description:       Allocates memory for the specified number of DAQ lists
 *
 *	Inputs:		       daqCount - Number of DAQ lists to be created
 *
 *	Outputs:	       Postive/Negative Response.
 *
 *****************************************************************************/
FUNC(vuint8, EPSDIAGSRVCS_CODE) XcpUserAllocDaq(vuint8 daqCount)
{
	#if defined ( XCP_ENABLE_PARAMETER_CHECK )
	if ( (xcp.Daq.OdtCount!=0) || (xcp.Daq.OdtEntryCount!=0) )
	{
		return (vuint8)CRC_SEQUENCE;
	}
	#endif

	xcp.Daq.DaqCount = daqCount;
	#if defined ( XCP_ALLIGN_WORD )
		xcp.Daq.DaqCount &= 0x00FFu;
	#endif

	return XcpUserAllocMemory();
} /* deviation of MISRA rule 82 (more than one return path). */


/*****************************************************************************
 *
 *	Function Name: 	   XcpUserAllocOdt
 *
 *	Description:       Allocates an ODT for the specified DAQ
 *
 *	Inputs:		       daq - DAQ number to assign the ODT(s)
 * 					   odtCount - Number of ODTs to assign to the given DAQ
 *
 *	Outputs:	       Postive/Negative Response.
 *
 *****************************************************************************/
FUNC(vuint8, EPSDIAGSRVCS_CODE) XcpUserAllocOdt( vuint8 daq, vuint8 odtCount )
{
	#if defined ( XCP_ENABLE_PARAMETER_CHECK )
		if ( (xcp.Daq.DaqCount==0) || (xcp.Daq.OdtEntryCount!=0) )
		{
			return (vuint8)CRC_SEQUENCE;
		}
	#endif

	/* Absolute ODT count must fit in a BYTE */
	#if !defined ( XCP_ENABLE_DAQ_HDR_ODT_DAQ )
		if (((vuint16)xcp.Daq.OdtCount+(vuint16)odtCount) > (vuint16)0xFBu)
		{
			return (vuint8)CRC_MEMORY_OVERFLOW;
		}
	#endif

	xcp.Daq.u.DaqList[daq].firstOdt = xcp.Daq.OdtCount;
	xcp.Daq.OdtCount += odtCount;
	#if defined ( XCP_ALLIGN_WORD )
		xcp.Daq.OdtCount &= 0x00FFu;
	#endif
	xcp.Daq.u.DaqList[daq].lastOdt = (tXcpOdtIdx)(xcp.Daq.OdtCount-1);

	return XcpUserAllocMemory();
} /* Deviation of MISRA rule 82 (more than one return path). */


/*****************************************************************************
 *
 *	Function Name: 	   XcpUserAllocOdtEntry
 *
 *	Description:       Allocates the number of ODT entries, per ODT
 *
 *	Inputs:		       daq - DAQ number containing the ODT the entries are to
 * 							 be assigne.d
 * 					   odt - The ODT for the given DAQ to apply the entries
 * 					   odtEntryCount - Number of ODT entries to allocate
 *
 *	Outputs:	       Postive/Negative Response.
 *
 *****************************************************************************/
FUNC(vuint8, EPSDIAGSRVCS_CODE) XcpUserAllocOdtEntry( vuint8 daq, vuint8 odt, vuint8 odtEntryCount )
{
	tXcpOdtIdx xcpFirstOdt;

	#if defined ( XCP_ENABLE_PARAMETER_CHECK )
		if ( (xcp.Daq.DaqCount==0) || (xcp.Daq.OdtCount==0) )
		{
			return (vuint8)CRC_SEQUENCE;
		}
	#endif

	/* Absolute ODT entry count count must fit in a WORD */
	if (xcp.Daq.OdtEntryCount > (0xFFFFu - odtEntryCount))
	{
		return (vuint8)CRC_MEMORY_OVERFLOW;
	}

	xcpFirstOdt = xcp.Daq.u.DaqList[daq].firstOdt;
	xcp.pOdt[xcpFirstOdt+odt].firstOdtEntry = xcp.Daq.OdtEntryCount;
	xcp.Daq.OdtEntryCount += (vuint16)odtEntryCount;
	xcp.pOdt[xcpFirstOdt+odt].lastOdtEntry = (vuint16)(xcp.Daq.OdtEntryCount-1);

	return XcpUserAllocMemory();
} /* Deviation of MISRA rule 82 (more than one return path). */



/*****************************************************************************
 *
 *	Function Name: 	   XcpUserAllocMemory
 *
 *	Description:       Allocates the required memory space in the xcp
 * 					   structure. Called by all allocate commands
 *
 *	Inputs:		       N/A
 *
 *	Outputs:	       Postive/Negative Response.
 *
 *****************************************************************************/
FUNC(vuint8, EPSDIAGSRVCS_CODE) XcpUserAllocMemory( void )
{
	vuint16 s;
	#if defined ( XCP_ENABLE_NO_P2INT_CAST  )
		vuint8* p;
		vuint8  i;
	#endif

	/* Check memory overflow */
	s = (vuint16)( ( xcp.Daq.DaqCount      *   (vuint8)sizeof(tXcpDaqList)                           ) +
                 ( xcp.Daq.OdtCount      *  (vuint16)sizeof(tXcpOdt)                               ) +
                 ( xcp.Daq.OdtEntryCount * ( (vuint8)sizeof(DAQBYTEPTR) + (vuint8)sizeof(vuint8) ) )
               );

	#if defined ( XCP_DISABLE_UNALIGNED_MEM_ACCESS )
		#if defined ( C_CPUTYPE_8BIT ) || defined ( C_CPUTYPE_16BIT )
			s += 3; /* Worst case 3 bytes needed for alignment */
		#else
			s += 9; /* Worst case 9 bytes needed for alignment */
		#endif
	#endif

	if (s>=(vuint16)kXcpDaqMemSize)
	{
		return (vuint8)CRC_MEMORY_OVERFLOW;
	}

	/* Force WORD alignment for ODTs */
	#if defined ( XCP_DISABLE_UNALIGNED_MEM_ACCESS )
		#if defined ( XCP_ENABLE_NO_P2INT_CAST  )
			p = (vuint8*)&xcp.Daq.u.DaqList[xcp.Daq.DaqCount];
			i = ((vuint8)p) & (vuint8)0x01u;
			p += i;
			xcp.pOdt = (tXcpOdt*)p;
		#else
			#if defined ( C_CPUTYPE_8BIT ) || defined ( C_CPUTYPE_16BIT )
				/* Allign to words */
				xcp.pOdt = (tXcpOdt*)((((vuint32)(&xcp.Daq.u.DaqList[xcp.Daq.DaqCount])) + (vuint32)1u) & (vuint32)0xFFFFFFFEu );
      		#else
  				/* Allign to dwords */
				xcp.pOdt = (tXcpOdt*)((((vuint32)(&xcp.Daq.u.DaqList[xcp.Daq.DaqCount])) + (vuint32)3u) & (vuint32)0xFFFFFFFCu );
			#endif
		#endif
	#else
		xcp.pOdt = (tXcpOdt*)&xcp.Daq.u.DaqList[xcp.Daq.DaqCount];
	#endif

	/* Force DWORD alignment for ODT entries */
	#if defined ( XCP_DISABLE_UNALIGNED_MEM_ACCESS )
 		#if defined ( XCP_ENABLE_NO_P2INT_CAST  )
			p = (vuint8*)&xcp.pOdt[xcp.Daq.OdtCount];
			i = ((vuint8)p) & (vuint8)0x03u;
			i = (vuint8)4u - i;
			i &= 0x03;
			p += i;
			xcp.pOdtEntryAddr = (DAQBYTEPTR*)p;
		#else
			xcp.pOdtEntryAddr = (DAQBYTEPTR*) ((((vuint32)&xcp.pOdt[xcp.Daq.OdtCount]) + (vuint32)3u) & (vuint32)0xFFFFFFFCu );
		#endif
	#else
  		xcp.pOdtEntryAddr = (DAQBYTEPTR*)&xcp.pOdt[xcp.Daq.OdtCount];
  	#endif

  	xcp.pOdtEntrySize = (vuint8*)&xcp.pOdtEntryAddr[xcp.Daq.OdtEntryCount];

	#if defined ( XCP_ENABLE_SEND_QUEUE )
	/* Force WORD alignment for the queue */
		#if defined ( XCP_DISABLE_UNALIGNED_MEM_ACCESS )
			#if defined ( XCP_ENABLE_NO_P2INT_CAST  )
				p = (vuint8*)&xcp.pOdtEntrySize[xcp.Daq.OdtEntryCount];
				i = ((vuint8)p) & (vuint8)0x01u;
				p += i;
				xcp.pQueue = (tXcpDto*)p;
			#else
				#if defined ( C_CPUTYPE_8BIT ) || defined ( C_CPUTYPE_16BIT )
  					/* Allign to words */
  					xcp.pQueue = (tXcpDto*)((((vuint32)(&xcp.pOdtEntrySize[xcp.Daq.OdtEntryCount])) + (vuint32)1u) & (vuint32)0xFFFFFFFEu );
				#else
  					/* Allign to dwords */
					xcp.pQueue = (tXcpDto*)((((vuint32)(&xcp.pOdtEntrySize[xcp.Daq.OdtEntryCount])) + (vuint32)3u) & (vuint32)0xFFFFFFFCu );
				#endif
			#endif
		#else
			xcp.pQueue = (tXcpDto*)&xcp.pOdtEntrySize[xcp.Daq.OdtEntryCount];
		#endif

		xcp.QueueSize = ((vuint16)kXcpDaqMemSize - s) / sizeof(tXcpDto);

	    #if defined ( kXcpSendQueueMinSize )
			if (xcp.QueueSize<(vuint16)kXcpSendQueueMinSize)
			{
	 			return (vuint8)CRC_MEMORY_OVERFLOW;
			}
		#else
			/* At least one queue entry per odt */
			if (xcp.QueueSize<xcp.Daq.OdtCount)
			{
				return (vuint8)CRC_MEMORY_OVERFLOW;
			}
		#endif
	#endif /* XCP_ENABLE_SEND_QUEUE */


	return (vuint8)0u;
} /* Deviation of MISRA rule 82 (more than one return path). */


/*****************************************************************************
 *
 *	Function Name: 	   XcpUserSetDaqListMode
 *
 *	Description:       Configures the selected DAQ for certain operating modes
 * 					   and the event to send the data.
 *
 *	Inputs:		       mode - DAQ mode, see requirements for detail
 * 					   daq - DAQ number
 * 					   event - Event number for the given DAQ to be executed
 * 							   (ex, 2ms)
 *
 *	Outputs:	       Postive/Negative Response.
 *
 *****************************************************************************/
FUNC(vuint8, EPSDIAGSRVCS_CODE) XcpUserSetDaqListMode( vuint8 Mode, vuint8 daq, vuint8 event, uint8 prescale )
{
	vuint8 result = 0;

	#if defined ( XCP_ENABLE_DAQ_PRESCALER ) || ( !defined ( XCP_ENABLE_DAQ_PRESCALER ) && defined ( XCP_ENABLE_PARAMETER_CHECK ) )
		vuint8 xcpPrescaler = prescale;	// Vector driver does not support anything else but 1
	#endif


	#if defined ( XCP_ENABLE_PARAMETER_CHECK )
    	if (daq>=xcp.Daq.DaqCount)
    	{
        	result = (vuint8)CRC_OUT_OF_RANGE;
		}

		#if defined ( kXcpMaxEvent )
        	if (event >= (vuint8)kXcpMaxEvent)
            {
            	result = (vuint8)CRC_OUT_OF_RANGE;
			}
		#endif

    	#if !defined ( XCP_ENABLE_DAQ_PRESCALER )
	        if (xcpPrescaler!=1)
	        {
	        	result = (vuint8)CRC_OUT_OF_RANGE;
	        }
    	#endif


        /* <KS> Priorities are not supported, removed this check since the arguments for XCP User functions do not use it. 
		if (CRO_SET_DAQ_LIST_MODE_PRIORITY!=0)   
        {
        	result = (vuint8)CRC_OUT_OF_RANGE;
		}
		*/

	#endif

  	#if defined ( XCP_ENABLE_DAQ_PRESCALER )
        if (xcpPrescaler==0)
        {
        	xcpPrescaler = 1;
		}

		DaqListPrescaler(daq) = xcpPrescaler;
  	#endif

  	#if defined ( kXcpMaxEvent ) && ! defined ( XCP_ENABLE_STIM )
    	xcp.Daq.EventDaq[event] = daq;
	#else
    	DaqListEventChannel(daq) = event;
	#endif

    DaqListFlags(daq) = Mode;

	#if defined ( XCP_ENABLE_STIM )
    	result = (vuint8)XcpAllocStimMemory();
	#endif

	#if defined ( XCP_ENABLE_READ_PROTECTION ) || defined ( XCP_ENABLE_WRITE_PROTECTION )
    {
    	tXcpOdtIdx   odt;
        vuint16      e, el;
        vuint8       n, r;


        for (odt=DaqListFirstOdt(daq);odt<=DaqListLastOdt(daq);odt++)
        {
        	e = DaqListOdtFirstEntry(odt);
            if(OdtEntrySize(e) > (vuint8)0)
            {
            	el = DaqListOdtLastEntry(odt);

                while (e <= el)
                {
                	n = OdtEntrySize(e);
                    if (n > 0)
                    {
                    	#if defined ( XCP_ENABLE_STIM )
                        	#if defined ( XCP_ENABLE_WRITE_PROTECTION )
								if ( (DaqListFlags(daq)&(vuint8)DAQ_FLAG_DIRECTION) != 0 ) /* STIM */
                          		{
                            		r = ApplXcpCheckWriteAccess(OdtEntryAddr(e), n);
                          		}
                          		else
                        	#endif
                          	{
                            	#if defined ( XCP_ENABLE_READ_PROTECTION )
                            		r = ApplXcpCheckReadAccess(OdtEntryAddr(e), (vuint16)n);
                            	#endif
                          	}
                        #else
                        	#if defined ( XCP_ENABLE_READ_PROTECTION )
                            	r = ApplXcpCheckReadAccess(OdtEntryAddr(e), (vuint16)n);
                          	#endif
                        #endif

                        if ( r == (vuint8)XCP_CMD_DENIED )
                        {
                        	vuint32 address = (vuint32)OdtEntryAddr(e);
                          	result = CRC_PAGE_MODE_NOT_VALID;
                          	xcp.CrmLen = CRM_SET_DAQ_LIST_MODE_LEN;

                          	#if defined(XCP_CPUTYPE_LITTLEENDIAN)
                          		CRM_BYTE(2)= (vuint8)(address     );
                          		CRM_BYTE(3)= (vuint8)(address >> 8);
                          		CRM_BYTE(4)= (vuint8)(address >>16);
                          		CRM_BYTE(5)= (vuint8)(address >>24);
                          	#else
                          		CRM_BYTE(2)= (vuint8)(address >>24);
                          		CRM_BYTE(3)= (vuint8)(address >>16);
                          		CRM_BYTE(4)= (vuint8)(address >> 8);
                          		CRM_BYTE(5)= (vuint8)(address     );
                          	#endif

                   	       /* Response length is arbitrary */
                    		/* goto negative_response1; <KS> Removed this since the goto statement will not work in this scope. Handled via calling function on result */
                    		result = 0;
                        }
                  	}

                    e++;
         		}
         	}
         }
	}
	#endif

	return result;
}

/*****************************************************************************
 *
 *	Function Name: 	   XcpUserSetDaqPtr
 *
 *	Description:       configures the pointer to the ODT entry to write the
 * 					   address of the variable.
 *
 *	Inputs:		       daq - DAQ containing the ODT
 * 					   odt - ODT containing the entry
 * 					   idx - index for the odt entries.
 *
 *	Outputs:	       Postive/Negative Response.
 *
 *****************************************************************************/
FUNC(vuint8, EPSDIAGSRVCS_CODE) XcpUserSetDaqPtr( vuint8 daq, vuint8 odt, vuint8 idx)
{
	tXcpOdtIdx odt0 = (tXcpOdtIdx)(DaqListFirstOdt(daq)+odt); /* Absolute odt number */

	#if defined ( XCP_ENABLE_PARAMETER_CHECK )
		if ( (daq>=xcp.Daq.DaqCount) || (odt>=(vuint8)DaqListOdtCount(daq)) || (idx>=(vuint8)DaqListOdtEntryCount(odt0)) )
		{
			return (vuint8)CRC_OUT_OF_RANGE;
		}
	#endif

	xcp.CrmLen = CRM_SET_DAQ_PTR_LEN;
	xcp.DaqListPtr = DaqListOdtFirstEntry(odt0)+idx;

	return 0;
}


/*****************************************************************************
 *
 *	Function Name: 	   XcpUserWriteDaq
 *
 *	Description:       Writes the variable information for use by the DAQ list
 *
 *	Inputs:		       bitOffset - bit mask for data coming out of the DAQ, 0xFF ignores
 * 					   daqSize - length of the variable (ex, a float is 4 bytes)
 * 					   addrExtension - Optional addressing extension of the variable, typically 0
 * 					   address - address of the variable.
 *
 *	Outputs:	       Postive/Negative Response.
 *
 *****************************************************************************/
FUNC(vuint8, EPSDIAGSRVCS_CODE) XcpUserWriteDaq( vuint8 bitOffset, vuint8 daqSize, vuint8 addrExtension, vuint32 address )
{
	/* CheckResourceProtection( RM_DAQ ); <KS> Removed */

	#if defined ( XCP_ENABLE_PARAMETER_CHECK )
		if ( ((vuint8)daqSize == (vuint8)0u ) || (daqSize > (vuint8)XCP_MAX_ODT_ENTRY_SIZE) )
		{
			return (vuint8)CRC_OUT_OF_RANGE;
		}
	#endif

	OdtEntrySize(xcp.DaqListPtr) = daqSize;
	OdtEntryAddr(xcp.DaqListPtr) = (DAQBYTEPTR)ApplXcpGetPointer(addrExtension,address);

	xcp.DaqListPtr++; /* Autoincrement */

    return 0;
}
