//Room: /d/dali/yanchi1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�سص̰�");
        set("long", @LONG
�����ǵ���ο;ۼ�֮������۷���������ʱʱ������ʤ����ˮ
翰��ĵ�أ����͡���ɲ�ڵᲨ�����֡�������������ͣ�۹ٶɣ���
�Ƹ�ʫ������֮Ϊ��ͣ���̻᡻������Ķ��ֲʺ硢��ɽ���ꡢ����
��𸡢��ϼ���졢�鷫ԶӰ���޲��������������ܡ�
LONG );
        set("objects", ([
           "/d/dali/npc/guigongzi": 1,
           "/d/dali/npc/enu": 2,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "west"      : "/d/dali/yanchi2",
            "southeast" : "/d/dali/luojiadian",
        ]));
	set("coor/x", -19080);
	set("coor/y", -6860);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}