#ifndef __SUNPLUS_DEF_BUILD_H__
#define __SUNPLUS_DEF_BUILD_H__

#if defined(SP7021)

    #define CMSIS_STARTUP_FILE "startup_sp7021_arm926.S"

#elif defined(SP645)

#elif defined(SP7350)

#else
	#warning "No CMSIS startup file defined"
#endif

#endif

