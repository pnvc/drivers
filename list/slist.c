#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>

#define SLIST "slist"
#define SLISTM "slist: "

struct ls {
	char name[25];
	struct list_head list;
	int a;
	unsigned long b;
	char c;
};

static int __init slist_init(void)
{
	struct list_head ls_list;
	INIT_LIST_HEAD(&ls_list);

	struct ls ls0 = {.name="ls0",.a=10,.b=0xffffffffff,.c=0x30};
	struct ls ls1 = {.name="ls1",.a=11,.b=0xfffffffff0,.c=0x31};
	struct ls ls2 = {.name="ls2",.a=12,.b=0xffffffff0f,.c=0x32};
	struct ls ls3 = {.name="ls3",.a=13,.b=0xfffffff0ff,.c=0x33};
	struct ls ls4 = {.name="ls4",.a=14,.b=0xffffff0fff,.c=0x34};

	list_add_tail(&ls0.list, &ls_list);
	list_add_tail(&ls1.list, &ls_list);
	list_add_tail(&ls2.list, &ls_list);
	list_add_tail(&ls3.list, &ls_list);
	list_add_tail(&ls4.list, &ls_list);

	if (!list_empty(&ls_list)) {
		struct list_head *tmp_list;
		list_for_each(tmp_list, &ls_list) {
			struct ls *tmp_ls;
			tmp_ls = list_entry(tmp_list, struct ls, list);
			pr_info("slist: %s, %d, %lx, %c\n", tmp_ls->name,
					tmp_ls->a, tmp_ls->b, tmp_ls->c);

		}

		struct ls *tmp_ls;
		list_for_each_entry(tmp_ls, &ls_list, list) {
			pr_info("slist2: %s, %d, %lx, %c\n", tmp_ls->name,
					tmp_ls->a, tmp_ls->b, tmp_ls->c);
		};

		struct list_head *cur,*next;
		list_for_each_safe(cur, next, &ls_list)
			list_del(cur);

		if (list_empty(&ls_list))
			pr_info("slist: empty ls_list\n");
	}

	return 0;
}

static void __exit slist_exit(void)
{
	;
}

module_init(slist_init);
module_exit(slist_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("trying");
MODULE_VERSION("list");
MODULE_LICENSE("GPL");
