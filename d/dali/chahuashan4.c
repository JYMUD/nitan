//Room: /d/dali/chahuashan4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�軨ɽ");
        set("long", @LONG
�����ڲ軨ɽ�ϣ�������������ïʢ�Ĳ軨����Ȼ���󲿷���
��Ʒ����ż��Ҳ����һ�����Ʒ�������С�������Զ�Ǵ���ǵı��ţ�
�ϱ߲�Զ�ǳ�ǽ��
LONG );
        set("objects", ([
           "/d/dali/obj/shanchahua": 1,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "north"     : "/d/dali/chahuashan2",
        ]));
	set("coor/x", -19140);
	set("coor/y", -6870);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}