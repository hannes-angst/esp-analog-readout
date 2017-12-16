#ifndef _USER_CONFIG_H_
#define _USER_CONFIG_H_

#define DEBUG_ON	true


#define DATA_SEND_DELAY 3000	/* milliseconds */


#if defined(DEBUG_ON)
#define INFO( format, ... ) os_printf( format, ## __VA_ARGS__ )
#else
#define INFO( format, ... )
#endif

#endif
