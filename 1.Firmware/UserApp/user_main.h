#ifndef STM32_PROJECT_USER_MAIN_H
#define STM32_PROJECT_USER_MAIN_H

#define __AT__(x)               __attribute__((section(".ARM.__at_" x)))
#define __AT_ZERO__(x)          __attribute__((section(".bss.ARM.__at_" x)))
#define __AT_EXFLASH__          __attribute__((section("EXFLASH")))
#define __AT_EXFLASH_CONST__    __attribute__((section("EXFLASH"))) const

void user_main(void);

#endif //STM32_PROJECT_USER_MAIN_H
