// Room: /d/xingxiu/jushi.c
// Last Modified by winder on Apr. 25 2001

#include <ansi.h>
inherit ROOM;
int xxdazuo(object me);
int halt_xxdazuo(object me);
void create()
{
        set("short", HIB"��ʯ"NOR);
        set("long", @LONG
�������һ��ں�ɫ�ľ�ʯ�ϡ������ڰ�գ�����һ�������ɵ�ͷ��Ŀѣ��
���ֻ��Զ������ɽɫ��һ��ɽ�紵���������Ŀ���������Ŷ�ʱ����������
��(liangong)һ�ѵء�
LONG
        );
        set("exits", ([
                "down" : __DIR__"xiaolu",
        ]));
        set("outdoors", "xingxiu");
        set("coor/x", -49900);
        set("coor/y", 20200);
        set("coor/z", 100);
        setup();
}

void init()
{
        object me = this_player();
        object ob = this_object();
        object        *inv = all_inventory( ob );
        
        if( query("family/family_name", me) != "������" && !wizardp(me) )
                for ( int i = 0; i < sizeof(inv); i++ )
                        if( (userp(inv[i]) && inv[i] != me && !wizardp(inv[i])) || time()-query_temp("LAST_PKER_TIME", me)<7200 )
                        {        
                                write( WHT"�����Ͼ�ʯ��ȴ����������������֮����ֻ���㬵�����������\n"NOR );
                                me->move( __DIR__"xiaolu" );
                                return;
                        }

        add_action("do_xxdazuo", "liangong");
}

int do_xxdazuo(string arg)
{     
        int xxdazuo_cost;
        mapping fam;
        object me;
        me = this_player();   
        fam=query("family", this_player());

//        if (!fam || fam["family_name"] != "������")
//               return notify_fail("��͵�������ɽ��أ����������������\n");
    
        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if( query("max_qi", me)<400 )
                return notify_fail("�����ڵ���̫���ˣ��޷��ڴ�������\n");

        if(me->query_skill("force") < 100 )
                return notify_fail("����ڹ��������������ڴ������к����档\n");

        if( !stringp(me->query_skill_mapped("force")) )
        return notify_fail("��������� enable ѡ����Ҫ�õ������ڹ���\n");

              if( (me->query_skill("force")*8+query("combat_exp", me)/1000) <= query("max_neili", me) )
              return notify_fail("�����Ѿ������������Ϊ�ˡ�\n");

        if( !arg || !sscanf(arg, "%d", xxdazuo_cost))
                return notify_fail("��Ҫ��������������\n");
        if (xxdazuo_cost < 10)
        return notify_fail("���޷�������Ϣ���е���˾�ϸ�ĳ̶ȣ�\n");

        if( query("qi", me)<xxdazuo_cost )
                return notify_fail("�����ڵ���̫���ˣ��޷�������Ϣ����ȫ��������\n");

        if( query("jing", me)*100/query("max_jing", me)<70 )
                return notify_fail("�����ھ��������޷�������Ϣ��������\n");

        message_vision("$N��ϥ�����˹������彥����һ����������Χ��\n",me); 
        write(BLU"�����ھ�ʯ�ϣ��˶������ھ�����о�����ɽ���ѹ�������ڵ��ھ���ʼ������ǿ�ˡ�\n"NOR);

        set_temp("pending/xxdazuo", 1, me);
        set_temp("xxdazuo_cost", xxdazuo_cost, me);
        me->start_busy((: xxdazuo :), (:halt_xxdazuo:));
        return 1;
}

int xxdazuo(object me)
{
        int xxdazuo_cost=query_temp("xxdazuo_cost", me);
        int neili_gain = 1 + (int)me->query_skill("force") / 10
                * (1 + (int)me->query_skill("force") / 300);    

        if (neili_gain > xxdazuo_cost) neili_gain = xxdazuo_cost;
        neili_gain = neili_gain + random(neili_gain) / 2;
        addn("neili", neili_gain, me);
        set_temp("xxdazuo_cost", xxdazuo_cost-=neili_gain, me);
        me->receive_damage("qi", neili_gain);

        if (xxdazuo_cost > 0) return 1;

        delete_temp("pending/exercise", me);
        delete_temp("pending/xxdazuo", me);
        message_vision("ɽ�罥����ǿ��$N�������Ͳ�ס��˫��һ����վ��������\n", me);    
//        me->improve_skill("huagong-dafa", 1);
        if ((int)me->query_skill("force",1)<150)
            me->improve_skill("force", 1); 
        if( query("neili", me)<query("max_neili", me)*2 )
                return 0;
     if( (me->query_skill("force")*8+query("combat_exp", me)/1000) <= query("max_neili", me)){
                write("���������Ϊ�Ѿ��ﵽ�˴˵����ܰ�����ļ��ޡ�\n"); 
                set("neili",query("max_neili",  me), me);
                return 0;
        }
        addn("max_neili", 1, me);
        set("neili",query("max_neili",  me), me);
        write("���������Ϊ�����ˣ���\n");   
        return 0;
}



int halt_xxdazuo(object me)
{
        if( query("neili", me)>(query("max_neili", me)*2) )
        {
                message_vision("$Nǿѹס��Ϣ��˫��һ����վ��������\n", me); 
                set("neili", (query("max_neili", me)*2), me);
        }
        delete_temp("pending/xxdazuo", me);
        return 1;
}