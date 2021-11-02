; programa de exemplo para SO21b
     CARGI 0      ; A = A1
     MVAX         ; x = 0
     CARGI 10     ; A = 10
     ARMM l       ; l = 10
ali  MVXA         ; A = x
     ESCR 1       ; print x
     INCX         ; x++
     MVXA         ; A = x
     SUB l        ; A - l
     DESVNZ ali   ; if x != l goto ali
     PARA         ; stop
l    ESPACO 1
