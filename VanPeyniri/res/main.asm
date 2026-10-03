    processor 6502

EKX = $1000
EKY = $1001
EKR = $1002
EKK = $1003

KLAVYE = $0A00

HDDi0 = $0A01
HDDi1 = $0A02
HDDi2 = $0A03
HDDi3 = $0A04
HDDsize = $0A05
HDDcontrol = $0A06
HDDstatus = $0A07
HDDram0 = $0A08
HDDram1 = $0A09

	seg zeroPage
	org $0000	
	ds 10, $2		;10 tane 2 sayisini yerlestir	
	align 256, $aa	;geri kalan yerlere 0xAA sayisini yerlestir
	
	seg stack
	org $0100
	ds 10, $0	;ds 10 dersem ayni sey varsayilan olarak 0 sayisini yerlestirir
	align 256, $00
	
    seg code
	org $0200   ; Define the code origin at RAM start
	
hdddeneme:
    lda #$30
    sta HDDi0

    lda #$00
    sta HDDi1

    lda #$00
    sta HDDram0

    lda #$02
    sta HDDram1

    lda #10
    sta HDDsize

    lda #2
    sta HDDcontrol

    lda #$30
    sta HDDi0
    lda #$00
    sta HDDi1

    lda #$00
    sta HDDram0
    lda #$FF
    sta HDDram1

    lda #10
    sta HDDsize

    lda #1
    sta HDDcontrol



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
    .word hdddeneme     ;Reset Vector
    .word IRQ       ;IRQ/BRK Vector    