
; inc max
; if(nearvar<maxvar)nearvar++;
incm   macro   nearvar maxvar
        lda     ~1~
        cmp     #~2~
        bhs     Lab$$$          ;; Do not inc maxvar reached
        inc     ~1~
Lab$$$
        endm

; dec min
; if(minvar<nearvar)nearvar--;
decm   macro   nearvar minvar
        lda     ~1~
        cmp     #~2~
        bls     Lab$$$          ;; Do not dec minvar reached
        dec     ~1~
Lab$$$
        endm

