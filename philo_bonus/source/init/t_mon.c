#include "init_priv.h"

void	init_monitor(
			t_mon *monitor,
			t_philo *philos,
			t_semaphores *semaphores,
			t_rules *rules)
{
	memset(monitor, 0, sizeof(t_mon));
	monitor->philos = philos;
	monitor->semaphores = semaphores;
	monitor->rules = rules;
}
