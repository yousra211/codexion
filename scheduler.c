#include "ft_utils.h"

int scheduler_is_empty(t_scheduler *scheduler)
{
    return (scheduler->size == 0);
}


int		higher_priority(t_queue_node *a, t_queue_node *b)
{
	unsigned long deadline_a;
	unsigned long deadline_b;

	deadline_a = a->coder->last_compile_start
			+ a->coder->shared_data->time_to_burnout;

	deadline_b = b->coder->last_compile_start
			+ b->coder->shared_data->time_to_burnout;
	if (a->coder->shared_data->scheduler_type == EDF)
	{
		if (deadline_a > deadline_b)
			return (0);
		else if (deadline_a < deadline_b)
			return (1);
	}
	if (a->request_timestamp > b->request_timestamp)
		return (0);
	else if (a->request_timestamp < b->request_timestamp)
		return(1);
	if (a->coder->id > b->coder->id)
		return (0);
	else if (a->coder->id < b->coder->id)
		return (1);
	return (0);
	
}


void		heapify_up(t_scheduler *scheduler, int index)
{
	int	parent_index;

	parent_index = -1;
	while(index > 0)
	{
		parent_index = (index - 1) / 2;
		if(higher_priority(&scheduler->heap[parent_index], &scheduler->heap[index]) == 0)
			swap(&scheduler->heap[parent_index], &scheduler->heap[index]);
		else
			break;
			index = parent_index;
		}
	}

int		scheduler_insert(t_coder *coder, t_scheduler *scheduler)
{

	if ((*scheduler).size + 1 > (*scheduler).capacity)
		return (0);
	scheduler->heap[(*scheduler).size].coder = coder;
	scheduler->heap[(*scheduler).size].request_timestamp = get_current_time();
	heapify_up(scheduler, (*scheduler).size);
	(*scheduler).size++;
	return (1);
}


void		heapify_down(t_scheduler *scheduler)
{
	int current_index;
	int	left;
	int right;
	int high;

	current_index = 0;
	while (current_index < scheduler->size)
	{
		left = 2 * current_index + 1;
		right = 2 * current_index + 2;
		//because in a binary heap, the right child cannot exist if the left child doesn't exist.
		if (left >= scheduler->size)
			break;

		if (right >= scheduler->size)
			high = left;
		else if (higher_priority(&scheduler->heap[left],
								&scheduler->heap[right]) == 1)
			high = left;
		else
			high = right;
		if(higher_priority(&scheduler->heap[high], &scheduler->heap[current_index]) == 1)
		{
			swap(&scheduler->heap[high], &scheduler->heap[current_index]);
			current_index = high;
		}
		else
			break;
	}
}

//scheduler_pop() is never called on an empty heap e.d scheduler.size =0
t_queue_node		scheduler_pop(t_scheduler *scheduler)
{
	t_queue_node winner;

	winner = scheduler->heap[0];
	scheduler->heap[0] = scheduler->heap[scheduler->size - 1];
	scheduler->size--;
	if (scheduler->size > 0)
		heapify_down(scheduler);
	
	return (winner);
}

t_queue_node		scheduler_peek(t_scheduler *scheduler)
{
	return (scheduler->heap[0]);
}

void scheduler_destroy(t_scheduler *scheduler)
{
    free(scheduler->heap);
    scheduler->heap = NULL;
    scheduler->size = 0;
    scheduler->capacity = 0;
}