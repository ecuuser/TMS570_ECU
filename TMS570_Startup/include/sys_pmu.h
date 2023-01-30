/** @file sys_pmu.h
*   @brief System Pmu Header File
*   @date 25.April.2014
*   @version 03.09.00
*   
*   This file contains:
*   - Pmu Interface Functions
*   .
*   which are relevant for the performance monitor unit driver.
*/
/* Version Control:
 * Date Created:      Wed Apr 13 12:17:00 2011
 * %version:          1 %
 * %derived_by:       gz7pm0 %
 * %date_modified:    Thu Oct  3 16:34:55 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 05/05/14  1        LK             Initial Version
 */

#ifndef SYS_PMU_H__
#define SYS_PMU_H__

#define pmuCYCLE_COUNTER 0x80000000U

void _pmuEnableCountersGlobal_(void);

void _pmuDisableCountersGlobal_(void);

void _pmuResetCounters_(void);

void _pmuStartCounters_(uint32 counters);

void _pmuStopCounters_(uint32 counters);

uint32 _pmuGetCycleCount_(void);

#endif
