// Room: /d/guiyun/zhongting.c
// Last Modified by winder on Jul. 9 2001

#include <ansi.h>
inherit ROOM;

string look_xiao();
string look_zishi();

void create()
{
        set("short","����");
        set("long",@LONG
���ǹ���ׯ��������ׯ�еĴ����Լ��ټ�����ѵ���������������
�ġ������޽������Զ������������Ϊ�¾ɣ�����ɨ��ʮ�ָɾ�������
Ҳ��Ϊ���㣬��ȫû�г����լ������֮�����ıڹ���һЩ�����黭��
Ʒ����Ϊ�ϳ�֮�����Ե������۹ⲻ�������д������֡�
    ��������һ��̫ʦ�Σ��κ��ǽ�Ϲ���һ����(hua)��
LONG );
        set("objects",([
                __DIR__"npc/kezhene" : 1,
                __DIR__"npc/zhucong" : 1,
                __DIR__"npc/hanbaoju" : 1,
                __DIR__"npc/nanxiren" : 1,
                __DIR__"npc/zhangasheng" : 1,
                __DIR__"npc/quanjinfa" : 1,
                __DIR__"npc/hanxiaoying" : 1,
                __DIR__"npc/guanjia" :     1,
                __DIR__"npc/zhuangding3" : 1,
        ]));
        set("exits",([
                "east"  : __DIR__"qianting",
                "north" : __DIR__"zoulang1",
                "south" : __DIR__"zoulang4",
        ]) );
        set("item_desc", ([
                "hua" :  "������һλ��ò���ǵ��������ߣ����ڴ���(xiao)��������������(zishi)ȴ�е���֡�\n",
                "xiao" : (: look_xiao :),
                "zishi" : (: look_zishi :),
        ]) );

        set("no_clean_up",0);
        set("coor/x", 260);
        set("coor/y", -830);
        set("coor/z", 0);
        setup();
}

string look_xiao()
{
        object me = this_player();

        if( !query_temp("guiyun_hua", me))return "��������������������ǹ��죡\n";
        set_temp("guiyun_hua", 2, me);
        return "ԭ���������˾��ǰ��������ŵ��ﵱ���˽����衣\n";
}

string look_zishi()
{
        object me = this_player();
        int level, exp;

        level = me->query_skill("sword", 1);
        exp=query("combat_exp", me);
        if( query_temp("guiyun_hua", me)<2 )
        {
                set_temp("guiyun_hua", 1, me);
                return "����ϸ�ض����Ż������˵����ˣ���㱼�·𿴼��������ڻ����趯��ʲô��\n";
        }
        else
        {
                write("ԭ��������������������ﾹȻ�����Ÿ���Ľ�����\n");
                if (me->is_busy())
                {
                        write("��ϧ��������æ��������£��޷�ר���о��������\n");
                        return "";
                }
                if( me->is_fighting() ) {
                        write("��ϧ����������ս���У��޷�ר���о��������\n");
                        return "";
                }
                if( query("jing", me)<30 )
                        return "��ϧ��̫���ˣ��޷����о������о��������\n";
                if (me->query_skill("sword", 1) > 100)
                        return "�������ǰ���㿴���ܼ���Ļ������ڵ�������Ѿ�û��ʲô��ֵ���о����ˡ�\n";
                if ((int)me->query_skill("sword", 1) < 30 )
                        return "��Ŭ����ͼ�ӻ������˵������￴��Щʲô��ȴ����һ�ж���ͽ�͵ġ�\n";

                me->receive_damage("jing", 25);
                if( level * level * level /10 < exp)
                        me->improve_skill("sword",query("int", me));

                write("����ϸ�����Ż���������������ˡ�\n");
                if (!random(8))
                        tell_room(this_object(), me->name() + "��ϸ�����Ż���������������ˡ�\n", ({me}));
                return "��Խ������õ�΢��֮�����˽�һ������ʶ��\n";
        }
}

void init()
{
        object me = this_player();
        int score, skill, age;

        if( query("age", me) >= 30 || random(query("kar", me))<15 )
                return;

        if( query("family/master_id", me) != "lu chengfeng" && 
            query("family/master_id", me) != "qu lingfeng" )
                return;


        age=query("age", me)-10;
        skill = (me->query_skill("force") + me->query_skill("dodge") +
                me->query_skill("strike") + me->query_skill("qimen-wuxing")) / 4;
        skill*=query("combat_exp", me)/1000;
        score = skill / age;

        if (score < 1000)
                return;

        remove_call_out("recruit_ob");
        call_out("recruit_ob", 1, me);

        tell_object(me, CYN "���������е�Ź֣��ƺ����˸��棿\n" NOR);
}

void recruit_ob(object me)
{
        object ob, *obj;
        int i, j = 0;

        if (! me) return;

        obj = all_inventory(environment(me));

        for(i = 0; i < sizeof(obj); i++)
        {
                if (playerp(obj[i]))
                j++;
        }

        if (j > 1) return;

        ob = new(CLASS_D("taohua/huang"));
        if (! me->is_busy())
                me->start_busy(1);
        ob->move(environment(me));

        message_sort("$Nǰ��ͻȻ������һ�ˣ���ĸ��ݣ�����ɫ���ۣ���ɫ�Ź�֮�������������ƺ�����"
                       "΢΢ת��������֮�⣬����ڱǣ����Խ�Ӳ��ľʯ��ֱ��һ������ͷװ�ڻ��˵������ϡ�\n\n", me);

        message_sort("$Nһ��֮�£���ʱһ�������ӱ�����ֱ��������Ŀ�������������ഥ���㶼�����ٿ�����ʱ��"
                       "ͷת����������Ȼ������Ī���������ʦүү�������д��ŵ��һ������� æ��ǰ����������"
                       "�����ĸ�ͷ��˵���������ߵ��ʦ�档����ҩʦ���������ˣ����������������ȴ������ץס$N��"
                       "��һ�ᣬ���Ʊ���$N��ͷ���¡�����\n", me);
        message_sort("$Nһ�����������ϸ�룬�Ͻ����μ�����ʹ��һ�С������ڿա���������ͬΪ�������������Ʈ��һ�����ࡣ\n\n", me);
        message_sort("��ҩʦ΢һ㶣�����һ������" + RANK_D->query_rude(me) + "ȴ�м������ʣ��Ҿͳ�ȫ��ɡ�\n\n", me);

        message_sort("$N��Ҫ��$nΪ���ӡ�\n", ob, me);
        tell_object(me, YEL "�����Ը���" + ob->name() + "Ϊʦ������ apprentice ָ�\n" NOR);
        set_temp("huang_recr", 1, me);

        //remove_call_out("finish_recr");
        call_out("finish_recr", 30, me, ob);
}

void finish_recr(object me, object ob)
{
        if (! objectp(me) || ! objectp(ob))
                return;

        if( query("family/master_id", me) != "huang yaoshi" )
        {
                message_vision("$N��Цһ����" + RANK_D->query_rude(me) + "��Ȼ�м��ֳ����ӡ�˵��ƮȻ��ȥ��\n", ob);
                delete_temp("huang_recr", me);
                destruct(ob);
        }
        return;
}
