//rama@sz
//�׽��ƪ

inherit BOOK;

int do_xiulian();
int finish(object me);

void setup()
{}
void init()
{
        add_action("do_xiulian", "xiulian");
        add_action("do_xiulian", "xiu");
}

void create()
{
        set_name("�׽��ƪ", ({ "yijinjing" }));
        set_weight(600);
              set("no_drop",1);
              set("no_get",1);
              set("no_steal",1);
        if( clonep() )
        set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", "����һ�����ľ��飬ÿһҳ�϶�д�������������֣�ûһ��ʶ�á�\n");
                set("value", 5000);
                set("material", "paper");
                
        }
}

int do_xiulian()
{
        object me,ob;
        object where_1;
        int poison_lvl;
        me=this_player();
        if(!me->query_skill("poison",1))
        return notify_fail("���������Ķ��������ᣬ����������ô����ļ��ɣ�\n");
         
        poison_lvl = me->query_skill("poison",1);
               
        where_1 = environment(me);

        if (!present("yijinjing", me))
                return 0;
                
        if( me->is_busy() )
             return notify_fail("����æ���أ�\n");       
        if( query("pigging", where_1) )
                return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

        if( query("sleep_room", where_1) )
                return notify_fail("������˯�������������Ӱ�����ˡ�\n");

        if( query("no_fight", where_1) )
                return notify_fail("����������ã������ұ𴦰ɣ�\n");

        if( query("name", where_1) == "����" )
                return notify_fail("����̫����, �������߻���ħ. \n");

        if( me->is_busy() || query_temp("pending/exercising", me) )
        if( me->is_fighting() )
                return notify_fail("ս���в������������߻���ħ��\n");

        if( query_temp("is_riding", me) )
                return notify_fail("�����������������߻���ħ��\n");

        if( query("canewhua", me) == 1 )
                return notify_fail("���޷��ٴ��Ȿ����ѧ���κ��¶����ˡ�\n");

        if( !stringp(me->query_skill_mapped("force")) || me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("��������� enable �����󷨡�\n");

        if (poison_lvl < 250) 
                return notify_fail("��һҳ�����һЩ�ö����ɣ�����ôҲ���Բ��ˣ�������Ķ������д���ǿ��");
        
        if(present("yijinjing",me) && !present("shenmuwang ding",me))
        {
                write("�㿪ʼ���ն��������Ķ�������������Ϣ������\n");
                if(random(4)==1){
                        write("û����ľ�����İ�����������޷�����ס�Լ���������ֻ�������ں��ֱײ������Щ���ǲ����ˣ�\n");
                        write("���۵��³�һ����Ѫ����ֻ������ʶ����������ʧ��\n");
                        set_temp("die_reason", "�����׽�б⣬�߻���ħ����", me);
                        me->receive_damage("qi",query("eff_qi", me)+200);
                        return 1;
                }
                else
                me->start_busy(30);
                call_out("finish",60);
                return 1;
        }

        ob=present("shenmuwang ding",me);
        if( query("fake", ob) || query("item_make", ob) )
        {
                return notify_fail("�����˰��죬��ľ����û�а�㶯���������Ǹ��ٻ���\n");
        }

        write("�㿪ʼ�����׽������ص�����������ʼ��Ϣ������\n");
        write("��ľ����Ҳð�������������̣�һ�ж���������ú�г���ˣ��������������������ҵĴ��ڡ�\n");
        if( random((200/query("int", me)))>3 )
        {
                write("��Ȼ���������������Щ���ң������ĸ��ط������ˣ�\n");
                write("���۵��³�һ����Ѫ����ֻ������ʶ����������ʧ��\n");
                me->receive_damage("jing",30);
                me->receive_damage("qi",100);
                me->start_busy(30);
                return 1;
        }
        else
        {
                 me->start_busy(30);
                call_out("finish",60);
        }
        return 1;
}

int finish(object me)
{
        me=this_player();
        write("��ֻ���û��������泩�ޱȣ����ɰ���̾�������治�����׽����\n");
        me->clear_condition("bingcan_poison",5);
        if( query("yijinjing", me)<1 )
        {
                set("yijinjing", 1, me);
        }
        addn("yijinjing", 1, me);
        if( query("yijinjing", me) >= 10 )
        {
                write("����̨��ȻһƬ���ʣ�������������һɨ���գ���������˻�����������������ڣ�\n");
                delete("yijinjing", me);
                set("canewhua", 1, me);
                set("huagong_hua", 1, me);
                me->clear_condition("bingcan_poison");
                return 1;
                //ѧ��yun hua
         }
         return 1;
}
