#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<iterator>
#include<sstream>
#include<fstream>
#include<chrono>
#include<map>

using namespace std;

int main()
{
	auto start = chrono::steady_clock::now();
	fstream input;
	int integer;
	std::map<int, unsigned int> mapped_list;
	std::vector<std::pair<int, unsigned int>> top_sorted_list(6);
	input.open("data.txt", fstream::in);
	while (input >> integer)
	{
		mapped_list[integer]++;
	}
	std::partial_sort_copy(mapped_list.begin(), mapped_list.end(), top_sorted_list.begin(), top_sorted_list.end(), [](const std::pair<int, int>& left, const std::pair<int, int>& right)
		{
			return left.second > right.second;
		});
	std::cout << "TOP SIX VALUE" << endl;
	for (auto& value : top_sorted_list)
	{
		std::cout << value.first << ": " << value.second << endl;
	}
	std::partial_sort_copy(mapped_list.begin(), mapped_list.end(), top_sorted_list.begin(), top_sorted_list.end(), [](const std::pair<int, int>& left, const std::pair<int, int>& right)
		{
			return left.second < right.second;
		});
	std::cout << "DOWN SIX VALUE" << endl;
	for (auto& value : top_sorted_list)
	{
		std::cout << value.first << ": " << value.second << endl;
	}
	int x;
	auto end = chrono::steady_clock::now();
	auto difference = end - start;
	cout << "Time measure : " << std::scientific << double(difference.count() / 1000000000) << " Sekund/y " << endl;
	cout << "Enter given value." << endl;
	while (true)
	{
		while (!(cin >> x) || !(x > 0 and x < 50))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Try Again. " << endl;
		}
		cout << "Value " << x << " occured " << mapped_list[x] << " times." << endl;
	}
	return 0;
}