#include "ft_utils.h"

int		higher_priority(queue_node *a, queue_node *b)
{

}


int		heapify_up(t_scheduler *scheduler, int index)
{
	int	parent_index;

	parent_index = -1;
	if (index == 0)
		return (1);
	while(parent_index != 0)
	{
		parent_index = (index - 1) / 2;
		if(higher_priority(&(*scheduler).heap[parent_index], &(*scheduler).heap[index]) == 1)
			swap(&(*scheduler).heap[parent_index], &(*scheduler).heap[index]);
		index = parent_index;
	}
}


int		scheduler_insert(t_coder *coder, t_scheduler *scheduler)
{
	int		size;

	size = (*scheduler).size;
	if (size + 1 > (*scheduler).capacity)
		return (0);
	(*scheduler).heap[size].coder = coder;
	(*scheduler).heap[size].request_timestamp = get_current_time();
	if (heapify_up(scheduler, size) == 0)
		return (0);
	size++;
	return (1);
}
