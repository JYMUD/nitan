// sg_mianzhao.c ����
// Last Modified by winder on Jul. 12 2002

#include <armor.h>
inherit HEAD;

#define SGCANGKU "/d/shenlong/cangku"

void do_copy(object, object);
void do_flee(object);
int eff_fam(object);

#include "/d/shenlong/masters.h"
#include "/d/shenlong/safeplaces.h"

void create()
{
        set_name("����", ({ "mianzhao", "mask" }) );
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "���Ǹ����������еĺڲ�ͷ�ף��ܰ������Դ���������ֻ¶�������۾���\n��ÿ��Ϊ�����̰참�������ʬ����д��(sign)������������ɱ������\n");
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("value", 10);
                set("no_get", "�������������뿪�Ƕ���\n");
                set("no_drop", "�������������뿪�㡣\n");
        }
        setup();
}

void init()
{
        add_action("do_wear", "wear");
        add_action("do_remove", "remove");
        add_action("do_sign", "sign");
        add_action("do_forcejoin", "forcejoin");
        add_action("do_search", "search");
        add_action("do_open", "open");
        add_action("do_job", "job");
        add_action("do_jobtime", "jobtime");
}

int do_wear(string arg)
{
        if (!arg || (arg != "mianzhao" && arg != "mask") ) return 0;

        set_temp("apply/name", ({"������"}), this_player());
        set_temp("apply/short", ({"������(Mengmianren)"}), this_player());
        set_temp("apply/long", ({"һ���ڲ����棬��������ļһ\n"}), this_player());

        return 0;
}

int do_remove(string arg)
{
        if (!arg || (arg != "mianzhao" && arg != "mask") ) return 0;

        delete_temp("apply/name", this_player());
        delete_temp("apply/short", this_player());
        delete_temp("apply/long", this_player());

        return 0;
}

int do_sign(string arg)
{
        object obj;
        object me = this_player();
        string v_id, v_name;
        mapping pkjob;
        int mygain;

       if( !query("sg/spy",me) && !mapp(query("sgjob_join",me)) ) 
                return 0;

        if( !arg || arg != "corpse" || !(obj = present(arg, environment(me))) )
                return 0;

        if( query("my_killer", obj) != query("id", me) )
                return 0;

        v_name=query("victim_name", obj);
        if( query("signed", obj) || 
                (v_name != query("sgjob/victim_name", me) && 
                v_name != query("sgjob_join/victim_name", me)) )
                return 0;

        if( v_id=query("sgjob_join/victim_id", me) )
        {
                delete("sgjob_join", me);
                set("sg_ok/join", 1, me);
        }
        else
        {
                v_id=query("sgjob/victim_id", me);
                delete("sgjob", me);
                set("sg_ok/pk", 1, me);
                mygain=query("combat_exp", obj)/1000;
                addn("sg/exp", 100+mygain*(mygain/2000+1)/40, me);
                if( mygain > 1000 ) mygain = 1000;
                addn("combat_exp", mygain, me);
        }

        set("signed", 1, obj);
        log_file("test/ShenlongPker",sprintf("%s��%sʱɱ��%s(%s).\n",query("name", me),ctime(time()),v_name,v_id));

        set("sg_victim/"+time(), v_id, me);
        tell_room(environment(me), "��������ʬ����д�¡�����������ɱ�����������֡�", ({me}));
        tell_object(me, "����ʬ����д�¡�����������ɱ�����������֡�\n");
        return 1;
}

int do_forcejoin(string arg)
{
        object *inv, target, me = this_player();
        int fp, dp;
        mixed busy;

        if( !query("sg/spy", me) )
                return notify_fail("�㲻�������̵��ˣ���ʲô����\n");
        if( query("sg_ok/forcejoin", me) )
                return notify_fail("���Ȼ�ȥ�����ɡ�\n");
        if( query("no_fight", environment(me)) )
                return notify_fail("���ﲻ��ǿ�ȵĵط���\n");
        if ( busy = me->query_busy() )
        {
                if (intp(busy)) me->start_busy(busy+1);
                        return notify_fail("��������æ�ţ�\n");
        }
        if( !arg || !(target = present(arg, environment(me))) )
                return notify_fail("��Ҫ��˭�������̣�\n");

        if( query("sgjob/forcejoin", me) != query("id", target) )
                return notify_fail("���Ҵ����ˡ�\n");

        if( query("sg/spy", target) || 
                query("family/family_name", target) == "������" )
                return notify_fail(target->name()+ "�Ѿ����������ˣ������ٷ����ˡ�\n");
        if( !living(target) )
                return notify_fail("�������ٱ�"+target->name()+"Ҳû���á�\n");
        if( query_temp("forcejoining", me) )
                return notify_fail("���Ѿ��ڱ������ˡ�\n");
        if( query("jing", me)*100/query("max_jing", me)<40 || 
                query("jingli", me)*100/query("max_jingli", me)<40 )
                return notify_fail("��̫���ˣ���Ϣһ�����Ȱ�ɡ�\n");

        me->receive_damage("jing", 60);
        me->receive_damage("qi", 60);

        message_vision("\n$N��$n�����ȵ���" + RANK_D->query_rude(target) + "����������̣������ɱ���ۣ�����\n", me, target);

        inv = all_inventory(environment(target));
        for(int i = 0; i < sizeof(inv); i++)
        {
                if( living(inv[i]) && inv[i] != me && inv[i] != target &&
                        !query("sg/spy", inv[i]) && 
                        query("family/family_name", inv[i]) && 
                        query("family/family_name", inv[i]) == query("family/family_name", target))inv[i]->kill_ob(me);
        }
        fp = (int)me->query_skill("force") * 3 +
                (int)me->query_skill("parry") * 2 +
                (int)me->query_skill("dodge");
        fp*=query("sg/exp", me)+
                query("combat_exp", me)/1000+1;
        dp=query("jing", target)+query("max_jing", target)+
                query("qi", target)+query("max_qi", target)+
                query("jingli", target)*2+
                query("neili", target)*3;
        if ( dp < 1 ) dp = 1;
        dp*=query("combat_exp", target)/1000+1;

        set_temp("forcejoining",query("id",  target), me);
        call_out("complete_forcejoin", 8+random(10), me, target, fp, dp);
        return 1;
}

private void complete_forcejoin(object me, object target, int fp, int dp)
{
        object ob, *inv;
        int t_shen, t_exp, bonus = 2, times, record;

        if( !present(target, environment(me)) ) return ;
        if( !objectp(me) )  return;
        delete_temp("forcejoining", me);
        addn_temp("forcetimes", 1, target);

        if( !objectp(target) ) return;
        if( environment(target) != environment(me) ) return;

        if( !living(target) )
        {
                tell_object(me, "�������ٱ�Ҳû���á�\n");
                return;
        }
        t_shen=query("shen", target);
        while ( t_shen > 10 )
        {
                bonus += 1;
                t_shen = t_shen/16;
        }
        if( member_array(query("id", target),masters) != -1)bonus*=30;
        dp *= bonus;
        dp *= 4 * eff_fam(target);
        if( target->query_condition("embedded") ) dp /= 2;
        if( (int)target->query_condition("snake_poison") > 0 ) dp /= 2;
        if( (int)target->query_condition("insect_poison") > 0 ) dp /= 2;
        if( (int)target->query_condition("xx_poison") > 0 ) dp /= 2;
        if( query_temp("hgmz", target)>0)dp/=4;
        if( (int)target->query_condition("hyz_damage") > 0 ) dp /= 2;
        if( (int)target->query_condition("hsf_poison") > 0 ) dp /= 2;
        if( dp < 1 ) dp = 1;
        if( random(fp+dp)  > dp )
        {
                message_vision("$N����������ֻ�ô�Ӧ$n���������̡�\n", target, me);
                if( member_array(query("id", target),masters) != -1 )
                        bonus += 100;
                bonus+=query("sg/exp", me)*2000/query("combat_exp", me);
                bonus *= eff_fam(target);
                if(bonus>300)bonus = 300;

                record = bonus/3 + random(bonus/3);
                addn("combat_exp", record, me);
                addn("sg/exp", 1, me);
                addn("shen", -query("combat_exp", target)/100, me);

                log_file("test/ForceJoin",sprintf("%s��%sʱ��%s�������̻��%s�����\n",query("name", me),ctime(time()),query("name", target),chinese_number(record)));

                bonus /= 4;
                addn("potential", bonus/3+random(bonus/3), me);
                if( query("potential", me)>query("max_potential", me) )
                set("potential",query("max_potential",  me), me);

                delete("sgjob", me);
                set("sg_ok/forcejoin", 1, me);

                inv = all_inventory(target);
                for(int i = 0; i < sizeof(inv); i++)
                        if( inv[i]->is_unique() ||
                                query("weapon_prop/damage", inv[i])>100 || 
                                query("armor_prop/armor", inv[i])>100 )
                        {
                                inv[i]->move(me);
                                message_vision("$N��" + inv[i]->name() + "˫�ַ��ϵݸ�$n��\n", target, me);
                        }
                set("sg/spy", 1, target);
                delete_temp("forcetimes", target);
                set("attitude", "heroism", target);
                set("shen_type", -1, target);
                target->remove_killer(me);
                target->start_busy(1);
                me->remove_killer(target);
                me->start_busy(1);
        }
        else
        {
                if( random(query_temp("forcetimes", target))>2 )
                {
                        "/cmds/std/halt"->main(target);
                        if( !random(3) ) do_flee(target);
                        else target->random_move();
                       if( !mapp(query("exits", environment(target))) ) 
                               target->return_home(query("startroom",target)); 
                }
                else
                {
                        target->kill_ob(me);
                        message_vision("\n$N��м��ƲƲ�죺" + RANK_D->query_rude(me) + "������ɱ�������ͽ������\n", target);
                }
                me->start_busy(1+random(3));
        }
}

int eff_fam(object ob)
{
        switch(query("family/family_name", ob) )
        {
                case "�䵱��"   :
                case "ȫ���"   :
                case "������"   :
                case "��������" :
                case "������"   :
                case "�컨��"   :
                case "����μ�" :  return 10; break;
                case "��ü��"   :
                case "������"   :
                case "��Ĺ��"   :
                case "��ɽ��"   :  return  9; break;
                case "̩ɽ��"   :
                case "��ɽ��"   :
                case "��ɽ��"   :
                case "��ɽ��"   :  return  8; break;
                case "�����"   :
                case "����Ľ��" :
                case "�һ���"   :  return  7; break;
                case "��ң��"   :
                case "������"   :  return  6; break;
                case "����"     :
                case "ؤ��"     :  return  5; break;
                case "ѩɽ��"   :
                case "��ľ��"   :  return  4; break;
                case "�嶾��"   :
                case "����ɽ��" :  return  3; break;
                case "���ư�"   :
                case "������"   :  return  2; break;
                default:
                        if( query("attitude", ob) == "aggressive" || 
                                query("attitude", ob) == "heroism" )
                                return 6;
                        else return 3;
                        break;
        }
        return  5;
}

void do_flee(object ob)
{
        message("vision", ob->name() + "һת�۱���ʧ�ˡ�\n", environment(ob), ({ob}));

        if( mapp(query("family", ob)) && 
                member_array(query("id", ob),masters) == -1 )
        {
                switch(query("family/family_name", ob) )
                {
                case "�䵱��"   : ob->move("/d/wudang/sanqingdian"); break;
                case "ȫ���"   : ob->move("/d/quanzhen/datang1"); break;
                case "������"   : ob->move("/d/shaolin/dxbdian"); break;
                case "��������" : ob->move("/d/nanshaolin/pingtai"); break;
                case "������"   : ob->move("/d/beijing/dating"); break;
                case "�컨��"   : ob->move("/d/huijiang/zongduo"); break;
                case "����μ�" : ob->move("/d/dali/wangfugate"); break;
                case "��ü��"   : ob->move("/d/emei/hcaguangchang"); break;
                case "������"   : ob->move("/d/kunlun/qianting"); break;
                case "��Ĺ��"   : ob->move("/d/gumu/zhongting"); break;
                case "��ɽ��"   : ob->move("/d/songshan/chanyuan"); break;
                case "̩ɽ��"   : ob->move("/d/taishan/riguan"); break;
                case "��ɽ��"   : ob->move("/d/huashan/buwei3"); break;
                case "��ɽ��"   : ob->move("/d/henshan/zhurongdian"); break;
                case "��ɽ��"   : ob->move("/d/hengshan/baiyunan"); break;
                case "�����"   : ob->move("/d/qingcheng/songfengguan"); break;
                case "����Ľ��" : ob->move("/d/yanziwu/lanyue"); break;
                case "�һ���"   : ob->move("/d/taohua/dating"); break;
                case "��ң��"   : ob->move("/d/xiaoyao/qingcaop"); break;
                case "������"   : ob->move("/d/lingxiao/dadian"); break;
                case "����"     : ob->move("/d/mingjiao/square"); break;
                case "ؤ��"     : ob->move("/d/yueyang/gaibangtang"); break;
                case "ѩɽ��"   : ob->move("/d/xueshan/dadian"); break;
                case "��ľ��"   : ob->move("/d/heimuya/chengdedian"); break;
                case "�嶾��"   : ob->move("/d/wudujiao/dating"); break;
                case "����ɽ��" : ob->move("/d/baituo/dating"); break;
                case "���ư�"   : ob->move("/d/tiezhang/guangchang"); break;
                case "������"   : ob->move("/d/xingxiu/riyuedong1"); break;
                default  : 
                        ob->move(safeplaces[random(sizeof(safeplaces))]); break;
                }
        }
        else ob->move(safeplaces[random(sizeof(safeplaces))]);

        message("vision", ob->name() + "���˹�����\n", environment(ob), ({ob}));
}      

private int is_spy(object ob)
{
        if( !query("sg/spy", ob))return 0;
        return 1;
}

int do_search(string arg)
{
        string str, *option;
        object *list;
        int i, j, ppl_cnt, total;

        if( !arg || !(arg == "shenlong" || arg == "������") ||
                query("sg/exp", this_player()) < 1000 ) 
                return 0;

        if( !wizardp(this_player()) && query("jing", this_player())<30 )
                return notify_fail("��ľ���̫���ˣ�û�а취��֪������֯����ϸ���ϡ�\n");

        this_player()->receive_damage("jing", 30);
        seteuid(getuid());

        str = "�� " + MUD_NAME + "\n";
        str += "��������������������������������������������������������������������������\n";

        list = filter_array(users(), "is_spy", this_object());   
        total = sizeof(list);

        list = sort_array(list, "sort_user", this_object());
        j = sizeof(list);
        while( j-- )
        {
// Skip those users in login limbo.
                if(!environment(list[j]) ) continue;
                if(this_player() && !this_player()->visible(list[j]) ) continue;
                str = sprintf("%s%12s %s\n", str, RANK_D->query_rank(list[j]), list[j]->short(1) );
        }

        str += "��������������������������������������������������������������������������\n";
        str = sprintf("%s���� %d λ�����̳�Ա�����С�\n", str, total);

        this_player()->start_more(str);
        return 1;
}

int sort_user(object ob1, object ob2)
{
        return (int)query("sg/exp",ob2) - (int)query("sg/exp",ob1); 
}

int do_job()
{
        string job;

        if( query("sg_ok/pk", this_player()) || 
                this_player(query("sg_ok/join", )) )
        {
                write("����������һ��׷ɱ����\n");
                return 1;
        }
        if( query("sg_ok/stuff", this_player()) )
        {
                write("����������һ���Ҷ���������\n");
                return 1;
        }
        if( query("sg_ok/forcejoin", this_player()) )
        {
                write("����������һ��������̵ĵ�����\n");
                return 1;
        }
        if( !mapp(query("sgjob",this_player())) && 
                !mapp(query("sgjob_join",this_player())) ) 
        {
                write("������û�н������\n");
                return 1;
        }
        if( (job=query("sgjob/forcejoin", this_player())) )
        {
                write("�㵱ǰ�������Ǳ���" + job + "��̡�\n");
                return 1;
        }
        if( (job=query("sgjob/victim_name", this_player())) )
        {
                write("�㵱ǰ��������׷ɱ"+job+"("+query("sgjob/victim_id", this_player())+")��\n");
                return 1;
        }
        if( (job=query("sgjob/sgjob", this_player())) )
        {
                write("�㵱ǰ����������" + job + "��\n");
                return 1;
        }
        write("������û�н������\n");
        return 1;
}

int do_jobtime()
{
        int start_time, time, s, m;

        if( mapp(query("sg_ok",this_player())) ) 
                return notify_fail("���Ѿ���������ˣ������ں�ʱ�䡣\n");
        if( !(start_time=query("sgjob/assigntime", this_player())) )
        if( !(start_time=query("sgjob_join/assigntime", this_player())) )
                return notify_fail("������û�н������\n");
        time = time() - start_time;
        if( time > 1800 )
        {
                write("�Ѿ����˰�Сʱ������ȥ���������ˡ�\n");
                return 1;
        }
        s = time % 60;
        m = time / 60;
        write("���ͣ����ͣ����ͣ��Ѿ�����" + chinese_number(m) + "��" + chinese_number(s) + "��\n");
        return 1;
}