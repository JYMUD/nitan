//ryu, 11/17/96. 

inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}

void create()
{
        set_name("�����ɲ�޾�", ({ "shu", "book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 400);
                set("material", "paper");

        }
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        mapping skill;
        int pxlevel; 
        int neili_lost;

        if (!(arg== "book" || arg== "shu"))
        return 0;

        if( query("pigging", where)){
                write("�㻹��ר�Ĺ���ɣ�\n");
                return 1;
        }
        if (me->is_busy()) {
                write("��������æ���ء�\n");
                return 1;
        }

        if( me->is_fighting() ) {
                write("���޷���ս����ר�������ж���֪��\n");
                return 1;
        }

        if (!id(arg)) { 
                write("��Ҫ��ʲô��\n");
                return 1;
        }
        if( !me->query_skill("literate", 1) ){
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;
        }

if( query("family/family_name", me) != "ѩɽ��"
         && query("family/family_name", me) != "Ѫ����"
         || query("class", me) != "bonze" )
                return notify_fail("��δ����ţ���Ե���ϣ��޷��޳������񷨡�\n");

        message("vision", me->name() + "��ϸ���ж��������ɲ�޾�����\n", environment(me), me);
        if( query("jing", me)<15){
                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                return 1;
        }

        if ( me->query_skill("necromancy", 1) > 200) neili_lost = 20;
             else if ( me->query_skill("necromancy", 1) > 100) neili_lost = 10;
             else neili_lost = 5;


        if( query("neili", me)<neili_lost){
                write("������������\n");
                return 1;
        }

            if ((!objectp(ob = present("kulou guan", me)) ) ||
               (!query("equipped", ob))){
                write("�����ͷ�Ϸ·����˵�ʲ�ᣬ����ͷ���ۻ���\n");
                return 1;
        }
            if ((!objectp(ob = present("rentou lian", me)) ) ||
               (!query("equipped", ob))){
                write("��������Ϸ·����˵�ʲ�ᣬ����ͷ���ۻ���\n");
                return 1;
        }
            if ((!objectp(ob = present("lubo", me)) ) ||
               (!query("equipped", ob))){
                write("��������з·����˵�ʲ�ᣬ����ͷ���ۻ���\n");
                return 1;
        }
        if(me->query_skill("lamaism", 1) < 30){
                write("���ж���һ��������Ƿ���������˵�Ķ������̫����ˡ�\n");
                return 1;
        }
        if( me->query_skill("necromancy", 1) > 300){
                write("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
                return 1;
        }
        if ( me->query_skill("necromancy", 1) >= me->query_skill("lamaism", 1)){ 
                write("��������ķ���Ϊ����������ô��Ҳû�ã�\n");
                return 1;
        }
        me->receive_damage("jing", 40);
        set("neili",query("neili",  me)-neili_lost, me);
        if( !me->query_skill("necromancy", 1) ) {
                me->set_skill("necromancy", 0);
        }
        me->improve_skill("necromancy", (int)me->query_skill("literate", 1)/3+1);
        write("���ж��������ɲ�޾����������ĵá�\n");
        return 1;
}

