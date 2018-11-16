// Room: /d/gumu/jitan.c
// Last Modifyed by Winder on Jan. 14 2002

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIC"ʯ��"NOR);
        set("long",@long
һ��յ�����ʯ�ң���ǰ������һ����̳������ʷ���һЩ�Ϲ���
��������ɢ����ҡҷ�Ļ�⣬һЩ��Ĺ���������ַ���Ĺ��������׼�
�ʷ��ڼ�̳����������ο�����Ӣ�顣
long);

        set("exits",([
                "west" : __DIR__"mudao21",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3180);
        set("coor/y", 0);
        set("coor/z", 90);
        setup();
}

void init()
{
//        add_action("do_jibai","jibai");
//        add_action("do_ketou","ketou"); 
}

int do_jibai(string arg)
{
        object ob, me=this_player();
        int exp, pot, score;
        
        ob = present("head", me);
        if ( arg == "head")
        {
                if ( ! ob )
                        return notify_fail("��û����ͷ������ʲô��\n");        
                if( !query_temp("gm/job", me) )
                        return notify_fail("�㻹ûȥѲ���أ�����������׼���\n");
                if( query("name", ob) != "����Ů�ӵ��׼�" )
                        return notify_fail("������Ū������ͷ�����˺����ǹ�Ĺ���氡��\n");        
                if( query("victim_user", ob) )
                        return notify_fail("������Ū�����׼���ɱ�����˰ɣ�\n");
//                if( ob->query("kill_by") != me)
//                        return notify_fail("���������ɱ�İɣ�������ô�õ������ͷ�ģ�\n");
                message_vision(HIY"$N���������ؿ��˼�����ͷ��Ȼ��������$n�ʷ��ڼ�̳���ࡣ\n"NOR,me,ob);
                exp =30+random(20);
                addn("combat_exp", exp, me);
                pot= 20+random(10);
                addn("potential", pot, me);
                score= 5+random(5);
                addn("score", score, me);
                delete_temp("gm/job", me);
                delete_temp("meet_nuzi", me);
                call_out("destroying", 1, ob);
                tell_object(me,HIW"�㱻�����ˣ�\n" + 
                chinese_number(exp) + "��ʵս����\n" +
                chinese_number(pot) + "��Ǳ��\n" +
                chinese_number(score) + "��ʦ���ҳ϶�\n"NOR);        
                return 1;
        }
        return notify_fail("����ʲô���ݰ���\n");
}

void destroying(object ob)
{
        destruct(ob);
        return;
}

int do_ketou(string arg)
{
        mapping fam;
        object me=this_player();
        if( !(fam=query("family", me)) || fam["family_name"] != "��Ĺ��" )
                return notify_fail("�㲻�ǹ�Ĺ���ˣ��ڴ˿�ͷ������\n");
        if ( arg == "jitan")
        {
                if( query("combat_exp", me)<30000 )
                        return notify_fail("�㿴�ż�̳���ĸ�����̫����ɻֲ̿�����������վ������\n");
                if( query("combat_exp", me)>180000 )
                        return notify_fail("�㻹��ȥ�����϶��Щ������ο��ʦ�ɣ�\n");
                if( query_temp("bishou", me)<2 )
                {
                        if(objectp(present("bi shou", me)))        
                                return notify_fail("�㷢�ֺ������Ѿ��յ����ģ�ʲôҲû���ˡ�\n");
                        addn_temp("bishou", 1, me);
                        message_vision(HIY"$N���������ض��ż�̳����ͷ����\n"NOR, me);
                        return 1;
                }
                message_vision(YEL "��̳����ת����$N�������С�������ó�һ��ذ�ס�\n"NOR, me);
                delete_temp("bishou", me);
                new(__DIR__"obj/bishou")->move(me);
                return 1;
        }
        return notify_fail("�����ʲô��ͷ����\n");
}
