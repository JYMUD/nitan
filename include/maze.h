// maze.h

// �Թ�����ԭ���ļ�
#define ROOM_FILE       "/inherit/room/maze"

// �Թ�����ͨ��ķ���
#define ROOM_EXIT_FILE  "/d/city/wumiao"

// �Թ�������ļ�
#define BAOXIANG_OB     "/clone/misc/baoxiang"

// �Թ��ػ����̵��������
#define HEART_TIME 30           /* ����Ӽ��һ��       */

// �Թ�����������
#define MAZE_LIFT_CYCLE 1800    /* ���Сʱ             */

// �Թ��ĺ궨��
#define LENGTH  8               /* �Թ�����ķ�������   */
#define HEIGHT  8               /* �Թ�����ķ�������   */
#define BOX_NUM 4               /* �Թ����������       */
#define XIANJING_NUM 3          /* �Թ����������       */
#define NORTH   1               /* ��������             */
#define SOUTH   2               /* ���Ϸ���             */
#define WEST    3               /* ��������             */
#define EAST    4               /* ��������             */
#define IS_ROAD 1               /* ����λ��·����       */
#define IS_ROOM 2               /* ���䲻λ��·����     */
#define CAN_WALK    1           /* ָ�������г�·       */
#define IS_WALL 9               /* ָ��������ǽ��       */
#define NOT_DEFINED 0           /* ��δ��ʼ��           */
#define TO_NORTH    0           /* �Թ���������       */
#define TO_SOUTH    1           /* �Թ����ɱ�����       */
#define TO_WEST     2           /* �Թ����ɶ�����       */
#define TO_EAST     3           /* �Թ���������       */
#define MAP_COMM    1           /* �Թ���ͼ����ͨģʽ   */
#define MAP_DEEP    2           /* �Թ���ͼ����ϸģʽ   */
#define MAP_NONE    3           /* �Թ���ͼ�ǹر�ģʽ   */

// �Թ�����������
#define BUSY        1           /* �����BUSY           */
#define TRIP        2           /* �����ˤ����ķ���   */
#define LOSTMAP     3           /* ���Թ���ͼʧЧ       */
#define CHANGEMAP   4           /* ���Թ���ͼˢ��       */
#define WOUND       5           /* ���������           */

// �Թ��ı�������
#define SPECIAL_MAP 1           /* �Թ���ͼ��Ϊ��ϸģʽ */ 
#define SPECIAL_DAN 2           /* �ɵ�����Ʒ           */
#define JINKUAI     3           /* ������Ʒ           */
#define GOLD        4           /* �ƽ�                 */
#define OBJ         5           /* ������Ʒ             */
#define SPECIAL_OBJ 6           /* �õ�������Ʒ         */
#define NPC_SKILL   7           /* ����ɱ�ֵ��书       */

void collect_all_maze_information();            /* �����е��Թ���������     */
void init_line(mapping maze);                   /* ��ʼ���Թ���ͼ           */
void init_road(object room, mapping maze);      /* ��ʼ���Թ�·��           */
void init_wall(object room, mapping maze);      /* ��·���ϵķ��������·   */
object *finish_room(object room, mapping maze); /* �������ķ����ͨ         */
void init_room_exits(mapping maze);             /* ������ĳ���ˢ��         */
void init_special_room(mapping maze);           /* ���Թ���ʼ�����������   */
