// book.c

inherit ITEM;

int is_book() { return 1; }

string extra_long()
{
        string str;
        
        str  = sprintf("\n��Ʒ���� : �鱾<�ؼ�>������%s��ʧ\n", 
                       (this_object()->query_autoload() || query("autoload")) ? "��" : "" );
        str += sprintf("�������� : %s\n", to_chinese(query("skill/name")));
        str += sprintf("����Ҫ�� : %d\n", query("skill/exp_required"));
        str += sprintf("��ϰ�Ѷ� : %d\n", query("skill/difficulty"));
        str += sprintf("��ϰҪ�� : %s %d ��\n", to_chinese(query("skill/name")), query("skill/min_skill"));
        str += sprintf("��ϰ���� : %d ��\n", query("skill/max_skill"));
        str += sprintf("�������� : %d ��/��\n", query("skill/jing_cost"));
        // str += sprintf("��ϰ���� : ����ָ�� du %s �ж���\n", query("id"));
        
        return str;
}
