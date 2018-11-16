#include <ansi.h> 

nosave string char_id; 
nosave string char_name;

object select_character();
int    give_gift(); 

nosave mixed *story = ({ 
        "�ܾã�", 
        "�ܾã�", 
        "�ܾã�", 
        "��ǰ��", 
        "ĳ��������һλŮ�ӣ�һ�����顣", 
        "ĳ�ˣ���˪������Ϊ�˰��㣬�������Ҵ��������ҲԸ�⡣������", 
        "����������ĳ�˱��ؽ����η���", 
        "ĳ�ˣ����������ﲻҪ���������书�Ժ�����֪������ô�죿��ô�Ե���÷����������", 
        "ĳ�ˣ�����������˭������Ե�ɡ�", 
        "����������ʲô�ƶ�������Ȼ���ҵ��ҵ�ͷ����$N��������һ������ģ���������ˡ�",
        (: give_gift :), 
 }); 

void create() 
{ 
        seteuid(getuid()); 
        if (! objectp(select_character())) 
        {
                destruct(this_object()); 
                return;
        }
}

object select_character() 
{ 
        object *obs; 
        object ob; 

        obs = filter_array(all_interactive(), (: ! wizardp($1) && 
                                                 living($1) && 
                                                 $1->query_skill("shenzhaojing", 1) < 1 && 
                                                 SKILL_D("shenzhaojing")->valid_learn($1) && 
                                                  !query("doing", $1):));
        if (! sizeof(obs)) 
                return 0; 

        ob = obs[random(sizeof(obs))]; 
        char_id=query("id", ob);
        char_name = ob->name(1);
        return ob;
}

mixed query_story_message(int step) 
{ 
        mixed msg; 

        if (step >= sizeof(story)) 
                return 0; 

        msg = story[step]; 
        if (stringp(msg)) 
        {
                msg = replace_string(msg, "$N", char_name); 
                msg = replace_string(msg, "$ID", char_id); 
        }
        return msg; 
}

int give_gift() 
{
        STORY_D->remove_story("shenzhaojing"); 
        STORY_D->give_gift("/clone/book/shenzhaojing", 1,
                           HIM "\n��ž����һ��һ�����������ǰ��\n\n" NOR); 
        return 1;
} 
