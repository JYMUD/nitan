// Room: road2.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short","��ʯ���");
        set("long", @LONG
����һ��ͨ���ɶ��Ĵ���ʯ��������������Σ�����ʮ�����¡�
�ɶ�ƽԭ����츮֮������Ұ����Ȯ�ͣ��������䣬һ�ɰ�����Ϣ��
�����������Կ����ɶ������ˡ�
LONG );
        set("outdoors", "chengdu");
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : __DIR__"road1",
            "west"       : __DIR__"fuheqiaoe",
            "east"      : __DIR__"shudao19",            
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15170);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}