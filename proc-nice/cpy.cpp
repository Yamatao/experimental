#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
#include <string>
#include <iostream>

int main(int argc, char **argv) {
	std::string name = argv[1];
	unsigned int seed = 0;
	
	FILE* urandom = fopen("/dev/urandom", "r");
	fread(&seed, sizeof(int), 1, urandom);
	fclose(urandom);
	srand(seed);

	std::string prefix = std::to_string(rand());
	
	auto start = std::chrono::steady_clock::now();
 	
	int idx = 0;
	for (int j = 0; j < 4; j++) {
		// input
		std::string fname;
	        if (idx == 0) {
		        fname = "gumno.txt";
		} else {
			fname = "tmp/" + prefix + "_" + std::to_string(idx) + ".txt";
		}

		std::cout << "Copying file " << fname << std::endl;
		int ifile = open(fname.c_str(), O_RDONLY | O_DIRECT, S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (ifile == -1) {
			std::cout << "Error opening " << fname << " for read\n";
			return 1;
		}

		size_t sz = lseek(ifile, 0, SEEK_END);
		lseek(ifile, 0, SEEK_SET);
		
		char *mem = new char[sz];
		ssize_t rd = read(ifile, mem, sz);
		if (rd < sz) {
			std::cout << "Failed to read " << fname << ", only " << rd << " bytes read" << std::endl;
			return 1;
		}
		close(ifile);

		// output
		idx++;
		if (idx == 4)
			idx = 1;

		fname = "tmp/" + prefix + "_" + std::to_string(idx) + ".txt";
		//std::cout << "Writing to " << fname << std::endl;

		int ofile = open(fname.c_str(), O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (ofile == -1) {
			std::cout << "Error opening " << fname << " for write\n";
			return 1;
		}

		static const int Step = 4000;
		for (char * pos = mem; pos < mem + sz; pos += Step) {
			ssize_t wr = 0;
			if (pos + Step < mem + sz) {
				wr = write(ofile, pos, Step);
			} else {
				wr = write(ofile, pos, mem + sz - pos);
			}
			if (wr == -1) {
				std::cout << "Error writing " << fname << ", only " << wr << " bytes written" << std::endl;
				return 1;
			}
			fsync(ofile);
		}
		close(ofile);
		
		delete mem;
	}

	auto end = std::chrono::steady_clock::now();
	std::cout << "\n" << name << " finished in " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "sec\n";
	return 0;
}
