// Room: /d/xiangyang/anfupailou.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "��������¥");
        set("long", @LONG
�����ǰ���ʹ��ǰ��һ����¥���ߴ���ɣ��ɻ����Ƴɣ��Ͷ���
�Ľ������ݶ������������������ҫ�»ư���ӳ����̻Իͣ�����Ŀ
Ϊ֮ѣ���о�����Ρ��ׯ�ϡ���̧ͷ��ȥ��������¥���ĸ�����֡�
����ʹ��������¥��վ���������ǵ�ǹ���α�����������ÿһ������
������ˡ�������ǰ�������Ժ�ˡ������������������㳡��
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "south" : __DIR__"guangchang",
                "north" : __DIR__"anfugate",
        ]));
        set("coor/x", -7820);
	set("coor/y", -760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}