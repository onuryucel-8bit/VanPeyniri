    processor 6502

    seg code
  
	org $0000   ; Define the code origin at RAM start

	lda #5
	
loop:
    jmp loop