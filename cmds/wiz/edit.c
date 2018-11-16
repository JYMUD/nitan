// edit.c

#include <ansi.h>
inherit F_CLEAN_UP;

string string_name()
{
        return HIM "�༭��(Edit)";
}

int main(object me, string file)
{
        string dir;
        
        if (! SECURITY_D->valid_grant(me, "(apprentice)"))
                return 0;

        if (! file) return notify_fail("ָ���ʽ��edit <����>\n");
                
        if (in_edit(me)) return notify_fail("���Ѿ���ʹ�ñ༭���ˡ�\n");

        file = resolve_path(query("cwd", me), file);

        if (! me->is_admin()) 
        {
                dir = SECURITY_D->query_site_privilege("edit");
                if( !dir && !sscanf(file, "/u/%*s") )
                        return notify_fail("��ֻ�������Լ���Ŀ¼�±༭��\n");
                        
                if( dir != "all" && !sscanf(file, "/%s/%*s", dir) )
                        return notify_fail("��ֻ�������Լ�Ŀ¼�Լ���" + dir + "Ŀ¼�±༭��\n");
        }
        
        foreach (object user in users())
        if (file == in_edit(user))
                return notify_fail(HIM "�����ͻ��" + user->name(1) + HIM "(" +
                        capitalize(query("id", user)) + ")" +
                        HIM "���ڱ༭���ļ�(" + file + ")��\n" NOR);

        printf("�༭�ļ���%s\n", file);
        CHANNEL_D->channel_broadcast("sys",
                sprintf("%s(%s)���ڱ༭�ļ�(%s)��",
                me->name(1),
                capitalize(query("id", me)),
                file));

        seteuid(geteuid(me));
        set("cwf", file, me);
        SECURITY_D->backup_file(file);
        ed(file);

        log_file("static/edit", sprintf("%s %-9s edit %s from %s.\n",
                                        log_time(),
                                        geteuid(me), file,
                                        query_ip_name(me)));
        return 1;
}
int help(object me)
{
        write(@HELP
ָ���ʽ : edit <����>, edit here
���ô�һָ���ֱ�������ϱ༭������
                /��ǰ����ƥ����
                ?�������ƥ����
                =��ʾ��ǰ��������
                a�ڵ�ǰ�еĺ������
                A��'a'����
                c�޸ĵ�ǰ�У��滻��ѯ�ı�
                dɾ��һ�л����
                e����һ���ļ����ǵ�ǰ�ļ�
                E��'e'���ƣ���ֻ���ļ������޸�֮����Ч
                f��ʾ/�ı䵱ǰ�ļ����ļ���
                g��������ƥ�����ִ��ĳ������
                h����
                i�ڵ�ǰ��ǰ�����ַ�
                k��һ���ַ���ǵ�ǰ��
                l�г�һ�л���У��������ַ���
                m�ƶ�һ�л���е�ָ����λ�ã��кţ�
                n����к�
                Oͬ'i'
                oͬ 'a'
                p�г�һ����Χ����
                q�˳�
                Q�˳������Ҳ���
                r���ļ�β����ָ���к���������ļ�
                s�������滻
                set��ѯ���ı��洢ĳ���趨ѡ��
                t����һ�л��е�ָ������
                v�������Բ�ƥ�����ִ��ĳ������
                x���ļ����˳�
                wд�뵱ǰ�ļ�����ָ���ļ������ø���
                W��'w'���ƣ�����׷��
                z��ʾ20�У����� . + - ���ֱ��
                Z��ʾ40�У����� . + - ���ֱ��

HELP
        );
        return 1;
}
