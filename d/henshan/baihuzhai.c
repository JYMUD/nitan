#include <ansi.h>
inherit ROOM;

string show_hua();

void create()
{
        set("short", "�ٺ�ի");
        set("long", @LONG
������Ƕŷ���İٺ�ի����ʵһ����֪���ⲻ����һ���ƾɵ�
���ã� ֻ�����ڳ����ª��ǽ��ȴ�����˻�(hua)����Щ���Ƕŷ��
�Լ�������ƽʱ�Ϳ�����Щ��Ϊ����
LONG );
        set("objects", ([
                __DIR__"npc/dufeng" : 1,
        ]));

        set("exits", ([
                "north"  : __DIR__"xiaoxiang2",
        ]));

        set("no_fight", 1);

        set("item_desc", ([
                "hua" : (: show_hua :),
        ]));

	set("coor/x", -6880);
	set("coor/y", -5730);
	set("coor/z", 0);
	setup();

}

string show_hua()
{
        return HIW "\nֻ��ÿ���������ľ��Ǻ����а׺���������ں����������Ϻ�\n"
               "�����򾲡����ҡ���ŭ�����ģ���������顢�򽿺���ǧ\n"
               "�˰�̬�������ߡ�\n\n" NOR;
}