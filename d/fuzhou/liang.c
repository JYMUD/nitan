// room: liang.c

#include <ansi.h>
#include <room.h>

#define JIASHA    "/clone/lonely/book/kuihua3"

inherit ROOM;

void create()
{
        object item;
        set("short","���ҷ���");
        set("long", @LONG
�����������ҵķ��������¹��ƣ���Χ����Щ��ľͷ��ש�ߡ�ͻȻ
��������깴���һ�����ġ�
LONG );
        set("exits", ([
                "down" : __DIR__"mishi",
        ]));
        set("objects", ([
                //__DIR__"obj/jiasha" : 1,
                "/d/xingxiu/npc/snake" :1,
        ]));
        set("coor/x", 1820);
        set("coor/y", -6312);
        set("coor/z", 10);
        setup();
        item = find_object(JIASHA);
        if( !objectp(item) || !environment(item) ) {
                item = get_object(JIASHA);
                item->move(this_object());
                item->start_borrowing();
        }
}


void init()
{
        object me = this_player(), ob;
        int exp, pot, sc;

        exp = 10000 + random(3000);
        pot = 1000 + random(300);
        sc = random(50);

        ob = find_object(JIASHA);
        if (! ob) ob = load_object(JIASHA);

        if (! objectp(ob))
                return 0;

        if (! objectp(present("jia sha", this_object())))
                return 0;

        if( !query("skybook/xiaoao/baodian", me) )
        {
                addn("combat_exp", exp, me);
                addn("potential", pot, me);
                addn("score", sc, me);
                tell_object(me, HIY "\n���Ծ�Ϸ�������ʱ����һ�����İڷ����С�\n\n"
                                NOR + HIW "��ɹ����ҵ��˿������䣡\n" NOR + HIC
                                "ͨ����ε�������������" + chinese_number(exp) +
                                "�㾭�顢" + chinese_number(pot) + "��Ǳ\n���Լ�"
                                + chinese_number(sc) + "�㽭��������\n\n" NOR);
                set("skybook/xiaoao/baodian", 1, me);
        } else
                tell_object(me, HIY "\n���Ծ�Ϸ�������ʱ����һ�����İڷ����С�\n\n" NOR);
}

void reset()
{
        object item;
        ::reset();
        item = find_object(JIASHA);
        if( !objectp(item) || !environment(item) ) {
                item = get_object(JIASHA);
                item->move(this_object());
                item->start_borrowing();
        }
}
