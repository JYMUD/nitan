// quest.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        mapping to_kill, to_find;
        mapping killed, finded;
        array tk, tf;
        string msg;
        int i, n;

        ob = FUBEN_D->query_maze_mainobj(me);

        if (! ob) return notify_fail("�㵱ǰ�ص�û�п�����ʾ�ĸ�������\n");

        if( !query("quest/quest_name", ob) )
                return notify_fail("��Ŀǰ��û����ȡ�κθ�������\n");

        to_kill=query("quest/to_kill", ob);
        killed=query("quest/killed", ob);
        to_find=query("quest/to_find", ob);
        finded=query("quest/finded", ob);

        write("��������: "+query("quest/quest_name", ob)+"\n");
        write("��������: "+query("quest/quest_desc", ob)+"\n");
        if (mapp(to_kill) && sizeof(to_kill))
        {
                write("ɱ���������: \n");
                msg = "";
                tk = keys(to_kill);
                for (i=0;i<sizeof(tk);i++)
                {
                        if (sizeof(killed) && !undefinedp(killed[tk[i]]))
                                n = killed[tk[i]];
                        else n = 0;
                        msg += tk[i] + ": " + n + "/" + to_kill[tk[i]] + "\n";
                }
                write(msg);
        }
        if (mapp(to_find) && sizeof(to_find))
        {
                write("Ѱ���������: \n");
                msg = "";
                tf = keys(to_find);
                for (i=0;i<sizeof(tf);i++)
                {
                        if (sizeof(finded) && !undefinedp(finded[tf[i]]))
                                n = finded[tf[i]];
                        else n = 0;
                        msg += tf[i] + ": " + n + "/" + to_find[tf[i]] + "\n";
                }
                write(msg);
        }
        if (n = ob->query_remove_time()-time())
                 write("��������"+CHINESE_D->chinese_period(n)+"����ʧ��\n");

        return 1;
}
