#include <iostream>
#include <queue>
#include <utility>
#include <map>
#include <algorithm>

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
		return start < t.start;
	}

};

int interval_partitioning(std::vector<Task> &task_list, std::map<int, std::vector<Task>>& classrooms)
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
	classrooms[rooms].push_back(task_list[0]);

	for (auto task = std::next(task_list.begin()); task != task_list.end(); task++)
	{
		int earliest_end_time = p_queue.top().first;
		int curr_room = p_queue.top().second;
	
		if (task->start >= earliest_end_time)
		{
			classrooms[curr_room].push_back(*task);	

			// update heap with the new finish time
			p_queue.pop();
			p_queue.push({task->end, curr_room});
		}
		else
		{
			// allocate a new room for the task
			rooms++;
			classrooms[rooms].push_back(*task);
			p_queue.push({task->end, rooms});
		}
	}


	return rooms;
}

int main()
{
	std::vector<Task> task_list;
	std::map<int, std::vector<Task>> classrooms;
	int no_tasks;

	std::cout << "Digite a quantidade de tarefas: ";
	std::cin >> no_tasks;

	std::cout << "Insira a entrada e saida das tarefas, separada por espaco:\n";
	for (int i = 0; i < no_tasks; i++)
	{
		Task task;

		std::cin >> task.start >> task.end;

		task_list.push_back(task);
	}

	int answer = interval_partitioning(task_list, classrooms);
	std::cout << "Numero de salas necessarias: " << answer << "\n";

	std::cout << "\n";

	for (int i = 1; i <= classrooms.size(); i++)
	{
		std::cout << "Sala " << i << ":\n";
		for (auto task : classrooms[i])
		{
			std::cout << task.start << "->" << task.end << "\n";
		}

	}
	
}
