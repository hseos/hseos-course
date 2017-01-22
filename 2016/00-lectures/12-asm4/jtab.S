        // реализация switch с помощью таблицы переходов
a:      .int    0

        .text
        mov     a, %eax
        sub     $1, %eax
        cmp     $2, %eax
        ja      out_switch
        jmp     *switch_tab(,%eax,4)
switch_tab:
        .int    blk1, blk2, blk3
blk1:
        jmp     out_switch
blk2:
        jmp     out_switch
blk3:
        jmp     out_switch
out_switch:
