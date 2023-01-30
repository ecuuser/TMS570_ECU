/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2011 by Vector Informatik GmbH.                                                  All rights reserved.
 * 
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Port.c
 *      Project:  DrvPort_Tms570Tigio01Asr
 *       Module:  DrvPort
 *    Generator:  -
 *
 *  Description:  This module implements a driver in ANSI C programming language to centralize the
 *                configuration of ports and pins which are used by more than one driver module.
 *                With this driver you can:
 *                - Configure all port pins
 *                - Initialize the configuration
 *                - Refresh the configuration (EMC purposes)
 *                - Switch the port pin configuration during runtime
 *
 *  
 *********************************************************************************************************************/

#define PORT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Port.h"


/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if (  (PORT_SW_MAJOR_VERSION != (0x01)) \
    || (PORT_SW_MINOR_VERSION != (0x01)) )
  #error "Vendor specific version numbers of Port.c and Port.h are inconsistent"
#endif

/* versions of all included header files shall be checked, configuration is just an example */
#if (  (PORT_CFG_MAJOR_VERSION != (0x01)) \
    || (PORT_CFG_MINOR_VERSION != (0x02)) )
  #error "Version numbers of Port.c and Port_Cfg.h are inconsistent!"
#endif


/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
/* Memory mapping, done via MemMap.h: Variables that are initialized */
#define PORT_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/* Global buffer for the pointer to the current configuration             */
static P2CONST( Port_ConfigType, PORT_VAR, PORT_PBCFG) Port_ConfigPtr_pt = NULL_PTR;

/* Memory mapping, done via MemMap.h: Variables that are initialized */
#define PORT_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 *//* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/
/* Memory mapping, done via MemMap.h: Code */
#define PORT_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 *//* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Port_InitMemory
 **********************************************************************************************************************/
/*! \brief      Service for initialization of global variables
 *              
 *  \param[in]  -
 *  \pre        Input parameter must not be NULL.
 *              Call of service must not interrupt running operation
 *              Module must be in state uninitialized before calling
 *  \context    Function could be called from task level
 *  \note       Function shall be used only if startup code does not
                initialize the global variables.
 **********************************************************************************************************************/
FUNC(void, PORT_CODE) Port_InitMemory( void )
{
    /* Global buffer for the pointer to the current configuration             */
    Port_ConfigPtr_pt = NULL_PTR;

    return;
}

/***********************************************************************************************************************
 *  Port_Init
 **********************************************************************************************************************/
/*! \brief      Initialization of whole port registers, ports and pins and selection of port functionality   
 *  \param[in]  ConfigPtr        pointer to the port configuration struct.
 *  \pre        Input parameter must not be NULL_PTR.
 *  \context    Function could be called from interrupt level or from task level
  **********************************************************************************************************************/
FUNC(void, PORT_CODE) Port_Init(P2CONST( Port_ConfigType, AUTOMATIC, PORT_PBCFG) ConfigPtr)
{
            
    #if (STD_ON == PORT_CFG_CHK_PARAM_CONFIG)
        /* Call of Errorhook if parameter refers to NULL */
        if(NULL_PTR == ConfigPtr)
        {
            Port_Errorhook(PORT_SID_INIT, PORT_E_PARAM_CONFIG);

            return;
        }
    #endif
 
    /* Initialize the pointer to the current variant                        */
    Port_ConfigPtr_pt = ConfigPtr;

 
    /* Set all registers to configured values */
    Port_ConfigPtr_pt->Port_InitPortPins_t();


    return;

}   /* Port_Init() */ /* PRQA S 2006 *//* MD_MSR_14.7 */



#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
/***********************************************************************************************************************
 *  Port_SetPinDirection
 **********************************************************************************************************************/
/*! \brief      This function sets the direction of each configured pin
 *              if allowed.
 *
 *  \param[In]  Pin               Configured handle of a port pin.
 *  \param[In]  Direction         Required pin direction
 *  \pre        Module have to be initialized.
 *  \context    Function could be called from interrupt level or from task level
  **********************************************************************************************************************/
    FUNC(void, PORT_CODE) Port_SetPinDirection(
                                                Port_PinType           Pin,
                                                Port_PinDirectionType  Direction
                                              )
    {
       uint32 DirRegAddress_u32;
       uint32 SetMask_u32;
       uint32 ClearMask_u32;

      
       /* Check if module has been initialzied. */
       #if (STD_ON == PORT_CFG_CHK_UNINIT)
           if ( NULL_PTR == Port_ConfigPtr_pt)
           {
               /* Report error to an Errorhook function. */
               Port_Errorhook(PORT_SID_SET_PIN_DIR, PORT_E_UNINIT);
              

               /* Return from function because of an error. */
               return;
           }
           else
           {
               /* Module is initialized because global config
                  pointer was written. Continue with normal
                  program flow                              */
           }
       #endif /*(STD_ON == PORT_CFG_CHK_UNINIT)*/

       /* Check of the parameter "pin" enabled ?                           */
       #if (PORT_CFG_CHK_PARAM_PIN == STD_ON)

            /*  Is the parameter "pin" a part of the list                   */
            if(Pin < (Port_ConfigPtr_pt->NumberOfPinChannels_u8) )
            {  
                /* Parameter is obviously a part of the pin handle list    */
            }
            else
            {   
                /* Parameter was not ok                                     */
                /* Report error to an Errorhook function                    */
                Port_Errorhook( PORT_SID_SET_PIN_DIR, PORT_E_PARAM_PIN);


                return;
            }  /* else: Parameter was not ok                                */

       #endif  /* Check of the parameter enabled */

       DirRegAddress_u32 = (uint32)&(((Port_RegisterPtrType)((Port_ConfigPtr_pt->PinChlConfig_pt[Pin] >> (uint32)(12u)) /* PRQA S 303 *//* MD_PORT_11.3 */
	                       | (uint32)(0xfff00000u)))->Reg.Direction_u32); 
        

       /* Check, which direction shall be set                              */
       if(PORT_PIN_OUT == Direction)
       {
           SetMask_u32 = ((uint32)(0x1u) << (Port_ConfigPtr_pt->PinChlConfig_pt[Pin] & (uint32)(0x1f)));
           ClearMask_u32 = 0xffffffffu; 
       }

       else
       {
            SetMask_u32 = 0x0u;
            ClearMask_u32 =(0xffffffffu & ~((uint32)(0x1u) << (Port_ConfigPtr_pt->PinChlConfig_pt[Pin] & (uint32)(0x1f)))); 

       }

       /* Suspend all interrupts                                       */
       Port_GlobalSuspend();


    /* A seperate handling of privileged and non-priveleged register has only to be done if *
     * the special register access is enabled at all */
    #if (PORT_SPECIAL_REGISTER_ACCESS_ENABLED == STD_ON)

       /* Bit number 11 is set if the target register can only written in privileged mode */
       if( (((uint32)Port_ConfigPtr_pt->PinChlConfig_pt[Pin]) & (uint32) 0x00000800u) != 0u )
       {
            /* Set or Clear the pin (only for changeable pins) */
           PORT_MODIFY_REGISTER_32BIT_SUPERVISOR(DirRegAddress_u32, ClearMask_u32, SetMask_u32, /* PRQA S 303 *//* MD_PORT_11.3 */
                                      Port_MemoryAreas_at[((Port_ConfigPtr_pt->PinChlConfig_pt[Pin] >> 6) & (uint32)(0x1f))]);
       }
       else
    #endif /*(PORT_SPECIAL_REGISTER_ACCESS_ENABLED == STD_ON)*/
       {
          /* Set or Clear the pin (only for changeable pins) */
           PORT_MODIFY_REGISTER_32BIT(DirRegAddress_u32, ClearMask_u32, SetMask_u32, /* PRQA S 303 *//* MD_PORT_11.3 */
                                      Port_MemoryAreas_at[((Port_ConfigPtr_pt->PinChlConfig_pt[Pin] >> 6) & (uint32)(0x1f))]);
       }
								   
           
       /* Restore all interrupts                                       */
       Port_GlobalRestore();
            
       


       return;

    }   /* Port_SetPinDirection */ /* PRQA S 2006 *//* MD_MSR_14.7 */

#endif  /* ( STD_ON == PORT_SET_PIN_DIRECTION_API )                       */



#if ( STD_ON == PORT_REFRESH_PORT_DIRECTION_API )
/***********************************************************************************************************************
 *  Port_RefreshPortDirection
 **********************************************************************************************************************/
/*! \brief      This function refreshes the pin direction. 
 *              
 *  \pre        Module have to be initialized.
 *  \context    Function could be called from interrupt level or from task level.
 **********************************************************************************************************************/
    FUNC(void, PORT_CODE) Port_RefreshPortDirection(void)
    {
        /* Function local variables */
        uint32 LoopCount_u32;       /* Counter variable                */
        uint32 MaxCount_u32;        /* Boundary for loop-counter       */
        uint32 DirRegAddress_u32; 
        uint32 SetMask_u32;
        uint32 ClearMask_u32;   
        P2CONST(Port_RefreshConfigType, AUTOMATIC, PORT_PBCFG) CurrentRefreshConfig_pt;
       



          /* Check if module has been initialzied. */
         #if (STD_ON == PORT_CFG_CHK_UNINIT)
            if ( NULL_PTR == Port_ConfigPtr_pt)
            {
                /* Report error to an Errorhook function. */
                Port_Errorhook(PORT_SID_REFRESH_PORT_DIR, PORT_E_UNINIT);


                /* Return from function because of an error. */
                return;
            }
            else
            {
                /* Intentionally left free. */
            }
        #endif /*(STD_ON == PORT_CFG_CHK_UNINIT)*/

        /* Store the loop counter boundary for the next loop                */
        MaxCount_u32 = Port_ConfigPtr_pt->NumberOfRefreshPorts_u8;


        /* Suspend all interrupts                                           */
        Port_GlobalSuspend();

        /* Refresh the direction registers with taking account of direction
         * changeable pins (these are not refreshable).                     */
        for ( LoopCount_u32 = (uint32)0u; MaxCount_u32 > LoopCount_u32; LoopCount_u32++ )
        {

            /* Read back the current register content to get the
             * current valid direction settings (also the settings of pins
             * which are direction-changeable).   
             */

            CurrentRefreshConfig_pt = &Port_ConfigPtr_pt->RefreshConfig_pt[LoopCount_u32];
            DirRegAddress_u32 = (uint32)&(((Port_RegisterPtrType)((CurrentRefreshConfig_pt->RegisterInfo_pt) | ((uint32)0xfff00000u)))->Reg.Direction_u32); /* PRQA S 303 *//* MD_PORT_11.3 */
            SetMask_u32 = (CurrentRefreshConfig_pt->InitialDirection_u32 & CurrentRefreshConfig_pt->RefreshMask_u32);
            ClearMask_u32 = ~((~(CurrentRefreshConfig_pt->InitialDirection_u32)) & CurrentRefreshConfig_pt->RefreshMask_u32);


            /* A seperate handling of privileged and non-priveleged register has only to be done if *
             * the special register access is enabled at all */
            #if (PORT_SPECIAL_REGISTER_ACCESS_ENABLED == STD_ON)

               /* Bit number 31 is set if the target register can only written in privileged mode */             
               if( (((uint32)CurrentRefreshConfig_pt->RegisterInfo_pt) & (uint32) 0x80000000u) != 0u )
               {
                   PORT_MODIFY_REGISTER_32BIT_SUPERVISOR(DirRegAddress_u32, ClearMask_u32, SetMask_u32, /* PRQA S 303 *//* MD_PORT_11.3 */
                       Port_MemoryAreas_at[(((CurrentRefreshConfig_pt->RegisterInfo_pt) >> (uint32)24u ) & (uint32)0x7fu)]);
               }
               else
            #endif /*(PORT_SPECIAL_REGISTER_ACCESS_ENABLED == STD_ON)*/
               {
                   PORT_MODIFY_REGISTER_32BIT(DirRegAddress_u32, ClearMask_u32, SetMask_u32, /* PRQA S 303 *//* MD_PORT_11.3 */
                       Port_MemoryAreas_at[(((CurrentRefreshConfig_pt->RegisterInfo_pt) >> (uint32)24u ) & (uint32)0x7fu)]);
               }

        }   /* End for loop to refresh all configured register settings     */

        /* Restore all interrupts                                           */
        Port_GlobalRestore();



        return;

    }   /* Port_RefreshPortDirection() */ /* PRQA S 2006 *//* MD_MSR_14.7 */                                  

#endif  /*( STD_ON == PORT_REFRESH_PORT_DIRECTION_API )*/



#if (STD_ON == PORT_SET_PIN_MODE_API)
/***********************************************************************************************************************
 *  Port_SetPinMode
 **********************************************************************************************************************/
/*! \brief      This function allows to change the Pin Mode during runtime;
 *              At present this feature is not supported.
 *
 *  \param[In]  Pin               Configured handle of a port pin.
 *  \param[In]  Mode              The Mode the port pin should be set
 *  \pre        Module have to be initialized.
 *  \context    Function could be called from interrupt level or from task level
  **********************************************************************************************************************/
FUNC(void, PORT_CODE) Port_SetPinMode( Port_PinType Pin,         /* PRQA S 3206 *//* MD_PORT_3206 */
                                       Port_PinModeType Mode )   /* PRQA S 3206 *//* MD_PORT_3206 */
{

    #if (STD_ON == PORT_DEV_ERROR_DETECT) 
    Port_Errorhook(PORT_SID_SET_PIN_MODE, PORT_E_FEATURE_NOT_SUPPORTED);
    #endif /*(STD_ON == PORT_DEV_ERROR_DETECT)*/ 

    
    return;
}
#endif /*(STD_ON == PORT_SET_PIN_MODE_API)*/



#if (STD_ON == PORT_VERSION_INFO_API)
/***********************************************************************************************************************
 *  Port_GetVersionInfo
 **********************************************************************************************************************/
/*! \brief      This service returns the version information of this module. 
 *              The version information includes:
 *                 - Module Id
 *                 - Vendor Id
 *                 - Vendor specific version numbers
 *
 *  \param[out] versioninfo        pointer to struct of type Std_VersionInfoType
 *  \pre        Output parameter must not be NULL_PTR.
 *  \context    Function could be called from interrupt level or from task level
  **********************************************************************************************************************/
FUNC(void, PORT_CODE) Port_GetVersionInfo
                (
                    P2VAR(Std_VersionInfoType, AUTOMATIC, PORT_APPL_DATA) versioninfo
                )
{


    /*  Check parameter for NULL_PTR.  */
    #if (STD_ON == PORT_CFG_CHK_PARAM_VINFO)
    if (NULL_PTR == versioninfo)
    {
        Port_Errorhook(PORT_SID_GET_VERSION_INFO, PORT_E_PARAM_VINFO);
        return;
    }
    #endif
    
    versioninfo->vendorID         = ( PORT_VENDOR_ID );
    versioninfo->moduleID         = ( PORT_MODULE_ID );
    versioninfo->instanceID       = ( PORT_INSTANCE_ID );
    versioninfo->sw_major_version = ( PORT_SW_MAJOR_VERSION );
    versioninfo->sw_minor_version = ( PORT_SW_MINOR_VERSION );
    versioninfo->sw_patch_version = ( PORT_SW_PATCH_VERSION );


    return;

}   /*  Port_GetVersionInfo()  */ /* PRQA S 2006 *//* MD_MSR_14.7 */
#endif  /*( PORT_VERSION_INFO_API == STD_ON )*/

/* Memory mapping, done via MemMap.h: Code */
#define PORT_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 *//* MD_MSR_19.1 */

/* module specific MISRA deviations:

   MD_RORT_11.3:
     Reason: Due to ressource optimization, an address was coded into a config value with several other
             parameters. A cast from a numeric to an pointer type can't be avoided
     Risk: Impact on portability and readability. 
     Prevention: There are no requirements on portability to a driver. 

*/

/**********************************************************************************************************************
 *  END OF FILE: Port.c
 **********************************************************************************************************************/
