#include <fstream>
#include <iostream>
#include <unistd.h>
#include <chrono>

int main(int argc, char **argv) {
	printf("PID %u\n", (unsigned)getpid());

	std::string name = argv[1];

	std::string prefix = std::to_string(rand());
	
	auto start = std::chrono::steady_clock::now();
	
	int idx = 0;
	for (int j = 0; j < 6; j++) {
		// input
		std::string fname;
	        if (idx == 0) {
		        fname = "gumno.txt";
		} else {
			fname = "tmp/" + prefix + "_" + std::to_string(idx) + ".txt";
		}

		std::ifstream ifs(fname, std::ios_base::binary);
		size_t sz = 0;
		if (!ifs.is_open()) {
			std::cout << "Error opening " << fname << "\n";
			return 1;
		}

		ifs.seekg(0, std::ios_base::end);
		sz = ifs.tellg();
		ifs.seekg(0, std::ios_base::beg);
		
		char *mem = new char[sz];
		ifs.read(mem, sz);
		ifs.close();

		// output
		idx++;
		if (idx == 10)
			idx = 1;

		fname = "tmp/" + prefix + "_" + std::to_string(idx) + ".txt";
		//std::cout << "Writing to " << fname << std::endl;
		std::cout << "." << std::endl;

		std::ofstream ofs(fname, std::ios_base::binary);
		if (!ofs.is_open()) {
			std::cout << "Error opening " << fname << " for write\n";
			return 1;
		}

		static const int Step = 800;
		for (int i = 0; i < 2; i++) {
		for (char * pos = mem; pos < mem + sz; pos += Step) {
			if (pos + Step < mem + sz) {
				ofs.write(pos, Step);
			} else {
				ofs.write(pos, mem + sz - pos - 1);
			}
		}
		}
		ofs.close();
		
		delete mem;
	}

	auto end = std::chrono::steady_clock::now();
	std::cout << "\n" << name << " finished\n";
	std::cout << "\nTime: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "sec\n";
	return 0;
}
