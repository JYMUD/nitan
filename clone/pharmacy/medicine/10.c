#include <ansi.h>

inherit MEDICINE;

void create()
{
        set_name(RED"��ȸ��"NOR, ({"zhuque dan", "dan"}));
        set("unit", "��");

        set("upgrade_stat", ([ "kee" : 20,
                               "sen" : 20 ]));
        set("apply_condition", ([ "drunk" : 20 ]));
        set("env_message", RED"$Nȡ��һ�ź�ɫ�����ӣ�һ��ͷ������ȥ����ʱ��ɫ��ú��");
        set("prv_message", HIR"����ø��ں����л����գ�һ������˳��Ѫ�л������澭������");

        setup();
}
