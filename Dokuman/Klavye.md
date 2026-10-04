```

                                        ┌─────────────┐                                                               
     RAM                                │tusa basilir │                                                               
┌────────────────────┐                  └─────┬───────┘                                                               
│                    │                        │                                                                       
│                    │                        │                                                                       
├────────────────────┤                 ┌──────▼───────────────────────────┐                                           
│ Kesme Tablosu      │                 │tusun ascii degeri 0x0A00(suanlik)│                                           
│                    │◄──────────┐     │buraya kaydedilir                 │                                           
│                    │           │     └──────┬───────────────────────────┘                                           
├────────────────────┤           │            │                                                                       
│ Basilan tusun      │           │            │                                                                       
│ tutuldugu alan     │           │     ┌──────▼─────────────────────────┐                                             
│ 8bit ASCII         │           │     │islemciye kesme sinyali yollanir│◄───────────────────────────────────────────┐
│                    │           │     └──────┬─────────────────────────┘                                            │
├────────────────────┤           │            │                                                                      │
│                    │           │            │                                                                      │
│ IRQ vektoru        ├───────────┘            │                                                                      │
│                    │                        │                                                                      │
└────────────────────┘                 ┌──────▼────────────────────────────────────────┐                             │
                                       │islemci IRQ(kesme) vektorunun bulundugu noktaya│                             │
                                       │gidip vektorun gosterdigi yere ziplar          │                             │
                                       └──────┬────────────────────────────────────────┘                             │
                                              │                                                                      │
                                              │                                                                      │
                                              │                                                                      │
                                              │                                                                      │
                                       ┌──────▼───────────────────────────────────────┐                              │
                                       │kesme tablosu denilen alanda                  │  lda $0A00 islemi yapilmadi  │
                                       │lda $0A00 veya lda KLAVYE denilmedigi muddetce┼──────────────────────────────┘
                                       │kesme sinyali aktif kalir                     │                               
                                       └──────┬───────────────────────────────────────┘                               
                                              │                                                                       
                                              │                                                                       
                                        ┌─────▼────────────────────────────────────────────┐                          
                                        │islemci tusun basildiginda andaki program sayacini│                          
                                        │geri yukler kaldigi yerden devam eder             │                          
                                        └──────────────────────────────────────────────────┘                          

```                                        
processor 6502

KLAVYE = $0A00

	seg zeroPage
	org $0000	
	ds 10, $2		;10 tane 2 sayisini yerlestir	
	align 256, $aa	;geri kalan yerlere 0xAA sayisini yerlestir
	
	seg stack
	org $0100
	ds 10, $0	    ;ds 10 dersem ayni sey varsayilan olarak 0 sayisini yerlestirir
	align 256, $00
	
    seg code
	org $0200       ; Define the code origin at RAM start
	
Main:

    ;kesmeleri kapat
    sei

    ;piksel.x = px
	lda px
	sta EKX

    ;piksel.y = py
    lda #2
    sta EKY
    
    ;renk = 1
    lda #1
    sta EKR

    ;komut piksel cizdir = 1
    lda #1
    sta EKK

    ;kesmeleri ac
    cli

jmp Main

px:
    .byte 0
py:
    .byte 0

nmi:
    lda #10
    rti

IRQ:            
    lda KLAVYE

    ;renk = 0
    lda #0
    sta EKR

    ;komut ekrani temizle = 2
    lda #2
    sta EKK

    ;x pozisyonunu arttir
    inc px
    rti

    ;==========================================================;
    ;==========================================================;
    ;==========================================================;
    org $FFFA
        
    .word nmi       ;NMI Vector
    .word Main      ;Reset Vector
    .word IRQ       ;IRQ/BRK Vector    