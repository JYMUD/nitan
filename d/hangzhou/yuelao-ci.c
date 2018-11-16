// Room: /yuelaoci.c
#define QIUQIAN "/d/hangzhou/qiuqian"

#include <ansi.h>

#include <room.h>
inherit ROOM;
int is_chat_room() { return 1;}
void create(){
        set("short", "������");
        set("long", @LONG
�����������ƹ���Ե�����ˣ���˵���к��ߣ�������ϵ����Ů
�󷽵Ľ��ϣ�����˻����ǧ��ջ�����Ե��������һ��СԺ��
�������ݡ���������������������������ˣ����ñ�����磬�׷�ͯ
�գ�Ц�����档����ǰ�������ǹ�������¯����̨��ǩͲ����Ȼ����
��Ҳ���ٲ��˵ġ�����һ�������С������Ը���������ˣ������˾�
������ǰ��ע���£�Ī�����Ե�������İ��о����������������ǩ
��qiuqian����һ����Ե���¡�
LONG );
        set("no_fight", "1");
        set("no_steal", "1");
        set("no_sleep_room","1");

        set("exits", ([
                "south" : "/d/hangzhou/yuanyuan-tai",

        ]));
	set("coor/x", 770);
	set("coor/y", -1960);
	set("coor/z", 10);
	setup();
}
void init()
{
        add_action("do_qiuqian","qiuqian");
}

int do_qiuqian(string arg)
{
            object me;

        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( time()-query("last_qiuqian_time", me)<600 )
                return notify_fail("��ôƵ������ǩ����Ĳ�����ǩ���飬��ʮ���������ɡ�\n");

        write(HIC "
���ϵ�����������˼��ݣ����������дʣ����������ϣ��͸��Һ���Ե�ɣ���
�����������֧ǩ��������һ�ᣬ��������۾���ǩ�ġ�\n
" NOR, me);
        write(HIC "ǩ��д�ţ�" + QIUQIAN->query_qiuqian() + "��\n" NOR, me);
        set("last_qiuqian_time", time(), me);
        return 1;
}