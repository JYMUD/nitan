// ��ѧ����

inherit SKILL;
string type() { return "knowledge"; }

int valid_learn(object me)
{
        return notify_fail("��ѧ���������Ļ��������ᣬ�޷�"
                           "ͨ����ѧϰ���������\n");
}

int valid_research(object me)
{
        return notify_fail("��ѧ������������Ļ�����ļ�ȡ��"
                           "�գ��޷�ͨ���о�������\n");
}