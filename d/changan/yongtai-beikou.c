//Room: yongtai-beikou.c

inherit ROOM;

void create ()
{
        set ("short", "��̩����");
        set("long", @LONG
����ֵ�����ͷ��һ�����ɶ�ߵ����֮�ϣ���������յ�����
������ÿ��ĺɫ���٣�����ƻ�ͨ����������һ���鱦�У���������
ɢ�����˵���ⱦ�����ܶ฾��·�����ﶼ����Ҫ������һ�ơ��Ϸ�
ͨ����̩�����
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "east" : "/d/changan/qixiang1",
                "north" : "/d/changan/zhubaohang",
                "south" : "/d/changan/yongtai-dadao1"
        ]));

        set("outdoors", "changan");  
        set("coor/x", -10760);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}