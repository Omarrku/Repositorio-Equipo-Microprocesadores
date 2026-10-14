;========================================================
; Autores: Omar, Angel, Chipi
;
; Programa: Interrupción externa en PA0 (flanco de bajada)
;           para alternar el estado del LED en PC13.
; Descripción: Configuración de GPIO, EXTI e interrupciones.
;========================================================

; Flujo de programación de GPIO y EXTI:
; 1) Habilitar los relojes de GPIOA, GPIOC y AFIO.
; 2) Configurar PA0 como entrada con resistencia pull-up
;    y PC13 como salida push-pull.
; 3) Asignar EXTI0 a PA0 mediante AFIO_EXTICR1,
;    configurar el flanco de bajada y habilitar la línea.
; 4) Habilitar EXTI0 en el controlador NVIC.
; 5) En la rutina de interrupción, limpiar la bandera
;    pendiente y alternar el estado de PC13.

; Directivas del ensamblador
;---------------------------
area constants, data, readonly
RCC_APB2ENR equ 0x40021018      ; Registro de habilitación de relojes
GPIOA_CRL   equ 0x40010800      ; Registro de configuración baja de GPIOA
GPIOA_ODR   equ 0x4001080C      ; Registro de datos de salida de GPIOA
GPIOC_CRH   equ 0x40011004      ; Registro de configuración alta de GPIOC
GPIOC_ODR   equ 0x4001100C      ; Registro de datos de salida de GPIOC
AFIO_EXTICR1 equ 0x40010008     ; Registro de configuración de interrupciones externas 1
EXTI_IMR    equ 0x40010400      ; Registro de máscara de interrupciones
EXTI_RTSR   equ 0x40010408      ; Selección de disparo por flanco ascendente
EXTI_FTSR   equ 0x4001040C      ; Selección de disparo por flanco descendente
EXTI_PR     equ 0x40010414      ; Registro de interrupciones pendientes
NVIC_ISER0  equ 0xE000E100      ; Registro 0 de habilitación de interrupciones NVIC

; Programa principal
;-------------------
area p_05, code, readonly
export __main
export EXTI0_IRQHandler ; Sustituye el manejador débil del archivo de inicio

__main
; Habilitar relojes de AFIO (bit 0), GPIOA (bit 2) y GPIOC (bit 4)
;-----------------------------------------------------------------
ldr r0,=0x00000015
ldr r1,=RCC_APB2ENR
str r0,[r1]

```
; PA0 = entrada con resistencia pull-up/pull-down
; CNF=10, MODE=00 -> 0x8
;------------------------------------------------
ldr r0,=0x44444448
ldr r1,=GPIOA_CRL
str r0,[r1]
ldr r0,=0x00000001      ; ODR0=1: selecciona la resistencia pull-up
ldr r1,=GPIOA_ODR
str r0,[r1]

; PC13 = salida push-pull a 2 MHz
;--------------------------------
ldr r0,=0x44244444
ldr r1,=GPIOC_CRH
str r0,[r1]
ldr r0,=0x00002000      ; PC13=1: LED apagado (lógica activa en bajo)
ldr r1,=GPIOC_ODR
str r0,[r1]

; Fuente de EXTI0 = PA0 (EXTI0[3:0] = 0000)
;-------------------------------------------
ldr r0,=0x00000000
ldr r1,=AFIO_EXTICR1
str r0,[r1]

; Configurar únicamente el flanco de bajada y habilitar la línea 0
;----------------------------------------------------------------
ldr r0,=0x00000000
ldr r1,=EXTI_RTSR       ; Sin activación por flanco ascendente
str r0,[r1]
ldr r0,=0x00000001
ldr r1,=EXTI_FTSR       ; Activar por flanco de bajada en la línea 0
str r0,[r1]
ldr r1,=EXTI_PR
str r0,[r1]             ; Limpiar cualquier interrupción pendiente (escribir 1)
ldr r1,=EXTI_IMR
str r0,[r1]             ; Desenmascarar la línea 0

; Habilitar EXTI0 en el NVIC (posición de interrupción IRQ 6)
;-----------------------------------------------------------
ldr r0,=0x00000040
ldr r1,=NVIC_ISER0
str r0,[r1]
```

loop
wfi                     ; Esperar una interrupción
b loop                  ; Repetir indefinidamente

; Rutina de servicio de interrupción
;-----------------------------------
EXTI0_IRQHandler
; Retardo para eliminar rebotes (~50 ms a 8 MHz)
ldr r2,=0x00020000
delay
subs r2,r2,#1
bne delay

```
; Limpiar la bandera pendiente de la línea 0 (escribir 1)
ldr r0,=0x00000001
ldr r1,=EXTI_PR
str r0,[r1]

; Alternar el estado del LED conectado a PC13
ldr r1,=GPIOC_ODR
ldr r0,[r1]
eor r0,r0,#0x2000
str r0,[r1]

bx lr
```

; Fin del programa
;-----------------
end
