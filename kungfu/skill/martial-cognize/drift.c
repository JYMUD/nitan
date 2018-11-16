// drift.c
// Modified by Dumbness, 2003-5-25 13:24

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int i;
        object *inv;
        string *can_perform;

        // ???������ʲô��˼
        can_perform=query("can_perform/martial-cognize", me);
        set("test", can_perform, me);

        if(!arrayp(can_perform) || 
                !sizeof(can_perform) || 
                member_array("drift",can_perform) == -1)
                return notify_fail("�㻹û��ѧ��ʹ������֮��\n");

        if( me->is_fighting() )
                return notify_fail("ս�����޷�ʹ������֮��\n");

        if(me->is_busy())
                return notify_fail("����һ��������û����ɣ��޷�ʹ������֮��\n");
        
        //By Dumbness, ������no_drift���Եķ����ֹ������ɳ�
        if( query("no_drift", environment(me)) )
                return notify_fail("�����ֹʹ������֮��\n");

        if( query("jing", me)<300 )
                return notify_fail("��ľ��񲻺ã�\n");

        if( query("jingli", me)<500 )
              return notify_fail("��ľ���������\n");
 
        if( query("max_jingli", me) <= 1000 )
              return notify_fail("��ľ�����û�дﵽ�����Σ�\n");

        if( me->is_ghost())
                return notify_fail("����޷�ʹ������֮��\n");

        if( me->in_prison())
                return notify_fail("�������޷�ʹ������֮��\n");

        if( query("trds", environment(me)) )
                return notify_fail("���˳����޷�ʹ������֮��\n");     
        
        if((int) me->query_skill("martial-cognize",1) < 300)
                return notify_fail("�����ѧ�����������\n");

        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! userp(inv[i]) && ! inv[i]->is_muxiang()) continue;
                if (userp(inv[i]))
                        return notify_fail("�㱳����˭����һ������˻���ô�ɣ�\n");
                if (inv[i]->is_muxiang())
                        return notify_fail("���ֲ��Ƿɻ���������ô��һ��ľ�䣬�ܷɵö�ô��\n");
        }

        inv = 0;
        write("��Ҫ�ƶ�����һ������ߣ�");
        input_to( (: call_other, __FILE__, "select_target", me :));
        return 1;
}

void select_target(object me, string name)
{
        object ob;
        int effect;

        if( !name || name=="" ) {
                write("��ֹʹ������֮��\n");
                return;
        }

        ob = find_player(name);
        if( !ob || !me->visible(ob) || wizardp(ob) )
                ob = find_living(name);

        //by rama �����˿���ͨ���ε��Ĵ���drift����������get��Ʒ��bug
        if( !ob || 
            !living(ob) || 
            !me->visible(ob) || 
            wizardp(ob) || 
            !environment(ob) || 
            !query("max_jingli", ob) || 
            (strsrch(base_name(ob), "/kungfu/class/generate/") == 0 ) ||
            !query("jingli", ob)){
                write("���޷����ܵ�����˵Ĵ��� ....\n");
                write("��Ҫ�ƶ�����һ������ߣ�");
                input_to( (: call_other, __FILE__, "select_target", me :));
                return;
        }

        if( environment(ob) == environment(me)) {
                write(ob->name() + "��������������� ....\n");
                return;
        }

        //By Dumbness, ������no_drift���Եķ����ֹ������ɳ�
        if( query("no_drift", environment(me)) )
        {
                write("�����ֹʹ��̫��֮��\n");
                return;
        }

        if( me->is_fighting() ) {
                write("ս�����޷�ʹ������֮��\n");
                return;
        }else if( query("jingli", me)<100){
                write("��ľ���������\n");
                return;
        }else if( query("jing", me)<300){
                write("��ľ��񲻺�! \n");
                return;
        } else if( me->is_ghost()) {
                write("��겻��ʹ������֮��\n");
                return;
        } else if( me->in_prison()) {
                write("�����ﲻ��ʹ������֮��\n");
                return;
        }else if( query("trds", environment(me))){
                write("���˳��ﲻ��ʹ������֮��\n");
                return;
        }

        effect = random(200);
        addn("jingli", -(100+effect), me);
        me->receive_damage("jing", 100+effect);
        
        if( query("max_jingli", ob)<500){
                write("����ܵ��˶Է��Ĵ��ڣ����ǲ��ܾ�ȷ��λ��\n");
                return;
        }

        //By Dumbness, ������no_drift���Եķ����ֹʹ������֮�����
        if( query("no_drift", environment(ob)) || query("no_fight", environment(ob)) )
        {
                write("����Ҫȥ�ĵط�������������֮��\n");
                return;
        }

        // һЩ�ر����������ʹ������֮��
        if( query("trds", environment(ob)) || 
            strsrch(base_name(environment(ob)),"/data/room/") != -1 ||
            strsrch(base_name(environment(ob)),"/u/") != -1 ||
            strsrch(base_name(environment(ob)),"/d/xiakedao/") != -1 ||
            strsrch(base_name(environment(ob)),"/d/tulong/") != -1 ) {
                write("����Ҫȥ�ĵط�������������֮��\n");
                return;
        }

        message_vision( HIY "$Nһ��Х����������һ���ɫ�������ں󱳻�ۣ��γ�һ�Խ�ɫ����ƺ�Ҫ���߷� ....\n" NOR, me);

        //if( random(ob->query("max_jingli")) > me->query("max_jingli")) {
        //Modified by Dumbness for use effect jingli as conform condition
        if( random(query("max_jingli", ob))>(query("max_jingli", me)>query("eff_jingli", me)?query("max_jingli", me):query("eff_jingli", me))){
                write("����Ϊ����������ʧ���ˡ�\n");
                return;
        }

        /* Sigh, ʧ�ܡ�����Ŀǰ�����Ѿ���һ�����С��ȶ�����MUD������������ϵ�ʧ�ܣ�Ҳ�Ѿ�����
        �ӱ�����������Ч�Ŀ��ƣ�������۲��ο�һЩ�������������֮��ؿ��Ƴ�����������ȡ����
        ԭ��ܴ�̶���Դ����ҵ�ϰ����˼ά��ʽ���Ѹı䡣�������������йؽ���������빹˼Ҳһ��
        ȡ��������ʦ���ٶԴ����κγ��ԡ�
        //Added by Dumbness for contract with level of skill which named 'martial-cognize'
        if( (random(( (int) me->query_skill("martial-cognize",1)-250)) > 50) 
                 && (query_temp("drift_fail_times", me)<4)){
                addn_temp("drift_fail_times", 1, me);
                write("����Ϊ����������ʧ���ˡ�\n");
                return;
        }
        delete_temp("drift_fail_times", me);
        */
        
        message( "vision", HIY "\n" + me->name() + "����չ��˫�ۣ�����Ľ�ɫ�������ľ���һ��ů��"
                + "��ֻ��" + me->name() + "�������գ�˲����ʧ����Ӱ���٣�\n\n" NOR, environment(me), ({ me }) );
        me->move(environment(ob));
        message( "vision", HIY "\nһ��΢�紵����" + me->name() + "��������㻺����������ɫ�ĳ���â���䡣\n\n" NOR,
                environment(ob), ({ me }) );
}
