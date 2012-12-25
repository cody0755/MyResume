#ifndef MYRESUME_IDDEFINE_H
#define MYRESUME_IDDEFINE_H
enum
{
	invalid_signal = 0,
	object_destroy_signal,
	press_down_signal,
	press_up_signal,
	click_signal,
	timer_timeout_signal,
	animator_start_signal, 
	animator_update_signal,
	animator_stop_signal
};

enum
{
	invalid_view_id = 0,
	id_quit = 1,
	id_view_navi = 2,
	id_bn_class_personal = 3,

};
#endif