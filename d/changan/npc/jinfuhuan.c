//jinfuhuan.c

#include <ansi.h>
inherit BUNCHER; 
inherit F_DEALER;

string *can_converts = ({
        "skull1", "skull2", "skull3", "skull4", "skull5", "skull6",
        "blu gem1", "blu gem2", "blu gem3", "blu gem4", "blu gem5", "blu gem6",
        "grn gem1", "grn gem2", "grn gem3", "grn gem4", "grn gem5", "grn gem6",
        "mag gem1", "mag gem2", "mag gem3", "mag gem4", "mag gem5", "mag gem6",
        "red gem1", "red gem2", "red gem3", "red gem4", "red gem5", "red gem6",
        "yel gem1", "yel gem2", "yel gem3", "yel gem4", "yel gem5", "yel gem6",
});

void create()
{
        set_name("�𸴻�", ({ "jin fuhuan", "jin","fuhuan" }));
        set("title", "�鱦���ϰ�");
        set("shen_type", 1);
        set("str", 35);
        set("gender", "����");
        set("age", 45);
        set("combat_exp", 50000);
        set("attitude", "friendly");
        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set("vendor_goods", ({
                "/d/changan/npc/obj/ring",
                "/d/changan/npc/obj/wrists",
                "/d/changan/npc/obj/neck",
        }));

       setup();

       carry_object("/d/changan/npc/obj/choupao")->wear();
       add_money("silver", 50);
}

void init()
{
        ::init();
        add_action("do_list","list");
        add_action("do_buy", "buy");
        //add_action("do_convert", ({ "convert", "duihuan" }));
}

int do_convert(string arg)
{
        object me, ob, *inv;
        string what, sid, id;
        int i, amount, n1, n2, flag, n;

        me = this_player();
        if( !arg || sscanf(arg, "%d %s to %s", amount, sid, what) != 3 )
                return notify_fail("ָ���ʽ��convert <����> <��Ʒ> to <����Ʒ>\n");

        if( amount < 1 || amount > 5000 )
                return notify_fail("�һ�������������С��1��ͬʱ�����Դ���5000����\n");

        if( !objectp(ob = present(sid, me)) )
                return notify_fail("������û�����ֶ�����\n");

        if( member_array(sid, can_converts) == -1 )
                return notify_fail("�鱦��˵�������Ҷ����������û����Ȥ����\n");

        if( member_array(what, can_converts) == -1 )
                return notify_fail("�鱦��˵��������Ҫ�һ��������������û�С���\n");

        sscanf(sid, "%s%d", id, n1);
        sscanf(what, "%s%d", id, n2);

        if( n1 > n2 ) return notify_fail("�鱦��˵�������Ҳ��������Ķһ���ʽ��������\n");
        else if( n1 < n2 ) n = (int)pow(3, (n2 - n1));

        flag = 0;
        what = replace_string(what, " ", "");
        inv = all_inventory(me);
        for( i=0; i<sizeof(inv); i++ ) {
                if( amount < 1 ) break;
                if( query("id", inv[i]) == sid){
                        if( n1 < n2 ) {
                                flag++;
                                if( flag != n ) {
                                        destruct(inv[i]);
                                        continue;
                                }
                                flag = 0;
                        } else {
                                if( !query("no_identify", inv[i]) )
                                        continue;
                        }
                        
                        destruct(inv[i]);
                        ob = new("/clone/enchase/" + what);
                        ob->move(me, 1);
                        amount--;
               }
        }
        
        sid = replace_string(sid, " ", "");
        while( flag > 0 ) {
                ob = new("/clone/enchase/" + sid);
                ob->move(me, 1);
                flag--;
        }

        message_vision(HIC "$N���һ������Ʒ����$n��\n", this_object(), me);
        return 1;
}

