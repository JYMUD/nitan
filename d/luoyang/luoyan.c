inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
��С������������߻�����֮��ʶ������������ڸ�ˬ������̨��
�������й�һ������С������һ�Ű�ľ��齡�����֮�࣬ɫɫ�ྻ����ɨ
�õ������˺����������л����������У�ʮ�ַ�ï�������ʱ��л���˽�
������
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"jiyuan2",
        ]));

	set("coor/x", -6990);
	set("coor/y", 2130);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}