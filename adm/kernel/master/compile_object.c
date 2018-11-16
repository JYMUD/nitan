// This program is a part of NT MudLIB

// compile_object: This is used for loading MudOS "virtual" objects.
// It should return the object the mudlib wishes to associate with the
// filename named by 'file'.  It should return 0 if no object is to be
// associated.
/*
���ƣ�
        compile_object - �ṩ������� (virtual object) ���ܵ� mudlib ���档
�﷨��
        object compile_object( string pathname );

        ��� compile_object( �ִ� ·���� );
�÷���
        �� mudlib ָʾ������ʽ����һ���������ڼ������еĵ�����������ʽ���
        �� compile_object ��ʽ��������˵����� mudlib ����
        call_other("/obj/file.r", "some_function") �� new("/obj/file.r") ʱ
        ����������û�н��� /obj/file.r.c �Ķ�����������ʽ�ͺ����������
         (master object) �� compile_object("/obj/file.r")����� mudlib ��ϣ
        ������ (associate) /obj/file.r ������compile_object() ������ 0����
        �� mudlib Ը�⣬��Ҫ���� /obj/file.r ���������� compile_object()
        ����һ���������ƺ����֮�󣬶�������ʽ���ԣ�����ͬ��Ϸ�д���
        file.r.c �������������������ʱ�����ľ��� compile_object() ���ص�
        �����
���ߣ�
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
���룺
        spock@muds.net          2000.May.20.    v22 ��
*/

varargs mixed compile_object(string file, int cloning)
{
        object daemon;

        if( daemon = find_object(VIRTUAL_D) )
                return daemon->compile_object(file, cloning);
        else
                return 0;
}