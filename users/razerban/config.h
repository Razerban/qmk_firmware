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

// If you press a dual-role key, press another key, and then release the
// dual-role key, all within the tapping term, by default the dual-role key
// will perform its tap action. If the HOLD_ON_OTHER_KEY_PRESS option is
// enabled, the dual-role key will perform its hold action instead.
#define HOLD_ON_OTHER_KEY_PRESS

