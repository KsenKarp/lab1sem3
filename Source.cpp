#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include "DynamicArray.cpp"
#include "LinkedList.cpp"
#include "Sequence_types.cpp"
#include "Isorter.cpp"
#include <SDL.h>
#include <vector>

using namespace std;
int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 720;

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

bool init() {
	bool ok = true;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "Can't init SDL: " << SDL_GetError() << endl;
	}

	win = SDL_CreateWindow("Graphs", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (win == NULL) {
		cout << "Can't create window: " << SDL_GetError() << endl;
		ok = false;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL) {
		cout << "Can't create renderer: " << SDL_GetError() << endl;
		ok = false;
	}
	return ok;
}

void quit() {
	SDL_DestroyWindow(win);
	win = NULL;

	SDL_DestroyRenderer(ren);
	ren = NULL;

	SDL_Quit;
}

bool a_greater_b(const int& a, const int& b) {
	return a > b;
}

void draw_arr_seq(int amount, const char* filename, bool (*cmp)(const int&, const int&)) {
	Isorter<int> sorter;
	fstream q_time("q_time.txt");
	fstream m_time("m_time.txt");
	fstream b_time("b_time.txt");
	ifstream file(filename);
	for (int i = 9; i < amount; i += 10) {
		ArraySequence<int> seq(i+1);
		file.seekg(0, ios::beg);
		for (int j = 0; j < i; j++) {
			int num;
			std::string line;
			getline(file, line);
			num = std::stoi(line);
			seq.append(num);
		}
		float qtime;
		sorter.quick_sort(&seq, (*cmp), qtime);
		q_time << qtime * 1000 << endl;
		float mtime;
		sorter.merge_sort(&seq, (*cmp), mtime);
		m_time << mtime * 1000 << endl;
		float btime;
		sorter.quick_sort(&seq, (*cmp), btime);
		b_time << btime * 1000 << endl;
	}
	file.close();
	q_time.seekg(0, ios::beg);
	m_time.seekg(0, ios::beg);
	b_time.seekg(0, ios::beg);
	vector<float> q_vec = vector<float>();
	q_vec.reserve(amount / 10);
	vector<float> m_vec = vector<float>();
	m_vec.reserve(amount / 10);
	vector<float> b_vec = vector<float>();
	b_vec.reserve(amount / 10);

	for (int k = 0; k < amount / 10; k++) { //Все времена по порядку загнала в векторы для удобства :(
		int q;
		int m;
		int b;
		std::string qline;
		std::string mline;
		std::string bline;
		getline(q_time, qline);
		q = std::stof(qline);
		q_vec.push_back(q);
		getline(m_time, mline);
		m = std::stof(mline);
		m_vec.push_back(m);
		getline(b_time, bline);
		b = std::stof(bline);
		b_vec.push_back(b);
	}

	if (!init()) {
		cout << "SDL window initiation error" << endl;
		quit();
		system("pause");
		return;
	}
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(ren);
	
	SDL_Event e;
	bool _quit = false;
	while (!_quit) {
		SDL_RenderPresent(ren);
		for (int i = 1; i < amount / 10; i++) {
			SDL_SetRenderDrawColor(ren, 0, 255, 0, 50);
			SDL_RenderDrawLine(ren, (i-1) * 10, SCREEN_HEIGHT - 30 - q_vec[i-1], i * 10, SCREEN_HEIGHT - 30 - q_vec[i]);
			SDL_SetRenderDrawColor(ren, 0, 0, 255, 0);
			SDL_RenderDrawLine(ren, (i - 1) * 10, SCREEN_HEIGHT - 30 - m_vec[i - 1], i * 10, SCREEN_HEIGHT - 30 - m_vec[i]);
			SDL_SetRenderDrawColor(ren, 255, 0, 0, 50);
			SDL_RenderDrawLine(ren, (i - 1) * 10, SCREEN_HEIGHT - 30 - b_vec[i - 1], i * 10, SCREEN_HEIGHT - 30 - b_vec[i]);
		}
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
			{
				_quit = true;
			}
			SDL_Delay(30);
		}
	}
	quit();
	q_time.close();
	m_time.close();
	b_time.close();
}

void draw_list_seq(int amount, const char* filename, bool (*cmp)(const int&, const int&)) {
	Isorter<int> sorter;
	fstream q_time("q_time.txt");
	fstream m_time("m_time.txt");
	fstream b_time("b_time.txt");
	ifstream file(filename);
	for (int i = 9; i < amount; i += 10) {
		ListSequence<int> seq = ListSequence<int>();
		file.seekg(0, ios::beg);
		for (int j = 0; j < i; j++) {
			int num;
			std::string line;
			getline(file, line);
			num = std::stoi(line);
			seq.append(num);
		}
		float qtime;
		sorter.quick_sort(&seq, (*cmp), qtime);
		q_time << qtime * 1000 << endl;
		float mtime;
		sorter.merge_sort(&seq, (*cmp), mtime);
		m_time << mtime * 1000 << endl;
		float btime;
		sorter.quick_sort(&seq, (*cmp), btime);
		b_time << btime * 1000 << endl;
	}
	file.close();
	q_time.seekg(0, ios::beg);
	m_time.seekg(0, ios::beg);
	b_time.seekg(0, ios::beg);
	vector<float> q_vec = vector<float>();
	q_vec.reserve(amount / 10);
	vector<float> m_vec = vector<float>();
	m_vec.reserve(amount / 10);
	vector<float> b_vec = vector<float>();
	b_vec.reserve(amount / 10);

	for (int k = 0; k < amount / 10; k++) {
		int q;
		int m;
		int b;
		std::string qline;
		std::string mline;
		std::string bline;
		getline(q_time, qline);
		q = std::stof(qline);
		q_vec.push_back(q);
		getline(m_time, mline);
		m = std::stof(mline);
		m_vec.push_back(m);
		getline(b_time, bline);
		b = std::stof(bline);
		b_vec.push_back(b);
	}

	if (!init()) {
		cout << "SDL window initiation error" << endl;
		quit();
		system("pause");
		return;
	}
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(ren);

	SDL_Event e;
	bool _quit = false;
	while (!_quit) {
		SDL_RenderPresent(ren);
		for (int i = 1; i < amount / 10; i++) {
			SDL_SetRenderDrawColor(ren, 0, 255, 0, 50);
			SDL_RenderDrawLine(ren, (i - 1) * 10, SCREEN_HEIGHT - 30 - q_vec[i - 1], i * 10, SCREEN_HEIGHT - 30 - q_vec[i]);
			SDL_SetRenderDrawColor(ren, 0, 0, 255, 0);
			SDL_RenderDrawLine(ren, (i - 1) * 10, SCREEN_HEIGHT - 30 - m_vec[i - 1], i * 10, SCREEN_HEIGHT - 30 - m_vec[i]);
			SDL_SetRenderDrawColor(ren, 255, 0, 0, 50);
			SDL_RenderDrawLine(ren, (i - 1) * 10, SCREEN_HEIGHT - 30 - b_vec[i - 1], i * 10, SCREEN_HEIGHT - 30 - b_vec[i]);
		}
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
			{
				_quit = true;
			}
			SDL_Delay(30);
		}
	}

	quit();
	q_time.close();
	m_time.close();
	b_time.close();
}

void random_integer_sequence(int amount, const char* filename) {
	ofstream file(filename);
	for (int i = 0; i < amount; i++) file << rand() % (2*amount) - amount << endl;
	file.close();
}

int main(int argc, char* argv[]) {

	random_integer_sequence(2000, "lab1file.txt");
	draw_arr_seq(2000, "lab1file.txt", (*a_greater_b));
	draw_list_seq(2000, "lab1file.txt", (*a_greater_b));
	Isorter<int> sorter;
	int arr2[5] = { -1, 8, 2, 0, 0 };
	DynamicArray<int> dynarr(5, arr2);

	ArraySequence<int> arr(5, arr2);
	float time00;
	Sequence<int>* arr_q_sorted = sorter.quick_sort(&arr, (*a_greater_b), time00);
	cout << "Quick sort array sequence: ";
	for (int i = 0; i < arr_q_sorted->get_length(); i++) {
		cout << arr_q_sorted->get_i(i) << " ";
	}
	cout << endl;
	cout << "Time elapsed for quick sort by dynamic array: " << time00 << " milliseconds\n";

	float msort_array_time;
	Sequence<int>* arr_m_sorted = sorter.merge_sort(&arr, (*a_greater_b), msort_array_time);
	cout << "Merge sort array sequence: ";
	for (int i = 0; i < 5; i++) {
		cout << arr_m_sorted->get_i(i) << " ";
	}
	cout << endl;
	cout << "Time elapsed for merge sort by dynamic array: " << msort_array_time << " milliseconds\n";

	float bsort_array_time;
	Sequence<int>* arr_b_sorted = sorter.bubble_sort(&arr, (*a_greater_b), bsort_array_time);
	cout << "Bubble sort array sequence: ";
	for (int i = 0; i < 5; i++) {
		cout << arr_b_sorted->get_i(i) << " ";
	}
	cout << endl;
	cout << "Time elapsed for bubble sort by dynamic array: " << bsort_array_time << " milliseconds\n";

	ListSequence<int> lseq(5, arr2);
	float qsort_list_time;
	Sequence<int>* lseq_q_sorted = sorter.quick_sort(&arr, (*a_greater_b), qsort_list_time);
	cout << "Quick sort list sequence: ";
	for (int i = 0; i < 5; i++) {
		cout << lseq_q_sorted->get_i(i) << " ";
	}
	cout << endl;
	cout << "Time elapsed for quick sort by linked list: " << qsort_list_time << " milliseconds\n";

	float msort_list_time;
	Sequence<int>* lseq_m_sorted = sorter.merge_sort(&arr, (*a_greater_b), msort_list_time);
	cout << "Merge sort list sequence: ";
	for (int i = 0; i < lseq_m_sorted->get_length(); i++) {
		cout << lseq_m_sorted->get_i(i) << " ";
	}
	cout << endl;
	cout << "Time elapsed for merge sort by linked list: " << msort_list_time << " milliseconds\n";

	float bsort_list_time;
	Sequence<int>* lseq_b_sorted = sorter.bubble_sort(&arr, (*a_greater_b), bsort_list_time);
	cout << "Bubble sort list sequence: ";
	for (int i = 0; i < lseq_b_sorted->get_length(); i++) {
		cout << lseq_b_sorted->get_i(i) << " ";
	}
	cout << endl;
	cout << "Time elapsed for bubble sort by linked list: " << bsort_list_time << " milliseconds\n";
	
	return 0;
}