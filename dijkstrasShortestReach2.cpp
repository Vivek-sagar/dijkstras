#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct neighbor
{
	vector<long int> neighbors;
	vector<long int> distance;
};

void print_graph(vector<neighbor> graph)
{
	for (vector<neighbor>::iterator it1 = graph.begin();it1 < graph.end(); it1++)
	{
		for (long int i=0; i<it1->neighbors.size(); i++)
		{
			cout << it1->neighbors[i] << " " << it1->distance[i] << ";";
		}
		cout << endl;
	}
}

void print_list(list<long int> lst)
{
	for (list<long int>::iterator it = lst.begin(); it != lst.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void print_vector(vector<long int> vec, int start)
{
	for (vector<long int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		if (it-vec.begin() != start)
			cout << *it << " ";
	}
	cout << endl;
}

// list<long int>::iterator min_element (list<long int>::iterator start, list<long int>::iterator end)
// {
// 	list<long int>::iterator min = start;
// 	for (list<long int>::iterator it = start; it != end; it++)
// 	{
// 		if (*it < *min)
// 		{
// 			min = it;
// 		}
// 	}
// 	return min;
// }

void dijkstra(vector<neighbor> graph, vector<long int> distance, list<long int> to_check, long int start)
{
	long int current = start;
	long int dist;
	while (to_check.size() > 0)
	{
		to_check.remove(current);
		for (vector<long int>::iterator it = graph[current].neighbors.begin(); it != graph[current].neighbors.end(); it++)
		{

			//print_list(to_check);
			 //cout << "Checking " << *it <<". ";

			//Check if the neighbor is in to_check
			list<long int>::iterator finder = find(to_check.begin(), to_check.end(), *it);
			if (finder != to_check.end())
			{
				dist = graph.at(current).distance[it-graph[current].neighbors.begin()];

				//If the checking node is new, or if the distance can be improved, assign the new distance
				if (distance[*it] == -1 || distance[*it] > distance[current]+dist)
				{
					distance[*it] = distance[current]+dist;
					//cout << "Distance is " << distance[*it] << endl;
				}
				else
					continue;
			}
		}

		//Pop the first element from to_check
		// cout << "Popping " << *to_check.begin() << endl;
		
		//list<long int>::iterator new_min = min_element(to_check.begin(), to_check.end());

		long int min = 10000;
		long int min_idx = -1;
		for (list<long int>::iterator i=to_check.begin(); i!= to_check.end(); i++)
		{
			if (distance[*i] > -1)
			{
				if (distance[*i] < min)
				{
					min_idx = *i;
					min = distance[*i];
				}
			}
		}
		if (min_idx == -1)
			min_idx = *to_check.begin();
		//cout << "\nNew Min is: " << min_idx << endl;
		current = min_idx;
	}
	print_vector(distance, start);
}

int main()
{
	long int t;
	long int n, s;

	long int m;
	
	
	long int input_n;
	long int input_m;
	long int input_r;

	cin >> t;
	for (long int x=0; x<t; x++)
	{
		cin >> n;
		cin >> m;

		vector<neighbor> graph;

		for (long int i=0; i<n; i++)
		{
			neighbor temp;
			graph.push_back(temp);
		}


		for (long int i=0; i<m; i++)
		{
			cin >> input_n >> input_m >> input_r;
			input_n--;
			input_m--;
			vector<long int>::iterator finder = find(graph.at(input_n).neighbors.begin(), graph.at(input_n).neighbors.end(), input_m);
			if (finder == graph.at(input_n).neighbors.end())
			{
				graph.at(input_n).neighbors.push_back(input_m);
				graph.at(input_n).distance.push_back(input_r);
			}
			else
			{
				int idx = finder - graph.at(input_n).neighbors.begin();
				if (graph.at(input_n).distance[idx] > input_r)
				{
					//cout << "...m" << input_m << input_n << input_r << "\n";
					graph.at(input_n).neighbors[idx] = (input_m);
					graph.at(input_n).distance[idx] = (input_r);
				}
			}

			finder = find(graph.at(input_m).neighbors.begin(), graph.at(input_m).neighbors.end(), input_n);
			if (finder == graph.at(input_m).neighbors.end())
			{
				graph.at(input_m).neighbors.push_back(input_n);
				graph.at(input_m).distance.push_back(input_r);
			}
			else
			{
				int idx = finder - graph.at(input_m).neighbors.begin();
				if (graph.at(input_m).distance[idx] > input_r)
				{
					//cout << "...n" << graph.at(input_m).distance[idx] << input_m << input_n << input_r << "\n";
					graph.at(input_m).neighbors[idx] = (input_n);
					graph.at(input_m).distance[idx] = (input_r);
				}
			}
		}

		cin >> s;
		s--;

		vector<long int> distance;
		long int temp;
		for (long int i=0; i<n; i++)
		{
			temp = -1;
			if (i==s)
				temp = 0;
			distance.push_back(temp);

		}

		list<long int> to_check;

		for(long int i=0; i<n; i++)
		{
			//if (i != s)
				to_check.push_back(i);
		}
		//print_graph(graph);
		dijkstra(graph, distance, to_check, s);
	}
	
	return 0;
}