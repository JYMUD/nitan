// ��������

inherit SKILL;
string type() { return "technic"; }

int valid_learn(object me)
{
        return notify_fail("�����������㹤�ռ��ܷ������ᣬ�޷�"
                           "ͨ����ѧϰ���������\n");
}

int valid_research(object me)
{
        return notify_fail("��������������Թ��ռ����������Ϥ"
                           "���ã��޷�ͨ���о�������\n");
}