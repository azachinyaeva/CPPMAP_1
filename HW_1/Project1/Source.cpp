#include <iostream>
#include <thread>
#include <chrono>


int queue = 0;
int max_client = 10;

void client() {
	while (queue < max_client) {
		++queue;
		std::cout << "client " << queue << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void operationist() {
	while (queue != 0) {
		--queue;
		std::cout << "operationist " << queue << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}


int main()
{
	
	std::thread cl(client);
	std::thread op(operationist);
	
		if (cl.joinable()) {
			cl.join();
		}
		if (op.joinable()) {
			op.join();
		}
	

	return 0;
}
