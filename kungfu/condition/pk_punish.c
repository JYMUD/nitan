int dispel() { return 0; }

int update_condition(object me, int duration)
{
        if (duration < 1)
        {
                tell_object(me, "�������ϣ������뿪�ˣ�\n");
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "��Ϊ" + me->name(1) + "���Ļڹ�������������ˡ�");
                return 0;
        }
        me->apply_condition("pk_punish", duration - 1);
        return 1;
}
