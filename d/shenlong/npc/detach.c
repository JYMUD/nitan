// detach.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob, old_app;
        mapping family, skills;
        int i;
        string *skname;

	return  notify_fail("脱离师门请使用指令 tuoli 或 tuoli2 即可！\n");
	
        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if (! arg)
                return notify_fail("指令格式：detach|tuoli [cancel]|<对象>\n");

        if (arg == "cancel")
	{
                old_app=query_temp("pending/deatch", me);
                if( !objectp(old_app) )
                        return notify_fail("你现在并没有脱离你的师傅的想法。\n");
                write("你改变主意不想脱离师门了。\n");
                tell_object(old_app, me->name() + "改变主意不想脱离师门了。\n");
                delete_temp("pending/detach", me);
                delete_temp("pending/want", me);
                return 1;
        }

        if( !query_temp("pending/want", me) )
        {
                tell_object(me, HIR "\n请注意，一但你脱离师门，将会被废除掉所有"
                                "的特殊武功。\n" NOR + HIC "如果你下了决心，就"
                                "再输入一次这条命令。\n" NOR);
                set_temp("pending/want", 1, me);
                return 1;
        }

        if (! (ob = present(arg, environment(me))) ||
            ! ob->is_character())
        {
                delete_temp("pending/want", me);
                write("你想和谁断绝师徒关系？\n");
                return 1;
        }

        if (ob == me)
        {
                delete_temp("pending/want", me);
                write("你想和自己断绝师徒关系？\n");
                return 1;
        }

        if (! living(ob))
        {
                delete_temp("pending/want", me);
                write("你必须先把" + ob->name() + "弄醒。\n");
                return 1;
        }

        message_vision(CYN "\n$N" CYN "向$n" CYN "磕了一个头，说道：师"
                       "父！我…我想脱离师门。\n" NOR, me, ob);

        if (! me->is_apprentice_of(ob))
	{
                if( query("family/family_name", ob) == query("family/family_name", me) )
                {
                        delete_temp("pending/want", me);
                        message_vision(CYN "$N" CYN "大吃一惊，对$n" CYN "道：什"
                                       "…什么？你要脱离师门？这事可得找你师傅去"
                                       "。\n" NOR, ob, me);
                        return 1;
                } else
		{
                        delete_temp("pending/want", me);
                        message_vision(CYN "$N" CYN "看了看跪在地上的$n" CYN "，"
                                       "冷笑一声，道：我又不是你师傅，找我做甚？"
                                       "\n" NOR, ob, me);
                        return 1;
		}
        }

        set_temp("pending/detach", 1, me);
        tell_object(ob, me->name() + "想脱离师门。\n");
        ob->attempt_detach(me);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : detach|tuoli [cancel]|<对象>
 
这个指令能让你向你的师傅请求脱离师门，因为一般的大门派不愿意接
收判师的人，所以如果你想改投其他门派，最好按照规矩脱离师门，然
而一旦脱离师门，师傅将追回你所有学到的本门秘学，并追回部分其他
武功，知识不会受到任何影响。

请参考相关指令 expell
HELP );
        return 1;
}