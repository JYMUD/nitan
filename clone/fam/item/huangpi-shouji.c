
#include <ansi.h>

inherit ITEM;

mixed check_title(string arg)
{
    arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);

        if (strlen(filter_color(arg)) > 30 || strlen(arg) > 100)
                return notify_fail("������̫���ˣ�Ϊ�˽�Լ��Դ�����������趨��\n");

    return arg + NOR;
}

void create()
{
        set_name(NOR + YEL "����Ƥ�ּǡ�" NOR, ({ "huangpi shouji" }) );
        set_weight(100);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "����һ�����Ƶ�Ƥ���ӣ��������������޸�����ͷ�ε��ؾ���\n"
                                                "ʹ�ú���޸�����ͷ�Σ�TITLE����ָ�retitle ͷ�� ���ɡ�\n" 
                                                                "���߶�ʧ:��\n" 
                                                        "��ɫ���壬������������ͷ���м���ָ����ɫ��\n"
                                                                "$BLK$ - ��ɫ      $NOR$ - �ָ�������ɫ\n"
                                                                "$RED$ - ��ɫ      $HIR$ - ����ɫ\n"
                                                                "$GRN$ - ��ɫ      $HIG$ - ����ɫ\n"
                                                                "$YEL$ - ����ɫ    $HIY$ - ��ɫ\n"
                                                                "$BLU$ - ����ɫ    $HIB$ - ��ɫ\n"
                                                                "$MAG$ - ǳ��ɫ    $HIM$ - �ۺ�ɫ\n"
                                                                "$CYN$ - ����ɫ    $HIC$ - ����ɫ\n"
                                                                "$WHT$ - ǳ��ɫ    $HIW$ - ��ɫ������ɫ��\n\n"
                                                                "����ϵͳ�Ĳ�ͬ��������ɫ������һ��ƫ�\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                        set("unit", "��");
        }

        setup();
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_retitle", "retitle");
        }
}

int do_retitle(string arg)
{
                object me;

                me = this_player();

                if (! arg)return notify_fail("ָ���ʽ: retitle ͷ��\n");

        if (! stringp(arg = check_title(arg)))return 1;

                me->set("title", arg);

                me->save();

                write(HIG "�޸�ͷ�γɹ��������ڵĽ����ƺ��ǣ�" + arg + "��\n" NOR);

                destruct(this_object());

                return 1;
}

int query_autoload()
{
         return 1;
}
