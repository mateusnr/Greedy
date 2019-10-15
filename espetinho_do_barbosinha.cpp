#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>
#include <cstdio>
#include <queue>

struct Task
{
	int start, end;

	Task(){}
	Task(int s, int e)
	{
		start = s;
		end = e;
	}

	bool operator<(const Task& t)
	{
		return start< t.start;
	}

};

int interval_partitioning(std::vector<Task> &task_list)
{
	// we need to sort the task list by start time
	std::sort(task_list.begin(), task_list.end());

	/*
	 * By default pairs are ordered by their first element and second
	 * The min heap will contain {finish time, classroom}
	 */
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> p_queue;

	int rooms = 1;
	
	p_queue.push({task_list[0].end, rooms});

	for (auto task = std::next(task_list.begin()); task != task_list.end(); task++)
	{
		int earliest_end_time = p_queue.top().first;
		int curr_room = p_queue.top().second;
	
		if (task->start > earliest_end_time)
		{
			// update heap with the new finish time
			p_queue.pop();
			p_queue.push({task->end, curr_room});
		}
		else
		{
			// allocate a new room for the task
			rooms++;
			p_queue.push({task->end, rooms});
		}
	}

	return rooms;
}

int main()
{
	int no_of_tasks;
	std::cin >> no_of_tasks;

	std::vector<Task> task_list(no_of_tasks);
	for (int i = 0; i < no_of_tasks; i++)
	{
		Task task;
		int h1, m1, s1, h2, m2, s2;
		scanf("%d:%d:%d %d:%d:%d", &h1, &m1, &s1, &h2, &m2, &s2);
		task.start = h1*3600 + m1*60 + s1;
		task.end = h2*3600 + m2*60 + s2;
		task_list[i] = task;
	}

	// sorting by finish time 
	std::sort(task_list.begin(), task_list.end());

	int answer = interval_partitioning(task_list);

	std::cout << answer << "\n";
}
