#include "ft_utils.h"

int		higher_priority(t_queue_node *a, t_queue_node *b)
{
	if (a->coder->shared_data->scheduler_type = EDF)
	{
		if ((a->coder->last_compile_start + a->coder->shared_data->time_to_burnout)
		> (b->coder->last_compile_start + b->coder->shared_data->time_to_burnout))
	}
	
}


void		heapify_up(t_scheduler *scheduler, int index)
{
	int	parent_index;

	parent_index = -1;
	// if (index == 0)
	// 	break;
	while(parent_index != 0)
	{
		parent_index = (index - 1) / 2;
		if(higher_priority(&(*scheduler).heap[parent_index], &(*scheduler).heap[index]) == 1)
			swap(&(*scheduler).heap[parent_index], &(*scheduler).heap[index]);
		else
			break;
		index = parent_index;
	}
}

int		scheduler_insert(t_coder *coder, t_scheduler *scheduler)
{

	if ((*scheduler).size + 1 > (*scheduler).capacity)
		return (0);
	(*scheduler).heap[(*scheduler).size].coder = coder;
	(*scheduler).heap[(*scheduler).size].request_timestamp = get_current_time();
	heapify_up(scheduler, (*scheduler).size);
	(*scheduler).size++;
	return (1);
}
