// dahai.c

#include <ansi.h>

inherit ROOM;
 
void create()
{
        set("short", "��");
        set("long",@LONG
��������ãã��֮�С��㼫ĿԶ����ֻ������һ�ߣ���Χ����
�ڵ㶼û�У�����ֻ�к��˵��Ĵ�����
LONG);   
        set("no_magic", 1);
        setup();
        replace_program(ROOM) ;
}
