/* Kernbauer Version: 2.04 Konfiguration: TMS570SafeCtx Erzeugungsgangnummer: 633 Zweig: 1 */

/*****************************************************************************
| Project Name: Autosar OS 2.1 / Autosar OS 3.0
|    File Name: atosappl.c
|
|  General code: @Version: 5.23c@
|  Module version: $vv$=1.24
|
|  Description: API-functions for controlling applications
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2006-2012 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/


#if defined USE_QUOTE_INCLUDES
 #include "osek.h"
 #include "osekext.h"
#else
 #include <osek.h>
 #include <osekext.h>
#endif

/* Vector release management */
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif
/* KB begin vrmReleaseNumber (overwritten) */
/* TR:SPMF36:0002 Start */
/* Source release number */
#define osdVrmMajRelNum 5
#define osdVrmMinRelNum 6
/* TR:SPMF36:0002 End */
/* KB end vrmReleaseNumber */
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif

/* CovComment 0:  file: atosappl.c */

/* KB begin osekStartOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
#pragma SET_CODE_SECTION(".oscode") /* TR:SPMF49:0001 */ /* TR:SPMF49:0002 */
#endif
/* KB end osekStartOfCModule */



#if ((osdSC== SC3) || (osdSC== SC4)) /* TR:SASR30:0094 Start */

/*-+--------------------------------------------------------------------------
 / CheckObjectOwnership
 / ====================
 /
 / Syntax: ApplicationType CheckObjectOwnership (ObjectTypeType ObjectType,
 /                                               ObjectIDType ObjectID)
 / Parameter (In): ObjectType: Type of the following parameter
 /                 ObjectID: The object to be examined
 / Parameter (Out): none
 / Return value: The service returns the OS-Application to which the object ObjectType 
 /               belongs. If the object does not exists the service returns 
 /               INVALID_OSAPPLICATION.
 / Description: 
 / OS273: If the specified object ObjectType exists, CheckObjectOwnership shall
 /        return the identifier of the OS-Application to which the object belongs.
 / OS274: If the specified object ObjectType does not exist, CheckObjectOwnership
 /        shall return INVALID_OSAPPLICATION.
 / OS319: If the object to be examined is the RES_SCHEDULER
 /        CheckObjectOwnership shall always return INVALID_OSAPPLICATION.
 / Scalability Classes: SC3, SC4
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 not violated: (comment 1503) In not SafeContext projects this function 
 * may be switched off by the OS configuration parameter OS/APIOptimization/Manual/CheckObjectOwnership 
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and exist, even if they are not used in a project.
 */
/* TR:SASR30:0008 Start */
/* TR:SASR30:0118 Start */
/* TR:SASR30:0185 Start No error hook in CheckObjectOwnership */
osqFunc1 ApplicationType osqFunc2 osCheckObjectOwnership(ObjectTypeType ObjectType, /* PRQA S 1503 */ /* TR:SASR30:0374 Start */
                                                         ObjectIDType ObjectID)     /* TR:SASR30:0374 End */
{
   /* CovComment 4:  Function: osCheckObjectOwnership */
   ApplicationType retval;

   OS_OO_ENTRY()   

   /* TR:SASR30:0035 Start Context check in CheckObjectOwnership  */
   /* TR:SASR30:0336 Start Context check in CheckObjectOwnership  */
   if ((osdValidCtx_CheckObjectOwnership & osCurrentContext) == 0)
   {
      COVER(0x03D5)
      OS_OO_EXIT()
      return INVALID_OSAPPLICATION;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x03D6)
   /* TR:SASR30:0119 Start */
   switch (ObjectType)
   {
      case OBJECT_TASK:
#if (osdNumberOfAllTasks > 0)
         if (ObjectID < osdNumberOfAllTasks)
         {
            COVER(0x03D7)
            retval = oskTaskToAppl[ObjectID];
         }
         else
         {
            COVER(0x03D8)
#else
            COVER(0x03D9)
#endif         
            retval = INVALID_OSAPPLICATION;
#if (osdNumberOfAllTasks > 0)
         } 
#endif         
         break;
      case OBJECT_ISR:
#if (osdNumberOfCat2ISRs > 0)
         if (ObjectID < osdNumberOfCat2ISRs)
         {
            COVER(0x03DA)
            retval = oskISRToAppl[ObjectID];
         }
         else
         {
            COVER(0x03DB)
#else
            COVER(0x03DC)
#endif         
            retval = INVALID_OSAPPLICATION;
#if (osdNumberOfCat2ISRs > 0)
         }
#endif         
         break;
      case OBJECT_ALARM:
#if (osdNumberOfAlarms > 0)
         if (ObjectID < osdNumberOfAlarms)
         {
            COVER(0x03DD)
            retval = oskAlarmToAppl[ObjectID];
         }
         else
         {
            COVER(0x03DE)
#else
            COVER(0x03DF)
#endif         
            retval = INVALID_OSAPPLICATION;
#if (osdNumberOfAlarms > 0)
         }
#endif         
         break;
      case OBJECT_RESOURCE:
#if (osdNumberOfAllResources > 0)
         if (ObjectID < osdNumberOfAllResources)
         {
            COVER(0x03E0)
            retval = oskResourceToAppl[ObjectID]; /* TR:SASR30:0153 */
         }
         else
         {
            COVER(0x03E1)
#else
            COVER(0x03E2)
#endif         
            retval = INVALID_OSAPPLICATION;
#if (osdNumberOfAllResources > 0)
         }
#endif         
         break;
      case OBJECT_COUNTER:
#if (osdNumberOfCounters > 0)
         if (ObjectID < osdNumberOfCounters)
         {
            COVER(0x03E3)
            retval = oskCounterToAppl[ObjectID];
         }
         else
         {
            COVER(0x03E4)
#else
            COVER(0x03E5)
#endif         
            retval = INVALID_OSAPPLICATION;
#if (osdNumberOfCounters > 0)
         }
#endif         
         break;
      case OBJECT_SCHEDULETABLE:
#if (osdNumberOfScheduleTables > 0)
         if (ObjectID < osdNumberOfScheduleTables)
         {
            COVER(0x03E6)
            retval = oskScheduleTableToAppl[ObjectID];
         }
         else
         {
            COVER(0x03E7)
#else
            COVER(0x03E8)
#endif         
            retval = INVALID_OSAPPLICATION;
#if (osdNumberOfScheduleTables > 0)
         }
#endif         
         break;
      default:
         COVER(0x03E9)
         retval = INVALID_OSAPPLICATION;
         break;
   }

   COVER(0x03EA)
   OS_OO_EXIT()   

   return retval;
   /* TR:SASR30:0119 End */
} /* END OF osCheckObjectOwnership */
/* TR:SASR30:0185 End */
/* TR:SASR30:0118 End */
/* TR:SASR30:0008 End */

/*-+--------------------------------------------------------------------------
 / CheckObjectAccess
 / =================
 /
 / Syntax: ObjectAccessType CheckObjectAccess (ApplicationType   ApplID,
 /                                             ObjectTypeType    ObjectType,
 /                                             ObjectIDType      ObjectId)
 / Parameter (In): ApplID      OS-Application identifier
 /                 ObjectType  Type of the following parameter
 /                 ObjectId    The object to be examined
 / Parameter (Out): none
 / Return value: ACCESS if the ApplID has access to the object, NO_ACCESS otherwise 
 / Description: 
 / OS271: If the OS-Application <ApplID> has access to the queried object, 
 /        CheckObjectAccess shall return ACCESS (SASR30:0116).
 / OS272: If the OS-Application <ApplID> has no access to the queried object, 
 /        CheckObjectAccess shall return NO_ACCESS (SASR30:0117).
 / OS318: If the object to be examined is the RES_SCHEDULER CheckObjectAccess 
 /        shall always return ACCESS (SASR30:0152).
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 not violated: (comment 1503) In not SafeContext projects this function 
 * may be switched off by the OS configuration parameter OS/APIOptimization/Manual/CheckObjectAccess
 * In SafeContext implementations however all APIs are encapsulated in wrappers. 
 * This wrappers belong to static ASIL code and exist, even if they are not used in a project. 
 */
/* TR:SASR30:0103 Start */
/* TR:SASR30:0185 Start No error hook in CheckObjectAccess */
/* TR:SASR30:0252 Start Available for/from all applications, no rights check */
osqFunc1 ObjectAccessType osqFunc2 osCheckObjectAccess(ApplicationType   ApplID,       /* PRQA S 1503 *//* TR:SASR30:0373 Start */
                                                       ObjectTypeType    ObjectType,
                                                       ObjectIDType      ObjectId)     /* TR:SASR30:0373 End */
{
   /* CovComment 4:  Function: osCheckObjectAccess */
   OS_OA_ENTRY()

   /* TR:SASR30:0035 Start Context check in CheckObjectAccess  */
   /* TR:SASR30:0336 Start Context check in CheckObjectAccess  */
   if ((osdValidCtx_CheckObjectAccess & osCurrentContext) == 0)
   {
      COVER(0x03EB)
      OS_OA_EXIT()
      return NO_ACCESS;
   }
   /* TR:SASR30:0336 End */
   /* TR:SASR30:0035 End */
   ELSEWITHCOVER(0x03EC)
   
   /* Is the application identifier (ApplID) valid? */
   if((ApplID < osdNumberOfApplications) && (ObjectType < osdNumberOfObjectTypes)) /* 5011271_ISSUE_08 (ESOS00003677) */
   {
      COVER(0x03ED)
      if((ObjectId < oskObjectCount[ObjectType])
         && ((oskApplObjectAccess[ObjectType][ObjectId] & (1UL << ApplID)) != 0))
      {
         COVER(0x03EE)
         OS_OA_EXIT() 
         return ACCESS; /* TR:SASR30:0116 */ /* TR:SASR30:0152 */
      }
      ELSEWITHCOVER(0x03EF)

   } /* if(ApplID < osdNumberOfApplications) */

   COVER(0x03F0)
   OS_OA_EXIT() 
   return NO_ACCESS; /* TR:SASR30:0117 */ /* TR:SASR30:0228 */
} /* END OF CheckObjectAccess */
/* TR:SASR30:0252 End */
/* TR:SASR30:0185 End */
/* TR:SASR30:0103 End */


#endif /* ((osdSC== SC3) || (osdSC== SC4)) */ /* TR:SASR30:0094 End */

/* KB begin osekEndOfCModule (overwritten) */
#if (osdCompiler==osdCompilerTIARM)
/* Reset to default section TR:SPMF49:0004 */
#pragma SET_CODE_SECTION()
#endif
/* KB end osekEndOfCModule */


/* END OF MODULE atosappl.c */
