#include "StarletParser/parser.hpp"
#include "StarletParser/utils/log.hpp"

bool Parser::getFileSize(FILE* file, size_t& sizeOut) {
	if (fseek(file, 0, SEEK_END) != 0) return error("FileParser", "getFileSize", "Failed to seek end of file");

	const long size = ftell(file);
	if (size == -1L) return error("FileParser", "getFileSize", "Invalid file, ftell failed");

	if (size <= 0 || static_cast<size_t>(size) > MAX_SIZE)
		return error("FileParser", "getFileSize", "Invalid file size");

	if (fseek(file, 0, SEEK_SET) != 0) return error("FileParser", "getFileSize", "Failed to rewind file");

	sizeOut = static_cast<size_t>(size);
	return true;
}


bool Parser::loadFile(std::string& out, const std::string& path) {
	FILE* file = fopen(path.c_str(), "rb");
	if (!file) return error("FileParser", "loadFile", "Failed to open file: " + path);

	size_t fileSize;
	if (!getFileSize(file, fileSize)) {
		fclose(file);
		return error("FileParser", "loadFile", "Failed to get file size");
	}

	out.resize(fileSize);

	size_t bytesRead = 0;
	while (bytesRead < fileSize) {
		size_t byteRead = fread(&out[bytesRead], 1, fileSize - bytesRead, file);
		if (byteRead == 0) {
			if (ferror(file)) {
				fclose(file);
				out.clear();
				return error("FileParser", "loadFile", "fread failed at byte " + std::to_string(bytesRead));
			}
			break;
		}
		bytesRead += byteRead;
	}

	fclose(file);

	if (bytesRead != fileSize) {
		out.clear();
		return error("FileParser", "loadFile", "fread failed. Expected " + std::to_string(fileSize) + ", got " + std::to_string(bytesRead));
	}
	return true;
}

bool Parser::loadBinaryFile(std::vector<unsigned char>& dataOut, const std::string& path) {
	FILE* file = fopen(path.c_str(), "rb");
	if (!file) return error("FileParser", "loadBinaryFile", "Failed to open file: " + path);

	size_t fileSize;
	if (!getFileSize(file, fileSize)) {
		fclose(file);
		return error("FileParser", "loadBinaryFile", "Failed to get file size");
	}

	dataOut.resize(fileSize);
	size_t bytesRead = fread(dataOut.data(), 1, fileSize, file);
	fclose(file);

	if (bytesRead != fileSize) {
		dataOut.clear();
		return error("FileParser", "loadBinaryFile", "fread failed. Expected " + std::to_string(fileSize) + ", got " + std::to_string(bytesRead));
	}

	return true;
}