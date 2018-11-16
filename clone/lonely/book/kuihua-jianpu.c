#include <ansi.h>; 
inherit ITEM;

void create()
{
        set_name(HIW "���������ס�" NOR, ({ "kuihua jianpu", "kuihua", "jianpu"}));
        set_weight(500);
        if (clonep())
               set_default_object(__FILE__); 
        else {
                set("unit", "��");
                set("material", "paper");
                set("no_sell", 1);
                set("long", HIW "\n����һ���ñ�ֽд�ɵ��飬��Ƥ��д�С�������"
                            "�ס���\n�֡���������Ŷ���(read)����\n\n" NOR, );
        }
}

void init()
{
        add_action("do_du", "read");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;

        string skill, book, msg;
        int lv;

        if (! arg)
        {
                write("�ж���������ָ���ʽ��read <����> from <��������>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", skill, book) != 2)
        {
                write("�ж���������ָ���ʽ��read <����> from <��������>\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("��������æ���ء�\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("���޷���ս����ר�������ж���֪��\n");
                return 1;
        }

        if( query("no_fight", where )
            && query("doing", me) != "scheme" )
        {
                write("���޷������ﾲ�������ж��������ס�\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;
        }

        if (! id(book))
        {
                write("����û���Ȿ�顣\n");
                return 1;
        }

        if (skill != "��а��Ӱ" && skill != "��а��Ӱ")
        {
                write("���������ϲ�û�м���������о������ݡ�\n" NOR);
                return 1;
        }

        if (me->query_skill("pixie-jian", 1) < 1000)
        {
                write("���а������Ϊ���㣬�޷��������а��\n");
                return 1;
        }
        
        if (me->query_skill("dodge", 1) < 1000)
        {
                write("������Ṧ��Ϊ���㣬�޷��������а��\n");
                return 1;
        }
                
        if( !query("reborn/times", me) )
        {
                write("��δ����ת�����飬�޷��������а��\n");
                return 1;                
        }
        
        if( query("combat_exp", me)<10000000 )
        {
                write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                return 1;
        }

        if( query("jing", me)<100
            || query("qi", me)<100
            || query("neili", me)<200 )
        {
                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                return 1;
        }

        write(HIW "��ѧ���ˡ�" HIG "��а��Ӱ" HIW "����\n" NOR);
        set("can_perform/pixie-jian/jian", 1, me);
        destruct(this_object());
        return 1;

}
