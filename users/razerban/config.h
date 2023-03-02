#pragma once

// Override to be compatible with Purea Andrei firmwares
#undef VENDOR_ID
#define VENDOR_ID    0x0481
// Override to be compatible with Purea Andrei firmwares
#undef  PRODUCT_ID
#define PRODUCT_ID   0x0002

#ifndef NO_DEBUG
#define NO_DEBUG
#endif

#ifndef NO_PRINT
#define NO_PRINT
#endif

#define TAPPING_TERM 200
