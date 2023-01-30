#ifndef _WDGM_VERIFIER_H_
#define _WDGM_VERIFIER_H_

#include "WdgM.h"
#include "wdgm_verifier_types.h"
#include "wdgm_verifier_version.h"

/* begin of DLL boilerplate code */
#ifdef __WIN32__
    #ifdef BUILD_DLL
        // the dll exports
        #define EXPORT __declspec(dllexport)
    #else
        // the exe imports
        #define EXPORT __declspec(dllimport)
    #endif
#endif
/* end of DLL boilerplate code */

#ifdef __WIN32__
EXPORT int verify
    ( const WdgM_ConfigType        * main_struct
    , const verifier_main_struct_t * verifier_info
    );
#else
int verify
    ( const WdgM_ConfigType        * main_struct
    , const verifier_main_struct_t * verifier_info
    );
#endif

#endif  /* _WDGM_VERIFIER_H_ */
