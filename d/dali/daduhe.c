//Room: /d/dali/daduhe.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","��ɺӱ�");
        set("long", @LONG
��ɺ��������������ӹ���խ��ˮ���ļ������Ѷɹ���ֻ��Զ��
���β��к�������������д��ɺӡ��˴��Ǻӹ�ת���ǳ̲��ˮ����
���������Կɼ����Ϻ�ˮ��ӿ��ȥ���԰����������ɼ����ϱ�ɽ����
��ʯ�ǡ�
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "southup"  : "/d/dali/wunong",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19180);
	set("coor/y", -6770);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}