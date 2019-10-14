#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>

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
		return end < t.end;
	}

};

std::vector<Task> interval_scheduling(const std::vector<Task>& task_list)
{
	std::vector<Task> schedule;

	Task last_task = *task_list.begin();

	// as the task list is already sorted, the first one always enters the list
	schedule.push_back(last_task);

	for (auto task = std::next(task_list.begin()); task != task_list.end(); task++)
	{
		/*
		 * If the task's start is greater or equal than the last one in the list,
		 * add to the answer
		 */

		if (task->start >= last_task.end)
		{
			schedule.push_back(*task);
			last_task = *task;
		}
	}

	return schedule;
}

int main()
{
	std::vector<Task> task_list;
	int no_of_tasks;
	std::cout << "Digite a quantidade de tarefas: ";
	std::cin >> no_of_tasks;

	std::cout << "Insira o comeco e fim de uma tarefa, separado por espaco: \n";
	for (int i = 0; i < no_of_tasks; i++)
	{
		Task task;

		std::cin >> task.start >> task.end;

		task_list.push_back(task);
	}

	// sorting by finish time 
	std::sort(task_list.begin(), task_list.end());

	std::vector<Task> schedule = interval_scheduling(task_list);

	std::cout << "O melhor agendamento de tarefas, com o comeco e fim, eh: \n";
	for (auto task : schedule)
	{
		std::cout << task.start << " " << task.end << "\n";
	}

}
