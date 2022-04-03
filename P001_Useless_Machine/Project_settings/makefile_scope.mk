HEADERS	+=../1_app
HEADERS	+=../2_services
HEADERS	+=../3_hal
HEADERS	+=../4_mcu_drivers

SRC_C	:=../1_app/app_cfg.c
SRC_C	+=../1_app/app.c
SRC_C	+=../2_services/main.c
SRC_C	+=../2_services/os.c
SRC_C	+=../3_hal/led.c
SRC_C	+=../3_hal/uln2003.c
SRC_C	+=../4_mcu_drivers/mcu.c
SRC_C	+=../4_mcu_drivers/timer.c

LD_SCRIPT =avr5.x
