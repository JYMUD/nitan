//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "��¡��");
        set ("long", @LONG
����һ��С��ׯ����������Ⱥɽ�������ɰز��죬Ϫ�����ƣ���ɫ
�������ഫ���������ʧȥ˫�ף�ʮ���������常����������������ӣ�
���������
LONG);
        set("outdoors", "jiangling");
        set("exits", ([
                "west" : __DIR__"shennongjia",
        ]));
  
        set("coor/x", -15060);
	set("coor/y", -1810);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}