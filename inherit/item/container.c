// container.c

inherit ITEM;

int is_container() { return 1; }

string extra_long()
{
        string str;

        str  = sprintf("\n��Ʒ���� : ����������%s��ʧ\n", 
                       (this_object()->query_autoload() || query("autoload")) ? "��" : "" );      
        str += sprintf("��    �� : %d\n", this_object()->query_max_encumbrance());
        str += sprintf("��    �� : %s\n", this_object()->no_limit_amount() ? "��" : "��");
        //str += sprintf("ʹ�÷��� : ����ָ�� put <id> in %s ���롣\n", query("id"));
        //str += sprintf("                  ����ָ�� get <id> from %s ȡ����\n", query("id"));

        return str;
}
