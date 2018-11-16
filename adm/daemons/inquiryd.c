#include <ansi.h>

int parse_inquiry(object me, object ob, string topic)
{
        switch (topic)
        {
        case "name":
                message_vision(CYN "$N" CYN "��$n" CYN "�ʵ�������" +
                               RANK_D->query_respect(ob) + "���մ�"
                               "����\n" NOR, me, ob);
                return 1;

        case "here":
                message_vision(CYN "$N" CYN "��$n" CYN "�ʵ�����λ" +
                               RANK_D->query_respect(ob) + "��" +
                               RANK_D->query_self(me) + "�����󱦵�"
                               "����֪������Щʲ��������飿\n" NOR,
                               me, ob);
                return 1;
        
        case "all":
                message_vision(CYN "$N" CYN "��$n" CYN "�ʵ�����λ" + 
                               RANK_D->query_respect(ob) + 
                               "���㶼֪��Щʲô����ѽ��\n" NOR, 
                               me, ob);
                return 1;
                        
        case "clue":
        case "����":
                message_vision(CYN "$N" CYN "��$n" CYN "��������" +
                               RANK_D->query_self(me) + "�����˴���"
                               "֪" + RANK_D->query_respect(ob) +
                               "��Щ�������ܷ��֪���£�\n" NOR, me, ob);
                return 1;

        case "rumor":
        case "rumors":
        case "��Ϣ":
                message_vision(CYN "$N" CYN "��$n" CYN "�ʵ�����λ" +
                               RANK_D->query_respect(ob) + "����֪"
                               "�����û����˵ʲô��Ϣ��\n" NOR, me,
                               ob);
                return 1;

        case "marry":
                message_vision(CYN "$N����һ˫���ۣ������������$n"+ 
                               CYN"�ʵ���������λ"+RANK_D->query_respect(ob) +
                               "�Ƿ���䣿\n" NOR,me,ob);
                return 1;
        
        case "food":
                message_vision(CYN "$N�����������$n"+CYN"�ʵ�������֪��λ"+
                               RANK_D->query_respect(ob) +
                               "�Ƿ��ܸ��ҵ�Ե�, �����Ѿ�����û�н�ʳ�ˣ���\n" NOR,
                               me,ob);
                return 1;
        
        case "water":
                message_vision(CYN "$N�����������$n"+CYN"�ʵ�������֪��λ"+
                               RANK_D->query_respect(ob) +
                               "�Ƿ��ܸ��ҵ�ȵ�, ���¿ڿʵúܣ���\n" NOR,
                               me,ob);
                return 1;
        
        case "money":
                message_vision(CYN "$N˫�ֱ�ȭ��$n"+CYN"�ʵ��������³���զ�������߽���ȱ��Щ�̲�,��λ"+
                               RANK_D->query_respect(ob) +
                               "�Ƿ���ʩ��һ��, ���²����м�����\n" NOR,
                               me,ob);
                return 1;
                
        case "friend":
                message_vision(CYN "$N˫�ֱ�ȭ��$n"+CYN"˵�������ĺ�֮�ڽ��ֵ�Ҳ,��λ"+
                               RANK_D->query_respect(ob) +
                               ",��֪Ը�������½������ѡ�\n" NOR,
                               me,ob);
                return 1;
                
        default:
                return 0;
        }
}