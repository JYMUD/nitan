// xiulian.c

#include <ansi.h>

inherit F_CLEAN_UP;

int mending(object me);
int halt_mending(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int lvl;
        object where;
        string msg, sign;

        seteuid(getuid());
        where = environment(me);

        if (! arg) return notify_fail("��Ҫ����ʲô��\n");
                
        if( query("pigging", where) )
                return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

        if( !query("no_fight", where) )
                return notify_fail("��������������̫��ȫ�ɣ�\n");

        if( !query("sleep_room", where) )
                return notify_fail("�����һ���ܹ���Ϣ�ĵط�������\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("�����ڵ���̫���ˣ��޷�����������\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("�����ڵľ�̫���ˣ��޷�����������\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("�����ڵ�����̫���ˣ��޷����ıչء�\n");
                
        if (! me->query_skill("yinyang-shiertian"))
                return notify_fail("����������תʮ�����컹û��ѧ�ᣬ��ôȥ������\n");

        if( query("yinyang-shiertian/succeed", me) )
                return notify_fail("���Ѿ���������תʮ����������������߾��磡\n");
                                
        lvl = me->query_skill("yinyang-shiertian", 1);                                
        
        switch (arg)
        {
        case "shier":         
        
                if( !query("can_perform/yinyang-shiertian/zhen", me) )
                        return notify_fail("�㻹û���������������磬��������ʮ�����쾳�磿\n");
                 
                if( !query("can_perform/yinyang-shiertian/jiu", me) )
                        return notify_fail("�㻹û��������Ǭ�����磬��������ʮ�����쾳�磿\n");
                        
                if (lvl < 1200)
                        return notify_fail("���������תʮ��������Ϊ��������������ʮ�����쾳�磡\n");

                if( query("max_neili", me)<50000 )
                        return notify_fail("������������в��㣬����Ŀǰ����������ʮ�����쾳�硣\n");

                if( query("max_jingli", me)<50000 )
                        return notify_fail("����þ������в��㣬����Ŀǰ����������ʮ�����쾳�硣\n");

                if( query("max_qi", me)<50000 )
                        return notify_fail("�������Ѫ���в��㣬����Ŀǰ����������ʮ�����쾳�硣\n");

                if( query("potential", me)-query("learned_points", me)<500000 )
                        return notify_fail("���Ǳ�ܲ�����û��������\n");
                                                                
                msg = "ʮ������";
                sign = "shier";
                break;
                
        case "qiankun":        
        
                if( !query("can_perform/yinyang-shiertian/zhen", me) )
                        return notify_fail("�㻹û���������������磬��������Ǭ�����磿\n");
                 
                if( query("can_perform/yinyang-shiertian/jiu", me) )
                        return notify_fail("���Ѿ�������Ǭ�����磬�������ظ�������\n");
                                                        
                if (lvl < 800)
                        return notify_fail("���������תʮ��������Ϊ��������������Ǭ�����磡\n");

                if( query("max_neili", me)<30000 )
                        return notify_fail("������������в��㣬����Ŀǰ����������Ǭ�����硣\n");

                if( query("max_jingli", me)<30000 )
                        return notify_fail("����þ������в��㣬����Ŀǰ����������Ǭ�����硣\n");

                if( query("max_qi", me)<30000 )
                        return notify_fail("�������Ѫ���в��㣬����Ŀǰ����������Ǭ�����硣\n");

                if( query("potential", me)-query("learned_points", me)<300000 )
                        return notify_fail("���Ǳ�ܲ�����û��������\n");                        
                        
                msg = "Ǭ��";
                sign = "qiankun";
                break;
                
        case "yinyang":

                if( query("can_perform/yinyang-shiertian/zhen", me) )
                        return notify_fail("���Ѿ��������������磬�������ظ�������\n");
                        
                if (lvl < 500)
                        return notify_fail("���������תʮ��������Ϊ���������������������磡\n");

                if( query("max_neili", me)<10000 )
                        return notify_fail("������������в��㣬����Ŀǰ�����������������硣\n");

                if( query("max_jingli", me)<10000 )
                        return notify_fail("����þ������в��㣬����Ŀǰ�����������������硣\n");

                if( query("max_qi", me)<10000 )
                        return notify_fail("�������Ѫ���в��㣬����Ŀǰ�����������������硣\n");

                if( query("potential", me)-query("learned_points", me)<100000 )
                        return notify_fail("���Ǳ�ܲ�����û��������\n");                        
                
                msg = "����";
                sign = "yinyang";
                break;
                
        default:
                return notify_fail("����Ҫ����ʲô����\n");                
        }


        message_vision("$N��ϥ���£���ʼڤ���˹����չ�����������תʮ�����졣\n", me);
        set("startroom", base_name(where), me);
        set("doing", "xiulian", me);
        set("yinyang-shiertian/xiulian", sign, me);
        CLOSE_D->user_closed(me);
        me->start_busy(bind((: call_other, __FILE__, "mending" :), me),
                       bind((: call_other, __FILE__, "halt_mending" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("%s%s(%s)��ʼ�չ����У���ͼ����������תʮ�������" + msg + "���硣",
                              ultrap(me) ? "����ʦ" : "",
                              me->name(1),query("id", me)));

        return 1;
}

int continue_mending(object me)
{
        me->start_busy(bind((:call_other, __FILE__, "mending" :), me),
                       bind((:call_other, __FILE__, "halt_mending" :), me));
        CLOSE_D->user_closed(me);
        tell_object(me, HIR "\n������չ�����������תʮ������...\n" NOR);
        return 1;
}

private void stop_mending(object me)
{
        CLOSE_D->user_opened(me);
        if (! interactive(me))
        {
                me->force_me("chat* sigh");
                call_out("user_quit", 0, me);
        }
}

int mending(object me)
{
        string msg = "";

        if( query("potential", me) <= query("learned_points", me) )
        {
                tell_object(me, "���Ǳ�ܺľ��ˡ�\n");
                message_vision("$N����˫Ŀ����������һ������վ��������\n", me);
                msg = "�˳�";
        }
        
        switch(query("yinyang-shiertian/xiulian", me) )
        {
        case "shier":
        
                if( query("max_qi", me)<10000 || query("max_neili", me)<10000
                 || query("max_jingli", me)<2000 )
                {
                        tell_object(me, "���״̬���ѣ��޷���������������תʮ�����졣\n");
                        message_vision("$N����˫Ŀ����������һ������վ��������\n", me);
                        msg = "�˳�";
                }
                set("max_qi",query("max_qi",  me)-2, me);
                set("max_neili",query("max_neili",  me)-2, me);
                set("max_jingli",query("max_jingli",  me)-1, me);
                
                break;

        case "qiankun":
        
                if( query("max_jingli", me)<2000 )
                {
                        tell_object(me, "���״̬���ѣ��޷���������������תʮ�����졣\n");
                        message_vision("$N����˫Ŀ����������һ������վ��������\n", me);
                        msg = "�˳�";
                }
                set("max_jingli",query("max_jingli",  me)-1, me);
                
                break;

        case "yinyang":

                if( query("max_neili", me)<2000 )
                {
                        tell_object(me, "���״̬���ѣ��޷�����������\n");
                        message_vision("$N����˫Ŀ����������һ������վ��������\n", me);
                        msg = "�˳�";
                }
                set("max_neili",query("max_neili",  me)-1, me);
                
                break;
        }       

        if( query("neili", me)<query("max_neili", me) )
                set("neili",query("max_neili",  me), me);

        if( query("eff_jingli", me)<query("max_jingli", me) )
                set("eff_jingli",query("max_jingli",  me), me);

        if( query("eff_qi", me)<query("max_qi", me) )
                set("eff_qi",query("max_qi",  me), me);

        if (msg == "�˳�")
        {
                CLOSE_D->user_opened(me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                        sprintf("��˵%s(%s)�չ�����������תʮ������������ƺ�û��̫��Ľ�չ��",
                                me->name(1),query("id", me)));

                if (! interactive(me))
                {
                        me->force_me("chat* sigh");
                        call_out("user_quit", 0, me);
                }
                return 0;
        }
        
        addn("learned_points", 1, me);


        if (random(10) == 0)
                tell_object(me, "����������תʮ��������...\n");

        if (random(4000000) < me->query_skill("yinyang-shiertian", 1))
        {
                tell_object(me, HIR "��ϲ���������תʮ���������µ�������ѧ��������ͻ�ƣ�\n" NOR);
 
                if( query("yinyang-shiertian/xiulian", me) == "shier" )
                {
                        addn("yinyang-shiertian/shier", 1, me);
                        if( query("yinyang-shiertian/shier", me) == 12 )
                        {
                                delete("yinyang-shiertian", me);
                                set("yinyang-shiertian/succeed", 1, me);
                                set("can_perform/yinyang-shiertian/tian", 1, me);
                                set("potential",query("learned_points",  me), me);
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                                sprintf("��˵%s(%s)������������תʮ������ġ�ʮ�����졹�����ӵ������ϵ���ѧ���硣",
                                                                me->name(1),query("id", me)));
                                CHAR_D->setup_char(me);
                                stop_mending(me);
                                return 0;
                        }
                
                }

                if( query("yinyang-shiertian/xiulian", me) == "qiankun" )
                {
                        addn("yinyang-shiertian/jiu", 1, me);
                        if( query("yinyang-shiertian/jiu", me) == 9 )
                        {
                                delete("yinyang-shiertian", me);
                                set("can_perform/yinyang-shiertian/jiu", 1, me);
                                set("potential",query("learned_points",  me), me);
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                                sprintf("��˵%s(%s)������������תʮ������ġ���תǬ��������ѧ��������ͻ�ơ�",
                                                        me->name(1),query("id", me)));
                                CHAR_D->setup_char(me);
                                stop_mending(me);
                                return 0;
                        }                
                }
        
                if( query("yinyang-shiertian/xiulian", me) == "yinyang" )
                {
                        switch(query("yinyang-shiertian/zhen", me) )
                        {
                        case "yinyang":
                                delete("yinyang-shiertian", me);
                                set("can_perform/yinyang-shiertian/zhen", 1, me);
                                set("potential",query("learned_points",  me), me);
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        sprintf("��˵%s(%s)������������תʮ�����졸������������ѧ��������ͻ�ơ�",
                                                me->name(1),query("id", me)));
                                CHAR_D->setup_char(me);
                                stop_mending(me);
                                return 0;

                        case "yin":
                                delete("yinyang-shiertian/zhen", me);
                                set("yinyang-shiertian/zhen", "yinyang", me);
                                break;

                        default:
                                set("yinyang-shiertian/zhen", "yin", me);
                        }
                } 

                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("��˵%s(%s)�����չؿ��ޣ���������תʮ���������µ�����",
                                              me->name(1),query("id", me)));

                me->improve_skill("yinyang-shiertian", 250000);
        }

        if( query("yinyang-shiertian/xiulian", me) == "shier" )
        {
                switch (random(4))
                {
                case 0:
                        msg = "����ʱ������ţ�$Nͷ�����ڳ������ɫ��ϼ��ɲ�Ǽ䣬"
                              "������ɢƮ����ԭ���Ļ����ۻ�֮��ȫ����ɢ��ֻ�����Ŀ�������������ҷ���\n";
                        break;

                case 1:
                        msg = "$N���ϵ��ǹɰ�����������·�ʲô�����ǣ�������ϸ��ʱ��"
                              "ȴ���ڲ��ϵػû������������������̬�������к�����ʲô����ȴ�ǲ���ġ�\n";
                        break;

                case 2:
                        msg = "�ǹɰ����ٶȱ任��̬���𽥵س�����ȥ����ס$N�����Σ�"
                              "��ͣ����$N����Χת�����ٶ�Խ��Խ�죬ԶԶ��ȥ������һ������Χ��$N������������\n";
                        break;

                default:
                        msg = "$N�����΢΢���̣�������һ��Ц���������ϣ���Χ�İ�������Ц��"
                              "�����������ر䵭�ˣ���û�ˣ�ֻ��$N��������ƽ����һ�ֹ⻪��\n";
                        break;
                }
        }
                
        if( query("yinyang-shiertian/xiulian", me) == "qiankun" )
        {
                switch (random(5))
                {
                case 0:
                        msg =  "$N�����룬˵��һ����ɽ����Ȼ���һ����������������ؼ䣬"
                               "�����˴��ڵ��ⶼ����һ�ּ���ֹ��״̬�������������Ķ�����Ҳ������ҡ��֡�\n";
                        break;

                case 1:
                        msg = "$N�����룬˵��һ����ˮ�������λ��������ﲻ���ֺ�����������"
                              "����$N������һ��ѩ����һֱ��Ʈҡ���������޷�"
                              "��׽ס$N��Ӱ�ӡ�\n";
                        break;

                case 2:
                        msg = "$N�����룬˵��һ�����硱��ֻ����Χ���ϵ���Ҷ�����ر�����"
                              "�������ڰ����Ʈ�ţ�����$Nȴ�о����������ĸ�����"
                              "�ӹ�$N�����š�\n";
                        break;

                case 3:
                        msg = "$N��Ȼ��Ц������һ�ֿ���һ�е�������¶��һͶ�֡�һ����֮�У�"
                              "�Լ��������������֣�������ͬ��\n";
                        break;

                default:
                        msg = "$NͻȻ������ڰ���л���һ���ۼ����ǵ��ۼ��·�ɽ�ǰ㼫����"
                              "����ˮ����������������Ƶļ��䣬���̺�����ؼ������һ�ж���ѭ���䶯"
                              "��������\n";
                        break;
                }
        }

        if( query("yinyang-shiertian/xiulian", me) == "yinyang" )
        {
                if( query("yinyang-shiertian/zhen", me) == "yin" )
                        msg = "$N���²������ˣ����Ż��Ĵ������������ɽ��һ�ɺ���֮��"
                              "�Եص׼������$N���ľ�������\n";
                else
                if( query("yinyang-shiertian/zhen", me) == "yinyang" )
                {
                        if (random(2) == 1)
                                msg = "$N��ɫ��ײ�����˫Ŀ��ɫҲ��������һͫ�����ʺ����Σ�"
                                      "һͫ��������˪���������÷���ɢȥ��\n"; 
                        else
                                msg = "$N�����У�����֮�������ھ���֮�䣬Ψ�����񴦳��Ȳ��䣬"
                                      "һ����㱣�����֮��ȴ���뾭��������֮�����ػ����������ҡ�\n";
                }
                else
                        msg = "$N��Ŀ���ӹ�â����ĺ��գ�����Ϊ�飬��������εĴ��ۣ�"
                              "һ������֮����ͷ����ɢ���ڿ����ٸ��ص�$N���ļ䡣\n";                
        }

        message_vision(msg, me);
        return 1;
}

int halt_mending(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me, "����ֹ������������תʮ�����졣\n");
        message_vision(HIY "$N" HIY "����̾��һ�����������������ۡ�\n\n" NOR, me);
        addn("potential", (query("learned_points", me)-query("potential", me))/2, me);
        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name(1) +
                              "����������תʮ��������;ͻȻ������");
        return 1;
}

private void user_quit(object me)
{
        if (! me || interactive(me))
                return;

        me->force_me("quit");
}

int help(object me)
{
        write(@HELP
ָ���ʽ : xiulian

�����������ǽ��������ѧ����������
����תʮ�����쵱�У�������תʮ����
�����������д�ĳ����������˵�Ѿ���
����һ�ֵ�������ѧ��ʽ������һ����
ѧ���磬��Ϊ���������������ļ�����
ѧ�������ɣ������������֪�����Բ�
�ܿ������ļ��м�ʽ�����ֳ������壬
������Ҫ��������������ľ��磬ֻ��
ӵ���߽��⼸�־��������ɹ��󣬷���
��������תʮ�����췢�����硣

HELP );
        return 1;
}