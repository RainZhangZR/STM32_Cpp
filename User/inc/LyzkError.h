/* This file defines the error code that used in our project */
#include <stdint.h>

typedef uint32_t                LYZK_RETURN_CODE;

#define LYZK_FAILED             0       // Failed
#define LYZK_SUCCESSED          1       // Successed


/* -------------------------------------------------------------------------- */
/*                                GPIO ERROR                                  */
/*							   From 51 - 100 								  */
#define LYZK_GPIO_ERR           51      // GPIO peripher or pin dose not exist
#define LYZK_GPIO_MODE_ERR      52      // GPIO Mode error when initializing
#define LYZK_GPIO_SPEED_ERR     53      // GPIO Speed error when initializing
#define LYZK_GPIO_INIT_ERR      54      // GPIO is not initialized before using
