inherit ROOM;

void create()
{
        set("short", "ҩ��");
        set("long", @LONG
������һ��ҩ�̣�һ��ŨŨ��ҩζ���㼸����Ϣ�����Ǵ�ҩ����
�ļ��ٸ�С������ɢ�������ġ���ҽ���Ӷ������ڲ輸�ԣ����Ժ���
�裬��Ҳ������һ�ۡ�һ��С���վ�ڹ�̨���к��Ź˿͡�
LONG );
        set("objects", ([
                __DIR__"npc/huatuo" : 1,
                __DIR__"npc/huoji" : 1,
        ]));
        set("exits", ([
                "east" : __DIR__"beidajie2",
        ]));

        set("coor/x", -7110);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}