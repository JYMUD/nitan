//Cracked by Kafei
// xiaolu1.c ��ɽ����
// qfy 10/8/1997

# include <room.h>
inherit ROOM;
inherit F_SSERVER;

void create()
{
        set("short", "����");
        set("long",
"�����ڵ�ʯǽ(wall)���ɴ���ʯ���ɣ���ͷ�տյ���������Ҳû�С�\n"
"��Χ���ż������˲��ܺϱ��Ĵ��͸ף���Ӧ�ŵƻ��ȼ�ϣ��������յ���\n"
"��������\n"
);

        set ("item_desc", ([
                "wall" :
"������������˵�ʯ�ţ��þ�ȫ����ʯ��ȴ�Ʒ粻�����ƺ�ֻ�������濪\n"
"��������ϸ����ǽ���ô���Ѱ��ã��ַ�������һ����ʯǽ�Ǻ�ϸ�ܵ�ʯ\n"
"��(door)��\n",
        ])  ) ;

        set("cost", 0);
        setup();
}

void init()
{
        object me = this_player();

        if( query("huashan/yin-jue", me)<2){
                remove_call_out("close_door");
                call_out("close_door", 1, me);
        }

        add_action("do_biguan", "biguan");
        add_action("do_biguan", "�չ�");
        add_action("do_push", "push");
}

int close_door(object me)
{
        message_vision("�������ʯ���Զ������Ĺ��ϡ�\n", me);
        return 1;
}

int do_biguan(string arg)
{
        object me = this_player();
        int bili, wuxing, gengu, shenfa;
        int sum, num1, num2, num3, num4;

        if ( !arg ) return notify_fail("�㻹���ٿ�����ϼ��ҳ�ɣ�С�ı�ѹ�������˲����ź���\n");

        if ( sscanf(arg, "%d %d %d %d", bili, wuxing, gengu, shenfa) != 4  )
                return notify_fail("�㻹���ٿ�����ϼ��ҳ�ɣ�С�ı�ѹ�������˲����ź���\n");

        if( query("huashan/yin-jue", me)>1 )
                return notify_fail("���ζ�����������������ͨ�������ٱչ��ˡ�\n");

        if ( bili < 0 ) return notify_fail("����ֵ�����㣡\n");
        if ( gengu < 0 ) return notify_fail("����ֵ�����㣡\n");
        if ( shenfa < 0 ) return notify_fail("��ֵ�����㣡\n");
        if ( wuxing < 0 ) return notify_fail("����ֵ�����㣡\n");

        sum =  bili + wuxing + gengu + shenfa;

        if ( sum != 4 ) return notify_fail("���������츳ֵ���ܺ���Ϊ�ĵ㣡\n");

        message_vision("$N��ϥ���£������⣬�����ķ��������ɵش�����\n", me);
        me->start_busy(12);

        remove_call_out("stage1");
        call_out("stage1", 3, me, (int)bili, (int)wuxing, (int)gengu, (int)shenfa);

        return 1;
}

int stage1(object me, int bili, int wuxing, int gengu, int shenfa)
{
        tell_object(me, "���ã���ֻ���õ������й�ů���������ۣ�Խ��Խǿ��\n");
        tell_object(me, "�������������������֫�ٺ�������춸����澭������\n");

        remove_call_out("stage2");
        call_out("stage2", 5, me, bili, wuxing, gengu, shenfa);

        return 1;
}

int stage2(object me, int bili, int wuxing, int gengu, int shenfa)
{
        tell_object(me, "���ã���ȫ���������ȣ����û�¯����ƽ������������ת�ľ����н�����ͨ������\n");

        remove_call_out("stage3");
        call_out("stage3", 4, me, bili, wuxing, gengu, shenfa);

        return 1;
}

int stage3(object me, int bili, int wuxing, int gengu, int shenfa)
{
        object env, link_ob, obj, place;

        if ( !me->query_skill("ziyin-yin") || !me->query_skill("zhengqi-jue") || !me->query_skill("zixia-gong") ) {
                tell_object(me, "ͻȻһ����������Ŀڣ��ƺ����������ţ�������������ȴ�����Ĵζ��岻��ȥ��\n");
                tell_object(me, "������ؿ�����ľ�������鴦��������Χ��ɢ������Ҳ�ƺ��������䣡\n");
                tell_object(me, "���ſ�����ȴ��Ȼ�����������߿�����������ͷ����ը����ȫ��Ѫ���ƺ�ӿ�ں�ͷ��\n");
                message_vision("$NͻȻ���һ���Ϻ����Ѫ��������״�����ɵûӶ�˫�֣��ڵ��¼��ҷ�����\n", me);
                addn("max_neili", -300, me);
                addn("max_jingli", -300, me);
                addn("str", -1, me);
                addn("dex", -1, me);
                addn("con", -1, me);
                me->receive_wound("qi",query("max_qi", me)+100,"�����߻���ħ����");
        }
        else if ( me->query_skill("ziyin-yin", 1) < 80 || me->query_skill("zhengqi-jue", 1) < 80
        || me->query_skill("zixia-gong", 1) < 100 ) {
                tell_object(me, "ͻȻһ����������Ŀڣ��ƺ����������ţ�������������ȴ�����Ĵζ��岻��ȥ��\n");
                tell_object(me, "������ؿ�����ľ�������鴦��������Χ��ɢ������Ҳ�ƺ��������䣡\n");
                tell_object(me, "���ſ�����ȴ��Ȼ�����������߿�����������ͷ����ը����ȫ��Ѫ���ƺ�ӿ�ں�ͷ��\n");
                message_vision("$N���һ���Ϻ����Ѫ������֮�£�ֻ�õ��ڵ�������������ķ���������������\n", me);
                addn("max_neili", -150, me);
                addn("max_jingli", -150, me);
                me->receive_wound("qi",query("max_qi", me)/2,"�����߻���ħ����");
                tell_object(me, "�������ã��������Խ�ֹ�������ܶ��ˡ�\n");
                message_vision("$N˫�ֳŵأ����������������Եù��������������������鼫֮ή�ң�\n", me);
        }
        else if ( me->query_skill("ziyin-yin", 1) < 120 || me->query_skill("zhengqi-jue", 1) < 120
        || me->query_skill("zixia-gong", 1) < 150 ) {
                tell_object(me, "ͻȻһ����������Ŀڣ��ƺ����������ţ�������������ȴ�����Ĵζ��岻��ȥ��\n");
                tell_object(me, "������ؿ�����ľ�������鴦��������Χ��ɢ������Ҳ�ƺ��������䣡\n");
                tell_object(me, "����æ�������볺����������ķ�����˼������������ɢ���˵��������䵼���ڸ���\n");
        }
        else {
                place = environment(me);

                tell_object(me, "����������ʢ������Ѩ���������봩�̣�����֮����\n");
                tell_object(me, "ͻȻ�ƺ��и�����������ͥѨ��ը������������Ѩ�����̵�������ͬʱ��Ѩ����ͨ��\n");
                tell_object(me, "��ֻ��ȫ��������ʮ����ˮ���ھ��������ܣ���ͨ�ޱȣ�ʮ����̩��\n");
                addn("str", bili, me);
                addn("dex", shenfa, me);
                addn("int", wuxing, me);
                addn("con", gengu, me);
                addn("huashan/yin-jue", 1, me);
                addn("max_neili", 200, me);

                link_ob=query_temp("link_ob", me);
                obj = LOGIN_D->make_body(link_ob);
                if (!obj) return 0;

                me->save();
                exec(link_ob, me);
                destruct(me);

                obj->restore();
                LOGIN_D->enter_world(link_ob, obj, 1);

                write("���츳�����������ˣ�\n\n");
                obj->move(place);
                obj->write_prompt();

                set("neili",query("max_neili",  me), obj);
                set("jingli",query("max_jingli",  me), obj);
                set("eff_qi",query("max_qi",  me), obj);
                set("qi",query("max_qi",  me), obj);
                set("eff_jing",query("max_jing",  me), obj);
                set("jing",query("max_jing",  me), obj);
                obj->save();
        }

        return 1;
}

int do_push(string arg)
{
        object me = this_player();

        if ( !arg ) return notify_fail("���������᣿\n");

        if ( arg != "door" ) return notify_fail("�㲻���ƶ�����������\n");

        message_vision("$N˫��ƽ�죬������������ʯ�š�\n", me);

        if( query("huashan/yin-jue", me)<2){
                if( query("neili", me)<300){
                        set("neili", 0, me);
                        message_vision("$N�þ�ȫ�����۵û�������죬ʯ��ȴ��Ȼ�ֺ�������\n", me);
                        return 1;
                }

                addn("neili", -300, me);
        }

        message_vision("ʯ����$N���ƶ��·���һ����죬���������ƣ�һ��һ��Ŀ����ˡ�\n", me);

        set("exits/out", __DIR__"outmishi");
        remove_call_out("auto_close");
        call_out("auto_close", 5, this_object());

        return 1;
}

void auto_close(object room)
{
        message("vision","ʯ��ͻȻ����һ����죬�Զ��ر�������\n", room);
        delete("exits/out", room);
}