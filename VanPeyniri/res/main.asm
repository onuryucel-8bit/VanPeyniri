    processor 6502

    seg code
  
	org $0000   ; Define the code origin at RAM start

Start:

	lda #5
	
loop:
    jmp loop

    ;==========================================================;
    ;==========================================================;
    ;==========================================================;
    org $fffc
    .word Start ; Reset vector at $fffc where program starts
    .word Start ; Interrupt vector at $fffe