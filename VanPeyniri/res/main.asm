    processor 6502

EKX = $1000
EKY = $1001
EKR = $1002
EKK = $1003

KLAVYE = $0A00

    seg code
  
	org $0000   ; Define the code origin at RAM start

Start:
    
    

drawloop:
    ;kesmeleri kapat
    sei

    ;posx
	lda px
	sta EKX

    ;posy
    lda #2
    sta EKY
    
    ;color
    lda #1
    sta EKR

    ;komut
    lda #1
    sta EKK

    ;kesmeleri ac
    cli

    jmp drawloop

px:
    .byte 0
py:
    .byte 0


nmi:
    lda #10
    rti

IRQ:        
    ;color
    lda #0
    sta EKR

    ;komut temizle
    lda #2
    sta EKK

    lda KLAVYE

    inc px
    rti

    ;==========================================================;
    ;==========================================================;
    ;==========================================================;
    org $FFFA
        
    .word nmi       ;NMI Vector
    .word Start     ;Reset Vector
    .word IRQ       ;IRQ/BRK Vector    